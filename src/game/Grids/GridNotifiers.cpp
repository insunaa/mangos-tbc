/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Grids/GridNotifiers.h"
#include "Server/WorldPacket.h"
#include "Server/WorldSession.h"
#include "Entities/UpdateData.h"
#include "Maps/MapPersistentStateMgr.h"
#include "Maps/Map.h"
#include "Entities/Transports.h"
#include "Globals/ObjectAccessor.h"
#include "BattleGround/BattleGroundMgr.h"
#include "AI/BaseAI/UnitAI.h"

using namespace MaNGOS;

void VisibleChangesNotifier::Visit(CameraMapType& m)
{
    for (auto& iter : m)
    {
        iter.getSource()->UpdateVisibilityOf(&i_object);
        m_unvisitedGuids.erase(iter.getSource()->GetOwner()->GetObjectGuid());
    }
}

void VisibleNotifier::Notify()
{
    Player& player = *i_camera.GetOwner();
#ifdef ENABLE_PLAYERBOTS
    if (!player.isRealPlayer())
        return;
#endif

    // at this moment i_clientGUIDs have guids that not iterate at grid level checks
    // but exist one case when this possible and object not out of range: transports
    if (GenericTransport* transport = player.GetTransport())
    {
        for (auto itr : transport->GetPassengers())
        {
            if (i_clientGUIDs.find(itr->GetObjectGuid()) != i_clientGUIDs.end())
            {
                // ignore far sight case
                if (itr->IsPlayer())
                    static_cast<Player*>(itr)->UpdateVisibilityOf(static_cast<Player*>(itr), &player);
                player.UpdateVisibilityOf(&player, itr, i_data, i_visibleNow);
                i_clientGUIDs.erase(itr->GetObjectGuid());
            }
        }
    }

    // Far objects update on player notify
    for (GuidSet::iterator itr = i_clientGUIDs.begin(); itr != i_clientGUIDs.end();)
    {
        GuidSet::iterator current = itr++;
        if (WorldObject* obj = player.GetMap()->GetWorldObject(*current))
        {
            if (!obj->GetVisibilityData().IsVisibilityOverridden())
                continue;

            player.UpdateVisibilityOf(&player, obj);
            i_clientGUIDs.erase(current);
        }
    }

    // generate outOfRange for not iterate objects
    i_data.AddOutOfRangeGUID(i_clientGUIDs);
    for (GuidSet::iterator itr = i_clientGUIDs.begin(); itr != i_clientGUIDs.end(); ++itr)
    {
        if (WorldObject* target = player.GetMap()->GetWorldObject(*itr))
        {
            if (target->GetTypeId() == TYPEID_UNIT)
                player.BeforeVisibilityDestroy(static_cast<Creature*>(target));
            player.RemoveAtClient(target);
        }
        else
            sLog.outCustomLog("Object was %s in current map.", player.GetMap()->m_objRemoveList.find(*itr) == player.GetMap()->m_objRemoveList.end() ? "not found" : "found");
        

        DEBUG_FILTER_LOG(LOG_FILTER_VISIBILITY_CHANGES, "%s is out of range (no in active cells set) now for %s",
                         itr->GetString().c_str(), player.GetGuidStr().c_str());
    }

    if (i_data.HasData())
    {
        // send create/outofrange packet to player (except player create updates that already sent using SendUpdateToPlayer)
        for (size_t i = 0; i < i_data.GetPacketCount(); ++i)
        {
            WorldPacket packet = i_data.BuildPacket(i);
            player.GetSession()->SendPacket(packet);
        }

        // send out of range to other players if need
        GuidSet const& oor = i_data.GetOutOfRangeGUIDs();
        for (auto iter : oor)
        {
            if (!iter.IsPlayer())
                continue;

            if (Player* plr = ObjectAccessor::FindPlayer(iter))
                plr->UpdateVisibilityOf(plr->GetCamera().GetBody(), &player);
        }
    }

    // Now do operations that required done at object visibility change to visible

    // send data at target visibility change (adding to client)
    for (auto vItr : i_visibleNow)
    {
        // target aura duration for caster show only if target exist at caster client
        if (vItr != &player && vItr->isType(TYPEMASK_UNIT))
            player.SendAuraDurationsForTarget((Unit*)vItr);
    }
}

void MessageDeliverer::Visit(CameraMapType& m)
{
    for (auto& iter : m)
    {
        Player* owner = iter.getSource()->GetOwner();

        if (i_toSelf || owner != &i_player)
        {
            if (WorldSession* session = owner->GetSession())
                session->SendPacket(i_message);
        }
    }
}

void MessageDelivererExcept::Visit(CameraMapType& m)
{
    for (auto& iter : m)
    {
        Player* owner = iter.getSource()->GetOwner();

        if (owner == i_skipped_receiver)
            continue;

        if (WorldSession* session = owner->GetSession())
            session->SendPacket(i_message);
    }
}

void ObjectMessageDeliverer::Visit(CameraMapType& m)
{
    for (auto& iter : m)
    {
        if (WorldSession* session = iter.getSource()->GetOwner()->GetSession())
            session->SendPacket(i_message);
    }
}

void MessageDistDeliverer::Visit(CameraMapType& m)
{
    for (auto& iter : m)
    {
        Player* owner = iter.getSource()->GetOwner();

        if ((i_toSelf || owner != &i_player) &&
                (!i_ownTeamOnly || owner->GetTeam() == i_player.GetTeam()) &&
                (!i_dist || iter.getSource()->GetBody()->IsWithinDist(&i_player, i_dist)))
        {
            if (WorldSession* session = owner->GetSession())
                session->SendPacket(i_message);
        }
    }
}

void ObjectMessageDistDeliverer::Visit(CameraMapType& m)
{
    for (auto& iter : m)
    {
        if (!i_dist || iter.getSource()->GetBody()->IsWithinDist(&i_object, i_dist))
        {
            if (WorldSession* session = iter.getSource()->GetOwner()->GetSession())
                session->SendPacket(i_message);
        }
    }
}

template<class T>
void ObjectUpdater::Visit(GridRefManager<T>& m)
{
    for (auto& iter : m)
        m_objectToUpdateSet.emplace(iter.getSource());
}

bool CannibalizeObjectCheck::operator()(Corpse* u)
{
    // ignore bones
    if (u->GetType() == CORPSE_BONES)
        return false;

    Player* owner = ObjectAccessor::FindPlayer(u->GetOwnerGuid());

    if (!owner || i_fobj->CanAssist(owner))
        return false;

    return i_fobj->IsWithinDistInMap(u, i_range);
}

bool TauntFlagObjectCheck::operator()(Corpse* u)
{
    // ignore bones
    if (u->GetType() == CORPSE_BONES)
        return false;

    Player* owner = ObjectAccessor::FindPlayer(u->GetOwnerGuid());

    if (!owner || i_fobj->CanAssist(owner))
        return false;

    return i_fobj->IsWithinDistInMap(u, i_range);
}

void MaNGOS::RespawnDo::operator()(Creature* u) const
{
    // prevent respawn creatures for not active BG event
    Map* map = u->GetMap();
    if (map->IsBattleGroundOrArena())
    {
        BattleGroundEventIdx eventId = map->GetMapDataContainer().GetCreatureEventIndex(u->GetDbGuid());
        if (!((BattleGroundMap*)map)->GetBG()->IsActiveEvent(eventId.event1, eventId.event2))
            return;
    }

    if (u->IsUsingNewSpawningSystem())
    {
        if (u->IsDead() && !u->GetCreatureGroup())
        {
            if (u->GetMap()->GetMapDataContainer().GetSpawnGroupByGuid(u->GetDbGuid(), TYPEID_UNIT))
                u->GetMap()->GetPersistentState()->SaveCreatureRespawnTime(u->GetDbGuid(), time(nullptr));
            else
                u->GetMap()->GetSpawnManager().RespawnCreature(u->GetDbGuid(), 0);
        }
    }
    else
        u->Respawn();
}

void MaNGOS::RespawnDo::operator()(GameObject* u) const
{
    // prevent respawn gameobject for not active BG event
    Map* map = u->GetMap();
    if (map->IsBattleGroundOrArena())
    {
        BattleGroundEventIdx eventId = map->GetMapDataContainer().GetGameObjectEventIndex(u->GetDbGuid());
        if (!static_cast<BattleGroundMap*>(map)->GetBG()->IsActiveEvent(eventId.event1, eventId.event2))
            return;
    }

    u->Respawn();
}

void MaNGOS::CallOfHelpCreatureInRangeDo::operator()(Creature* u)
{
    if (u == i_funit)
        return;

    if (!u->CanAssist(i_funit) || !u->CanAttack(i_enemy))
        return;

    // too far
    if (!i_funit->IsWithinDistInMap(u, i_range))
        return;

    // only if see assisted creature
    if (!i_funit->IsWithinLOSInMap(u))
        return;

    if (u->AI())
        u->AI()->OnCallForHelp(i_enemy);
}

bool MaNGOS::AnyAssistCreatureInRangeCheck::operator()(Creature* u)
{
    if (u == i_funit)
        return false;

    if (!u->CanAssistInCombatAgainst(i_funit, i_enemy))
        return false;

    // too far
    if (!i_funit->IsWithinDistInMap(u, i_range))
        return false;

    // only if see assisted creature
    if (!i_funit->IsWithinLOSInMap(u))
        return false;

    return true;
}

template void ObjectUpdater::Visit<GameObject>(GameObjectMapType&);
template void ObjectUpdater::Visit<DynamicObject>(DynamicObjectMapType&);

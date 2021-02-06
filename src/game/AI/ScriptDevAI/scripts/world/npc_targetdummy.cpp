/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
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

/* ScriptData
SDName: Target_Dummy
SD%Complete: 50
SDComment: Should be replaced with core based AI
SDCategory: Creatures
EndScriptData */

#include "AI/ScriptDevAI/include/sc_common.h"

struct npc_targetDummyAI : public ScriptedAI
{
    std::map<Unit*, uint32> combatList;
    float x,y,z,o,d;

    npc_targetDummyAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        SetCombatMovement(false);
        SetMeleeEnabled(false);
        Reset();
    }

    void Reset() override
    {
        m_creature->GetRespawnCoord(x, y, z, &o, &d);
    }

    void AttackedBy(Unit* dealer)
    {
        combatList[dealer] = 5000;
    }

    void DamageTaken(Unit* /*dealer*/, uint32& damage, DamageEffectType /*damagetype*/, SpellEntry const* /*spellInfo*/) override
    {
        damage = std::min(damage, m_creature->GetHealth() - 1);

    }

    void UpdateAI(const uint32 diff) override
    {
        DoStopAttack();        
        m_creature->SetFacingTo(o);
        m_creature->SetHealth(m_creature->GetMaxHealth());
        m_creature->AttackStop();
        std::vector<Unit*> deleteMe;
        for(std::pair<Unit*, uint32> attacker : combatList){
            if (attacker.second < diff){
                attacker.first->CombatStop(true, true);
                deleteMe.push_back(attacker.first);
            } else {
                combatList[attacker.first] -= diff;
            }
        }
        for(Unit* attacker : deleteMe){
            combatList.erase(attacker);
        }
    }
};

void AddSC_targetDummy()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "npc_targetDummy";
    pNewScript->GetAI = &GetNewAIInstance<npc_targetDummyAI>;
    pNewScript->RegisterSelf(false);
}

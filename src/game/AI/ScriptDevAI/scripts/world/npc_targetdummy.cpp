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
#include "Entities/Object.h"
#include "Entities/ObjectGuid.h"

uint32 m_uiHeal_Timer;

struct npc_targetDummyAI : public ScriptedAI
{
    std::map<ObjectGuid, uint32> combatList;

    npc_targetDummyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset() override
    {
        combatList.clear();
        SetCombatMovement(false);
        SetMeleeEnabled(false);
        SetReactState(REACT_PASSIVE);
        SetDeathPrevention(true);
        SetRootSelf(true);
        m_uiHeal_Timer = 1000;
    }

    void AttackedBy(Unit* dealer)
    {
        combatList[dealer->GetObjectGuid()] = 5000;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_uiHeal_Timer < diff)
            {
                if (m_creature->GetHealthPercent()<=15.f)
                {
                    m_creature->SetHealthPercent(15.f);
                }
                m_creature->ModifyHealth(m_creature->GetMaxHealth()/95);
                m_uiHeal_Timer = 1000;
            }
        else
            m_uiHeal_Timer -= diff;

        for (auto itr = combatList.begin(); itr != combatList.end();)
        {
            Unit* attacker = m_creature->GetMap()->GetUnit(itr->first);
            
            if (!attacker && !attacker->IsInWorld())
            {
                itr = combatList.erase(itr);
                continue;
            }

            if (attacker->AI() && attacker->GetMaster() && !attacker->GetMaster()->IsInCombat())
            {
                itr->second = 0;
                attacker->CombatStop();
            }

            if (itr->second < diff){
                m_creature->_removeAttacker(attacker);
                m_creature->getThreatManager().modifyThreatPercent(attacker, -101.0f);
                itr = combatList.erase(itr);
                continue;
            }

            itr->second -= diff;
            itr++;
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

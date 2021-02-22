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

uint32 m_uiHeal_Timer;

struct npc_targetDummyAI : public ScriptedAI
{
    std::map<Unit*, uint32> combatList;
    float x,y,z,o,d;

    npc_targetDummyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset() override
    {
        m_creature->GetRespawnCoord(x, y, z, &o, &d);
        SetCombatMovement(false);
        SetMeleeEnabled(false);
        SetReactState(REACT_PASSIVE);
        SetDeathPrevention(true);
        m_uiHeal_Timer = 1000;
    }

    void AttackedBy(Unit* dealer)
    {
        combatList[dealer] = 5000;
    }

    void UpdateAI(const uint32 diff) override
    {
        m_creature->SetFacingTo(o);
        if(m_uiHeal_Timer < diff)
            {
                if(m_creature->GetHealthPercent()<=19.f)
                {
                    m_creature->SetHealthPercent(19.f);
                } else {
                    m_creature->ModifyHealth(m_creature->GetMaxHealth()/95);
                    m_uiHeal_Timer = 1000;
                }
            }
        else
            m_uiHeal_Timer -= diff;

        std::vector<Unit*> deleteMe;
        for(std::pair<Unit*, uint32> attacker : combatList){
            if (attacker.second < diff){
                if(attacker.first->IsInCombat()){
                    attacker.first->CombatStop(true, true);
                    deleteMe.push_back(attacker.first);
                }
            } else {
                if(attacker.first->IsInCombat())
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

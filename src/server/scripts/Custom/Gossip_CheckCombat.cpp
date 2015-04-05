/*
 * Copyright (C) 2013-2015 DeathCore <http://www.noffearrdeathproject.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// Place Gossip_CheckCombat to scriptname for the NPC to check if player is in combat on gossip hello

#include "ScriptPCH.h"

class Gossip_CheckCombat : public CreatureScript
{
	public:
	Gossip_CheckCombat()
	: CreatureScript("Gossip_CheckCombat")
	{
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
	{
		if (pPlayer->IsInCombat())
		{
			pPlayer->GetSession()->SendAreaTriggerMessage("|cffff0000You are in combat|r");
			return true;
		}
		else
		{
			return false;
		}
	}
};

void AddSC_Gossip_CheckCombat()
{
	new Gossip_CheckCombat();
}
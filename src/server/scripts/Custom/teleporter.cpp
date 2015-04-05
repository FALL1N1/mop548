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

// Chat Icons
//CHAT_ICON = 0
//VENDOR_ICON = 1
//FLIGHT_ICON = 2
//TRAINER_ICON = 3
//GEAR_ICON = 4
//GEAR_ICON_2 = 5
//BANK_ICON = 6
//CHAT_DOTS_ICON = 7
//TABARD_ICON = 8
//SWORDS_ICON = 9
//GOLD_DOT_ICON = 10

#define ERROR_COMBAT "|cffff0000You are in Combat!|r"

class Tele : public CreatureScript
{
public:
	Tele() : CreatureScript("Tele") { }

	bool OnGossipHello(Player* plr, Creature* crt)
	{
		if(plr->IsInCombat())
		{	
			ChatHandler(plr->GetSession()).PSendSysMessage(ERROR_COMBAT);
			return false;
		}
		else 
		{
			plr->ADD_GOSSIP_ITEM(0, "|TInterface\\icons\\Achievement_Reputation_01:30|t  Global Mall", GOSSIP_SENDER_MAIN, 1);
			plr->ADD_GOSSIP_ITEM(0, "|TInterface\\icons\\Achievement_BG_winWSG:30|t  Dueling Zone", GOSSIP_SENDER_MAIN, 2);
			plr->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\ACHIEVEMENT_ARENA_2V2_1:30|t Gurubashi Arena", GOSSIP_SENDER_MAIN, 3);
			plr->SEND_GOSSIP_MENU(1, crt->GetGUID());
			return true;
		}
	}

	bool OnGossipSelect(Player* plr, Creature* crt, uint32 /*sender*/, uint32 actions)
	{
		switch (actions)
		{
			case 1: // Global Mall 
				plr->CLOSE_GOSSIP_MENU();
				plr->TeleportTo(0, -2728.552979f, -5352.151367f, 176.401581f, 2.448691f);
				break;

		    case 2: // Dueling Zone
				plr->CLOSE_GOSSIP_MENU();
				plr->TeleportTo(0, -3575.618652f, -5004.466797f, 33.229931f, 5.351537f);
				break;
				

			case 4: // Gurubashi Arena
				plr->CLOSE_GOSSIP_MENU();
				plr->TeleportTo(0, -13225.893555f, 232.465149f, 33.310444f, 1.121269f);
				break;

		}
		return true;
	}
};

void AddSC_Tele()
{
	new Tele();
}
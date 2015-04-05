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
 
#include "ScriptPCH.h"

enum  defines
{
 faction_token = 110666, // Faction Change Token
 race_token = 110667, // Race Change Token
 customize_token = 110668,  // Customize Change Token
 rename_token = 110669, // Rename Change Token
};

class npc_changer : public CreatureScript
{
	public:
		npc_changer() : CreatureScript("npc_changer"){}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			
			
			pPlayer->ADD_GOSSIP_ITEM(4, "Quero mudar a minha raça!", GOSSIP_SENDER_MAIN, 0);
		    pPlayer->ADD_GOSSIP_ITEM(4, "Quero mudar a minha fação!", GOSSIP_SENDER_MAIN, 1);
            pPlayer->ADD_GOSSIP_ITEM(4, "Quero personalizar a minha personagem!", GOSSIP_SENDER_MAIN, 2);
             pPlayer->ADD_GOSSIP_ITEM(4, "Quero mudar o meu nome!", GOSSIP_SENDER_MAIN, 3);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;

			switch(uiAction)
			{
				case 0:
					if(Player->HasItemCount(race_token, 1))
					{
						Player->DestroyItemCount(race_token, 1, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
						Player->GetSession()->SendNotification("Você necessita de relogar para mudar a sua raça!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
						Player->GetSession()->SendNotification("Você necessita de pelo menos um Token para mudar de fação!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case 1:
					if(Player->HasItemCount(faction_token, 1))
					{
						Player->DestroyItemCount(faction_token, 1, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
						Player->GetSession()->SendNotification("Você necessita de relogar para mudar a sua fação!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
						Player->GetSession()->SendNotification("Você necessita de pelo menos um Token para mudar de raça!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
                               case 2:
                                        if(Player->HasItemCount(customize_token, 1))
                                        {
                                                Player->DestroyItemCount(customize_token, 1, true, false);
                                                Player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                                                Player->GetSession()->SendNotification("Você necessita de relogar para se personalizar!");
                                                Player->PlayerTalkClass->SendCloseGossip();
 
                                        }
 
                                        else
                                        {
                                                Player->GetSession()->SendNotification("Você necessita de pelo menos um Token para se personalizar!");
                                                Player->PlayerTalkClass->SendCloseGossip();
                                        }
                                        break;                         
                                case 3:
                                        if(Player->HasItemCount(rename_token, 1))
                                        {
                                                Player->DestroyItemCount(rename_token, 1, true, false);
                                                Player->SetAtLoginFlag(AT_LOGIN_RENAME);
                                                Player->GetSession()->SendNotification("Você necessita de pelo menos um Token para mudar de nome!");
                                                Player->PlayerTalkClass->SendCloseGossip();
 
                                        }
 
                                        else
                                        {
                                                Player->GetSession()->SendNotification("Você necessita de relogar para mudar o seu nome!");
                                                Player->PlayerTalkClass->SendCloseGossip();
                                        }
                                        break;
			}
			return true;
		}

};

void AddSC_npc_changer()
{
	new npc_changer();
}
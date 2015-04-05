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

/*Class E_Menu*/
#define E_Warrior "Ver os top 5 Warriors com mais kills"
#define E_Paladin "Ver os top 5 Paladins com mais kills"
#define E_Hunter "Ver os top 5 Hunters com mais kills"
#define E_Rogue "Ver os top 5 Rogues com mais kills"
#define E_Priest "Ver os top 5 Priests com mais kills"
#define E_Shaman "Ver os top 5 Shamans com mais kills"
#define E_Mage "Ver os top 5 Mages com mais kills"
#define E_Warlock "Ver os top 5 Warlocks com mais kills"
#define E_Druid "Ver os top 5 Druids com mais kills"
#define E_Death_knight "Ver os top 5 Death knights com mais kills"
/*Top 5 Message*/
#define M_Warrior "Aqui estão os 5 Warriors com mais kills"
#define M_Paladin "Aqui estão os 5 Paladins com mais kills"
#define M_Hunter "Aqui estão os 5 Hunters com mais kills"
#define M_Rogue "Aqui estão os 5 Rogues com mais kills"
#define M_Priest "Aqui estão os 5 Priests com mais kills"
#define M_Shaman "Aqui estão os 5 Shamans com mais kills"
#define M_Mage "Aqui estão os 5 Mages com mais kills"
#define M_Warlock "Aqui estão os 5 Warlocks com mais kills"
#define M_Druid "Aqui estão os 5 Druids com mais kills"
#define M_Death_knight "Aqui estão os 5 Death knights com mais kills"

class Top5_Killers : public CreatureScript
{
public:
    Top5_Killers() : CreatureScript("Top5_Killers") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(1, E_Warrior, GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(1, E_Paladin, GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(1, E_Hunter, GOSSIP_SENDER_MAIN, 3);
        player->ADD_GOSSIP_ITEM(1, E_Rogue, GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM(1, E_Priest, GOSSIP_SENDER_MAIN, 5);
        player->ADD_GOSSIP_ITEM(1, E_Shaman, GOSSIP_SENDER_MAIN, 7);
        player->ADD_GOSSIP_ITEM(1, E_Mage, GOSSIP_SENDER_MAIN, 8);
        player->ADD_GOSSIP_ITEM(1, E_Warlock, GOSSIP_SENDER_MAIN, 9);
        player->ADD_GOSSIP_ITEM(1, E_Druid, GOSSIP_SENDER_MAIN, 11);
        player->ADD_GOSSIP_ITEM(1, E_Death_knight, GOSSIP_SENDER_MAIN, 6);
        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (sender != GOSSIP_SENDER_MAIN)
            return true; // wrong sender, something fisy

        switch(action)
        {
        case 1: ChatHandler(player->GetSession()).PSendSysMessage(M_Warrior);       break;
        case 2: ChatHandler(player->GetSession()).PSendSysMessage(M_Paladin);       break;
        case 3: ChatHandler(player->GetSession()).PSendSysMessage(M_Hunter);        break;
        case 4: ChatHandler(player->GetSession()).PSendSysMessage(M_Rogue);         break;
        case 5: ChatHandler(player->GetSession()).PSendSysMessage(M_Priest);        break;
        case 6: ChatHandler(player->GetSession()).PSendSysMessage(M_Death_knight);  break;
        case 7: ChatHandler(player->GetSession()).PSendSysMessage(M_Shaman);        break;
        case 8: ChatHandler(player->GetSession()).PSendSysMessage(M_Mage);          break;
        case 9: ChatHandler(player->GetSession()).PSendSysMessage(M_Warlock);       break;
        case 11: ChatHandler(player->GetSession()).PSendSysMessage(M_Druid);        break;
        default: return true; // invalid class, something fishy
        }

        QueryResult result = CharacterDatabase.PQuery("SELECT name, totalKills FROM characters WHERE class = %u ORDER BY totalKills DESC LIMIT 5", action);
        if(result)
        {
            do
            {
                Field * fields = result->Fetch();
                std::string name = fields[0].GetString();
                uint32 totalKills = fields[1].GetUInt32();
                ChatHandler(player->GetSession()).PSendSysMessage("Nome: %s, com as kills : %u", name.c_str(), totalKills);
            } 
            while(result->NextRow());
        }
        OnGossipHello(player, creature); // return to main menu
        return true;
    }
};


void AddSC_Top5_Killers()
{
    new Top5_Killers();
}
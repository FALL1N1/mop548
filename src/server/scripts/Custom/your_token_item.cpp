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

class your_token_item : public ItemScript
{
public: your_token_item() : ItemScript("your_token_item") { }
       
  bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
  {
   if (player->GetSession()->GetSecurity() == SEC_VIP)
   {
    player->GetSession()->SendNotification("Você já é VIP!");
    return true;
   }
   else
   {
      QueryResult insertvip = LoginDatabase.PQuery("REPLACE INTO `account_access` VALUES(%u, 1, -1)", player->GetSession()->GetAccountId());
   player->GetSession()->SetSecurity(SEC_VIP);
   player->GetSession()->SendNotification("Agora a sua conta é VIP!");
   player->DestroyItemCount(item->GetEntry(), 1, true, false);
   return true;
     }
       }
};
 
void AddSC_your_token_item()
{
 new your_token_item();
}
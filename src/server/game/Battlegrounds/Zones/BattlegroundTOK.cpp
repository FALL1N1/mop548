/*
 * Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
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

#include "BattlegroundTOK.h"
#include "World.h"
#include "WorldPacket.h"
#include "ObjectMgr.h"
#include "BattlegroundMgr.h"
#include "Creature.h"
#include "Language.h"
#include "Object.h"
#include "Player.h"
#include "Util.h"
#include "WorldSession.h"

BattlegroundTOK::BattlegroundTOK()
{
  
}

BattlegroundTOK::~BattlegroundTOK() { }

void BattlegroundTOK::PostUpdateImpl(uint32 diff)
{
  
}

void BattlegroundTOK::StartingEventCloseDoors()
{
  
}

void BattlegroundTOK::StartingEventOpenDoors()
{
  
}

void BattlegroundTOK::AddPlayer(Player* player)
{
    
}

void BattlegroundTOK::RemovePlayer(Player* /*player*/, uint64 /*guid*/, uint32 /*team*/)
{

}

void BattlegroundTOK::HandleAreaTrigger(Player* player, uint32 trigger)
{
  
}

void BattlegroundTOK::FillInitialWorldStates(WorldStateBuilder& builder)
{
   
}

/* Invoked if a player used a banner as a gameobject */
void BattlegroundTOK::EventPlayerClickedOnFlag(Player* source, GameObject* /*target_obj*/)
{
   
}

uint32 BattlegroundTOK::GetPrematureWinner()
{
  
}

bool BattlegroundTOK::SetupBattleground()
{
    
}

void BattlegroundTOK::Reset()
{
   
}

void BattlegroundTOK::EndBattleground(uint32 winner)
{
   
}

WorldSafeLocsEntry const* BattlegroundTOK::GetClosestGraveYard(Player* player)
{
  
}

void BattlegroundTOK::UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor)
{
   
}

bool BattlegroundTOK::IsAllNodesControlledByTeam(uint32 team) const
{
    
}

bool BattlegroundTOK::CheckAchievementCriteriaMeet(uint32 criteriaId, Player const* player, Unit const* target, uint32 miscvalue)
{
  
}

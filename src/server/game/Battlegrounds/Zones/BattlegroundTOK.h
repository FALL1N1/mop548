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

#ifndef __BATTLEGROUNDTOK_H
#define __BATTLEGROUNDTOK_H

#include "Battleground.h"

enum BG_TOK_WorldStates
{
  
};

class BattlegroundTOK : public Battleground
{
    public:
        BattlegroundTOK();
        ~BattlegroundTOK();

        void AddPlayer(Player* player);
        void StartingEventCloseDoors();
        void StartingEventOpenDoors();
        void RemovePlayer(Player* player, uint64 guid, uint32 team);
        void HandleAreaTrigger(Player* Source, uint32 Trigger);
        bool SetupBattleground();
        void Reset();
        void EndBattleground(uint32 winner);
        WorldSafeLocsEntry const* GetClosestGraveYard(Player* player);

        /* Scorekeeping */
        void UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor = true);

        void FillInitialWorldStates(WorldStateBuilder& builder);

        /* Nodes occupying */
        void EventPlayerClickedOnFlag(Player* source, GameObject* target_obj);

        /* achievement req. */
        bool IsAllNodesControlledByTeam(uint32 team) const;
        bool CheckAchievementCriteriaMeet(uint32 /*criteriaId*/, Player const* /*player*/, Unit const* /*target*/ = NULL, uint32 /*miscvalue1*/ = 0);

        uint32 GetPrematureWinner();
  
};
#endif

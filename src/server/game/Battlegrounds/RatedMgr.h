/*
* Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
* Copyright (C) 2013-2014 TimelessCore <http://timeless.sk/>
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

#ifndef _RATEDMGR_H
#define _RATEDMGR_H

class RatedInfo;

class RatedMgr
{
    friend class ACE_Singleton<RatedMgr, ACE_Null_Mutex>;
    RatedMgr();
    ~RatedMgr();

public:
    typedef std::unordered_map<uint64, RatedInfo*> RatedInfoContainer;    

    RatedInfo* GetRatedInfo(uint64 guid);

    void LoadRatedInfo();
    void AddRatedInfo(RatedInfo* ratedInfo);
    void RemoveRatedInfo(RatedInfo* ratedInfo);

    RatedInfoContainer::iterator GetRatedInfoMapBegin() { return m_ratedInfoStore.begin(); }
    RatedInfoContainer::iterator GetRatedInfoMapEnd()   { return m_ratedInfoStore.end();   }

private:
    RatedInfoContainer m_ratedInfoStore;
};

#define sRatedMgr ACE_Singleton<RatedMgr, ACE_Null_Mutex>::instance()

#endif

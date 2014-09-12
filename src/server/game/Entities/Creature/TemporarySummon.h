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
#ifndef TRINITYCORE_TEMPSUMMON_H
#define TRINITYCORE_TEMPSUMMON_H

#include "Creature.h"

enum SummonerType
{
    SUMMONER_TYPE_CREATURE      = 0,
    SUMMONER_TYPE_GAMEOBJECT    = 1,
    SUMMONER_TYPE_MAP           = 2
};

/// Stores data for temp summons
struct TempSummonData
{
    uint32 entry;        ///< Entry of summoned creature
    Position pos;        ///< Position, where should be creature spawned
    TempSummonType type; ///< Summon type, see TempSummonType for available types
    uint32 time;         ///< Despawn time, usable only with certain temp summon types
};

// Creature Pet entries
enum EPetEntries
{
    // Warlock
    E_PET_ENTRY_INFERNAL = 89,
    E_PET_ENTRY_IMP = 416,
    E_PET_ENTRY_VOIDWALKER = 1860,
    E_PET_ENTRY_SUCCUBUS = 1863,
    E_PET_ENTRY_FELHUNTER = 417,
    E_PET_ENTRY_FELGUARD = 17252,
    E_PET_ENTRY_FEL_IMP = 58959,
    E_PET_ENTRY_VOIDLORD = 58960,
    E_PET_ENTRY_SHIVARRA = 58963,
    E_PET_ENTRY_OBSERVER = 58964,
    E_PET_ENTRY_WRATHGUARD = 58965,

    // Mage
    E_PET_ENTRY_WATER_ELEMENTAL = 510,
    E_PET_ENTRY_MIRROR_IMAGE = 31216,

    // Druid
    E_PET_ENTRY_TREANT_GUARDIAN = 54985,
    E_PET_ENTRY_TREANT_FERAL = 54984,
    E_PET_ENTRY_TREANT_RESTO = 54983,
    E_PET_ENTRY_TREANT_BALANCE = 1964,

    // Shaman
    E_PET_ENTRY_FIRE_ELEMENTAL = 15438,
    E_PET_ENTRY_FERAL_SPIRIT = 29264,
    E_PET_ENTRY_EARTH_ELEMENTAL = 15352,

    // Death Knight
    E_PET_ENTRY_GHOUL = 26125,
    E_PET_ENTRY_BLOODWORM = 28017,
    E_PET_ENTRY_GARGOYLE = 27829,

    // Priest 
    E_PET_ENTRY_SHADOWFIEND = 19668,

    // Hunter
    E_PET_ENTRY_VENOMOUS_SNAKE = 19833,
    E_PET_ENTRY_VIPER = 19921,
};

class TempSummon : public Creature
{
    public:
        explicit TempSummon(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject);
        virtual ~TempSummon() { }
        void Update(uint32 time);
        virtual void InitStats(uint32 lifetime);
        virtual void InitSummon();
        virtual void UnSummon(uint32 msTime = 0);
        void RemoveFromWorld();
        void SetTempSummonType(TempSummonType type);
        void SaveToDB(uint32 /*mapid*/, uint8 /*spawnMask*/, uint32 /*phaseMask*/) { }
        Unit* GetSummoner() const;
        Creature* GetSummonerCreatureBase() const;
        uint64 GetSummonerGUID() const { return m_summonerGUID; }
        TempSummonType const& GetSummonType() { return m_type; }
        uint32 GetTimer() { return m_timer; }

        const SummonPropertiesEntry* const m_Properties;
    private:
        TempSummonType m_type;
        uint32 m_timer;
        uint32 m_lifetime;
        uint64 m_summonerGUID;
};

class Minion : public TempSummon
{
public:
    Minion(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject);
    void InitStats(uint32 duration);
    void RemoveFromWorld();
    Unit* GetOwner() const { return m_owner; }
    float GetFollowAngle() const { return m_followAngle; }
    void SetFollowAngle(float angle) { m_followAngle = angle; }

    bool IsTreant() const;
    bool IsPetGhoul() const { return GetEntry() == E_PET_ENTRY_GHOUL; }
    bool IsPetGargoyle() const { return GetEntry() == E_PET_ENTRY_GARGOYLE; }
    bool IsSpiritWolf() const { return GetEntry() == E_PET_ENTRY_FERAL_SPIRIT; }
    bool isWrathGuard() const { return GetEntry() == E_PET_ENTRY_WRATHGUARD; }
    bool IsWaterElemental() const { return GetEntry() == E_PET_ENTRY_WATER_ELEMENTAL; }
    bool IsGuardianPet() const;
    bool IsWarlockPet() const;
protected:
    Unit* const m_owner;
    float m_followAngle;
};

class Guardian : public Minion
{
    public:
        Guardian(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject);
        void InitStats(uint32 duration);
        bool InitStatsForLevel(uint8 level);
        void InitSummon();

        bool UpdateStats(Stats stat);
        bool UpdateAllStats();
        void UpdateResistances(uint32 school);
        void UpdateArmor();
        void UpdateMaxHealth();
        void UpdateMaxPower(Powers power);
        void UpdateAttackPowerAndDamage(bool ranged = false);
        void UpdateDamagePhysical(WeaponAttackType attType);

        int32 GetBonusDamage() const { return m_bonusSpellDamage; }
        void SetBonusDamage(int32 damage);
    protected:
        int32   m_bonusSpellDamage;
        float   m_statFromOwner[MAX_STATS];
};

class Puppet : public Minion
{
    public:
        Puppet(SummonPropertiesEntry const* properties, Unit* owner);
        void InitStats(uint32 duration);
        void InitSummon();
        void Update(uint32 time);
        void RemoveFromWorld();
};

class ForcedUnsummonDelayEvent : public BasicEvent
{
public:
    ForcedUnsummonDelayEvent(TempSummon& owner) : BasicEvent(), m_owner(owner) { }
    bool Execute(uint64 e_time, uint32 p_time);

private:
    TempSummon& m_owner;
};

inline
bool Minion::IsTreant() const
{
    switch (GetEntry())
    {
        case E_PET_ENTRY_TREANT_GUARDIAN:
        case E_PET_ENTRY_TREANT_FERAL:
        case E_PET_ENTRY_TREANT_BALANCE:
        case E_PET_ENTRY_TREANT_RESTO:
            return true;
        default:
            return false;
    }
}

inline
bool Minion::IsGuardianPet() const
{
    return IsPet() || (m_Properties && m_Properties->Category == SUMMON_CATEGORY_PET);
}

inline
bool Minion::IsWarlockPet() const
{
    auto checkEntry = [this] ()
    {
        switch (GetEntry())
        {
            case E_PET_ENTRY_INFERNAL:
            case E_PET_ENTRY_IMP:
            case E_PET_ENTRY_VOIDWALKER:
            case E_PET_ENTRY_SUCCUBUS:
            case E_PET_ENTRY_FELHUNTER:
            case E_PET_ENTRY_FELGUARD:
            case E_PET_ENTRY_OBSERVER:
            case E_PET_ENTRY_SHIVARRA:
            case E_PET_ENTRY_VOIDLORD:
            case E_PET_ENTRY_FEL_IMP:
                return true;
            default:
                return false;
        }
    };

    return IsPet() && checkEntry() || isWrathGuard();
}

#endif

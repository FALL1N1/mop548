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

#pragma once
#include "Player.h"

typedef std::map<uint8, uint32> SlotEquipmentMap;

SlotEquipmentMap const mageEquipment = 
{
    { EQUIPMENT_SLOT_NECK, 101068 },
    { EQUIPMENT_SLOT_TRINKET2, 101069 },
    { EQUIPMENT_SLOT_FINGER1, 101070 },
    { EQUIPMENT_SLOT_FINGER2, 101071 },
    { EQUIPMENT_SLOT_TRINKET1, 101072 },
    { EQUIPMENT_SLOT_FEET, 101073 },
    { EQUIPMENT_SLOT_HANDS, 101074 },
    { EQUIPMENT_SLOT_HEAD, 101075 },
    { EQUIPMENT_SLOT_LEGS, 101076 },
    { EQUIPMENT_SLOT_CHEST, 101077 },
    { EQUIPMENT_SLOT_SHOULDERS, 101078 },
    { EQUIPMENT_SLOT_WAIST, 101079 },
    { EQUIPMENT_SLOT_WRISTS, 101080 },
    { EQUIPMENT_SLOT_BACK, 101082 },
    { EQUIPMENT_SLOT_MAINHAND, 101083 }
};

SlotEquipmentMap const hunterEquipment =
{
    { EQUIPMENT_SLOT_HEAD, 101061 },
    { EQUIPMENT_SLOT_NECK, 101053 },
    { EQUIPMENT_SLOT_SHOULDERS, 101063 },
    { EQUIPMENT_SLOT_BACK, 101052 },
    { EQUIPMENT_SLOT_CHEST, 101058 },
    { EQUIPMENT_SLOT_WRISTS, 101064 },
    { EQUIPMENT_SLOT_HANDS, 101060 },
    { EQUIPMENT_SLOT_WAIST, 101065 },
    { EQUIPMENT_SLOT_LEGS, 101062 },
    { EQUIPMENT_SLOT_FEET, 101059 },
    { EQUIPMENT_SLOT_FINGER1, 101055 },
    { EQUIPMENT_SLOT_FINGER2, 101056 },
    { EQUIPMENT_SLOT_TRINKET1, 101054 },
    { EQUIPMENT_SLOT_TRINKET2, 101057 },
    { EQUIPMENT_SLOT_MAINHAND, 101066 }
};

SlotEquipmentMap const rogueEquipmentAssassionation =
{
    { EQUIPMENT_SLOT_HEAD, 101207 },
    { EQUIPMENT_SLOT_NECK, 101199},
    { EQUIPMENT_SLOT_SHOULDERS, 101209 },
    { EQUIPMENT_SLOT_BACK, 101198 },
    { EQUIPMENT_SLOT_CHEST, 101204 },
    { EQUIPMENT_SLOT_WRISTS, 101211 },
    { EQUIPMENT_SLOT_HANDS, 101206 },
    { EQUIPMENT_SLOT_WAIST, 101210 },
    { EQUIPMENT_SLOT_LEGS, 101208 },
    { EQUIPMENT_SLOT_FEET, 101205 },
    { EQUIPMENT_SLOT_FINGER1, 101201 },
    { EQUIPMENT_SLOT_FINGER2, 101202 },
    { EQUIPMENT_SLOT_TRINKET1, 101200 },
    { EQUIPMENT_SLOT_TRINKET2, 101203 },
    { EQUIPMENT_SLOT_MAINHAND, 101214 },
    { EQUIPMENT_SLOT_OFFHAND, 101214 }
};

SlotEquipmentMap const rogueEquipmentCombat =
{
    { EQUIPMENT_SLOT_HEAD, 101207 },
    { EQUIPMENT_SLOT_NECK, 101199 },
    { EQUIPMENT_SLOT_SHOULDERS, 101209 },
    { EQUIPMENT_SLOT_BACK, 101198 },
    { EQUIPMENT_SLOT_CHEST, 101204 },
    { EQUIPMENT_SLOT_WRISTS, 101211 },
    { EQUIPMENT_SLOT_HANDS, 101206 },
    { EQUIPMENT_SLOT_WAIST, 101210 },
    { EQUIPMENT_SLOT_LEGS, 101208 },
    { EQUIPMENT_SLOT_FEET, 101205 },
    { EQUIPMENT_SLOT_FINGER1, 101201 },
    { EQUIPMENT_SLOT_FINGER2, 101202 },
    { EQUIPMENT_SLOT_TRINKET1, 101200 },
    { EQUIPMENT_SLOT_TRINKET2, 101203 },
    { EQUIPMENT_SLOT_MAINHAND, 101213 },
    { EQUIPMENT_SLOT_OFFHAND, 101213 }
};

SlotEquipmentMap const rogueEquipmentSubtlety =
{
    { EQUIPMENT_SLOT_HEAD, 101207 },
    { EQUIPMENT_SLOT_NECK, 101199 },
    { EQUIPMENT_SLOT_SHOULDERS, 101209 },
    { EQUIPMENT_SLOT_BACK, 101198 },
    { EQUIPMENT_SLOT_CHEST, 101204 },
    { EQUIPMENT_SLOT_WRISTS, 101211 },
    { EQUIPMENT_SLOT_HANDS, 101206 },
    { EQUIPMENT_SLOT_WAIST, 101210 },
    { EQUIPMENT_SLOT_LEGS, 101208 },
    { EQUIPMENT_SLOT_FEET, 101205 },
    { EQUIPMENT_SLOT_FINGER1, 101201 },
    { EQUIPMENT_SLOT_FINGER2, 101202 },
    { EQUIPMENT_SLOT_TRINKET1, 101200 },
    { EQUIPMENT_SLOT_TRINKET2, 101203 },
    { EQUIPMENT_SLOT_MAINHAND, 101212 },
    { EQUIPMENT_SLOT_OFFHAND, 101212 }
};

SlotEquipmentMap const warlockEquipment =
{
    { EQUIPMENT_SLOT_HEAD, 101269 },
    { EQUIPMENT_SLOT_NECK, 101262 },
    { EQUIPMENT_SLOT_SHOULDERS, 101272 },
    { EQUIPMENT_SLOT_BACK, 101276 },
    { EQUIPMENT_SLOT_CHEST, 101271 },
    { EQUIPMENT_SLOT_WRISTS, 101274 },
    { EQUIPMENT_SLOT_HANDS, 101268 },
    { EQUIPMENT_SLOT_WAIST, 101273 },
    { EQUIPMENT_SLOT_LEGS, 101270 },
    { EQUIPMENT_SLOT_FEET, 101267 },
    { EQUIPMENT_SLOT_FINGER1, 101264 },
    { EQUIPMENT_SLOT_FINGER2, 101265 },
    { EQUIPMENT_SLOT_TRINKET1, 101266 },
    { EQUIPMENT_SLOT_TRINKET2, 101263 },
    { EQUIPMENT_SLOT_MAINHAND, 101277 }
};

enum CharSpecialization
{
    CHAR_SPECIALIZATION_MAGE_ARCANE             = 62,
    CHAR_SPECIALIZATION_MAGE_FIRE               = 63,
    CHAR_SPECIALIZATION_MAGE_FROST              = 64,
    CHAR_SPECIALIZATION_PALADIN_HOLY            = 65,
    CHAR_SPECIALIZATION_PALADIN_PROTECTION      = 66,
    CHAR_SPECIALIZATION_PALADIN_RETRIBUTION     = 70,
    CHAR_SPECIALIZATION_WARRIOR_ARMS            = 71,
    CHAR_SPECIALIZATION_WARRIOR_FURY            = 72,
    CHAR_SPECIALIZATION_WARRIOR_PROTECTION      = 73,
    CHAR_SPECIALIZATION_DRUID_BALANCE           = 102,
    CHAR_SPECIALIZATION_DRUID_FERAL_CAT         = 103,
    CHAR_SPECIALIZATION_DRUID_FERAL_BEAR        = 104,
    CHAR_SPECIALIZATION_DRUID_RESTORATION       = 105,
    CHAR_SPECIALIZATION_DEATH_KNIGHT_BLOOD      = 250,
    CHAR_SPECIALIZATION_DEATH_KNIGHT_FROST      = 251,
    CHAR_SPECIALIZATION_DEATH_KNIGHT_UNHOLY     = 252,
    CHAR_SPECIALIZATION_HUNTER_BEAST_MASTERY    = 253,
    CHAR_SPECIALIZATION_HUNTER_MARKSMANSHIP     = 254,
    CHAR_SPECIALIZATION_HUNTER_SURVIVAL         = 255,
    CHAR_SPECIALIZATION_PRIEST_DISCIPLINE       = 256,
    CHAR_SPECIALIZATION_PRIEST_HOLY             = 257,
    CHAR_SPECIALIZATION_PRIEST_SHADOW           = 258,
    CHAR_SPECIALIZATION_ROGUE_ASSASSINATION     = 259,
    CHAR_SPECIALIZATION_ROGUE_COMBAT            = 260,
    CHAR_SPECIALIZATION_ROGUE_SUBTLETY          = 261,
    CHAR_SPECIALIZATION_SHAMAN_ELEMENTAL        = 262,
    CHAR_SPECIALIZATION_SHAMAN_ENHANCEMENT      = 263,
    CHAR_SPECIALIZATION_SHAMAN_RESTORATION      = 264,
    CHAR_SPECIALIZATION_WARLOCK_AFFLICTION      = 265,
    CHAR_SPECIALIZATION_WARLOCK_DEMONOLOGY      = 266,
    CHAR_SPECIALIZATION_WARLOCK_DESTRUCTION     = 267,
    CHAR_SPECIALIZATION_MONK_BREWMASTER         = 268,
    CHAR_SPECIALIZATION_MONK_BATTLEDANCER       = 269,
    CHAR_SPECIALIZATION_MONK_MISTWEAVER         = 270
};

#define CHARRACTER_BOOST_EQUIPED_ITEMS_MAIL_BODY "We've supplied you with a whole new set of high-level gear, but attached you'll find all the old items and equipment you once carried.\n\n - The WoW Dev Team"
#define CHARRACTER_BOOST_EQUIPED_ITEMS_MAIL_SUBJECT "Character Boost"

struct CharacterBoostData
{
    CharacterBoostData() : charGuid(0), lowGuid(0), action(0), specialization(0), allianceFaction(false) { }

    uint64 charGuid;
    uint32 lowGuid;
    uint32 action;
    uint32 specialization;
    bool allianceFaction;
};

class CharacterBooster
{
    public:
        CharacterBooster(WorldSession* session);
        void HandleCharacterBoost();
        void SetBoostedCharInfo(uint64 guid, uint32 action, uint32 specialization, bool allianceFaction);
        uint32 GetCurrentAction() const { return m_charBoostInfo.action; }
        uint32 GetGuidLow() const { return m_charBoostInfo.lowGuid; }
        bool IsBoosting(uint32 lowGuid) const { return m_boosting && (m_charBoostInfo.lowGuid == lowGuid); }
        void Update(uint32 diff);

    private:
        void _HandleCharacterBoost();
        SlotEquipmentMap const* _GetCharBoostItems(std::vector<uint32>& itemsToMail) const;
        void _SendCharBoostPacket(SlotEquipmentMap const* items);
        void _MailEquipedItems(SQLTransaction& trans) const;
        void _SendMail(SQLTransaction& trans, std::vector<uint32> const& items) const;
        uint32 _PrepareMail(SQLTransaction& trans, std::string const& subject, std::string const& body) const;

        CharacterBoostData m_charBoostInfo;
        WorldSession* m_session;
        uint32 m_timer;
        bool m_boosting;
        bool m_sendPacket;
};

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

SlotEquipmentMap const hunterEquipment =
{
    { EQUIPMENT_SLOT_HEAD, 101061 },
    { EQUIPMENT_SLOT_NECK, 101053 },
    { EQUIPMENT_SLOT_SHOULDERS, 101063 },
    { EQUIPMENT_SLOT_BACK, 101052 },
    { EQUIPMENT_SLOT_CHEST, 101058 },
    { EQUIPMENT_SLOT_WRISTS, 101065 },
    { EQUIPMENT_SLOT_HANDS, 101060 },
    { EQUIPMENT_SLOT_WAIST, 101064 },
    { EQUIPMENT_SLOT_LEGS, 101062 },
    { EQUIPMENT_SLOT_FEET, 101059 },
    { EQUIPMENT_SLOT_FINGER1, 101055 },
    { EQUIPMENT_SLOT_FINGER2, 101056 },
    { EQUIPMENT_SLOT_TRINKET1, 101054 },
    { EQUIPMENT_SLOT_TRINKET2, 101057 },
    { EQUIPMENT_SLOT_MAINHAND, 101066 }
};

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

SlotEquipmentMap const paladinEquipmentHoly =
{
    { EQUIPMENT_SLOT_HEAD, 101132 },
    { EQUIPMENT_SLOT_NECK, 101134 },
    { EQUIPMENT_SLOT_SHOULDERS, 101139 },
    { EQUIPMENT_SLOT_BACK, 101129 },
    { EQUIPMENT_SLOT_CHEST, 101128 },
    { EQUIPMENT_SLOT_WRISTS, 101141 },
    { EQUIPMENT_SLOT_HANDS, 101131 },
    { EQUIPMENT_SLOT_WAIST, 101140 },
    { EQUIPMENT_SLOT_LEGS, 101133 },
    { EQUIPMENT_SLOT_FEET, 101130 },
    { EQUIPMENT_SLOT_FINGER1, 101136 },
    { EQUIPMENT_SLOT_FINGER2, 101137 },
    { EQUIPMENT_SLOT_TRINKET1, 101135 },
    { EQUIPMENT_SLOT_TRINKET2, 101138 },
    { EQUIPMENT_SLOT_MAINHAND, 101142 },
    { EQUIPMENT_SLOT_OFFHAND, 101143 }
};

SlotEquipmentMap const paladinEquipmentProtection =
{
    { EQUIPMENT_SLOT_HEAD, 101157 },
    { EQUIPMENT_SLOT_NECK, 101159 },
    { EQUIPMENT_SLOT_SHOULDERS, 101164 },
    { EQUIPMENT_SLOT_BACK, 101154 },
    { EQUIPMENT_SLOT_CHEST, 101153 },
    { EQUIPMENT_SLOT_WRISTS, 101166 },
    { EQUIPMENT_SLOT_HANDS, 101156 },
    { EQUIPMENT_SLOT_WAIST, 101165 },
    { EQUIPMENT_SLOT_LEGS, 101158 },
    { EQUIPMENT_SLOT_FEET, 101155 },
    { EQUIPMENT_SLOT_FINGER1, 101161 },
    { EQUIPMENT_SLOT_FINGER2, 101162 },
    { EQUIPMENT_SLOT_TRINKET1, 101160 },
    { EQUIPMENT_SLOT_TRINKET2, 101163 },
    { EQUIPMENT_SLOT_MAINHAND, 101144 },
    { EQUIPMENT_SLOT_OFFHAND, 101145 }
};

SlotEquipmentMap const paladinEquipmentRetribution =
{
    { EQUIPMENT_SLOT_HEAD, 101123 },
    { EQUIPMENT_SLOT_NECK, 101148 },
    { EQUIPMENT_SLOT_SHOULDERS, 101125 },
    { EQUIPMENT_SLOT_BACK, 101147 },
    { EQUIPMENT_SLOT_CHEST, 101120 },
    { EQUIPMENT_SLOT_WRISTS, 101127 },
    { EQUIPMENT_SLOT_HANDS, 101122 },
    { EQUIPMENT_SLOT_WAIST, 101126 },
    { EQUIPMENT_SLOT_LEGS, 101124 },
    { EQUIPMENT_SLOT_FEET, 101121 },
    { EQUIPMENT_SLOT_FINGER1, 101149 },
    { EQUIPMENT_SLOT_FINGER2, 101150 },
    { EQUIPMENT_SLOT_TRINKET1, 101151 },
    { EQUIPMENT_SLOT_TRINKET2, 101152 },
    { EQUIPMENT_SLOT_MAINHAND, 101146 }
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

SlotEquipmentMap const warriorEquipmentArms =
{
    { EQUIPMENT_SLOT_HEAD, 101282 },
    { EQUIPMENT_SLOT_NECK, 101291 },
    { EQUIPMENT_SLOT_SHOULDERS, 101284 },
    { EQUIPMENT_SLOT_BACK, 101290 },
    { EQUIPMENT_SLOT_CHEST, 101279 },
    { EQUIPMENT_SLOT_WRISTS, 101286 },
    { EQUIPMENT_SLOT_HANDS, 101281 },
    { EQUIPMENT_SLOT_WAIST, 101285 },
    { EQUIPMENT_SLOT_LEGS, 101283 },
    { EQUIPMENT_SLOT_FEET, 101280 },
    { EQUIPMENT_SLOT_FINGER1, 101292 },
    { EQUIPMENT_SLOT_FINGER2, 101293 },
    { EQUIPMENT_SLOT_TRINKET1, 101294 },
    { EQUIPMENT_SLOT_TRINKET2, 101295 },
    { EQUIPMENT_SLOT_MAINHAND, 101278 }
};

SlotEquipmentMap const warriorEquipmentFury =
{
    { EQUIPMENT_SLOT_HEAD, 101282 },
    { EQUIPMENT_SLOT_NECK, 101291 },
    { EQUIPMENT_SLOT_SHOULDERS, 101284 },
    { EQUIPMENT_SLOT_BACK, 101290 },
    { EQUIPMENT_SLOT_CHEST, 101279 },
    { EQUIPMENT_SLOT_WRISTS, 101286 },
    { EQUIPMENT_SLOT_HANDS, 101281 },
    { EQUIPMENT_SLOT_WAIST, 101285 },
    { EQUIPMENT_SLOT_LEGS, 101283 },
    { EQUIPMENT_SLOT_FEET, 101280 },
    { EQUIPMENT_SLOT_FINGER1, 101292 },
    { EQUIPMENT_SLOT_FINGER2, 101293 },
    { EQUIPMENT_SLOT_TRINKET1, 101294 },
    { EQUIPMENT_SLOT_TRINKET2, 101295 },
    { EQUIPMENT_SLOT_MAINHAND, 101287 },
    { EQUIPMENT_SLOT_OFFHAND, 101287 }
};

SlotEquipmentMap const warriorEquipmentProtection =
{
    { EQUIPMENT_SLOT_HEAD, 101300 },
    { EQUIPMENT_SLOT_NECK, 101302 },
    { EQUIPMENT_SLOT_SHOULDERS, 101307 },
    { EQUIPMENT_SLOT_BACK, 101297 },
    { EQUIPMENT_SLOT_CHEST, 101296 },
    { EQUIPMENT_SLOT_WRISTS, 101309 },
    { EQUIPMENT_SLOT_HANDS, 101299 },
    { EQUIPMENT_SLOT_WAIST, 101308 },
    { EQUIPMENT_SLOT_LEGS, 101301 },
    { EQUIPMENT_SLOT_FEET, 101298 },
    { EQUIPMENT_SLOT_FINGER1, 101305 },
    { EQUIPMENT_SLOT_FINGER2, 101304 },
    { EQUIPMENT_SLOT_TRINKET1, 101303 },
    { EQUIPMENT_SLOT_TRINKET2, 101306 },
    { EQUIPMENT_SLOT_MAINHAND, 101288 },
    { EQUIPMENT_SLOT_OFFHAND, 101289 }

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

enum CharBoostMisc
{
    EMBERSILK_BAG_ID            = 54443,
    BOSSTED_BAG_COUNT           = 4,
    PLATE_MAIL_ARMOR_SPELL      = 750
};

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

        uint32 GetCurrentAction() const { return m_charBoostInfo.action; }
        uint32 GetGuidLow() const { return m_charBoostInfo.lowGuid; }
        void HandleCharacterBoost();
        bool IsBoosting(uint32 lowGuid) const { return m_boosting && (m_charBoostInfo.lowGuid == lowGuid); }
        void SetBoostedCharInfo(uint64 guid, uint32 action, uint32 specialization, bool allianceFaction);
        void Update(uint32 diff);

    private:
        SlotEquipmentMap const* _GetCharBoostItems(std::vector<uint32>& itemsToMail) const;
        uint8 _GetRace() const;
        void _HandleCharacterBoost();
        void _LearnSpells(SQLTransaction& trans, uint8 const& raceId, uint8 const& classId) const;
        void _MailEquipedItems(SQLTransaction& trans) const;
        uint32 _PrepareMail(SQLTransaction& trans, std::string const& subject, std::string const& body) const;
        std::string _SetSpecialization(SQLTransaction& trans, uint8 const& classId) const;
        void _SendMail(SQLTransaction& trans, std::vector<uint32> const& items) const;
        void _SendCharBoostPacket(SlotEquipmentMap const* items);

        CharacterBoostData m_charBoostInfo;
        WorldSession* m_session;
        uint32 m_timer;
        bool m_boosting;
        bool m_sendPacket;
};

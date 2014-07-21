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
        void _AddCharBoostItems(std::map<uint8, uint32>& itemsToEquip, std::vector<uint32>& itemsToMail) const;
        void _SendCharBoostPacket(std::map<uint8, uint32>& items);
        void _MailEquipedItems(SQLTransaction& trans) const;
        void _SendMail(SQLTransaction& trans, std::vector<uint32>& items) const;
        uint32 _PrepareMail(SQLTransaction& trans, std::string const& subject, std::string const& body) const;

        CharacterBoostData m_charBoostInfo;
        WorldSession* m_session;
        uint32 m_timer;
        bool m_boosting;
        bool m_sendPacket;
};

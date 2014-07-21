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

#include "BattleShop.h"
#include "WorldSession.h"

CharacterBooster::CharacterBooster(WorldSession* session) : m_session(session), m_timer(0), m_boosting(false), m_sendPacket(false) { }

SlotEquipmentMap const* CharacterBooster::_GetCharBoostItems(std::vector<uint32>& itemsToMail) const
{
    switch (m_charBoostInfo.specialization)
    {
        case CHAR_SPECIALIZATION_MAGE_ARCANE:
        case CHAR_SPECIALIZATION_MAGE_FIRE:
        case CHAR_SPECIALIZATION_MAGE_FROST:
            itemsToMail.push_back(101081);
            return &mageEquipment;
        case CHAR_SPECIALIZATION_HUNTER_BEAST_MASTERY:
        case CHAR_SPECIALIZATION_HUNTER_MARKSMANSHIP:
        case CHAR_SPECIALIZATION_HUNTER_SURVIVAL:
            return &hunterEquipment;
        case CHAR_SPECIALIZATION_ROGUE_ASSASSINATION:
            return &rogueEquipmentAssassionation;
        case CHAR_SPECIALIZATION_ROGUE_COMBAT:
            return &rogueEquipmentCombat;
        case CHAR_SPECIALIZATION_ROGUE_SUBTLETY:
            return &rogueEquipmentCombat;
        case CHAR_SPECIALIZATION_WARLOCK_AFFLICTION:
        case CHAR_SPECIALIZATION_WARLOCK_DEMONOLOGY:
        case CHAR_SPECIALIZATION_WARLOCK_DESTRUCTION:
            itemsToMail.push_back(101275);
            return &warlockEquipment;
        default:
            return NULL;
    }
}

void CharacterBooster::_SendCharBoostPacket(SlotEquipmentMap const* items)
{
    ObjectGuid guid = m_charBoostInfo.charGuid;
    WorldPacket data(SMSG_BATTLE_CHAR_BOOST_ITEMS, 8 + 3 + items->size());
    data.WriteBit(guid[2]);
    data.WriteBit(guid[0]);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[4]);
    data.WriteBit(guid[1]);
    data.WriteBits(items->size(), 22);
    data.WriteBit(guid[6]);
    data.FlushBits();

    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid[2]);
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid[5]);
    for (std::map<uint8, uint32>::const_iterator itr = items->begin(); itr != items->end(); itr++)
        data << (uint32)itr->second;
    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[3]);
    data.WriteByteSeq(guid[4]);

    m_session->SendPacket(&data);
}

uint32 CharacterBooster::_PrepareMail(SQLTransaction& trans, std::string const& subject, std::string const& body) const
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_MAIL);
    uint32 mailId = sObjectMgr->GenerateMailID();
    stmt->setUInt32(0, mailId);
    stmt->setUInt8(1, MAIL_NORMAL);
    stmt->setInt8(2, MAIL_STATIONERY_DEFAULT);
    stmt->setUInt16(3, 0);
    stmt->setUInt32(4, m_charBoostInfo.lowGuid);
    stmt->setUInt32(5, m_charBoostInfo.lowGuid);
    stmt->setString(6, subject);
    stmt->setString(7, body);
    stmt->setBool(8, true);
    stmt->setUInt64(9, time(NULL) + 180 * DAY);
    stmt->setUInt64(10, time(NULL)); // send immediatly
    stmt->setUInt32(11, 0);
    stmt->setUInt32(12, 0);
    stmt->setUInt8(13, 0);
    trans->Append(stmt);

    return mailId;
}

void CharacterBooster::_SendMail(SQLTransaction& trans, std::vector<uint32> const& items) const
{
    if (items.empty())
        return;

    uint32 mailId = _PrepareMail(trans, "", "");
    PreparedStatement* stmt = NULL;

    for (uint8 i = 0; i < items.size(); i++)
    {
        if (Item* item = Item::CreateItem(items[i], 1, m_charBoostInfo.charGuid))
        {
            item->SaveToDB(trans);
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_MAIL_ITEM);
            stmt->setUInt32(0, mailId);
            stmt->setUInt32(1, item->GetGUIDLow());
            stmt->setUInt32(2, m_charBoostInfo.lowGuid);
            trans->Append(stmt);
        }
    }
}

void CharacterBooster::_MailEquipedItems(SQLTransaction& trans) const
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_INVENTORY_ITEM_GUID_UNTIL_BAG_SLOT);
    stmt->setUInt32(0, 0);
    stmt->setUInt8(1, EQUIPMENT_SLOT_END);
    stmt->setUInt32(2, m_charBoostInfo.lowGuid);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
        return;

    uint32 mailId = _PrepareMail(trans, CHARRACTER_BOOST_EQUIPED_ITEMS_MAIL_SUBJECT, CHARRACTER_BOOST_EQUIPED_ITEMS_MAIL_BODY);

    do
    {
        uint32 itemGuid = (*result)[0].GetUInt32();
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_MAIL_ITEM);
        stmt->setUInt32(0, mailId);
        stmt->setUInt32(1, itemGuid);
        stmt->setUInt32(2, m_charBoostInfo.lowGuid);
        trans->Append(stmt);
    } while (result->NextRow());

    // unEquip after sending
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_INVENTORY_UNTIL_BAG_SLOT);
    stmt->setUInt32(0, 0);
    stmt->setUInt8(1, EQUIPMENT_SLOT_END);
    stmt->setUInt32(2, m_charBoostInfo.lowGuid);
    trans->Append(stmt);
}

void CharacterBooster::_HandleCharacterBoost()
{
    uint32& lowGuid = m_charBoostInfo.lowGuid;
    uint8 charRace = 0;

    uint32 const* languageSpells = NULL;
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_RACE);
    stmt->setUInt32(0, lowGuid);
    if (PreparedQueryResult result = CharacterDatabase.Query(stmt))
    {
        charRace = (*result)[0].GetUInt8();
        if (charRace == RACE_PANDAREN_NEUTRAL)
        {
            if (m_charBoostInfo.allianceFaction)
            {
                charRace = RACE_PANDAREN_ALLIANCE;
                languageSpells = pandarenLanguageSpellsAlliance;
            }
            else
            {
                charRace = RACE_PANDAREN_HORDE;
                languageSpells = pandarenLanguageSpellsHorde;
            }
        }
    }

    if (!charRace)
        return;

    std::vector<uint32> itemsToMail;
    SlotEquipmentMap const* itemsToEquip = _GetCharBoostItems(itemsToMail);
    if (!itemsToEquip)
        return;

    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    _MailEquipedItems(trans);
    _SendMail(trans, itemsToMail);

    std::map<uint8, uint32>::const_iterator itr;
    std::ostringstream items;
    for (uint8 i = 0; i < EQUIPMENT_SLOT_END; i++)
    {
        itr = itemsToEquip->find(i);
        if (itr != itemsToEquip->end())
        {
            if (Item* item = Item::CreateItem(itr->second, 1, m_charBoostInfo.charGuid))
            {
                item->SaveToDB(trans);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CHAR_INVENTORY);
                stmt->setUInt32(0, lowGuid);
                stmt->setUInt32(1, 0);
                stmt->setUInt8(2, itr->first);
                stmt->setUInt32(3, item->GetGUIDLow());
                trans->Append(stmt);

                items << (itr->second) << " 0 ";
            }
            else
                items << "0 0 ";
        }
        else
            items << "0 0 ";
    }

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHARACTER_FOR_BOOST);
    stmt->setUInt8(0, charRace);
    stmt->setString(1, items.str());
    stmt->setUInt32(2, lowGuid);
    trans->Append(stmt);

    if (languageSpells)
    {
        for (uint8 i = 0; i < PANDAREN_FACTION_LANGUAGE_COUNT; i++)
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CHAR_SPELL);
            stmt->setUInt32(0, lowGuid);
            stmt->setUInt32(1, languageSpells[i]);
            stmt->setBool(2, 1);
            stmt->setBool(3, 0);
            trans->Append(stmt);
        }
    }

    CharacterDatabase.CommitTransaction(trans);
    _SendCharBoostPacket(itemsToEquip);
}

void CharacterBooster::HandleCharacterBoost()
{
    if (!m_charBoostInfo.charGuid)
        return;

    switch (m_charBoostInfo.action)
    {
        case CHARACTER_BOOST_ITEMS:
            m_session->SendBattlePayDistributionUpdate(m_charBoostInfo.charGuid, CHARACTER_BOOST, m_charBoostInfo.action,
                CHARACTER_BOOST_TEXT_ID, CHARACTER_BOOST_BONUS_TEXT, CHARACTER_BOOST_BONUS_TEXT2);
            m_charBoostInfo.action = CHARACTER_BOOST_APPLIED;
            m_timer = 500;
            m_sendPacket = true;
            break;
        case CHARACTER_BOOST_APPLIED:
            m_session->SendBattlePayDistributionUpdate(m_charBoostInfo.charGuid, CHARACTER_BOOST, m_charBoostInfo.action,
                CHARACTER_BOOST_TEXT_ID, CHARACTER_BOOST_BONUS_TEXT, CHARACTER_BOOST_BONUS_TEXT2);
            m_charBoostInfo = CharacterBoostData();
            break;
        default:
            break;
    }
}

void CharacterBooster::SetBoostedCharInfo(uint64 guid, uint32 action, uint32 specialization, bool allianceFaction)
{
    m_boosting = true;
    m_charBoostInfo.charGuid = guid;
    m_charBoostInfo.lowGuid = GUID_LOPART(guid);
    m_charBoostInfo.action = action;
    m_charBoostInfo.specialization = specialization;
    m_charBoostInfo.allianceFaction = allianceFaction;
}

void CharacterBooster::Update(uint32 diff)
{
    if (m_sendPacket)
    {
        if (m_timer <= diff)
        {
            m_sendPacket = false;
            _HandleCharacterBoost();
        }
        else
            m_timer -= diff;
    }
}

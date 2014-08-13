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

#include "BattleShop.h"
#include "WorldSession.h"

void WorldSession::SetBoosting(bool boost, bool saveToDB)
{
    m_hasBoost = boost;

    if (!saveToDB)
        return;

    PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_ACCOUNT_BOOST);
    stmt->setBool(0, boost);
    stmt->setUInt32(1, _accountId);
    LoginDatabase.Execute(stmt);
}

void WorldSession::SendBattlePayDistributionUpdate(uint64 playerGuid, int8 bonusId, int32 bonusFlag, int32 textId, std::string const& bonusText, std::string const& bonusText2)
{
    ObjectGuid guid = GUID_LOPART(playerGuid);
    ObjectGuid guid2 = 0;

    WorldPacket data(SMSG_BATTLE_PAY_DISTRIBUTION_UPDATE, 8 + 4 + 8 + bonusText.length() + bonusText2.length() + 8 + 1 + 4 + 4 + 8 + 4 + 4 + 4);
    data.WriteBit(guid2[5]);
    data.WriteBit(guid2[0]);
    data.WriteBit(1); // unkBool
    data.WriteBit(guid2[1]);
    data.WriteBit(guid[4]);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[0]);
    data.WriteBit(0);
    data.WriteBit(guid[1]);
    data.WriteBit(guid[2]);
    // if (unkBool)
    // {
        data.WriteBits(1, 2);
        data.WriteBits(0, 20);
        data.WriteBit(1); // bool4
        // if (bool4)
        // {
            data.WriteBits(0, 10);
            data.WriteBit(0);
            data.WriteBits(bonusText2.length(), 10);
            data.WriteBit(0);
            data.WriteBit(0);
            data.WriteBits(bonusText.length(), 13);
            data.WriteBit(0); // bool11
        // }
    // }

    data.WriteBit(guid2[7]);
    data.WriteBit(guid[6]);
    data.WriteBit(guid2[2]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid2[3]);
    data.WriteBit(guid2[6]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid2[4]);
    data.FlushBits();

    // if (unkBool)
    // {
        data << int32(0);
        data << int64(0);
        data.WriteString(bonusText);
        data.WriteString(bonusText2);
        // if (bool11)
            //data << int32(0);
        data << int64(0);
        data << int8(bonusId);
        data << int32(0);
    // }

    data << int32(textId);
    data.WriteByteSeq(guid[4]);
    data << int64(0);
    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid2[2]);
    data.WriteByteSeq(guid2[4]);
    data.WriteByteSeq(guid2[1]);
    data.WriteByteSeq(guid2[0]);
    data << int32(0);
    data.WriteByteSeq(guid2[7]);
    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[7]);
    data << int32(0);
    data << int32(bonusFlag);
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid2[5]);
    data.WriteByteSeq(guid2[6]);
    data.WriteByteSeq(guid2[3]);
    data.WriteByteSeq(guid[3]);
    data.WriteByteSeq(guid[2]);

    SendPacket(&data);
}

void WorldSession::HandleBattleCharBoost(WorldPacket& recvData)
{
    if (!HasBoost())
    {
        TC_LOG_ERROR("network", "WorldSession::HandleBattleCharBoost called, but player has not allowed boost");
        recvData.rfinish();
        return;
    }

    ObjectGuid playerGuid, guid;
    bool hasCharInfo = false;

    recvData.read_skip<uint32>();
    guid[1] = recvData.ReadBit();
    playerGuid[0] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    playerGuid[3] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    playerGuid[5] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    playerGuid[1] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    playerGuid[2] = recvData.ReadBit();
    hasCharInfo = !recvData.ReadBit();
    playerGuid[7] = recvData.ReadBit();
    playerGuid[4] = recvData.ReadBit();
    playerGuid[6] = recvData.ReadBit();

    recvData.ReadByteSeq(playerGuid[2]);
    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(playerGuid[0]);
    recvData.ReadByteSeq(playerGuid[7]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(playerGuid[3]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(playerGuid[1]);
    recvData.ReadByteSeq(playerGuid[6]);
    recvData.ReadByteSeq(playerGuid[4]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(playerGuid[5]);

    if (hasCharInfo)
    {
        uint32 charInfo;
        recvData >> charInfo;

        SendBattlePayDistributionUpdate(playerGuid, CHARACTER_BOOST, CHARACTER_BOOST_CHOOSED, CHARACTER_BOOST_TEXT_ID, CHARACTER_BOOST_BONUS_TEXT, CHARACTER_BOOST_BONUS_TEXT2);
        m_charBooster->SetBoostedCharInfo(playerGuid, CHARACTER_BOOST_ITEMS, (charInfo & CHARACTER_BOOST_SPEC_MASK), (charInfo & CHARACTER_BOOST_FACTION_ALLIANCE));

        WorldPacket data(SMSG_BATTLE_CHAR_BOOST, 8);
        data.WriteBit(playerGuid[6]);
        data.WriteBit(playerGuid[2]);
        data.WriteBit(playerGuid[5]);
        data.WriteBit(playerGuid[4]);
        data.WriteBit(playerGuid[7]);
        data.WriteBit(playerGuid[0]);
        data.WriteBit(playerGuid[3]);
        data.WriteBit(playerGuid[1]);
        data.WriteByteSeq(playerGuid[4]);
        data.WriteByteSeq(playerGuid[1]);
        data.WriteByteSeq(playerGuid[6]);
        data.WriteByteSeq(playerGuid[0]);
        data.WriteByteSeq(playerGuid[7]);
        data.WriteByteSeq(playerGuid[5]);
        data.WriteByteSeq(playerGuid[2]);
        data.WriteByteSeq(playerGuid[3]);

        SendPacket(&data);
    }
}

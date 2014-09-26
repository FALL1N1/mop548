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

#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"
#include "Item.h"

void WorldSession::SendItemUpgradeResult(uint32 result)
{
    TC_LOG_DEBUG("network", "WORLD: SMSG_ITEM_UPGRADE_RESULT");

    WorldPacket data(SMSG_ITEM_UPGRADE_RESULT, 4);
    data << uint32(result);
    SendPacket(&data);

    TC_LOG_DEBUG("network", "WORLD: SendItemUpgradeResult result: %u", result);
}

void WorldSession::HandleUpgradeItem(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_UPGRADE_ITEM");

    uint32 pos, unk40, Ilvl;


    ObjectGuid guid, guid2;
    Player* player = GetPlayer();

    recvData >> pos >> unk40 >> Ilvl;

    guid2[5] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid2[6] = recvData.ReadBit();
    guid2[0] = recvData.ReadBit();
    guid2[1] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid2[7] = recvData.ReadBit();
    guid2[2] = recvData.ReadBit();
    guid2[3] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid2[4] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();

    recvData.ReadByteSeq(guid2[7]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid2[6]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid2[5]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid2[1]);
    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid2[2]);
    recvData.ReadByteSeq(guid2[0]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid2[3]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid2[4]);

    TC_LOG_DEBUG("network", "WORLD: HandleUpgradeItem unk36: %u, unk40: %u, unk32: %u", pos, unk40, Ilvl);

    SendItemUpgradeResult(true);
}
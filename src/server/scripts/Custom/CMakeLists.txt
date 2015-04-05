# Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

file(GLOB_RECURSE scripts_Custom Custom/*.cpp Custom/*.h)
source_group(Custom FILES ${scripts_Custom})

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  ${scripts_Custom}
custom/chatter.cpp
custom/DuelReset.cpp
custom/Gossip_CheckCombat.cpp
custom/morphs_npc.cpp
custom/npc_changer.cpp
custom/Protection_Script.cpp
custom/teleporter.cpp
custom/top5killers.cpp
custom/vanilla_title_npc.cpp
custom/vip.cpp
custom/your_token_item.cpp
)

message("  -> Prepared: Custom")

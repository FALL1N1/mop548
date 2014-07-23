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

SlotEquipmentMap const deathKnightEquipmentBlood =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 100996 },
    { (uint8)EQUIPMENT_SLOT_NECK, 100998 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101003 },
    { (uint8)EQUIPMENT_SLOT_BACK, 100993 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 100992 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101005 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 100995 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101004 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 100997 },
    { (uint8)EQUIPMENT_SLOT_FEET, 100994 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101000 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101001 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 100999 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101002 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 100976 }
};

SlotEquipmentMap const deathKnightEquipmentFrost =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 100980 },
    { (uint8)EQUIPMENT_SLOT_NECK, 100987 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 100982 },
    { (uint8)EQUIPMENT_SLOT_BACK, 100986 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 100977 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 100984 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 100979 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 100983 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 100981 },
    { (uint8)EQUIPMENT_SLOT_FEET, 100978 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 100988 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 100989 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 100990 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 100991 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 100976 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 100976 }
};

SlotEquipmentMap const deathKnightEquipmentUnholy =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 100980 },
    { (uint8)EQUIPMENT_SLOT_NECK, 100987 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 100982 },
    { (uint8)EQUIPMENT_SLOT_BACK, 100986 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 100977 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 100984 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 100979 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 100983 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 100981 },
    { (uint8)EQUIPMENT_SLOT_FEET, 100978 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 100988 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 100989 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 100990 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 100991 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101006 }
};

SlotEquipmentMap const druidEquipmentBalance =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101016 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101022 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101018 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101042 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101013 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101021 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101045 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101020 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101017 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101014 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101025 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101024 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101026 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101023 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101019 }
};

SlotEquipmentMap const druidEquipmentFeral =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101030 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101008 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101033 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101007 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101027 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101035 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101029 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101034 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101031 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101028 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101011 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101010 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101012 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101009 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101032 }
};

SlotEquipmentMap const druidEquipmentRestoration =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101046 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101037 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101048 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101036 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101043 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101050 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101015 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101049 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101047 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101044 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101040 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101039 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101041 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101038 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101051 }
};

SlotEquipmentMap const hunterEquipment =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101061 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101053 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101063 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101052 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101058 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101065 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101060 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101064 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101062 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101059 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101055 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101056 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101054 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101057 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101066 }
};

SlotEquipmentMap const mageEquipment = 
{
    { (uint8)EQUIPMENT_SLOT_NECK, 101068 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101069 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101070 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101071 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101072 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101073 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101074 },
    { (uint8)EQUIPMENT_SLOT_HEAD, 101075 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101076 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101077 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101078 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101079 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101080 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101082 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101083 }
};

SlotEquipmentMap const monkEquipmentBrewmaster =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101093 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101084 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101095 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101118 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101090 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101097 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101092 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101096 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101094 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101091 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101086 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101085 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101087 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101089 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101088 }
};

SlotEquipmentMap const monkEquipmentMistweaver =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101100 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101104 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101108 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101101 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101119 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101111 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101099 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101110 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101103 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101098 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101105 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101106 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101102 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101107 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101109 }
};

SlotEquipmentMap const monkEquipmentWindwalker =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101093 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101114 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101095 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101118 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101090 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101097 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101092 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101096 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101094 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101091 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101116 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101115 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101113 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101117 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101112 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101112 }
};

SlotEquipmentMap const paladinEquipmentHoly =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101132 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101134 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101139 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101129 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101128 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101141 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101131 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101140 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101133 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101130 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101136 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101137 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101135 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101138 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101142 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101143 }
};

SlotEquipmentMap const paladinEquipmentProtection =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101157 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101159 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101164 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101154 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101153 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101166 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101156 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101165 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101158 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101155 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101161 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101162 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101160 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101163 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101144 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101145 }
};

SlotEquipmentMap const paladinEquipmentRetribution =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101123 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101148 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101125 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101147 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101120 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101127 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101122 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101126 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101124 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101121 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101149 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101150 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101151 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101152 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101146 }
};

SlotEquipmentMap const priestEquipmentDisciplineAndHoly =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101191 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101178 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101184 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101173 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101182 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101186 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101190 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101185 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101192 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101174 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101180 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101181 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101179 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101183 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101187 }
};

SlotEquipmentMap const priestEquipmentShadow =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101176 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101167 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101194 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101188 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101193 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101196 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101175 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101195 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101177 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101189 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101169 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101170 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101171 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101168 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101197 }
};

SlotEquipmentMap const rogueEquipmentAssassionation =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101207 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101199},
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101209 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101198 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101204 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101211 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101206 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101210 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101208 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101205 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101201 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101202 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101200 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101203 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101214 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101214 }
};

SlotEquipmentMap const rogueEquipmentCombat =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101207 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101199 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101209 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101198 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101204 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101211 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101206 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101210 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101208 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101205 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101201 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101202 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101200 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101203 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101213 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101213 }
};

SlotEquipmentMap const rogueEquipmentSubtlety =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101207 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101199 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101209 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101198 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101204 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101211 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101206 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101210 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101208 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101205 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101201 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101202 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101200 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101203 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101212 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101212 }
};

SlotEquipmentMap const shamanEquipmentElemental =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101230 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101221 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101233 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101251 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101227 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101235 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101255 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101234 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101257 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101254 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101223 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101224 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101222 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101225 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101226 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101232 }
};

SlotEquipmentMap const shamanEquipmentEnhancement =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101240 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101216 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101242 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101215 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101237 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101244 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101239 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101243 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101241 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101238 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101218 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101219 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101217 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101220 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101236 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101236 }
};

SlotEquipmentMap const shamanEquipmentRestoration =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101256 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101246 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101259 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101245 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101253 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101261 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101229 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101260 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101231 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101228 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101249 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101248 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101247 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101250 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101252 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101258 }
};

SlotEquipmentMap const warlockEquipment =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101269 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101262 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101272 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101276 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101271 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101274 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101268 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101273 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101270 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101267 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101264 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101265 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101266 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101263 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101277 }
};

SlotEquipmentMap const warriorEquipmentArms =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101282 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101291 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101284 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101290 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101279 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101286 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101281 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101285 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101283 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101280 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101292 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101293 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101294 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101295 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101278 }
};

SlotEquipmentMap const warriorEquipmentFury =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101282 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101291 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101284 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101290 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101279 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101286 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101281 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101285 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101283 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101280 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101292 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101293 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101294 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101295 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101287 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101287 }
};

SlotEquipmentMap const warriorEquipmentProtection =
{
    { (uint8)EQUIPMENT_SLOT_HEAD, 101300 },
    { (uint8)EQUIPMENT_SLOT_NECK, 101302 },
    { (uint8)EQUIPMENT_SLOT_SHOULDERS, 101307 },
    { (uint8)EQUIPMENT_SLOT_BACK, 101297 },
    { (uint8)EQUIPMENT_SLOT_CHEST, 101296 },
    { (uint8)EQUIPMENT_SLOT_WRISTS, 101309 },
    { (uint8)EQUIPMENT_SLOT_HANDS, 101299 },
    { (uint8)EQUIPMENT_SLOT_WAIST, 101308 },
    { (uint8)EQUIPMENT_SLOT_LEGS, 101301 },
    { (uint8)EQUIPMENT_SLOT_FEET, 101298 },
    { (uint8)EQUIPMENT_SLOT_FINGER1, 101305 },
    { (uint8)EQUIPMENT_SLOT_FINGER2, 101304 },
    { (uint8)EQUIPMENT_SLOT_TRINKET1, 101303 },
    { (uint8)EQUIPMENT_SLOT_TRINKET2, 101306 },
    { (uint8)EQUIPMENT_SLOT_MAINHAND, 101288 },
    { (uint8)EQUIPMENT_SLOT_OFFHAND, 101289 }
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
    CHAR_SPECIALIZATION_DRUID_FERAL             = 103,
    CHAR_SPECIALIZATION_DRUID_GUARDIAN          = 104,
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
    CHAR_SPECIALIZATION_MONK_WINDWALKER         = 269,
    CHAR_SPECIALIZATION_MONK_MISTWEAVER         = 270
};

#define CHARRACTER_BOOST_EQUIPED_ITEMS_MAIL_BODY "We've supplied you with a whole new set of high-level gear, but attached you'll find all the old items and equipment you once carried.\n\n - The WoW Dev Team"
#define CHARRACTER_BOOST_EQUIPED_ITEMS_MAIL_SUBJECT "Character Boost"

enum CharBoostMisc
{
    // items
    EMBERSILK_BAG_ID                = 54443,
    EMBERSILK_BAG_COUNT             = 4,
    LEMON_FLAVOUR_PUDING_ID         = 108920,
    LEMON_FLAVOUR_PUDING_COUNT      = 20,

    // spells
    PLATE_MAIL_ARMOR_SPELL          = 750,
    SWIFT_PURPLE_WIND_RIDER_SPELL   = 32297,
    SWIFT_PURPLE_GRYPGON_SPELL      = 32292,

    // misc
    VALE_OF_ETERNAL_BLOSSOMS_MAP_ID = 870
};

std::vector<uint32> const CharBoostSpells = 
{
    34091,  // Artisan Riding
    54197,  // ColdWeather Flying
    90267,  // Flight Master License
    115913  // Wisdom of the Four Winds
};

float const hordeStartPosition[] =
{
    1605.908f,  // position x
    921.2222f,  // position y
    470.6227f,  // position z
    0.124413f   // orientation
};

float const allianceStartPosition[] =
{
    880.6965f,  // position x
    296.6945f,  // position y
    503.1162f,  // position z
    3.779655f   // orientation
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
        SlotEquipmentMap const* _GetCharBoostItems(std::vector<std::pair<uint32, uint32> >& itemsToMail) const;
        std::string _EquipItems(SQLTransaction& trans, SlotEquipmentMap const* itemsToEquip) const;
        uint8 _GetRace() const;
        void _HandleCharacterBoost();
        void _LearnSpells(SQLTransaction& trans, uint8 const& raceId, uint8 const& classId) const;
        void _MailEquipedItems(SQLTransaction& trans) const;
        uint32 _PrepareMail(SQLTransaction& trans, std::string const& subject, std::string const& body) const;
        std::string _SetSpecialization(SQLTransaction& trans, uint8 const& classId) const;
        void _SaveBoostedChar(SQLTransaction& trans, std::string const& items, uint8 const& raceId, uint8 const& classId);
        void _SendMail(SQLTransaction& trans, std::vector<std::pair<uint32, uint32> > const& items) const;
        void _SendCharBoostPacket(SlotEquipmentMap const* items);

        CharacterBoostData m_charBoostInfo;
        WorldSession* m_session;
        uint32 m_timer;
        bool m_boosting;
        bool m_sendPacket;
};

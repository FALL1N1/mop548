DELETE FROM `spell_script_names` WHERE `spell_id` IN (42955, 43987, 86949, 11426, 115610, 140468, 82691, 136511, 140376, 116, 44614,
84721, 42208, 44544, 30455, 44572, 11129, 44457, 133, 11366, 108853, 2948, 76613, 148023, 31707);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('42955','spell_mage_conjure_refreshment'),
('43987','spell_mage_conjure_refreshment_table'),
('86949','spell_mage_cauterize'),
('11426','spell_mage_ice_barrier'),
('115610','spell_mage_temporal_shield'),
('140468','spell_mage_flameglow'),
('82691','spell_mage_ring_of_frost_freeze'),
('136511','spell_mage_ring_of_frost_periodic'),
('140376','spell_mage_ring_of_frost_instant'),
('116','spell_mage_frostbolt'),
('44614','spell_mage_frostfire_bolt'),
('84721','spell_mage_frozen_orb_dmg'),
('42208','spell_mage_blizzard_dmg'),
('44544','spell_mage_fingers_of_frost_proc'),
('30455','spell_mage_ice_lance'),
('44572','spell_mage_deep_freeze'),
('11129', 'spell_mage_combustion'),
('44457', 'spell_mage_living_bomb'),
('133', 'spell_mage_mastery_ignite'),
('11366', 'spell_mage_mastery_ignite'),
('2948', 'spell_mage_mastery_ignite'),
('44614', 'spell_mage_mastery_ignite'),
('108853', 'spell_mage_mastery_ignite'),
('76613', 'spell_mage_mastery_icicles'),
('148023', 'spell_mage_icicle_trigger'),
('31707', 'spell_mage_waterbolt');

-- Ring of Frost
UPDATE `creature_template` SET `modelid1`=13069, `faction_A`=5, `faction_H`=5, `unit_flags`=33947724, `unit_flags2`=32768 WHERE `entry`=44199;
-- Frozen Orb
UPDATE `creature_template` SET `modelid1`=41204, `name`='Frozen Orb', `faction_A`=5, `faction_H`=5, `unit_flags`=33947724, `unit_flags2`=32768, `type_flags`=16778240, `ScriptName`='npc_mage_frozen_orb' WHERE `entry`=45322;

DELETE FROM `spell_bonus_data` WHERE `entry` IN (30455, 84721, 148022);
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('30455','0.335','-1','-1','-1','Mage - Ice Lance'),
('84721','0.511','-1','-1','-1','Mage - Frozen Orb'),
('148022','0','0','0','0','Icicle');

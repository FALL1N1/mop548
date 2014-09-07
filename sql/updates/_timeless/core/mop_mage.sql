DELETE FROM `spell_script_names` WHERE `spell_id` IN (42955, 43987, 86949, 11426, 115610, 140468, 82691, 136511, 140376);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('42955','spell_mage_conjure_refreshment'),
('43987','spell_mage_conjure_refreshment_table'),
('86949','spell_mage_cauterize'),
('11426','spell_mage_ice_barrier'),
('115610','spell_mage_temporal_shield'),
('140468','spell_mage_flameglow'),
('82691','spell_mage_ring_of_frost_freeze'),
('136511','spell_mage_ring_of_frost_periodic'),
('140376','spell_mage_ring_of_frost_instant');

-- Ring of Frost
UPDATE `creature_template` SET `modelid1`=13069, `faction_A`=5, `faction_H`=5, `unit_flags`=33947724, `unit_flags2`=32768 WHERE `entry`=44199;

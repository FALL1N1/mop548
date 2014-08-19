-- Lava Burst
DELETE FROM `spell_script_names` WHERE `spell_id` = 51505;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(51505, "spell_sha_lava_burst");

-- Talent Frozen Power
DELETE FROM `spell_script_names` WHERE `spell_id` = 8056;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(8056, "spell_sha_frost_shock");
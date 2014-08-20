-- Talent Body and Soul
DELETE FROM `spell_script_names` WHERE `spell_id` IN (17, 73325);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(17, "spell_pri_power_word_shield"),
(73325, "spell_pri_leap_of_faith");

-- Angelic Bulwark
DELETE FROM `spell_script_names` WHERE `spell_id` = 108945;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(108945, "spell_pri_angelic_bulwark");

DELETE FROM `spell_proc_event` WHERE `entry` = 108945;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `SpellFamilyMask3`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(108945, 0, 0, 0, 0, 0, 0, 0x000A22A8, 0, 0, 0, 0);

-- Twist of Fate
DELETE FROM `spell_script_names` WHERE `spell_id`=109142;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(109142, 'spell_pri_twist_of_fate');

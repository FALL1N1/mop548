DELETE FROM `spell_script_names` WHERE `spell_id` IN (20473, 19750);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('20473','spell_pal_holy_shock'),
('19750', 'spell_pal_selfless_healer');

DELETE FROM `spell_proc_event` WHERE `entry` IN (114250);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
('114250', '0', '10', '1073741824', '0', '0', '16384', '0', '0', '100', '0');

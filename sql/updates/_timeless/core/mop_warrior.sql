-- Ultimatum
DELETE FROM `spell_proc_event` WHERE `entry` IN (122509, -122509);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `SpellFamilyMask3`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(122509, 0, 4, 0, 0x00000200, 0, 0, 0x00000010, 0x0000002, 0, 0, 0);

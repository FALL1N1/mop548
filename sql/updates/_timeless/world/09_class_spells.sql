DELETE FROM `spell_bonus_data` WHERE `entry` IN (115767, 2098);
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('115767', '1.2', '-1', '-1', '0.24', 'Warrior - Deep Wounds'),
('2098', '0', '0', '0', '0', 'Rogue - Eviscerate');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (20243, 2565, 1784, 16511, 121411, 5938, 2823, 3408, 5761, 8679, 108211, 108215,
1943, 2098, 73651, 5171, 408, 115834, 113952);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('20243', 'spell_warr_sword_and_board'),
('2565', 'spell_warr_shield_block'),
('1784', 'spell_rog_nightstalker'),
('16511', 'spell_rog_hemorrhage'),
('121411', 'spell_rog_crimson_tempest'),
('5938', 'spell_rog_shiv'),
('2823', 'spell_rog_poisons'),
('3408', 'spell_rog_poisons'),
('5761', 'spell_rog_poisons'),
('8679', 'spell_rog_poisons'),
('108211', 'spell_rog_poisons'),
('108215', 'spell_rog_poisons'),
('115834', 'spell_rog_shroud_of_concealment'),
('2098', 'spell_rog_evescerate'),
('113952', 'spell_rog_paralytic_poison');

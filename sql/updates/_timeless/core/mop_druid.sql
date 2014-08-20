-- Glyph of the Treant
DELETE FROM `spell_script_names` WHERE `spell_id`=125047;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(125047, 'spell_druid_glyph_of_the_treant');

-- Incarnation
DELETE FROM `spell_script_names` WHERE `spell_id` IN (102543, 102560, 102558);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(102543, 'spell_druid_incarnation_king_of_the_jungle'),
(102560, 'spell_druid_incarnation_chosen_of_elune'),
(102558, 'spell_druid_incarnation_son_of_ursoc');

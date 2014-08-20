-- Glyph of the Treant
DELETE FROM `spell_script_names` WHERE `spell_id`=125047;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(125047, 'spell_druid_glyph_of_the_treant');

-- Incarnation
DELETE FROM `spell_script_names` WHERE `spell_id` IN (102543, 102560, 102558);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(102543, 'spell_druid_incarnation'), -- Incarnation: King of the Jungle
(102560, 'spell_druid_incarnation'), -- Incarnation: Chosen of Elune
(102558, 'spell_druid_incarnation'); -- Incarnation: Son of Ursoc

-- Cobra Shot
DELETE FROM `spell_script_names` WHERE `spell_id` = '77767';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('77767', "spell_hun_cobra_shot");

-- Chimera Shot
DELETE FROM `spell_script_names` WHERE `spell_id` = '53209';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('53209', "spell_hun_chimera_shot");

-- Steady Shot
DELETE FROM `spell_script_names` WHERE `spell_id` = '56641';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('56641', "spell_hun_steady_shot");

-- Camouflage
DELETE FROM `spell_script_names` WHERE `spell_id`= '51753' OR `ScriptName`='spell_hun_camouflage';
INSERT INTO `spell_script_names` VALUES
('51753','spell_hun_camouflage');

DELETE FROM `spell_script_names` WHERE `spell_id`= '51755' OR `ScriptName`='spell_hun_camouflage_aura';
INSERT INTO `spell_script_names` VALUES
('51755','spell_hun_camouflage_aura');

DELETE FROM `spell_script_names` WHERE `spell_id`= '80326' OR `ScriptName`='spell_hun_camouflage_visual';
INSERT INTO `spell_script_names` VALUES
('80326','spell_hun_camouflage_visual');

-- Talent Narrow Escape and Prohaste
DELETE FROM `spell_script_names` WHERE `spell_id` IN ('781', '115928');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('781', "spell_hun_disengage"),
('115928', "spell_hun_narrow_escape");

DELETE FROM `spell_script_names` WHERE `spell_id`= '55709';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('55709', 'spell_hun_pet_heart_of_the_phoenix');
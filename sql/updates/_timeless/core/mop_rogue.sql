-- Smoke Bomb
DELETE FROM `spell_script_names` WHERE `spell_id`=76577;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(76577, 'spell_rog_smoke_bomb');

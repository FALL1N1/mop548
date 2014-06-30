ALTER TABLE `character_achievement` ADD COLUMN `accountID` INT(10) NOT NULL AFTER `achievement`;

UPDATE `character_achievement` SET `accountID` = (SELECT `account` FROM `characters` WHERE characters.guid = character_achievement.guid LIMIT 1);

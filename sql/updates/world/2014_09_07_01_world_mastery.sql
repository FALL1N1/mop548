SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for masteries
-- ----------------------------
DROP TABLE IF EXISTS `masteries`;
CREATE TABLE `masteries` (
  `ID` int(11) NOT NULL,
  `base` float NOT NULL,
  `ratio` float NOT NULL,
  `commentaire` text NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of masteries
-- ----------------------------
INSERT INTO `masteries` VALUES
('71', '17.6', '272.7', 'Warrior - Arms'),
('72', '11.2', '428.6', 'Warrior - Fury'),
('73', '17.6', '272.7', 'Warrior - Protection'),
('65', '12', '400', 'Paladin - Holy'),
('66', '8', '600', 'Paladin - Protection'),
('70', '14.8', '324.5', 'Paladin - Retribution'),
('253', '10', '480', 'Hunter - Beast Mastery'),
('254', '16', '300', 'Hunter - Marksmanship'),
('255', '16', '300', 'Hunter - Survival'),
('259', '28', '171.4', 'Rogue - Assassination'),
('260', '16', '300', 'Rogue - Combat'),
('261', '24', '200', 'Rogue - Subtlety'),
('256', '12.8', '375', 'Priest - Discipline'),
('257', '10', '480', 'Priest - Holy'),
('258', '14.4', '333.5', 'Priest - Shadow'),
('250', '50', '96', 'Death Knight - Blood'),
('251', '16', '300', 'Death Knight - Frost'),
('252', '20', '240', 'Death Knight - Unholy'),
('262', '16', '300', 'Shaman - Elemental'),
('263', '16', '300', 'Shaman - Enhancement'),
('264', '24', '200', 'Shaman - Restoration'),
('62', '16', '300', 'Mage - Arcane'),
('63', '12', '400', 'Mage - Fire'),
('64', '16', '300', 'Mage - Frost'),
('265', '24.8', '193', 'Warlock - Affliction'),
('266', '8', '600', 'Warlock - Demonology'),
('267', '24', '200', 'Warlock - Destruction'),
('268', '5', '960', 'Monk - Brewmaster'),
('270', '9.6', '500', 'Monk - Mistweaver'),
('269', '1.6', '3000', 'Monk - WindWalker'),
('102', '15', '320', 'Druid - Balance'),
('103', '25.04', '191.7', 'Druid - Feral'),
('104', '16', '300', 'Druid - Guardian'),
('105', '10', '480', 'Druid - Restoration');
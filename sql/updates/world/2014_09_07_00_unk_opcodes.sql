SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for unk_opcodes
-- ----------------------------
DROP TABLE IF EXISTS `unk_opcodes`;
CREATE TABLE `unk_opcodes` (
  `id` varchar(16) NOT NULL,
  `type` varchar(255) DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

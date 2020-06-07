-- MySQL dump 10.13  Distrib 5.6.23, for Win32 (x86)
--
-- Host: 127.0.0.1    Database: spaceinvaders_local
-- ------------------------------------------------------
-- Server version	5.5.5-10.4.11-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `spaceinvaders_entity_highscore`
--

DROP TABLE IF EXISTS `spaceinvaders_entity_highscore`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spaceinvaders_entity_highscore` (
  `highscore_id` int(10) NOT NULL AUTO_INCREMENT,
  `highscore` int(10) DEFAULT NULL,
  PRIMARY KEY (`highscore_id`)
) ENGINE=InnoDB AUTO_INCREMENT=32 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spaceinvaders_entity_highscore`
--

LOCK TABLES `spaceinvaders_entity_highscore` WRITE;
/*!40000 ALTER TABLE `spaceinvaders_entity_highscore` DISABLE KEYS */;
INSERT INTO `spaceinvaders_entity_highscore` VALUES (1,0),(2,100),(3,200),(4,300),(5,400),(6,500),(7,600),(8,700),(9,800),(10,900),(11,1000),(12,1100),(13,1200),(14,1300),(15,1400),(16,1500),(17,1600),(18,1700),(19,1800),(20,1900),(21,2000),(22,2100),(23,2200),(24,2300),(25,2400),(26,2500),(27,2600),(28,2700),(29,2800),(30,2900),(31,3000);
/*!40000 ALTER TABLE `spaceinvaders_entity_highscore` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `spaceinvaders_entity_player`
--

DROP TABLE IF EXISTS `spaceinvaders_entity_player`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spaceinvaders_entity_player` (
  `plyr_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`plyr_id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spaceinvaders_entity_player`
--

LOCK TABLES `spaceinvaders_entity_player` WRITE;
/*!40000 ALTER TABLE `spaceinvaders_entity_player` DISABLE KEYS */;
INSERT INTO `spaceinvaders_entity_player` VALUES (1,'Chris'),(2,'Brandon'),(3,'Matt'),(4,'Martin'),(5,'Ian');
/*!40000 ALTER TABLE `spaceinvaders_entity_player` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `spaceinvaders_entity_ship`
--

DROP TABLE IF EXISTS `spaceinvaders_entity_ship`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spaceinvaders_entity_ship` (
  `ship_id` int(10) NOT NULL AUTO_INCREMENT,
  `id_color` int(10) DEFAULT NULL,
  PRIMARY KEY (`ship_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spaceinvaders_entity_ship`
--

LOCK TABLES `spaceinvaders_entity_ship` WRITE;
/*!40000 ALTER TABLE `spaceinvaders_entity_ship` DISABLE KEYS */;
INSERT INTO `spaceinvaders_entity_ship` VALUES (1,1),(2,2),(3,3),(4,4);
/*!40000 ALTER TABLE `spaceinvaders_entity_ship` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `spaceinvaders_enum_color`
--

DROP TABLE IF EXISTS `spaceinvaders_enum_color`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spaceinvaders_enum_color` (
  `id_ship` int(10) NOT NULL AUTO_INCREMENT,
  `what_color` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id_ship`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spaceinvaders_enum_color`
--

LOCK TABLES `spaceinvaders_enum_color` WRITE;
/*!40000 ALTER TABLE `spaceinvaders_enum_color` DISABLE KEYS */;
INSERT INTO `spaceinvaders_enum_color` VALUES (1,'Blue'),(2,'Green'),(3,'Red'),(4,'Yellow');
/*!40000 ALTER TABLE `spaceinvaders_enum_color` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `spaceinvaders_xref_plyr_highscore`
--

DROP TABLE IF EXISTS `spaceinvaders_xref_plyr_highscore`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spaceinvaders_xref_plyr_highscore` (
  `xref_id` int(10) NOT NULL AUTO_INCREMENT,
  `plyr_id` int(10) DEFAULT NULL,
  `highscore_id` int(10) DEFAULT NULL,
  PRIMARY KEY (`xref_id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spaceinvaders_xref_plyr_highscore`
--

LOCK TABLES `spaceinvaders_xref_plyr_highscore` WRITE;
/*!40000 ALTER TABLE `spaceinvaders_xref_plyr_highscore` DISABLE KEYS */;
INSERT INTO `spaceinvaders_xref_plyr_highscore` VALUES (1,1,31),(2,1,30),(3,2,1),(4,3,2),(5,4,3),(6,5,11);
/*!40000 ALTER TABLE `spaceinvaders_xref_plyr_highscore` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `spaceinvaders_xref_plyr_ship`
--

DROP TABLE IF EXISTS `spaceinvaders_xref_plyr_ship`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spaceinvaders_xref_plyr_ship` (
  `xref_id` int(10) NOT NULL AUTO_INCREMENT,
  `plyr_id` int(10) DEFAULT NULL,
  `ship_id` int(10) DEFAULT NULL,
  PRIMARY KEY (`xref_id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spaceinvaders_xref_plyr_ship`
--

LOCK TABLES `spaceinvaders_xref_plyr_ship` WRITE;
/*!40000 ALTER TABLE `spaceinvaders_xref_plyr_ship` DISABLE KEYS */;
INSERT INTO `spaceinvaders_xref_plyr_ship` VALUES (1,1,1),(2,1,2),(3,2,2),(4,3,3),(5,4,4),(6,5,1);
/*!40000 ALTER TABLE `spaceinvaders_xref_plyr_ship` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `spaceinvaders_xref_plyr_ship_highscore`
--

DROP TABLE IF EXISTS `spaceinvaders_xref_plyr_ship_highscore`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spaceinvaders_xref_plyr_ship_highscore` (
  `xref_id` int(10) NOT NULL AUTO_INCREMENT,
  `plyr_id` int(10) DEFAULT NULL,
  `ship_id` int(10) DEFAULT NULL,
  `highscore_id` int(10) DEFAULT NULL,
  PRIMARY KEY (`xref_id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spaceinvaders_xref_plyr_ship_highscore`
--

LOCK TABLES `spaceinvaders_xref_plyr_ship_highscore` WRITE;
/*!40000 ALTER TABLE `spaceinvaders_xref_plyr_ship_highscore` DISABLE KEYS */;
INSERT INTO `spaceinvaders_xref_plyr_ship_highscore` VALUES (1,1,1,31),(2,1,2,30),(3,2,2,2),(4,3,3,3),(5,4,4,4),(6,5,1,11);
/*!40000 ALTER TABLE `spaceinvaders_xref_plyr_ship_highscore` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-05-30 13:47:20

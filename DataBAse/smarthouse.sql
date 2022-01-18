-- MySQL dump 10.13  Distrib 8.0.26, for Win64 (x86_64)
--
-- Host: localhost    Database: smarthouse
-- ------------------------------------------------------
-- Server version	8.0.26

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `devices`
--

DROP TABLE IF EXISTS `devices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `devices` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Description` varchar(30) NOT NULL,
  `IdTypeDevice` int NOT NULL,
  `ByOrder` int DEFAULT NULL,
  `HasAlarm` tinyint DEFAULT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=59 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `devices`
--

LOCK TABLES `devices` WRITE;
/*!40000 ALTER TABLE `devices` DISABLE KEYS */;
INSERT INTO `devices` VALUES (1,'Camera',1,2,0),(2,'Camera',1,2,1),(3,'Sensor Temperatura',2,NULL,0),(4,'Dimmer',3,NULL,0),(5,'Riel',4,NULL,0),(6,'Sensor',5,NULL,0),(7,'Camera',1,1,0),(8,'Riel',4,NULL,0),(9,'Camera',1,1,1),(10,'Sensor Temperatura',2,NULL,0),(11,'Dimmer',3,NULL,0),(12,'Riel',4,NULL,0),(13,'Sensor',5,NULL,0),(14,'Camera',1,2,1),(15,'Sensor Temperatura',2,NULL,0),(16,'Dimmer',3,NULL,0),(17,'Riel',4,NULL,0),(18,'Sensor',5,NULL,0),(19,'Camera',1,1,0),(20,'Camera',1,1,0),(21,'Sensor Temperatura',2,NULL,0),(22,'Dimmer',3,NULL,0),(23,'Riel',4,NULL,0),(24,'Sensor',5,NULL,0),(25,'Camera',1,2,1),(26,'Camera',1,2,0),(27,'Camera',1,1,0),(28,'Camera',1,2,0),(29,'Camera',1,1,1),(30,'Camera',1,1,0),(31,'Camera',1,2,0),(32,'Camera',1,1,0),(33,'Camera',1,2,0),(34,'Camera',1,2,1),(35,'Camera',1,1,0),(36,'Camera',1,2,0),(37,'Camera',1,2,1),(38,'Sensor Temperatura',2,NULL,0),(39,'Dimmer',3,NULL,0),(40,'Riel',4,NULL,0),(41,'Sensor',5,NULL,0),(42,'Camera',1,1,1),(43,'Camera',1,1,0),(44,'Camera',1,2,1),(45,'Sensor Temperatura',2,NULL,0),(46,'Dimmer',3,NULL,0),(47,'Riel',4,NULL,0),(48,'Sensor',5,NULL,0),(49,'Camera',1,1,1),(50,'Sensor Temperatura',2,NULL,0),(51,'Dimmer',3,NULL,0),(52,'Riel',4,NULL,0),(53,'Sensor',5,NULL,0),(54,'Camera',1,2,0),(55,'Sensor Temperatura',2,NULL,0),(56,'Dimmer',3,NULL,0),(57,'Riel',4,NULL,0),(58,'Sensor',5,NULL,0);
/*!40000 ALTER TABLE `devices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rooms`
--

DROP TABLE IF EXISTS `rooms`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `rooms` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Description` varchar(30) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rooms`
--

LOCK TABLES `rooms` WRITE;
/*!40000 ALTER TABLE `rooms` DISABLE KEYS */;
INSERT INTO `rooms` VALUES (27,'Living'),(28,'Garden');
/*!40000 ALTER TABLE `rooms` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roomsdevices`
--

DROP TABLE IF EXISTS `roomsdevices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `roomsdevices` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `IdRoom` int NOT NULL,
  `IdDevice` int NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=59 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roomsdevices`
--

LOCK TABLES `roomsdevices` WRITE;
/*!40000 ALTER TABLE `roomsdevices` DISABLE KEYS */;
INSERT INTO `roomsdevices` VALUES (49,27,49),(50,27,50),(51,27,51),(52,27,52),(53,27,53),(54,28,54),(55,28,55),(56,28,56),(57,28,57),(58,28,58);
/*!40000 ALTER TABLE `roomsdevices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `statistics`
--

DROP TABLE IF EXISTS `statistics`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `statistics` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `IdUser` int NOT NULL,
  `Date` datetime NOT NULL,
  `IdRoom` int NOT NULL,
  `IdDevice` int NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `statistics`
--

LOCK TABLES `statistics` WRITE;
/*!40000 ALTER TABLE `statistics` DISABLE KEYS */;
/*!40000 ALTER TABLE `statistics` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `typedevices`
--

DROP TABLE IF EXISTS `typedevices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `typedevices` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Description` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `typedevices`
--

LOCK TABLES `typedevices` WRITE;
/*!40000 ALTER TABLE `typedevices` DISABLE KEYS */;
INSERT INTO `typedevices` VALUES (1,'Camara'),(2,'Sensor Temperatura'),(3,'Luz'),(4,'Riel'),(5,'Sensor');
/*!40000 ALTER TABLE `typedevices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Login` varchar(30) NOT NULL,
  `PassWord` varchar(30) NOT NULL,
  `IdUserType` int NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'Lautaro','Lautaro',1),(2,'Javier','Javier',1),(10,'pepe','pepe',2);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `userstypes`
--

DROP TABLE IF EXISTS `userstypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `userstypes` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Description` varchar(30) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userstypes`
--

LOCK TABLES `userstypes` WRITE;
/*!40000 ALTER TABLE `userstypes` DISABLE KEYS */;
INSERT INTO `userstypes` VALUES (1,'SuperUsuario'),(2,'Invitado');
/*!40000 ALTER TABLE `userstypes` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-11-14 22:53:22

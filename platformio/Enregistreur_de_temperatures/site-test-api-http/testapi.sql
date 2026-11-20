-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le : dim. 07 jan. 2024 à 20:19
-- Version du serveur : 8.0.31
-- Version de PHP : 8.0.26

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `testapi`
--
DROP DATABASE IF EXISTS `testapi`;
CREATE DATABASE IF NOT EXISTS `testapi` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `testapi`;

-- --------------------------------------------------------

--
-- Structure de la table `data`
--

DROP TABLE IF EXISTS `data`;
CREATE TABLE IF NOT EXISTS `data` (
  `id` int NOT NULL AUTO_INCREMENT,
  `datepub` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `donnee` varchar(2000) DEFAULT NULL,
  `ipsrc` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `data`
--

INSERT INTO `data` (`id`, `datepub`, `donnee`, `ipsrc`) VALUES
(1, '2024-01-07 20:11:08', '{\"TempCelcius\":\"20.5\"}', '172.16.0.100'),
(2, '2024-01-07 20:11:25', '{\"TempCelcius\":\"20.4\"}', '172.16.0.100');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le : lun. 05 fév. 2024 à 19:11
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
-- Base de données : `shopsample`
--
DROP DATABASE IF EXISTS `shopsample`;
CREATE DATABASE IF NOT EXISTS `shopsample` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci;
USE `shopsample`;

-- --------------------------------------------------------

--
-- Structure de la table `customers`
--

DROP TABLE IF EXISTS `customers`;
CREATE TABLE IF NOT EXISTS `customers` (
  `CustomerID` int NOT NULL,
  `FirstName` varchar(50) DEFAULT NULL,
  `LastName` varchar(50) DEFAULT NULL,
  `Gender` varchar(6) DEFAULT NULL,
  `Email` varchar(255) DEFAULT NULL,
  `PhoneNumber` varchar(15) DEFAULT NULL,
  `Address` varchar(255) DEFAULT NULL,
  `Category` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`CustomerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `customers`
--

INSERT INTO `customers` (`CustomerID`, `FirstName`, `LastName`, `Gender`, `Email`, `PhoneNumber`, `Address`, `Category`) VALUES
(1, 'Frederick', 'Johnson', 'Male', 'alFrederickice@email.com', '555-1234', '123 Main St, Cityville', 'Retail'),
(2, 'Bob', 'Smith', 'Male', 'bob@email.com', '555-5678', '456 Oak St, Townsville', 'Corporate'),
(3, 'Charlie', 'Brown', 'Male', 'charlie@email.com', '555-9012', '789 Pine St, Villagetown', 'Individual'),
(4, 'Elijah', 'King', 'Male', 'elijah@email.com', '555-1111', '987 Pine St, Hamletsville', 'Retail'),
(5, 'Zoe', 'Perry', 'Female', 'zoe@email.com', '555-2222', '654 Birch St, Villagetown', 'Corporate'),
(6, 'Walter', 'Cook', 'Male', 'Walter@email.com', '555-3333', '321 Elm St, Cityville', 'Individual'),
(7, 'Mila', 'Murphy', 'Female', 'mila@email.com', '555-4444', '456 Maple St, Townsville', 'Retail'),
(8, 'Davian', 'Mills', 'Male', 'Davian@email.com', '555-5555', '789 Oak St, Hamletsville', 'Corporate'),
(9, 'Sofia', 'Bell', 'Female', 'sofia@email.com', '555-6666', '123 Birch St, Villagetown', 'Individual'),
(10, 'Liam', 'Harrison', 'Male', 'liam@email.com', '555-7777', '876 Pine St, Cityville', 'Retail'),
(11, 'Sage', 'Evans', 'Female', 'Sage@email.com', '555-8888', '543 Elm St, Townsville', 'Corporate'),
(12, 'Carter', 'Dixon', 'Male', 'carter@email.com', '555-9999', '210 Maple St, Hamletsville', 'Individual'),
(13, 'Madelyn', 'Griffith', 'Female', 'madelyn@email.com', '555-0000', '987 Oak St, Villagetown', 'Retail'),
(14, 'Reese', 'Sullivan', 'Female', 'Reese@email.com', '555-1111', '654 Pine St, Cityville', 'Corporate'),
(15, 'Aubrey', 'Ward', 'Female', 'aubrey@email.com', '555-2222', '321 Birch St, Townsville', 'Individual'),
(16, 'Eli', 'Fisher', 'Male', 'eli@email.com', '555-3333', '456 Elm St, Hamletsville', 'Retail'),
(17, 'Alma', 'Greer', 'Female', 'Alma@email.com', '555-4444', '789 Maple St, Villagetown', 'Corporate'),
(18, 'Connor', 'Hendrix', 'Male', 'connor@email.com', '555-5555', '123 Oak St, Cityville', 'Individual'),
(19, 'Hazel', 'Sanchez', 'Female', 'hazel@email.com', '555-6666', '876 Birch St, Townsville', 'Retail'),
(20, 'Owen', 'Marshall', 'Male', 'owen@email.com', '555-7777', '543 Pine St, Hamletsville', 'Corporate'),
(21, 'Lily', 'Beck', 'Female', 'lily@email.com', '555-8888', '210 Elm St, Villagetown', 'Individual'),
(22, 'Ember', 'Carr', 'Male', 'Ember@email.com', '555-9999', '987 Maple St, Cityville', 'Retail'),
(23, 'Aaliyah', 'Monroe', 'Female', 'aaliyah@email.com', '555-0000', '654 Oak St, Townsville', 'Corporate'),
(24, 'Leo', 'Hess', 'Male', 'leo@email.com', '555-1111', '321 Birch St, Hamletsville', 'Individual'),
(25, 'Viviana', 'Langley', 'Female', 'Viviana@email.com', '555-2222', '456 Pine St, Villagetown', 'Retail'),
(26, 'Gabriel', 'Sharp', 'Male', 'gabriel@email.com', '555-3333', '789 Elm St, Cityville', 'Corporate'),
(27, 'Reign', 'Waller', 'Male', 'peReignnelope@email.com', '555-4444', '123 Maple St, Townsville', 'Individual'),
(28, 'Jaxon', 'Hudson', 'Male', 'jaxon@email.com', '555-5555', '876 Oak St, Hamletsville', 'Retail'),
(29, 'Ayden', 'Fleming', 'Male', 'Ayden@email.com', '555-6666', '543 Birch St, Villagetown', 'Corporate'),
(30, 'Wes', 'Cohen', 'Male', 'Wes@email.com', '555-7777', '210 Pine St, Cityville', 'Individual'),
(31, 'Sloane', 'Wheeler', 'Female', 'stella@email.com', '555-8888', '987 Elm St, Townsville', 'Retail'),
(32, 'Parker', 'Wallace', 'Male', 'parker@email.com', '555-9999', '654 Maple St, Hamletsville', 'Corporate'),
(33, 'Nova', 'Frost', 'Female', 'nova@email.com', '555-0000', '321 Oak St, Villagetown', 'Individual'),
(34, 'Rylan', 'Steele', 'Male', 'Rylan@email.com', '555-1111', '456 Pine St, Cityville', 'Retail'),
(35, 'Elena', 'Cameron', 'Female', 'elena@email.com', '555-2222', '789 Elm St, Townsville', 'Corporate'),
(36, 'Miles', 'Hartman', 'Male', 'miles@email.com', '555-3333', '123 Birch St, Hamletsville', 'Individual'),
(37, 'Aliza', 'Bauer', 'Female', 'Aliza@email.com', '555-4444', '876 Oak St, Villagetown', 'Retail'),
(38, 'Axel', 'Gallagher', 'Male', 'axel@email.com', '555-5555', '543 Pine St, Cityville', 'Corporate'),
(39, 'Evelyn', 'Quinn', 'Female', 'Evie@email.com', '555-6666', '210 Elm St, Townsville', 'Individual'),
(40, 'Ayden', 'Nolan', 'Male', 'Ayden@email.com', '555-7777', '987 Maple St, Hamletsville', 'Retail');

-- --------------------------------------------------------

--
-- Structure de la table `departments`
--

DROP TABLE IF EXISTS `departments`;
CREATE TABLE IF NOT EXISTS `departments` (
  `DepartmentID` int NOT NULL,
  `DepartmentName` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`DepartmentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `departments`
--

INSERT INTO `departments` (`DepartmentID`, `DepartmentName`) VALUES
(1, 'Sales'),
(2, 'Marketing'),
(3, 'IT'),
(4, 'Finance'),
(5, 'HR');

-- --------------------------------------------------------

--
-- Structure de la table `employees`
--

DROP TABLE IF EXISTS `employees`;
CREATE TABLE IF NOT EXISTS `employees` (
  `EmployeeID` int NOT NULL,
  `FirstName` varchar(50) DEFAULT NULL,
  `LastName` varchar(50) DEFAULT NULL,
  `Gender` varchar(6) DEFAULT NULL,
  `DepartmentID` int DEFAULT NULL,
  `HireDate` date DEFAULT NULL,
  `Position` varchar(50) DEFAULT NULL,
  `Salary` decimal(10,2) DEFAULT NULL,
  `PhoneNumber` varchar(15) DEFAULT NULL,
  `Email` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`EmployeeID`),
  KEY `DepartmentID` (`DepartmentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `employees`
--

INSERT INTO `employees` (`EmployeeID`, `FirstName`, `LastName`, `Gender`, `DepartmentID`, `HireDate`, `Position`, `Salary`, `PhoneNumber`, `Email`) VALUES
(1, 'Vivian', 'White', 'Female', 1, '2022-08-15', 'Sales Representative', '60000.00', '555-6666', 'Vivian.white@email.com'),
(2, 'Andrew', 'Miller', 'Male', 2, '2019-11-20', 'Marketing Coordinator', '55000.00', '555-7777', 'andrew.miller@email.com'),
(3, 'Lewis', 'Clark', 'Male', 3, '2020-04-10', 'IT Analyst', '70000.00', '555-8888', 'Lewis.clark@email.com'),
(4, 'Ava', 'Wilso', 'Female', 4, '2021-01-05', 'Financial Planner', '75000.00', '555-9999', 'Ava.wilson@email.com'),
(5, 'James', 'Taylor', 'Male', 5, '2018-06-28', 'HR Specialist', '60000.00', '555-0000', 'James.taylor@email.com'),
(6, 'John', 'Doe', 'Male', 1, '2020-01-15', 'Sales Manager', '70000.00', '555-1111', 'john.doe@email.com'),
(7, 'Jane', 'Smith', 'Female', 2, '2019-05-20', 'Marketing Specialist', '60000.00', '555-2222', 'jane.smith@email.com'),
(8, 'Robert', 'Johnso', 'Male', 3, '2021-03-10', 'IT Specialist', '75000.00', '555-3333', 'robert.johnson@email.com'),
(9, 'Emily', 'Brow', 'Female', 1, '2018-07-05', 'Sales Representative', '65000.00', '555-4444', 'emily.brown@email.com'),
(10, 'Lucas', 'Davis', 'Male', 5, '2022-02-28', 'HR Coordinator', '55000.00', '555-5555', 'Lucas.Davis@email.com'),
(11, 'Madeline', 'Anderson', 'Female', 2, '2022-03-15', 'Marketing Specialist', '65000.00', '555-1111', 'Madeline.anderson@email.com'),
(12, 'Ava', 'Moore', 'Female', 1, '2020-05-10', 'Sales Representative', '70000.00', '555-2222', 'ava.moore@email.com'),
(13, 'Logan', 'Baker', 'Male', 3, '2019-09-28', 'IT Specialist', '80000.00', '555-3333', 'logan.baker@email.com'),
(14, 'Madison', 'Garcia', 'Female', 4, '2021-04-05', 'Financial Analyst', '65000.00', '555-4444', 'madison.garcia@email.com'),
(15, 'Jackso', 'Thomas', 'Male', 5, '2018-11-15', 'HR Manager', '75000.00', '555-5555', 'jackson.thomas@email.com'),
(16, 'Parker', 'Hill', 'Male', 1, '2022-06-10', 'Sales Coordinator', '55000.00', '555-6666', 'Parker.hill@email.com'),
(17, 'David', 'Perez', 'Male', 2, '2020-09-20', 'Marketing Manager', '80000.00', '555-7777', 'david.perez@email.com'),
(18, 'Emma', 'Marti', 'Female', 3, '2019-02-10', 'IT Manager', '90000.00', '555-8888', 'emma.martin@email.com'),
(19, 'Avery', 'Barnes', 'Female', 5, '2018-09-28', 'HR Manager', '75000.00', '555-0000', 'avery.barnes@email.com'),
(20, 'Adam', 'Brooks', 'Male', 5, '2018-08-28', 'HR Coordinator', '60000.00', '555-0000', 'Adam.brooks@email.com'),
(21, 'Chloe', 'Ramirez', 'Female', 3, '2022-07-10', 'IT Analyst', '65000.00', '555-6666', 'chloe.ramirez@email.com'),
(22, 'Amelia', 'Wright', 'Female', 2, '2020-08-20', 'Marketing Specialist', '70000.00', '555-7777', 'Amelia.wright@email.com'),
(23, 'Blake', 'Stewart', 'Male', 3, '2019-11-10', 'IT Specialist', '80000.00', '555-8888', 'Blake.gomez@email.com'),
(24, 'Lily', 'Gomez', 'Female', 3, '2019-11-10', 'IT Specialist', '80000.00', '555-8888', 'lily.gomez@email.com'),
(25, 'Benjamin', 'Hayes', 'Male', 4, '2021-06-15', 'Financial Analyst', '65000.00', '555-9999', 'benjamin.hayes@email.com'),
(26, 'Harper', 'Turner', 'Female', 1, '2022-04-15', 'Sales Representative', '70000.00', '555-1111', 'Harper.turner@email.com'),
(27, 'Brody', 'Cooper', 'Female', 2, '2020-06-10', 'Marketing Coordinator', '55000.00', '555-2222', 'Brody.cooper@email.com'),
(28, 'Isla', 'Fisher', 'Male', 1, '2019-10-28', 'Sales Representative', '75000.00', '555-3333', 'Isla.fisher@email.com'),
(29, 'Ian', 'Stewart', 'Male', 4, '2021-02-05', 'Financial Planner', '80000.00', '555-4444', 'Ian.stewart@email.com'),
(30, 'Liam', 'Cruz', 'Male', 5, '2018-12-15', 'HR Specialist', '60000.00', '555-5555', 'liam.cruz@email.com');

-- --------------------------------------------------------

--
-- Structure de la table `orders`
--

DROP TABLE IF EXISTS `orders`;
CREATE TABLE IF NOT EXISTS `orders` (
  `OrderID` int NOT NULL,
  `CustomerID` int DEFAULT NULL,
  `OrderDate` date DEFAULT NULL,
  `ProductID` int DEFAULT NULL,
  `Quantity` int DEFAULT NULL,
  `SalesmanID` int DEFAULT NULL,
  PRIMARY KEY (`OrderID`),
  KEY `CustomerID` (`CustomerID`),
  KEY `ProductID` (`ProductID`),
  KEY `SalesmanID` (`SalesmanID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `orders`
--

INSERT INTO `orders` (`OrderID`, `CustomerID`, `OrderDate`, `ProductID`, `Quantity`, `SalesmanID`) VALUES
(1, 8, '2021-01-05', 2, 1, 23),
(2, 3, '2021-02-10', 4, 2, 21),
(3, 12, '2021-03-15', 6, 3, 4),
(4, 5, '2021-04-20', 8, 1, 12),
(5, 9, '2021-05-25', 10, 2, 5),
(6, 1, '2021-06-01', 1, 3, 21),
(7, 14, '2021-07-08', 3, 1, 5),
(8, 10, '2021-08-13', 5, 2, 23),
(9, 7, '2021-09-18', 7, 3, 4),
(10, 11, '2021-10-23', 9, 1, 23),
(11, 4, '2021-11-28', 2, 2, 4),
(12, 6, '2021-12-03', 4, 3, 12),
(13, 2, '2022-01-08', 6, 1, 23),
(14, 13, '2022-02-13', 8, 2, 21),
(15, 15, '2022-03-20', 10, 3, 5),
(16, 8, '2022-04-25', 1, 1, 23),
(17, 3, '2022-05-30', 3, 2, 21),
(18, 11, '2022-06-04', 5, 3, 12),
(19, 5, '2022-07-09', 7, 1, 5),
(20, 9, '2022-08-14', 9, 2, 12),
(21, 1, '2022-09-19', 2, 3, 23),
(22, 14, '2022-10-24', 4, 1, 4),
(23, 7, '2022-11-29', 6, 2, 21),
(24, 10, '2022-12-04', 8, 3, 5),
(25, 2, '2023-01-09', 10, 1, 12),
(26, 8, '2023-02-14', 2, 2, 23),
(27, 3, '2023-03-21', 4, 3, 21),
(28, 12, '2023-04-26', 6, 1, 12),
(29, 5, '2023-05-31', 8, 2, 5),
(30, 2, '2024-01-05', 10, 3, 23);

-- --------------------------------------------------------

--
-- Structure de la table `products`
--

DROP TABLE IF EXISTS `products`;
CREATE TABLE IF NOT EXISTS `products` (
  `ProductID` int NOT NULL,
  `ProductName` varchar(255) DEFAULT NULL,
  `Price` decimal(10,2) DEFAULT NULL,
  `QuantityInStock` int DEFAULT NULL,
  PRIMARY KEY (`ProductID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `products`
--

INSERT INTO `products` (`ProductID`, `ProductName`, `Price`, `QuantityInStock`) VALUES
(1, 'Laptop', '999.99', 50),
(2, 'Desktop', '799.99', 30),
(3, 'Monitor', '199.99', 100),
(4, 'Keyboard', '49.99', 80),
(5, 'Mouse', '29.99', 120),
(6, 'Printer', '149.99', 25),
(7, 'External Hard Drive', '129.99', 40),
(8, 'Headphones', '79.99', 60),
(9, 'Webcam', '59.99', 35),
(10, 'Router', '89.99', 15);

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `employees`
--
ALTER TABLE `employees`
  ADD CONSTRAINT `employees_ibfk_1` FOREIGN KEY (`DepartmentID`) REFERENCES `departments` (`DepartmentID`) ON DELETE RESTRICT ON UPDATE RESTRICT;

--
-- Contraintes pour la table `orders`
--
ALTER TABLE `orders`
  ADD CONSTRAINT `orders_ibfk_1` FOREIGN KEY (`CustomerID`) REFERENCES `customers` (`CustomerID`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `orders_ibfk_2` FOREIGN KEY (`ProductID`) REFERENCES `products` (`ProductID`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `orders_ibfk_3` FOREIGN KEY (`SalesmanID`) REFERENCES `employees` (`EmployeeID`) ON DELETE RESTRICT ON UPDATE RESTRICT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

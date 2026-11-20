# Déploiement du site de test

> * Auteur : Gwénaël LAURENT
> * Date : 07/03/2021
> * OS : Windows 10 (version 20H2)
> * OS : Raspbian GNU/Linux 10 (buster) ```cat /etc/os-release```

# Fichiers du site web
Le fichier ```SiteTestAPI.zip``` contient :
* les fichiers d'un site web PHP
* le fichier de création de la base de données ```testapi.sql```

# Base de données
Ce site fonctionne avec une base de données

Il faut déployer la base de données ```testapi``` sur le serveur MySQL de la même machine qui héberge le site web (fichier ```testapi.sql``` dans le fichier zip)

Il faut ensuite créer un ```utilisateur MySQL```

* Nom d'utilisateur MySQL : user_testapi
* Mot de passe MySQL : pass_testapi
* Droits d'accès : aucun privilège global + CRUD sur la base testapi

La liaison PHP - MySQL se fait dans le fichier /bdd/bddconfig.php

# Utilisation de l'API pour enregister des données dans la base
Les **```requêtes HTTP```** doivent être envoyées en ```méthode POST```

Les **```données```** doivent être envoyées au ```format RAW``` (comme pour Dweet.io) et sont souhaitées au ```format JSON```

Adresse de l'API pour enregistrer une données : ```http://adresse_du_site/api/insert.php```

# Utilisation de l'API pour lire la dernière donnée enregistrée
Les requêtes doivent être envoyées en ```méthode GET```

Adresse de l'API pour lire la dernière donnée : ```http://adresse_du_site/api/get-latest.php```
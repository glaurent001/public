(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 22 : Requêtes SQL avec python (MySQL)
> * Auteur : Gwénaël LAURENT
> * Date : 26/11/2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 22 : Requêtes SQL avec python (MySQL)](#chap-22--requêtes-sql-avec-python-mysql)
- [1. Bibliothèque pour communiquer avec MySQL](#1-bibliothèque-pour-communiquer-avec-mysql)
- [2. Connexion à une base de données](#2-connexion-à-une-base-de-données)
- [3. Requêtes SELECT](#3-requêtes-select)
  - [3.1. Récupérer tous les résultats avec `fetchall()`](#31-récupérer-tous-les-résultats-avec-fetchall)
  - [3.2. Récupérer les résultats ligne par ligne avec le `cursor`](#32-récupérer-les-résultats-ligne-par-ligne-avec-le-cursor)
  - [3.3. Requête avec des paramètres](#33-requête-avec-des-paramètres)
- [4. Requêtes INSERT, UPDATE ou DELETE](#4-requêtes-insert-update-ou-delete)
- [5. Sécuriser les identifiants d'accès à une base de données](#5-sécuriser-les-identifiants-daccès-à-une-base-de-données)
  - [5.1. Utiliser un fichier de variables d'environnement (.env)](#51-utiliser-un-fichier-de-variables-denvironnement-env)
  - [5.2. Utiliser les variables d'environnement de l'OS](#52-utiliser-les-variables-denvironnement-de-los)
    - [5.2.1. Gestion des variables d’environnement sur **Windows**](#521-gestion-des-variables-denvironnement-sur-windows)
    - [5.2.2. Gestion des variables d’environnement sur **Linux/Debian**](#522-gestion-des-variables-denvironnement-sur-linuxdebian)
    - [5.2.3. Lecture des variables dans un script Python](#523-lecture-des-variables-dans-un-script-python)
    - [5.2.4. Pour lancer le script python qui utilise les variables d'environnement temporaires](#524-pour-lancer-le-script-python-qui-utilise-les-variables-denvironnement-temporaires)
    - [5.2.5. Scripts **Windows** pour initialiser / nettoyer les variables d'environnements](#525-scripts-windows-pour-initialiser--nettoyer-les-variables-denvironnements)
    - [5.2.6. Scripts **Linux** pour initialiser / nettoyer les variables d'environnements](#526-scripts-linux-pour-initialiser--nettoyer-les-variables-denvironnements)


# 1. Bibliothèque pour communiquer avec MySQL

La bibliothèque la plus standard en Python pour se connecter à une base de données MySQL est `mysql-connector-python`, 
souvent appelée simplement mysql.connector. 
Elle est développée et maintenue par Oracle, ce qui en fait une solution officielle pour interagir avec MySQL en Python.

**Documentation générale** : https://dev.mysql.com/doc/connector-python/en/

**Documentation de l'API** : https://dev.mysql.com/doc/connector-python/en/connector-python-reference.html

Pour installer la bibliothèque : 
```sh
pip install mysql-connector-python
```

# 2. Connexion à une base de données
```py
import mysql.connector

# Connexion à la base de données
try:
    cnx = mysql.connector.connect(
        host="127.0.0.1",  # Remplacez par l'hôte de votre serveur MySQL
        user="userCommunes",  # Nom d'utilisateur MySQL
        password="user",  # Mot de passe MySQL
        database="communesfrance"  # Nom de la base de données
    )

    # Vérifiez la connexion
    if cnx.is_connected():
        print("Connexion réussie.")

        ##################################
        #  Exécution des requêtes SQL
        ##################################

        # Fermeture de la connexion
        cnx.close()
        print("Connexion fermée.")

except mysql.connector.Error as err:
    print("Impossible de se connecter à la base de données.")
    print(f"Erreur : {err}")

```

# 3. Requêtes SELECT

## 3.1. Récupérer tous les résultats avec `fetchall()`

La fonction `fetchall()` renvoie tous les résultats de la requête SELECT en un seul appel de la fonction.

```py
# Après connexion à la base de données

# Création d'un curseur
cursor = cnx.cursor()

# Exécution d'une requête SELECT
cursor.execute("SELECT code_reg, nom_region FROM region")

# Récupération de tous les résultats dans une liste de tuples
results = cursor.fetchall()

# Affichage des résultats ligne par ligne en parcourant la liste
for row in results:
    print(row[0], row[1])
```

**`fetchall()` renvoie une liste de tuples**. Les données des tuples sont ordonnées selon la liste des colonnes sélectionnées dans la requête SELECT.
```sh 
[
    (1, 'Guadeloupe'),
    (2, 'Martinique'),
    (3, 'Guyane'),
    ...
]
```

> **ATTENTION** : Si la requête renvoie un grand nombre de données, cette technique peut surcharger la RAM de l'odinateur qui exécute le script


## 3.2. Récupérer les résultats ligne par ligne avec le `cursor`
On n'utilise pas la fonction *fetchall()* mais on itère directement sur le cursor.

**Chaque itération sur le `cursor` renvoie un tuple**. Les données du tuple sont ordonnées selon la liste des colonnes sélectionnées dans la requête SELECT.

```py
# Après connexion à la base de données

# Création d'un curseur
cursor = cnx.cursor()

# Exécution d'une requête SELECT
cursor.execute("SELECT code_reg, nom_region FROM region")

# Récupération des résultats des résultats ligne par ligne
# une ligne = un tuple
for (num, region) in cursor:
    print(num, region)
```

## 3.3. Requête avec des paramètres
**Exemples de requête SELECT avec paramètres :**
* https://dev.mysql.com/doc/connector-python/en/connector-python-example-cursor-select.html
* https://dev.mysql.com/doc/connector-python/en/connector-python-api-mysqlcursor-execute.html
* https://dev.mysql.com/doc/connector-python/en/connector-python-api-mysqlcursorprepared.html

ou consulter la documentation `connector-python-en.a4.pdf` § 5.4, § 10.5.7 et § 10.6.5

# 4. Requêtes INSERT, UPDATE ou DELETE
Doc : https://dev.mysql.com/doc/connector-python/en/connector-python-example-cursor-transaction.html

> ATTENTION : Ne pas oublier l'appel à  commit() pour valider les modifications dans la base de données


# 5. Sécuriser les identifiants d'accès à une base de données
Les identifiants de connexion sont des informations sensibles. Il faut protéger ces informations.

**Bonnes pratiques pour que ce soit sûr :**
* ⚠️ Ne pas écrire les secrets en clair dans le code
* ⚠️ Ne pas les afficher dans les logs (print, traceback, etc.)
* ⚠️ Exclure les secrets des dépôt Git

## 5.1. Utiliser un fichier de variables d'environnement (.env)
Stockez les identifiants (nom d'utilisateur, mot de passe, hôte, etc.) dans un fichier d'environnement séparé du code principal.

1. Créez un fichier `.env` à la racine de votre projet python
    - **Appliquez des permissions restrictives** sur les fichiers contenant les identifiants. Par exemple, sous Linux : 
        ```sh
        chmod 600 .env
        ```
    - **Excluez le fichier du contrôle de version GIT** en utilisant le fichier `.gitignore`
        ```git
        .env
        ```

2. Ajoutez les variables dans le fichier `.env` :

    Note : il n'y a pas de quote/double-quote autour des chaines de caractères !
    ```conf
    DB_HOST=localhost
    DB_USER=votre_utilisateur
    DB_PASSWORD=votre_mot_de_passe
    DB_DATABASE=votre_base
    ```
    _Par convention, les noms de variables sont écrits en majuscules._

3. Dans vos scripts python, utilisez la bibliothèque `python-dotenv` pour accéder au fichier `.env`

    Pour installer la bibliothèque
    ```sh
    pip install python-dotenv
    ```

    Exemple d'utilisation dans un script :
    ```py
    from dotenv import load_dotenv
    import os

    # Charger les variables d'environnement contenues dans le fichier .env
    # situé à la racine du projet ou du répertoire de travail
    load_dotenv()

    # enregistrer les variables dans un dictionnaire de config
    db_config = {
        "host": os.getenv("DB_HOST"),
        "user": os.getenv("DB_USER"),
        "password": os.getenv("DB_PASSWORD"),
        "database": os.getenv("DB_DATABASE")
    }
    # Connexion à la base de données
    try:
        cnx = mysql.connector.connect(
            host=db_config["host"],
            user=db_config["user"],
            password=db_config["password"],
            database=db_config["database"]
        )
    ```

    Avec le paramètre `dotenv_path`, vous pouvez charger un fichier `.env` à n'importe quel emplacement.
    ```py
    from dotenv import load_dotenv
    from pathlib import Path
    import os

    # Spécifiez le chemin vers le fichier .env
    # Ex : Localiser le fichier .env par rapport au dossier du script
    script_directory = Path(__file__).parent
    config_path = script_directory.joinpath(".env")

    # Charger les variables d'environnement depuis ce fichier
    load_dotenv(dotenv_path=config_path)
    ```

    Si vous avez plusieurs fichiers `.env` à différents emplacements, vous pouvez les charger successivement :
    ```py
    load_dotenv(dotenv_path="config/.env")
    load_dotenv(dotenv_path="secrets/.env")
    ```
<!-- En production, il est préférable de déplacer les variables d'environnement vers un système plus sécurisé comme des gestionnaires de secrets (AWS Secrets Manager
Azure Key Vault, Google Cloud Secret Manager, Vault by HashiCorp) ou directement dans les variables d'environnement du système d'exploitation.  -->

## 5.2. Utiliser les variables d'environnement de l'OS
### 5.2.1. Gestion des variables d’environnement sur **Windows**

> Par convention, les noms de variables d'environnement sont écrits en majuscules.

| Objectif                                               | Commande CLI                 |
|--------------------------------------------------------|------------------------------|
| Créer une variable (temporaire, session courante)      | `set NOM_VARIABLE=valeur`    |
| Créer une variable (persistante, pour l’utilisateur)   | `setx NOM_VARIABLE "valeur"` |
| Lire une variable dans CMD                             | `echo %NOM_VARIABLE%`        |
| Lire une variable dans PowerShell                      | `$env:NOM_VARIABLE`          |
| Supprimer une variable(temporaire, session courante)   | `set NOM_VARIABLE=`          |
| Supprimer une variable (persistante, de l’utilisateur) | `setx NOM_VARIABLE ""`       |

⚠️ Les variables persistantes ne sont disponibles que dans les **nouveaux shells** ouverts.

### 5.2.2. Gestion des variables d’environnement sur **Linux/Debian**

| Objectif                                               | Commande CLI                                                                                                           |
|--------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------|
| Créer une variable (temporaire, session courante)      | `export NOM_VARIABLE="valeur"`                                                                                         |
| Créer une variable (persistante, pour l’utilisateur)   | Ajouter dans : `nano ~/.bashrc`<br/>et écrire : `export NOM_VARIABLE="valeur"`<br/>Puis recharger : `source ~/.bashrc` |
| Lire une variable                                      | `echo $NOM_VARIABLE`                                                                                                   |
| Supprimer une variable(temporaire, session courante)   | `unset NOM_VARIABLE`                                                                                                   |
| Supprimer une variable (persistante, de l’utilisateur) | Supprimer la ligne export ... dans : `nano ~/.bashrc`<br/>Puis recharger : `source ~/.bashrc`                          |


### 5.2.3. Lecture des variables dans un script Python
```py
import os
secret = os.getenv("NOM_VARIABLE")
```
### 5.2.4. Pour lancer le script python qui utilise les variables d'environnement temporaires
Linux
```bash
export APP_PASSWORD="SuperSecret123"
python3 mon_script.py
unset APP_PASSWORD
```
Windows CMD
```cmd
set APP_PASSWORD=SuperSecret123
python mon_script.py
set APP_PASSWORD=
```
Windows PowerShell
```powershell
$env:APP_PASSWORD="SuperSecret123"
python mon_script.py
Remove-Item Env:APP_PASSWORD
```


### 5.2.5. Scripts **Windows** pour initialiser / nettoyer les variables d'environnements

**Initialiser les variables** : Fichier `init_secrets.cmd`

```cmd
@echo off

REM === CONFIG : secrets à charger ===
set APP_PASSWORD=MonSuperSecret
set API_TOKEN=abc123xyz
set DB_USER=admin

echo Secrets définis (session courante)
echo Pour tester : echo %%APP_PASSWORD%%
echo Pour exécuter un script Python : python mon_script.py
echo Pour nettoyer : cleanup_secrets.cmd
```

**Nettoyer les variables** : Fichier `cleanup_secrets.cmd`

```cmd
@echo off

set APP_PASSWORD=
set API_TOKEN=
set DB_USER=

echo Variables d'environnement nettoyées
```

**Utilisation pour lancer le script python :**

```cmd
init_secrets.cmd
python mon_script.py
cleanup_secrets.cmd
```
*Note : Les scripts utilisent des variables **temporaires** car c'est plus sûr pour des secrets !*

> ⚠️ Exclure les scripts du contrôle de version GIT en utilisant le fichier `.gitignore`


### 5.2.6. Scripts **Linux** pour initialiser / nettoyer les variables d'environnements
**Initialiser les variables** : Fichier `init_secrets.sh`

```bash
#!/usr/bin/env bash

# === CONFIG : secrets à charger ===
# NomVar="valeur"
APP_PASSWORD="MonSuperSecret"
API_TOKEN="abc123xyz"
DB_USER="admin"

# === Export des variables ===
export APP_PASSWORD
export API_TOKEN
export DB_USER

echo "Secrets chargés dans les variables d'environnement (session courante)"
echo "Pour vérifier : echo \$APP_PASSWORD"
echo "Pour nettoyer : source cleanup_secrets.sh"
```

**Nettoyer les variables** : Fichier `cleanup_secrets.sh`

```bash
#!/usr/bin/env bash

unset APP_PASSWORD
unset API_TOKEN
unset DB_USER

echo "Secrets supprimés de l'environnement"
```

**Utilisation pour lancer le script python :**

```bash
chmod +x init_secrets.sh cleanup_secrets.sh
source init_secrets.sh   # charge dans la session
python3 mon_script.py
source cleanup_secrets.sh # supprime
```
*Note : La commande `source` est utilisée pour que les vars existent dans le même shell que le script python*

> ⚠️ Exclure les scripts du contrôle de version GIT en utilisant le fichier `.gitignore`


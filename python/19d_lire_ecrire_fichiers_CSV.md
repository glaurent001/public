(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 19d : Accès aux fichiers CSV avec Python

> * Auteur : Gwénaël LAURENT
> * Date : 05/02/2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 19d : Accès aux fichiers CSV avec Python](#chap-19d--accès-aux-fichiers-csv-avec-python)
- [1. Introduction](#1-introduction)
- [2. Lecture d'un fichier CSV](#2-lecture-dun-fichier-csv)
  - [2.1. Lire un fichier ligne par ligne](#21-lire-un-fichier-ligne-par-ligne)
  - [2.2. Lire un fichier CSV en utilisant des noms de colonnes](#22-lire-un-fichier-csv-en-utilisant-des-noms-de-colonnes)
- [3. Écriture dans un fichier CSV](#3-écriture-dans-un-fichier-csv)
  - [3.1. Écrire des lignes sous forme de listes](#31-écrire-des-lignes-sous-forme-de-listes)
  - [3.2. Écrire des lignes sous forme de dictionnaires](#32-écrire-des-lignes-sous-forme-de-dictionnaires)
- [4. Extraction d'une information spécifique](#4-extraction-dune-information-spécifique)


# 1. Introduction
Le format CSV (Comma-Separated Values) est utilisé pour stocker des données sous forme de tableau (comme une feuille Excel). Python fournit un module standard csv pour lire et écrire facilement ces fichiers.

Documentation : https://docs.python.org/fr/3.11/library/csv.html#module-csv

# 2. Lecture d'un fichier CSV
## 2.1. Lire un fichier ligne par ligne
Voici comment ouvrir et lire un fichier CSV en affichant chaque ligne :

```py
import csv

# Ouvrir un fichier CSV en lecture
with open("data.csv", "r", newline="", encoding="utf-8") as fichier_csv:
    lecteur = csv.reader(fichier_csv, delimiter=";")  # Crée un objet lecteur
    for ligne in lecteur:  # Parcourt chaque ligne du fichier
        print(ligne)  # Affiche la ligne sous forme de liste
```

## 2.2. Lire un fichier CSV en utilisant des noms de colonnes
Si votre fichier CSV a une ligne d'en-tête (les noms des colonnes), vous pouvez utiliser csv.DictReader pour accéder aux valeurs par leur nom :

```py
import csv

# Ouvrir un fichier CSV en lecture
with open("data.csv", "r", newline="", encoding="utf-8") as fichier_csv:
    lecteur = csv.DictReader(fichier_csv, delimiter=";")  # Lit en tant que dictionnaire
    for ligne in lecteur:
        print(ligne["nom"])  # Accède à la colonne "nom"
```

# 3. Écriture dans un fichier CSV
## 3.1. Écrire des lignes sous forme de listes
Pour écrire un fichier CSV avec plusieurs lignes :

```py
import csv

# Données à écrire dans une liste de listes
donnees = [
    ["nom", "age", "ville"],  # Il faut commencer par l'en-tête
    ["Alice", 25, "Paris"],
    ["Bob", 30, "Lyon"],
    ["Charlie", 35, "Marseille"]
]

# Ouvrir un fichier CSV en écriture
with open("sortie.csv", "w", newline="", encoding="utf-8") as fichier_csv:
    ecrivain = csv.writer(fichier_csv, delimiter=";")  # Crée un objet écrivain
    ecrivain.writerows(donnees)  # Écrit toutes les lignes en une seule fois
```

**Remarque** : On peut aussi écrire une ligne à la fois en utilisant la méthode `writerow()`
```py
ecrivain.writerow(["Gérard", 75, "Lille"])
```

## 3.2. Écrire des lignes sous forme de dictionnaires
Si vous souhaitez écrire un fichier CSV en utilisant des noms de colonnes :

```py
import csv

# Données à écrire dans une liste de dictionnaires
donnees = [
    {"nom": "Alice", "age": 25, "ville": "Paris"},
    {"nom": "Bob", "age": 30, "ville": "Lyon"},
    {"nom": "Charlie", "age": 35, "ville": "Marseille"}
]

# Ouvrir un fichier CSV en écriture
with open("sortie.csv", "w", newline="", encoding="utf-8") as fichier_csv:
    champs = ["nom", "age", "ville"] # l'en-tête
    ecrivain = csv.DictWriter(fichier_csv, fieldnames=champs, delimiter=";")  # Écriture par clé
    ecrivain.writeheader()  # Écrit l'en-tête
    ecrivain.writerows(donnees)  # Écrit toutes les lignes de données
```

**Remarque** : On peut aussi écrire une ligne à la fois en utilisant la méthode `writerow()`
```py
ecrivain.writerow({"nom": "Gérard", "age": 75, "ville": "Lille"})
```

# 4. Extraction d'une information spécifique
Si on veut extraire une information précise, comme chercher une personne nommée "Bob" dans un fichier CSV :

```py
import csv

# Ouvrir le fichier CSV
with open("data.csv", "r", newline="", encoding="utf-8") as fichier_csv:
    lecteur = csv.DictReader(fichier_csv, delimiter=";")
    for ligne in lecteur:
        if ligne["nom"] == "Bob":
            print(f"Bob a {ligne['age']} ans et vit à {ligne['ville']}.")
```


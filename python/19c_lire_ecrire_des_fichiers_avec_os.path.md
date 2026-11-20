(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 19c : Lire et écrire des fichiers avec `os.path`
> * Auteur : Gwénaël LAURENT
> * Date : 03/10/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 19c : Lire et écrire des fichiers avec `os.path`](#chap-19c--lire-et-écrire-des-fichiers-avec-ospath)
- [1. Introduction](#1-introduction)
- [2. Les bases de la gestion des fichiers en Python](#2-les-bases-de-la-gestion-des-fichiers-en-python)
  - [2.1. Ouvrir un fichier](#21-ouvrir-un-fichier)
  - [2.2. Fermer un fichier](#22-fermer-un-fichier)
  - [2.3. Utilisation de with](#23-utilisation-de-with)
- [3. Les fichiers texte](#3-les-fichiers-texte)
  - [3.1. Lecture des fichiers](#31-lecture-des-fichiers)
    - [3.1.1. Lire tout le contenu](#311-lire-tout-le-contenu)
    - [3.1.2. Lire ligne par ligne](#312-lire-ligne-par-ligne)
    - [3.1.3. Lire un certain nombre de caractères](#313-lire-un-certain-nombre-de-caractères)
  - [3.2. Écriture dans les fichiers texte](#32-écriture-dans-les-fichiers-texte)
    - [3.2.1. Écriture avec `write()`](#321-écriture-avec-write)
    - [3.2.2. Ajout avec `append()`](#322-ajout-avec-append)
- [4. Les fichiers binaires](#4-les-fichiers-binaires)
  - [4.1. Lecture d’un fichier binaire](#41-lecture-dun-fichier-binaire)
  - [4.2. Écriture dans un fichier binaire](#42-écriture-dans-un-fichier-binaire)
- [5. Méthodes pratiques supplémentaires](#5-méthodes-pratiques-supplémentaires)
  - [5.1. `tell()` et `seek()`](#51-tell-et-seek)
- [6. Exemples d'utilisation pratiques](#6-exemples-dutilisation-pratiques)
  - [6.1. Exemple : Lire et copier un fichier texte](#61-exemple--lire-et-copier-un-fichier-texte)
  - [6.2. Exemple : Stocker des données structurées (CSV)](#62-exemple--stocker-des-données-structurées-csv)
- [7. Bonnes pratiques](#7-bonnes-pratiques)


# 1. Introduction
La gestion des fichiers est une compétence essentielle en programmation, car elle permet de lire et écrire des données de manière persistante.

Python supporte plusieurs types de fichiers, mais nous allons nous concentrer ici sur les **fichiers texte** (.txt, .log, .conf, ...) et les **fichiers binaires** (qui ne contiennent pas que des caractères).

Doc : https://www.w3schools.com/python/python_ref_file.asp

# 2. Les bases de la gestion des fichiers en Python

## 2.1. Ouvrir un fichier

Doc : https://docs.python.org/fr/3.11/library/functions.html#open

La première étape pour interagir avec un fichier est de l'ouvrir. Pour cela, on utilise la fonction `open()`, qui prend deux arguments principaux :
- **Nom du fichier** : Le chemin vers le fichier (relatif ou absolu).
- **Mode d'ouverture** : Indique l'action à effectuer sur le fichier (lecture, écriture, etc.).

Les modes d'ouverture les plus courants sont :
- `'r'` : Lecture seule (read). Le fichier doit exister.
- `'w'` : Écriture (write). Si le fichier existe, il est écrasé ; sinon, un nouveau fichier est créé.
- `'a'` : Ajout (append). Écrit à la fin du fichier sans effacer son contenu.
- `'b'` : Mode binaire. Utilisé pour ouvrir des fichiers non texte (images, vidéos, etc.).

**Exemple :**

```python
# Ouvre un fichier en lecture seule
fichier = open('monfichier.txt', 'r')
```

## 2.2. Fermer un fichier
Il est important de fermer un fichier après l'avoir utilisé pour libérer les ressources. On utilise la méthode close() pour cela.

Exemple :

```py
fichier.close()
```

## 2.3. Utilisation de with
Une bonne pratique est d’utiliser le mot-clé ` ` pour ouvrir un fichier. Cela garantit que le fichier sera automatiquement fermé, même en cas d'erreur.

Exemple :

```py
with open('monfichier.txt', 'r') as fichier:
    contenu = fichier.read()
# Ici, le fichier est automatiquement fermé
```

# 3. Les fichiers texte

Doc : https://docs.python.org/3/library/io.html#io.TextIOBase

## 3.1. Lecture des fichiers
### 3.1.1. Lire tout le contenu
La méthode read() permet de lire tout le contenu d'un fichier d’un coup.

Exemple :

```py
with open('monfichier.txt', 'r') as fichier:
    contenu = fichier.read()
    print(contenu)
```

### 3.1.2. Lire ligne par ligne
Pour lire un fichier ligne par ligne, on peut utiliser la méthode readline() ou itérer directement sur le fichier.

Exemple avec readline() :

```py
with open('monfichier.txt', 'r') as fichier:
    ligne = fichier.readline()
    while ligne:
        print(ligne, end='')  # `end=''` pour éviter les lignes vides supplémentaires
        ligne = fichier.readline()
```

Exemple avec une boucle for :

```py
with open('monfichier.txt', 'r') as fichier:
    for ligne in fichier:
        print(ligne, end='')
```

### 3.1.3. Lire un certain nombre de caractères
On peut également spécifier un nombre de caractères à lire en passant un argument à la méthode read().

Exemple :

```py
with open('monfichier.txt', 'r') as fichier:
    contenu = fichier.read(100)  # Lire les 100 premiers caractères
    print(contenu)
```

## 3.2. Écriture dans les fichiers texte
### 3.2.1. Écriture avec `write()`
La méthode `write()` permet d'écrire dans un fichier. Si le fichier n'existe pas, Python le crée automatiquement en mode 'w' ou 'a'.

Exemple :

```py
with open('monfichier.txt', 'w') as fichier:
    fichier.write("Ceci est un test.\n")
```

### 3.2.2. Ajout avec `append()`
Si vous voulez ajouter du contenu à un fichier existant sans le remplacer, vous pouvez utiliser le mode 'a'.

Exemple :

```py
with open('monfichier.txt', 'a') as fichier:
    fichier.write("Nouvelle ligne ajoutée.\n")
```

# 4. Les fichiers binaires
Les fichiers binaires sont utilisés pour des données autres que du texte, comme des images ou des fichiers audio. Lors de la manipulation de ces fichiers, il faut spécifier le mode binaire en ajoutant un 'b' après le mode d'ouverture ('rb', 'wb', etc.).

Doc : https://docs.python.org/3/library/io.html#io.BufferedIOBase

## 4.1. Lecture d’un fichier binaire
Exemple :

```py
with open('image.jpg', 'rb') as fichier:
    contenu = fichier.read()
    print(contenu[:100])  # Affiche les 100 premiers octets
```

## 4.2. Écriture dans un fichier binaire
Exemple :

```py
with open('copie_image.jpg', 'wb') as fichier:
    fichier.write(contenu)  # Écrit les données binaires dans un nouveau fichier
```

# 5. Méthodes pratiques supplémentaires
## 5.1. `tell()` et `seek()`
Ces méthodes sont utilisées pour gérer la position du curseur de lecture/écriture dans un fichier :

* **`tell()`** : Retourne la position actuelle du curseur.
* **`seek(offset)`** : Déplace le curseur à la position spécifiée.

Exemple :

```py
with open('monfichier.txt', 'r') as fichier:
    print(fichier.tell())  # Position initiale : 0
    fichier.read(10)  # Lire les 10 premiers caractères
    print(fichier.tell())  # Position : 10
    fichier.seek(0)  # Revenir au début du fichier
```

# 6. Exemples d'utilisation pratiques
## 6.1. Exemple : Lire et copier un fichier texte


```py
with open('fichier_source.txt', 'r') as source, open('fichier_copie.txt', 'w') as copie:
    for ligne in source:
        copie.write(ligne)
```

## 6.2. Exemple : Stocker des données structurées (CSV)
Les fichiers CSV sont souvent utilisés pour stocker des données tabulaires. Python dispose d’un module intégré pour les gérer : `csv`.

Documentation : https://docs.python.org/3/library/csv.html#module-csv

Exemple simple :

```py
import csv

# Lecture d'un fichier CSV
with open('donnees.csv', newline='') as fichier_csv:
    lecteur = csv.reader(fichier_csv)
    for ligne in lecteur:
        print(ligne)
```

# 7. Bonnes pratiques
* Toujours fermer les fichiers : Utiliser with pour s'assurer que le fichier est fermé automatiquement.
* Gérer les erreurs : Utiliser les blocs try-except pour gérer les erreurs liées aux fichiers inexistants ou aux permissions.
* Travailler avec des fichiers volumineux : Lire les fichiers en utilisant des boucles pour éviter de charger tout le fichier en mémoire.


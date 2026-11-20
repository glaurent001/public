(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 19a : Accéder au système de fichiers avec `pathlib`
> * Auteur : Gwénaël LAURENT
> * Date : 18/11/2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 19a : Accéder au système de fichiers avec `pathlib`](#chap-19a--accéder-au-système-de-fichiers-avec-pathlib)
- [1. Introduction](#1-introduction)
- [2. Importer la classe principale `Path`](#2-importer-la-classe-principale-path)
- [3. Chemins d'accès absolus ou relatifs](#3-chemins-daccès-absolus-ou-relatifs)
- [4. Créer un chemin à partir d'un chemin existant : `joinpath()`](#4-créer-un-chemin-à-partir-dun-chemin-existant--joinpath)
- [5. Les différentes parties d'un chemin d'accès : `parts` et `name`](#5-les-différentes-parties-dun-chemin-daccès--parts-et-name)
- [6. Tester si le fichier/dossier existe : `exists()`](#6-tester-si-le-fichierdossier-existe--exists)
- [7. Tester si c'est un dossier ou un fichier : `is_dir()`, `is_file()`](#7-tester-si-cest-un-dossier-ou-un-fichier--is_dir-is_file)
- [8. Répertoire courant : `cwd()`](#8-répertoire-courant--cwd)
- [9. Emplacement du fichier script](#9-emplacement-du-fichier-script)
- [10. Localiser un fichier **dans le même dossier que le script**](#10-localiser-un-fichier-dans-le-même-dossier-que-le-script)
- [11. Parcourir tous les sous dossiers : `iterdir()`](#11-parcourir-tous-les-sous-dossiers--iterdir)
- [12. Parcourir tous les fichiers présents dans un dossier : `glob()`](#12-parcourir-tous-les-fichiers-présents-dans-un-dossier--glob)
- [13. Informations sur un fichier : `stat()`](#13-informations-sur-un-fichier--stat)


# 1. Introduction

La technique présentée ici met en oeuvre le module **`pathlib`** pour accéder aux fichiers. Ce module est disponible pour des versions de python >= 3.4 (2014).\
*Pour info, l'ancienne technique utilisait `os.path`.*

`pathlib` offre plusieurs avantages :
* **Portabilité** : Gère automatiquement les différences de chemin entre les systèmes d'exploitation (Windows, Linux, macOS).
* **Fonctions intégrées** : Facilite les manipulations comme vérifier l'existence d'un fichier, créer des répertoires, lire/écrire des fichiers, etc.

Documentation [pathlib sur python.org](https://docs.python.org/fr/3.8/library/pathlib.html) et les [méthodes de la classe Path](https://docs.python.org/fr/3.11/library/pathlib.html#methods)

# 2. Importer la classe principale `Path`
```py
from pathlib import Path
```

La classe Path représente l'**emplacement des dossiers ou fichiers** sous une forme abstraire appelée **"path"** (chemin).

Quand on utilise *Path*, les chemins sont automatiquemnt adaptés au système de fichiers Windows ou Linux que vous utilisez. C'est très avantageux pour la portabilité de votre code.

Par exemple sur Windows :
```py
>>> Path("c:\\program files") 
WindowsPath('c:/program files')
```
et sur Linux :
```py
>>> Path('/etc')
PosixPath('/etc')
```
# 3. Chemins d'accès absolus ou relatifs
> Attention aux anti-slash `\` dans les chemins Windows. Dans une chaîne de caractères c'est le caractère d'échappement. Il faut donc :
> * soit les doubler (`\\`), 
> * soit indiquer que la string est en mode raw avec un r devant les doubles quotes : `r"..."`,
> * soir remplacer tous les `\` par de `/` (comme les chemins d'accès Linux)

On peut accéder à un fichier en indiquant son **emplacement absolu** dans une chaîne de caractères :

```py
p = Path(r"I:\tempPython\TP_python\19_fichiers\tests_pathlib.py")
```

> **Remarque** : *Les emplacement absolus peuvent aussi être des **chemins UNC** (Uniform Naming Convention).\
UNC est une convention sur une manière de définir l’adresse d’une ressource sur un réseau.\
Une adresse UNC utilise la syntaxe suivante :*\
`\\NomOuIpDuServeur\NomDuPartage\Dossier\NomDuFichier`

On peut aussi accéder à un fichier en indiquant son **emplacement relatif** par rapport au répertoire courant
```py
p = Path(r".\19_fichiers\tests_pathlib.py")
```

On peut **convertir un chemin relatif en chemin absolu** en appelant la méthode `resolve()`
```py
>>> p = Path(r".\19_fichiers\tests_pathlib.py")
>>> p.resolve()  
WindowsPath('I:/tempPython/TP_python/19_fichiers/tests_pathlib.py')
```
# 4. Créer un chemin à partir d'un chemin existant : `joinpath()`
La méthode `joinpath()` permet de créer des chemins enfants à partir d'un chemin de base :

```py
>>> p = Path(r"I:/tempPython/TP_python")
>>> p.joinpath(r"subdir/file.py")  
WindowsPath('I:/tempPython/TP_python/subdir/file.py')
```

L'opérateur slash `/` réalise la même chose pour les chemins de type `Path` (concaténation des chemins):

```py
>>> p = Path(r"I:/tempPython/TP_python")
>>> p / r"subdir\file.py"
WindowsPath('I:/tempPython/TP_python/subdir/file.py')
```

# 5. Les différentes parties d'un chemin d'accès : `parts` et `name`
La propriété `parts` renvoie un tuple composé des **différentes parties du chemin** :
```py
>>> p = Path(r"I:/tempPython/TP_python/19_fichiers/tests_pathlib.py")
>>> p.parts
('I:\\', 'tempPython', 'TP_python', '19_fichiers', 'tests_pathlib.py')
```

Attention aux chemins relatifs ! Si on veut obtenir toutes les parties du chemin absolu, il faut convertir le chemin relatif en chemin absolu avec la méthode `resolve()`
```py
>>> p = Path(r".\19_fichiers\tests_pathlib.py")
>>> p.parts
('19_fichiers', 'tests_pathlib.py')
>>> p.resolve()  
WindowsPath('I:/tempPython/TP_python/19_fichiers/tests_pathlib.py')
>>> p.resolve().parts
('I:\\', 'tempPython', 'TP_python', '19_fichiers', 'tests_pathlib.py')
```

On peut obtenir le **nom du fichier** à partir d'un chemin d'accès en utilisant la propriété `name`
```py
>>> p = Path(r".\19_fichiers\tests_pathlib.py")
>>> p.name
'tests_pathlib.py'
```

# 6. Tester si le fichier/dossier existe : `exists()`
Tester si le chemin pointe sur un fichier ou dossier existant :
```py
>>> Path('setup.py').exists()
True
>>> Path('nonexistentfile').exists()
False
```

# 7. Tester si c'est un dossier ou un fichier : `is_dir()`, `is_file()`

```py
>>> Path("c:\program files").is_dir()
True
>>> Path("c:\program files").is_file() 
False
>>> Path("c:\swapfile.sys").is_file()  
True
>>> Path("c:\swapfile.sys").is_dir()  
False
```


# 8. Répertoire courant : `cwd()`
Le **répertoire courant** ("current working directory" ou **CWD**) est le répertoire dans lequel votre programme Python est en train de s'exécuter à un moment donné.\
C'est à partir de ce répertoire que Python recherche les fichiers lorsqu'on utilise des chemins relatifs.

> Quand on lance un script à partir du terminal, **le répertoire courant correspond au prompt du terminal et pas nécessairement à l'emplacement du script !!!**

Pour afficher le répertoire courant :
```py
>>> rep_courant = Path.cwd()
>>> print(rep_courant)
I:\tempPython\TP_python
```
ou on peut aussi utiliser l'emplacement relatif actuel `'.'` et le convertir en chemin absolu :
```py
>>> rep_courant = Path('.').resolve()
>>> print(rep_courant)
I:\tempPython\TP_python
```

# 9. Emplacement du fichier script
Quand un script s'exécute, l'interpréteur créé la variable globale `__file__` qui contient l'emplacement absolu du script.

Dans un script  :
```py
script_path = Path(__file__)
print(f"Le script est situé à : {script_path}")
```
Ce qui donne par exemple :
```
Le script est situé à : I:\tempPython\TP_python\19_fichiers\tests_pathlib.py
```

Si vous voulez **juste obtenir le dossier** contenant le script en cours d'exécution :
```py
script_directory = Path(__file__).parent
print(f"Le script se trouve dans le répertoire : {script_directory}")
```
Ce qui donne par exemple :
```
Le script se trouve dans le répertoire : i:\tempPython\TP_python\19_fichiers
```
# 10. Localiser un fichier **dans le même dossier que le script**
**Objectif :** Ouvrir un fichier qui est situé dans le même dossier que le script python, mais ce n'est pas le répertoire courant.

Il faut :
* obtenir le dossier contenant le script avec `Path(__file__).parent`
* utiliser `joinpath()` pour ajouter le nom du fichier ciblé

Exemple :
```py
# Localiser le fichier dans le dossier du script
script_directory = Path(__file__).parent
fichier = script_directory.joinpath("monfichier.txt")
```



# 11. Parcourir tous les sous dossiers : `iterdir()`
```py
liste_d = Path(".")
for dossier in liste_d.iterdir():
    print(dossier)
```

# 12. Parcourir tous les fichiers présents dans un dossier : `glob()`
Pour rechercher tous les fichiers contenus dans un dossier, on utilise la méthode `glob()` :
```py
liste_f = Path(".").glob("*")
for fichier in liste_f :
    print(fichier.name)
```
L'argument de la méthode glob() est un "**motif**" qui permet de sélectionner tous les fichiers ou seulement certains types de fichier.

Par exemple 
```py
Path(".").glob("*.py")
```
ne retournera que les fichiers d'extension `.py`

L'ajout de `"**/"` permet de rechercher les fichiers dans « ce dossier et ses sous-dossiers, récursivement ».

Par exemple
```py
Path(".").glob("**/*.py")
```

De façon similaire à appeler glob() avec "**/", on peut utiliser la méthode `rglob()` pour une recherche récursive dans le dossier et ses sous-dossiers :

```py
Path(".").rglob("*.py")
```

# 13. Informations sur un fichier : `stat()`

```py
fichier = Path(__file__)
# Taille du fichier en bytes
print(fichier.stat().st_size)
# Date de la dernière modification, exprimé en secondes (POSIX timestamp)
print(fichier.stat().st_mtime)
```

La date de dernière modification `st_mtime` est exprimée en nombre de secondes (POSIX timestamp). Pour la **convertir au format datetime**, puis en chaîne de caractères du style `04-10-2024 23:33:14`, vous pouvez utiliser :

```py
from datetime import datetime

date_modif = datetime.fromtimestamp(fichier.stat().st_mtime)
print(date_modif.strftime("%d-%m-%Y %H:%M:%S"))
```

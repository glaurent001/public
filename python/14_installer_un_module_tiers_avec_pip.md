(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 14 : Installer un module tiers avec `pip`

> * Auteur : Gwénaël LAURENT
> * Date : 27/08/2024
> * OS : Windows 10

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 14 : Installer un module tiers avec `pip`](#chap-14--installer-un-module-tiers-avec-pip)
- [1. Gestionnaire de paquets](#1-gestionnaire-de-paquets)
- [2. Installer un paquet et ses dépendances](#2-installer-un-paquet-et-ses-dépendances)
- [3. Mettre à jour un paquet déjà installé](#3-mettre-à-jour-un-paquet-déjà-installé)
- [4. Lister les paquets installés](#4-lister-les-paquets-installés)
- [5. Supprimer un paquet](#5-supprimer-un-paquet)
- [6. Connaitre l'emplacement du paquet sur le disque](#6-connaitre-lemplacement-du-paquet-sur-le-disque)
- [7. Connaitre les noms des variables utilisées dans l'espace de nom d'un module](#7-connaitre-les-noms-des-variables-utilisées-dans-lespace-de-nom-dun-module)


# 1. Gestionnaire de paquets
Comme pour les modules intégrés et la bibliothèque standard (sys, math, random, ...), l'utilisation de la vaste collection de modules tiers de Python permet de gagner du temps (numpy, matplotlib, ...)

L'installation des bibliothèques tierses (modules ou paquets) se fait grâce à l'utilitaire **`pip`** :  *Package Installer for Python* (à utiliser dans un terminal). `pip` est le gestionnaire de paquets Python. Il permet d'installer ou de mettre à jour les paquets. Il est installé par défaut avec Python 3.4+.

La liste des paquets disponibles avec pip est disponible via le front-end web de **`PyPI`** (*Python Package Index*): https://pypi.org/

> **Si plusieurs modules sont disponibles pour gérer mon cas d’usage, lequel dois-je utiliser ?** 
> 
> La réponse est simple : commencez par le projet qui semble afficher le plus de cas d’usage ou bénéficier d’une forte adoption (en fonction du nombre d’étoiles ou de forks GitHub, par exemple), car il y a de fortes chances que votre cas d’usage soit semblable à celui de beaucoup d'autres personnes.

# 2. Installer un paquet et ses dépendances
La commande suivante va installer la dernière version d’un module et ses dépendances depuis PyPI :

```cmd
python -m pip install SomePackage
```

Le début de la commande (`python -m pip`) permet d'exécuter le module pip comme un script système.

> **Remarque pour Windows :**
> 
> Sous Windows, on peut utiliser la commande
> 
> ```cmd
> pip install SomePackage
> ```
> Cependant, la commande complète est à préférer car elle permet de sélectionner la version de l'interpréteur python. Ca peut être utile car pip gère les package en fonction de l'interpréteur choisi (et il peut y avoir plusieurs version de python sur la même machine)

Il est aussi possible de préciser une version du module à installer :

```cmd
python -m pip install SomePackage==1.0.4    # specific version
python -m pip install "SomePackage>=1.0.4"  # minimum version
```


# 3. Mettre à jour un paquet déjà installé
Normalement, si un module approprié est déjà installé, l'installer à nouveau n'aura aucun effet. La mise à jour de modules existants doit être demandée explicitement :

```cmd
python -m pip install --upgrade SomePackage
```

# 4. Lister les paquets installés

```cmd
python -m pip list
```

# 5. Supprimer un paquet


```cmd
python -m pip uninstall SomePackage
```

Malheureusement, pip ne désinstalle pas les dépendances lorsque vous désinstallez le package d'origine. Il faut donc au péalable vérifier la liste des dépendances du package avec :

```cmd
python -m pip show SomePackage
```

# 6. Connaitre l'emplacement du paquet sur le disque

```py
>>> import matplotlib
>>> matplotlib
<module 'matplotlib' from 'C:\\Users\\gwenael\\AppData\\Roaming\\Python\\Python311\\site-packages\\matplotlib\\__init__.py'>
```

# 7. Connaitre les noms des variables utilisées dans l'espace de nom d'un module

```py
>>> import matplotlib
>>> dir(matplotlib)
['ExecutableNotFoundError', 'MatplotlibDeprecationWarning', 'MutableMapping', 'Parameter', 'Path', 'RcParams', '_ExecInfo', '_VersionInfo', '__all__', '__bibtex__', '__builtins__', '__cached__', 
...
'transforms', 'use', 'validate_backend', 'warnings']
```


Voir aussi :
* https://docs.python.org/fr/3.10/installing/index.html
* https://packaging.python.org/en/latest/tutorials/installing-packages/
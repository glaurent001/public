(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 26 : Importation dynamique et installation de modules

> * Auteur : Gwénaël LAURENT
> * Date : 12/03/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 26 : Importation dynamique et installation de modules](#chap-26--importation-dynamique-et-installation-de-modules)
- [1. Présentation de l'importation dynamique](#1-présentation-de-limportation-dynamique)
- [2. Importation dynamique d'un module avec `importlib.import_module()`](#2-importation-dynamique-dun-module-avec-importlibimport_module)
- [3. Importation dynamique d'une seule fonction d'un module avec `getattr()`](#3-importation-dynamique-dune-seule-fonction-dun-module-avec-getattr)
- [4. Importer un module et installation automatique](#4-importer-un-module-et-installation-automatique)



# 1. Présentation de l'importation dynamique

**La manière classique et recommandée** pour importer un module en Python est d'utiliser `import` (cf [Modules et importations](12_modules_et_importations.md))
```py
import mon_module
```

Dans certains cas, il est nécessaire d'utiliser une autre méthode qu'on appelle l'**importation dynamique** :
* si le nom du module est inconnu à l’avance (ex. : chargé depuis un fichier, une entrée utilisateur)
* si le nom du module est stocké dans une variable (ex. : plugins, extensions)
* pour vérifier si une bibliothèque est installée et, si ce n’est pas le cas, l’installer automatiquement.

**Inconvénients de l'importation dynamique :**
* Importation à l’exécution, donc pas d'intellisense dans VScode.
* Moins lisible


# 2. Importation dynamique d'un module avec `importlib.import_module()`

`importlib.import_module()` est une fonction permettant d’importer un module dynamiquement à l’exécution (depuis python 3.1, [Documentation](https://docs.python.org/3/library/importlib.html#importlib.import_module))

```py
import importlib

module_name = "math"
math_module = importlib.import_module(module_name)
print(math_module.sqrt(16))
```

Il faut gérer l'exceptions `ModuleNotFoundError` si le module n'est pas installé (cf [Gestion des erreurs en Python](15_gestion_des_erreurs.md)).

Ce qui donne le code suivant :

```py
import importlib

try:
    module_name = "module_tiers"
    module_tiers = importlib.import_module(module_name)
except ModuleNotFoundError as e:
    print(f"Erreur : {e}")
```

# 3. Importation dynamique d'une seule fonction d'un module avec `getattr()`

On peut charger dynamiquement une seule fonction d'un module tiers sans charger le module complet (ce qui correspond à `from module_tiers import fonction_tierce`)

`getattr()` est une fonction intégrée à python permettant d’importer un fonction d'un module ([Documentation](https://docs.python.org/3/library/functions.html#getattr))

```py
import importlib

# Charger le module
module_name = "module_tiers"
function_name = "fonction_tierce"

fonction_tierce = getattr(importlib.import_module(module_name), function_name)

# Utilisation
fonction_tierce(...)
```

Il faut gérer 2 exceptions (cf [Gestion des erreurs en Python](15_gestion_des_erreurs.md)) :
* `AttributeError` si la fonction n'existe pas
* `ModuleNotFoundError` si le module n'est pas installé

Ce qui donne le code suivant : 
```py
import importlib

module_name = "module_tiers"
function_name = "fonction_tierce"

try:
    fonction_tierce = getattr(importlib.import_module(module_name), function_name)
    print(fonction_tierce(...))  # Appel de la fonction
except ModuleNotFoundError:
    print(f"Le module '{module_name}' est introuvable.")
except AttributeError:
    print(f"La fonction '{function_name}' n'existe pas dans '{module_name}'.")
```



# 4. Importer un module et installation automatique

> L'installation ne concerne que les modules tiers (non fournis avec python)

Si le module tiers est manquant, on peut proposer de l'installer automatiquement :
1. On tente d’importer le module.
2. S’il est absent, l'exception `ModuleNotFoundError` est capturé (cf [Gestion des erreurs en Python](15_gestion_des_erreurs.md)).
3. On installe le module avec `python -m pip install mon_module`.
4. On réessaie l’importation après installation.

```py
import importlib
import subprocess
import sys

module_name = "module_tiers"

try:
    module_tiers = importlib.import_module(module_name)
except ModuleNotFoundError:
    print(f"Le module '{module_name}' est introuvable. Installation en cours...")
    subprocess.check_call([sys.executable, "-m", "pip", "install", module_name])
    module_tiers = importlib.import_module(module_name)  # Réessayer après installation

print("Module importé avec succès !")
```

**Explications :**

* **`python -m pip install ma_bibliotheque`** C'est la commande complète pour installer un module. Elle permet de s'assurer que la bibliothèque est installé pour le même interpréteur python que celui qui exécute le script (car il peut y avoir plusieurs versions de python installées sur la même machine)

* **`subprocess.check_call()`** est une fonction du module subprocess qui permet d'exécuter une commande système en Python. Elle prend comme argument une liste  contenant la commande a exécuter et ses arguments.
    ```py
    import subprocess

    try:
        # Exécute la commande 'ls -l' (Linux/macOS)
        subprocess.check_call(["ls", "-l"])
        print("Commande exécutée avec succès !")
    except subprocess.CalledProcessError as e:
        print(f"Erreur lors de l'exécution de la commande : {e}")
    ```

* **`sys.executable`** est un attribut du module `sys` de Python qui retourne le chemin absolu de l’interpréteur Python en cours d’exécution. Il est souvent utilisé pour installer des packages via pip dans le bon environnement :
    ```py
    import subprocess
    import sys

    subprocess.check_call([sys.executable, "-m", "pip", "install", "ma_bibliotheque"])
    ```


(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 12 : Modules et importations

> * Auteur : David Cassagne - https://courspython.com/
> * Adaptation : Gwénaël LAURENT
> * Date : 01/10/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 12 : Modules et importations](#chap-12--modules-et-importations)
- [1. Modules](#1-modules)
  - [1.1. on importe une seule fonction](#11-on-importe-une-seule-fonction)
  - [1.2. on importe explicitement les deux fonctions](#12-on-importe-explicitement-les-deux-fonctions)
  - [1.3. on importe toutes les fonctions](#13-on-importe-toutes-les-fonctions)
  - [1.4. on importe le module](#14-on-importe-le-module)
  - [1.5. on importe le module et on lui donne un alias](#15-on-importe-le-module-et-on-lui-donne-un-alias)
  - [1.6. on importe une fonction d’un module et on lui donne un alias](#16-on-importe-une-fonction-dun-module-et-on-lui-donne-un-alias)
- [2. Package](#2-package)
- [3. Utiliser un script en tant que module](#3-utiliser-un-script-en-tant-que-module)
  - [3.1. Définitions : script et module](#31-définitions--script-et-module)
  - [3.2. Le problème du programme principal du script](#32-le-problème-du-programme-principal-du-script)


Dans cette page, nous allons répondre aux questions suivantes :

*   comment utiliser une même fonction dans plusieurs programmes différents ?
*   comment avoir la définition d’une fonction dans un fichier différent de celui qui contient le programme principal ?

# 1. Modules
Très souvent, c’est une personne qui définit une fonction et une autre qui l’utilise. Par exemple, avec la bibliothèque **matplotlib**, on peut utiliser la fonction `plot()` pour tracer des courbes sans avoir à écrire nous-mêmes cette fonction. Nous allons donc voir à présent comment définir des fonctions dans un **module** et faire en sorte qu’un utilisateur puisse appeler ces fonctions dans son programme.

Par exemple, nous allons créer un fichier nommé `puissance.py` qui va définir 2 fonctions : `carre()` et `cube()`. Un tel fichier est appelé un _module_ et il va pouvoir être _importé_ dans un autre fichier, et en particulier dans le fichier qui contient le programme principal.

```py
def carre(valeur):
    resultat = valeur**2
    return resultat

def cube(valeur):
    resultat = valeur**3
    return resultat
```

Il est maintenant possible d’utiliser dans un programme principal les fonctions qui ont été définies dans le module `puissance.py`. Pour cela, il faut importer les fonctions à partir du module.

## 1.1. on importe une seule fonction

```py
from puissance import carre

a = 5
u = carre(a)
print("le carre vaut", u)
```

> Avertissement : Le fichier `puissance.py` doit être dans le même répertoire que le programme principal (ou bien se trouver dans le « path » de Python).

## 1.2. on importe explicitement les deux fonctions

```py
from puissance import carre, cube

a = 5
u = carre(a)
print("le carre vaut", u)
v = cube(a)
print("le cube vaut", v)
```

## 1.3. on importe toutes les fonctions

```py
from puissance import *

a = 5
u = carre(a)
print("le carre vaut", u)
v = cube(a)
print("le cube vaut", v)
```

> **ATTENTION :**\
> L’importation de toutes les fonctions avec `*` est **fortement déconseillée**. En effet, elle ne permet pas d’avoir une vision claire des fonctions qui ont été importées. Ceci est donc une source potentielle d’erreurs.

## 1.4. on importe le module

```py
import puissance

a = 5
u = puissance.carre(a)
print("le carre vaut", u)
v = puissance.cube(a)
print("le cube vaut", v)
```

> Note : Dans ce cas, **il faut préciser le nom du module devant la fonction**.

## 1.5. on importe le module et on lui donne un alias

```py
import puissance as pu
a = 5
u = pu.carre(a)
print("le carre vaut", u)
v = pu.cube(a)
print("le cube vaut", v)
```

## 1.6. on importe une fonction d’un module et on lui donne un alias

Il est aussi possible de donner un alias à une fonction comme dans l’exemple suivant :

```py
from puissance import carre as ca

a = 5
u = ca(a)
print("le carre vaut", u)
```

# 2. Package 

Quand on a un grand nombre de modules, il peut être intéressant de les organiser dans des dossiers. **Un dossier qui rassemble des modules est appelé un package** (paquetage en français). Le nom du package est le même que celui du dossier. Par exemple, on crée un dossier `package1` dans lequel on place le fichier `module1.py` suivant :

```py
def fonction1(a):
    return a**2

```

On peut ensuite utiliser la fonction `fonction1()` définie dans `module1.py`, en important `package1.module1` comme dans l’exemple qui suit :

```py
import package1.module1

u = package1.module1.fonction1(3)
print("u vaut", u)
```

> Note : Il est aussi possible d’avoir des dossiers imbriqués, c’est-à-dire des dossiers qui contiennent d’autres dossiers.

# 3. Utiliser un script en tant que module
## 3.1. Définitions : script et module
Un même fichier `.py` peut jouer le rôle de script ou de module suivant son utilisation.

* **Script :**

    En Python, lorsqu’on crée un fichier qui rassemble des instructions, on appelle ce fichier un **_script_** et on le sauvegarde avec une extension `.py`, par exemple `essai.py`. La plupart du temps, ce fichier contient des fonctions et un programme principal.

* **Module :**

    Quand on est amené à travailler sur un programme long, il est possible d’effectuer la définition des fonctions dans un fichier séparé pour ensuite les utiliser dans un autre script. Le fichier qui contient ces définitions a aussi une extension `.py`, mais on appelle ce fichier un **_module_**.

## 3.2. Le problème du programme principal du script
Si on importe un script en tant que module, le code du programme principal qu'il contient va aussi s'exécuter ... et ce n'est pas souhaitable.

Pour éviter cela, on teste la valeur de la variable globale **`__name__`** :
* Quand on utilise un fichier en **tant que _script_**, la variable globale `__name__` prend pour valeur `'__main__'`.
* Quand on utilise un fichier **en tant que _module_**, la variable globale `__name__` prend pour valeur le nom du module

**Exemple :**

Par exemple, pour le fichier `puissance2.py` qui peut être utilisé aussi bien comme script ou comme module :

```py
def carre(valeur):
    resultat = valeur**2
    return resultat

if __name__ == "__main__":
    # Programme principal
    a = 3
    print("le carre vaut", carre(a))
```

On peut lancer une exécution directe en tant que script et on obtient alors :

```
le carre vaut 9
```

Ou bien on peut importer `puissance2` en tant que module, par exemple dans le fichier `test.py` suivant :

```py
import puissance2 as pu2

b = 4
print("le carre vaut", pu2.carre(b))
```

Si on exécute le script `test.py`, on obtient seulement l'exécution du programme principal de `test.py` (celui du module `puissance2` n'est pas exécuté) :

```
le carre vaut 16
```

Pour plus de détails, voir : 
* [Les modules sur la doc officielle de Python](https://docs.python.org/3/tutorial/modules.html).
* [Python Modules and Packages – An Introduction](https://realpython.com/python-modules-packages/)
* [Absolute vs Relative Imports in Python](https://realpython.com/absolute-vs-relative-python-imports/)

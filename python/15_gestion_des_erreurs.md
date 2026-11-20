(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 15 : Gestion des erreurs en Python

> * Auteur : Gwénaël LAURENT
> * Date : 17/09/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 15 : Gestion des erreurs en Python](#chap-15--gestion-des-erreurs-en-python)
- [1. Introduction](#1-introduction)
- [2. Types d'erreurs en Python](#2-types-derreurs-en-python)
  - [2.1. Erreurs de syntaxe](#21-erreurs-de-syntaxe)
  - [2.2. Exceptions](#22-exceptions)
- [3. Gestion des exceptions : `try`, `except`, `else`, `finally`](#3-gestion-des-exceptions--try-except-else-finally)
  - [3.1. Le bloc `try` et `except`](#31-le-bloc-try-et-except)
  - [3.2. Plusieurs blocs `except`](#32-plusieurs-blocs-except)
  - [3.3. Le bloc `else`](#33-le-bloc-else)
  - [3.4. Le bloc `finally`](#34-le-bloc-finally)
- [4. Lever des exceptions manuellement avec `raise`](#4-lever-des-exceptions-manuellement-avec-raise)
- [5. Création d'exceptions personnalisées](#5-création-dexceptions-personnalisées)
- [6. Remarque sur l'instruction `assert`](#6-remarque-sur-linstruction-assert)
  - [6.1. Quand utiliser assert ?](#61-quand-utiliser-assert-)
  - [6.2. Fonctionnement de `assert`](#62-fonctionnement-de-assert)
  - [6.3. Exemple simple d'utilisation d'assert](#63-exemple-simple-dutilisation-dassert)


# 1. Introduction
En programmation, il est fréquent de rencontrer des erreurs ou des exceptions. En Python, **la gestion des erreurs est essentielle pour éviter que les programmes ne plantent brusquement**. Cela permet de gérer les erreurs de manière contrôlée, d'informer l'utilisateur, ou de prendre des mesures correctives.


# 2. Types d'erreurs en Python
##  2.1. Erreurs de syntaxe
Les erreurs de syntaxe surviennent lorsque le code Python n'est pas correctement écrit. Elles sont détectées au moment de l'exécution, avant même que le programme ne se lance.

Exemple :

```py
print("Hello World
```
Erreur : le guillemet de fermeture est manquant.


## 2.2. Exceptions
Les exceptions sont des erreurs détectées lors de l'exécution d'un programme. Par exemple, division par zéro, accès à un index inexistant dans une liste, etc.

Exemple :

```py
x = 10 / 0  # Division par zéro
```

Cela génère une exception de type `ZeroDivisionError`.


# 3. Gestion des exceptions : `try`, `except`, `else`, `finally`
En Python, la gestion des exceptions se fait à l'aide des blocs `try`, `except` et `finally`.

## 3.1. Le bloc `try` et `except`
Le bloc `try` est utilisé pour tester un morceau de code susceptible de générer une exception.\
Si une exception survient, elle est capturée par le bloc `except`, ce qui permet de la gérer sans faire planter le programme.

Exemple :

```py
try:
    x = 10 / 0
except ZeroDivisionError:
    print("Erreur : division par zéro !")
```

##  3.2. Plusieurs blocs `except`
Il est possible de gérer plusieurs types d'exceptions en utilisant plusieurs blocs `except`.

Exemple :

```py
try:
    num = int(input("Entrez un nombre : "))
    resultat = 10 / num
except ValueError:
    print("Erreur : vous devez entrer un nombre valide.")
except ZeroDivisionError:
    print("Erreur : division par zéro.")
```

## 3.3. Le bloc `else`
Le bloc `else` s'exécute uniquement si aucune exception n'a été levée dans le bloc `try`.

Exemple :

```py
try:
    num = int(input("Entrez un nombre : "))
    resultat = 10 / num
except ZeroDivisionError:
    print("Erreur : division par zéro.")
else:
    print("Résultat :", resultat)
```

##  3.4. Le bloc `finally`
Le bloc `finally` s'exécute toujours, que l'exception soit levée ou non. Il est souvent utilisé pour des opérations de nettoyage (fermeture de fichiers, de connexions, etc.).

Exemple :

```py
try:
    fichier = open("data.txt", "r")
    contenu = fichier.read()
except FileNotFoundError:
    print("Erreur : fichier non trouvé.")
finally:
    fichier.close()
    print("Fichier fermé.")
```

# 4. Lever des exceptions manuellement avec `raise`
Il est possible de lever des exceptions manuellement en utilisant l'instruction `raise`. Cela est utile pour déclencher des **erreurs personnalisées**.

Exemple :

```py
def verifier_age(age):
    if age < 18:
        raise ValueError("L'âge doit être supérieur ou égal à 18.")
    return True

try:
    verifier_age(16)
except ValueError as e:
    print("Erreur :", e)
```
Affichage à l'exécution :
```
Erreur : L'âge doit être supérieur ou égal à 18.
```

# 5. Création d'exceptions personnalisées
Python permet également de définir ses propres exceptions en créant des classes héritant de ```Exception```.

Exemple :

```py
class MonException(Exception):
    pass

try:
    raise MonException("Ceci est une exception personnalisée.")
except MonException as e:
    print(e)
```
Affichage à l'exécution :
```
Ceci est une exception personnalisée.
```

# 6. Remarque sur l'instruction `assert`
* [python.org > L'instruction assert](https://docs.python.org/fr/dev/reference/simple_stmts.html#the-assert-statement)
* [w3schools.com > Python assert Keyword](https://www.w3schools.com/python/ref_keyword_assert.asp)
* 

Les instructions `assert` sont une manière pratique d'insérer des tests de débogage au sein d'un programme.

##  6.1. Quand utiliser assert ?
* *Débogage* : `assert` est souvent utilisé pour vérifier les hypothèses dans le code pendant le développement. Par exemple, vérifier qu'une variable a une valeur attendue avant de poursuivre l'exécution.
* *Vérification des préconditions* : Par exemple, vous pouvez l'utiliser pour valider les entrées dans une fonction.

> **ATTENTION :** en production,  Python est exécuté avec l'option -O (optimisation) et toutes les assertions sont ignorées. Cela signifie que **dans un environnement de production, il ne faut pas utiliser `assert`** pour des vérifications critiques liées à la logique de l'application, car ces vérifications peuvent être désactivées.

##  6.2. Fonctionnement de `assert`

La syntaxe de `assert` est la suivante :

```py
assert condition, message_optionnel
```

* _**condition**_ : Expression qui doit être évaluée comme True. Si elle est False, une exception est levée.
* _**message_optionnel**_ : (facultatif) Un message d'erreur qui s'affiche lorsque l'assertion échoue.


##  6.3. Exemple simple d'utilisation d'assert
```py
def diviser(a, b):
    assert b != 0, "Le diviseur ne doit pas être égal à zéro"
    return a / b
    
diviser(10, 0)  # Lève une AssertionError avec le message "Le diviseur ne doit pas être égal à zéro"
```

Dans cet exemple, si b est égal à zéro, l'assertion échoue et Python déclenche une AssertionError, signalant que la condition b != 0 n'est pas respectée.

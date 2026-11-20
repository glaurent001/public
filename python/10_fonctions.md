(_Cours Python : [retour sommaire](readme.md#les-bases-du-langage-python)_)
# Chap. 10 : Fonctions en Python

> * Auteur : David Cassagne - https://courspython.com/
> * Inspiré du livre de Gérard Swinnen [« Apprendre à programmer avec Python 3 »](http://inforef.be/swi/python.htm) 
> * Adaptation : Gwénaël LAURENT
> * Date : 01/10/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 10 : Fonctions en Python](#chap-10--fonctions-en-python)
- [1. A quoi ça sert ?](#1-a-quoi-ça-sert-)
- [2. Appel d'une fonction (utilisation)](#2-appel-dune-fonction-utilisation)
- [3. Définition d’une fonction (création)](#3-définition-dune-fonction-création)
- [4. Documenter la fonction](#4-documenter-la-fonction)
  - [4.1. Docstring de fonction](#41-docstring-de-fonction)
  - [4.2. Annotations de fonctions](#42-annotations-de-fonctions)
- [5. La définition des fonctions doit précéder leur utilisation](#5-la-définition-des-fonctions-doit-précéder-leur-utilisation)
- [6. Quelques remarques](#6-quelques-remarques)
  - [6.1. sur les paramètres des fonctions](#61-sur-les-paramètres-des-fonctions)
  - [6.2. sur les arguments d'appel](#62-sur-les-arguments-dappel)
  - [6.3. sur la valeur de retour](#63-sur-la-valeur-de-retour)
- [7. Variables locales, variables globales](#7-variables-locales-variables-globales)
  - [7.1. Espaces de noms](#71-espaces-de-noms)
  - [7.2. Accès aux  variables globales depuis l'intérieur d'une fonction](#72-accès-aux--variables-globales-depuis-lintérieur-dune-fonction)
  - [7.3. Modification d’une variable globale depuis l'intérieur d'une fonction](#73-modification-dune-variable-globale-depuis-lintérieur-dune-fonction)
- [8. Valeurs par défaut pour les paramètres](#8-valeurs-par-défaut-pour-les-paramètres)
- [9. Arguments avec étiquettes](#9-arguments-avec-étiquettes)
- [10. Voir aussi](#10-voir-aussi)


# 1. A quoi ça sert ?

**Lorsqu’une tâche doit être réalisée plusieurs fois par un programme avec seulement des paramètres différents, on peut l’isoler au sein d’une fonction**.

Par exemple, nous avons déjà utilisé diverses fonctions prédéfinies : `print()`, `input()`, `range()`, `len()` qui avaient été définise par quelqu’un d’autre.

# 2. Appel d'une fonction (utilisation)
L'appel (=l'utilisation) d'une fonction nécessite :
* d'utiliser son **nom** suivi de **parenthèses**
* de fournir un ou plusieurs **arguments**
* de récupérer sa **valeur de retour** (résultat de la fonction)

Exemple :

```py
val_max = max(15, 12)
```

* `max` : Nom de la fonction appelée
* `15` : 1er argument
* `12` : 2ème argument
* `val_max` contiendra le résultat de l'exécution de la fonction (sa valeur de retour)

# 3. Définition d’une fonction (création)

La création d'une fonction correspond à la **définition de son code interne**.

La définition d’une fonction contient :
1. Le mot clé **`def`** suivi du nom de la fonction et de ses paramètres
2. La définition des **variables locales** (elles n'existent que dans le corps de la fonction)
3. Le **traitement** réalisé par la fonction :
4. Une instruction permettant de **renvoyer une valeur** vers le programme appelant : **`return`**

La syntaxe Python pour la définition d’une fonction est la suivante :

```py
def nom_fonction(liste_de_paramètres):
      # définition des variables locales
      # traitement
      return valeur_de_retour
```

**Exemple de définition** d'une fonction :

```py
def soustraire(a, b):
    val_retour = a - b
    return val_retour
```

**Exemple d'appel** de cette fonction :

```py
resultat = soustraire(13, 5)
```

[Exécuter dans Python Tutor](https://pythontutor.com/render.html#code=def%20soustraire%28a,%20b%29%3A%0A%20%20%20%20val_retour%20%3D%20a%20-%20b%0A%20%20%20%20return%20val_retour%0A%0A%23%20programme%20principal%0A%0Aresultat%20%3D%20soustraire%2813,%205%29%0Aprint%20%28resultat%29&cumulative=false&curInstr=0&heapPrimitives=false&mode=display&origin=opt-frontend.js&py=3&rawInputLstJSON=%5B%5D&textReferences=false)

> Lors de l’appel, i**l faut respecter l’ordre des paramètres** indiqué dans la définition de la fonction.\
> *Dans l'exemple, le paramètre `a` recevra la valeur `13` et le paramètre `b` recevra la valeur `5`*.

**Nom des fonctions**

Vous pouvez choisir n’importe quel nom pour la fonction que vous créez, à l’exception des mots-clés réservés du langage, et à la condition de n’utiliser aucun caractère spécial ou accentué (le caractère souligné « \_ » est permis). Comme c’est le cas pour les noms de variables, on utilise par convention des minuscules, notamment au début du nom (les noms commençant par une majuscule seront réservés aux classes).

**Corps de la fonction**

Comme les instructions `if`, `for` et `while`, l’instruction `def` est une instruction composée. La ligne contenant cette instruction se termine obligatoirement par un deux-points `:`, qui introduisent un bloc d’instructions qui est précisé grâce à l’indentation. Ce bloc d’instructions constitue le **corps de la fonction**.


# 4. Documenter la fonction
## 4.1. Docstring de fonction
Chaque fonction doit avoir sa propre **`docstring de fonction`**.

La documentation de la fonction doit contenir :
* le rôle de la fonction
* chaque paramètre avec le type de donnée attendu et son rôle
* le type de la valeur de retour

Exemple :
```py
def soustraire(a, b):
    """
    Effectue la soustraction a - b
    :a: (float) 1er opérande de la soustraction
    :b: (float) 2eme opérande de la soustraction
    :return: (float) le résultat de a - b
    """
    val_retour = a - b
    return val_retour
```

## 4.2. Annotations de fonctions
Les annotations permettent d'**indiquer les types des paramètres et de la valeur de retour**.

Exemple :
```py
def soustraire(a: float, b: float) -> float:
    """
    Effectue la soustraction a- b
    :a: (float) 1er opérande de la soustraction
    :b: (float) 2eme opérande de la soustraction
    :return: (float) le résultat de a - b
    """
    val_retour = a - b
    return val_retour
```

> **Attention** : les annotations sont justes des indications, elles ne sont pas prises en compte à l'exécution du programme.


# 5. La définition des fonctions doit précéder leur utilisation
Le code des scripts doit être organisé de la façon suivante :
1. la définition des fonctions,
2. le corps principal du programme.

<br>

*Exemple : calculer le volume d’une sphère $V_{sphere} =\dfrac{4}{3} \times \pi \times r^3$*

```py
"""
Description du script
"""
# importation des modules
from math import pi

# déclaration des fonctions
def cube(n: float) -> float:
    """Retourne le cube de n"""
    return n**3

def volume_sphere(r: float) -> float:
    """retourne le volume d'une sphère"""
    return 4 / 3 * pi * cube(r)

# Programme principal
rayon = float(input("Entrez la valeur du rayon : "))
volume = volume_sphere(rayon)
print(f"Le volume de cette sphère vaut {volume}")
```
[Exécuter dans Python Tutor](https://pythontutor.com/render.html#code=%23%20importation%20des%20modules%0Afrom%20math%20import%20pi%0A%0A%23%20d%C3%A9claration%20des%20fonctions%0Adef%20cube%28n%3A%20float%29%20-%3E%20float%3A%0A%20%20%20%20%22%22%22Retourne%20le%20cube%20de%20n%22%22%22%0A%20%20%20%20return%20n**3%0A%0Adef%20volume_sphere%28r%3A%20float%29%20-%3E%20float%3A%0A%20%20%20%20%22%22%22retourne%20le%20volume%20d'une%20sph%C3%A8re%22%22%22%0A%20%20%20%20return%204%20/%203%20*%20pi%20*%20cube%28r%29%0A%0A%23%20Programme%20principal%0Arayon%20%3D%20float%28input%28%22Entrez%20la%20valeur%20du%20rayon%20%3A%20%22%29%29%0Avolume%20%3D%20volume_sphere%28rayon%29%0Aprint%28f%22Le%20volume%20de%20cette%20sph%C3%A8re%20vaut%20%7Bvolume%3A.1f%7D%22%29&cumulative=false&curInstr=0&heapPrimitives=false&mode=display&origin=opt-frontend.js&py=3&rawInputLstJSON=%5B%5D&textReferences=false)


# 6. Quelques remarques

> **Terminologie :** Les _**paramètres**_ sont les noms qui apparaissent dans une définition de fonction, alors que les _**arguments**_ sont les valeurs qui sont réellement passées à une fonction lors de l'appel de celle-ci.

## 6.1. sur les paramètres des fonctions

* **Nombre de paramètres** : Une fonction peut avoir un ou plusieurs paramètres, ou aucun.

* **Ordre des paramètres** : Lors de l’appel de la fonction, les arguments utilisés doivent être fournis dans le même ordre que celui des paramètres correspondants. Le premier argument sera affecté au premier paramètre, le second argument sera affecté au second paramètre, et ainsi de suite.

## 6.2. sur les arguments d'appel
* **Variable comme argument** : L’argument utilisé dans l’appel d’une fonction peut être une variable.

* **Fonction qui modifie ses paramètres** : En Python, les arguments sont passés comme des affectations de variables. On va donc avoir un comportement différents en fonctions du type de l'argument d'appel.
  * Si la variable utilisée comme argument est d'un type _**immuable**_ la fonction ne modifiera jamais l'argument d'appel.\
    > _Objets immuables : int, bool, float, complex, str, tuple, bytes, frozenset_
  * Si la variable utilisée comme argument est d'un type _**muable**_ la fonction peut modifier l'argument d'appel.\
    > _Objets muables (modifiable sur place): list, dict,  bytearray, set_


    [cf. doc python.org > Modèle de données](https://docs.python.org/fr/3.8/reference/datamodel.html)

## 6.3. sur la valeur de retour
* **Qualité du code** : On ne doit trouver qu'une seule instruction return par fonction.

* **Sans retour** : On peut trouver des fonctions sans valeur de retour. Ces fonctions s'appelle des "procédures". Elles sont par exemple utilisées pour l'affichage.

* **Retourner plusieurs valeurs** : La valeur de retour d'une fonction peut être d'un type de base (_int_, _float_, etc.) mais aussi d'un type construit (_liste_, _tuple_, _dictionnaire_). L'utilisation d'un type construit permet de renvoyer plusieurs valeurs avec un seul return.

    ```py
    def min_max(p_liste: list) -> tuple:
        mini = min(p_liste)
        maxi = max(p_liste)
        return mini, maxi


    val_min, val_max = min_max([2, 8, 5, 9])
    print(f"Mini = {val_min}, Maxi = {val_max}")
    ```
    [Exécuter dans Python Tutor](https://pythontutor.com/render.html#code=def%20min_max%28p_liste%3A%20list%29%20-%3E%20tuple%3A%0A%20%20%20%20mini%20%3D%20min%28p_liste%29%0A%20%20%20%20maxi%20%3D%20max%28p_liste%29%0A%20%20%20%20return%20mini,%20maxi%0A%0A%0Aval_min,%20val_max%20%3D%20min_max%28%5B2,%208,%205,%209%5D%29%0Aprint%28f%22Mini%20%3D%20%7Bval_min%7D,%20Maxi%20%3D%20%7Bval_max%7D%22%29&cumulative=false&curInstr=0&heapPrimitives=false&mode=display&origin=opt-frontend.js&py=3&rawInputLstJSON=%5B%5D&textReferences=false)




# 7. Variables locales, variables globales 
## 7.1. Espaces de noms

En Python, un espace de noms (ou _namespace_) est un espace où sont associées des noms (variables, fonctions, objets, etc.) avec leurs valeurs. 

Un espace de noms garantit que chaque nom est unique dans son contexte. Par exemple, le même nom peut exister à la fois dans un espace de noms global et dans un espace de noms local sans conflit.

Il existe deux types d'espaces de noms principaux :

1. **Espace de noms global**  :
  - Contient les noms définis au niveau du script ou du module principal.

  - Ces noms sont accessibles partout dans le script.

    > une variable déclarée au niveau du programme principal est dans l'espace de noms global.
 
1. **Espace de noms local**  :
  - Contient les noms définis à l'intérieur d'une fonction.

  - Ces noms ne sont accessibles qu'à l'intérieur de cette fonction et n'affectent pas les noms dans l'espace global.

    > Lorsqu'une fonction est appelée, un nouvel espace de noms local est créé et détruit une fois la fonction terminée.


Exemple :
```py
def puissance(a: int, b: int) -> int:
    power = a**b
    return power

x = 2
y = 8
z = puissance(x, y)
```

* `x`, `y` et `z` sont des variables globales
* `power`, `a` et `b` sont des variables locales

## 7.2. Accès aux  variables globales depuis l'intérieur d'une fonction
Les variables définies à l’extérieur d’une fonction sont des **variables globales**. Leur contenu est « visible » de l’intérieur d’une fonction, mais **en lecture seule**.

Si la fonction essaye de modifier une globale en utilisant seulement son nom, il s'agira en fait d'une variable locale portant le même nom que la globale umais ce n'est pas la même variable.

**Exemple** : la fonction peut lire la valeur de la variable globale `a`, mais ne peut pas modifier la valeur de la variable globale `b`

```py
def test():
    b = 5
    print(a, b)
    
a = 2
b = 7
test()
print(a, b)
```
Affichage après exécution :
```
2 5
2 7
```

[Exécuter dans Python Tutor](http://www.pythontutor.com/visualize.html#code=def+test()%3A%0A++++b+%3D+5%0A++++print(a,+b)%0A++++%0Aa+%3D+2%0Ab+%3D+7%0Atest()%0Aprint(a,+b)&mode=display&cumulative=false&heapPrimitives=false&drawParentPointers=false&textReferences=false&showOnlyOutputs=false&py=3&curInstr=0)



## 7.3. Modification d’une variable globale depuis l'intérieur d'une fonction

Il peut arriver que vous ayez à définir une fonction qui soit capable de modifier une variable globale. Pour atteindre ce résultat, il vous suffira d’utiliser l’instruction `global`. Cette instruction permet d’indiquer - à l’intérieur de la définition d’une fonction - quelles sont les variables à traiter globalement.

**Exemple** : la fonction peut modifier la valeur de la variable globale `b` grâce à l'utilisation de `global`.

```py
def test():
    global b
    b = 5
    print(a, b)
    
a = 2
b = 7
test()
print(a, b)
```
Affichage après exécution :
```
2 5
2 5
```

[Exécuter dans Python Tutor](http://www.pythontutor.com/visualize.html#code=def+test()%3A%0A++++global+b%0A++++b+%3D+5%0A++++print(a,+b)%0A++++%0Aa+%3D+2%0Ab+%3D+7%0Atest()%0Aprint(a,+b)&mode=display&cumulative=false&heapPrimitives=false&drawParentPointers=false&textReferences=false&showOnlyOutputs=false&py=3&curInstr=0)


# 8. Valeurs par défaut pour les paramètres 

Dans la définition d’une fonction, il est possible de définir un argument par défaut pour chacun des paramètres. On obtient ainsi une fonction qui peut être appelée avec une partie seulement des arguments attendus.

**Exemples :**

```py
def politesse(nom, titre ="Monsieur"):
    print("Veuillez agréer,", titre, nom, ", mes salutations distinguées.")
```

```py
>>> politesse("Dupont")
Veuillez agréer, Monsieur Dupont , mes salutations distinguées.
```

```py
>>> politesse('Durand', 'Mademoiselle')
Veuillez agréer, Mademoiselle Durand , mes salutations distinguées..
```

Lorsque l’on appelle cette fonction en ne lui fournissant que le premier argument, le second reçoit tout de même une valeur par défaut. Si l’on fournit les deux arguments, la valeur par défaut pour le deuxième est tout simplement ignorée.

# 9. Arguments avec étiquettes 

Dans la plupart des langages de programmation, les arguments que l’on fournit lors de l’appel d’une fonction doivent être fournis exactement dans le même ordre que celui des paramètres qui leur correspondent dans la définition de la fonction.

Python autorise cependant une souplesse beaucoup plus grande. Si les paramètres annoncés dans la définition de la fonction ont reçu chacun une valeur par défaut, sous la forme déjà décrite ci-dessus, on peut faire appel à la fonction en fournissant les arguments correspondants **dans n’importe quel ordre, à la condition de désigner nommément les paramètres correspondants**.

**Exemple :**

```py
def oiseau(voltage=100, etat="allumé", action="danser la java"):
    print("Ce perroquet ne pourra pas", action)
    print("si vous le branchez sur", voltage, "volts !")
    print("L'auteur de ceci est complètement", etat)
```

```py
>>> oiseau(etat="givré", voltage=250, action="vous approuver")
Ce perroquet ne pourra pas vous approuver
si vous le branchez sur 250 volts !
L'auteur de ceci est complètement givré
```

```py
>>> oiseau()
Ce perroquet ne pourra pas danser la java
si vous le branchez sur 100 volts !
L'auteur de ceci est complètement allumé
```


# 10. Voir aussi
* [www.w3schools.com](https://www.w3schools.com/python/python_functions.asp)
* [python.developpez.com/](https://python.developpez.com/cours/apprendre-python3/?page=page_9)
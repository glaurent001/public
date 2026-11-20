(_Cours Python : [retour sommaire](readme.md#les-bases-du-langage-python)_)
# Chap. 7 : Listes et range en Python

> * Auteur : David Cassagne - https://courspython.com/
> * Adaptation et ajouts: Gwénaël LAURENT
> * Autres sources : https://python.sdv.u-paris.fr/04_listes/
> * Date : 08/04/2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 7 : Listes et range en Python](#chap-7--listes-et-range-en-python)
- [1. Le type `list`](#1-le-type-list)
- [2. Accès aux éléments d’une liste](#2-accès-aux-éléments-dune-liste)
- [3. La fonction `len()`](#3-la-fonction-len)
- [4. Parcourir tous les éléments d'une liste](#4-parcourir-tous-les-éléments-dune-liste)
- [5. Ajouter des éléments à une liste](#5-ajouter-des-éléments-à-une-liste)
- [6. Indiçage négatif](#6-indiçage-négatif)
- [7. Tranches (slices)](#7-tranches-slices)
- [8. Minimum, maximum et somme d'une liste](#8-minimum-maximum-et-somme-dune-liste)
- [9. Tester si un élément existe dans la liste](#9-tester-si-un-élément-existe-dans-la-liste)
- [10. Créer une suite arithmétique avec la fonction `range()`](#10-créer-une-suite-arithmétique-avec-la-fonction-range)
- [11. Trier les éléments d'une liste](#11-trier-les-éléments-dune-liste)
- [12. Trier les éléments d'une liste (avancé)](#12-trier-les-éléments-dune-liste-avancé)
- [13. Problème avec les copies de listes](#13-problème-avec-les-copies-de-listes)
- [14. Des listes en paramètre de fonction](#14-des-listes-en-paramètre-de-fonction)
- [15. Méthodes associées aux listes](#15-méthodes-associées-aux-listes)
- [16. Voir aussi](#16-voir-aussi)



# 1. Le type `list` 
> A partir des types de base (_int_, _float_, etc.), il est possible d’en élaborer de nouveaux. On les appelle des _types construits_.

Un exemple de _type construit_ est la **liste**. On peut définir une liste comme une **collection ordonnée d’éléments (=items)**, ou séquence d'éléments. Sous python, on écrit les listes en séparant les éléments par des virgules, l’ensemble étant enfermé dans des crochets.

**Exemple :**
```py
>>> jour = ["lundi", "mardi", "mercredi", "jeudi", "vendredi"]               
>>> type(jour)
<class 'list'>
>>> jour 
['lundi', 'mardi', 'mercredi', 'jeudi', 'vendredi']
```

En python, les éléments d'une liste peuvent être de différents types
```py
>>> jour = ["samedi", 31, 8, 2024] 
>>> type(jour)
<class 'list'>
```


# 2. Accès aux éléments d’une liste 

```py
>>> l = [1, 2, 3, 4]
```

Pour accéder à un élément d’une liste, on indique entre crochets `[ ]` l’**indice (=index) de l’élément**.

```py
liste  : ["girafe", "tigre", "singe", "souris"]
indice :        0        1        2         3
```

> **Avertissement** : En Python, l’indice du premier élément d’une liste est 0.

```py
>>> animaux = ["girafe", "tigre", "singe", "souris"]
>>> animaux[0]
'girafe'
>>> animaux[1]
'tigre'
>>> animaux[3]
'souris'
```

Les listes sont des **séquences MODIFIABLES**, c'est à dire qu'on peut :
* modifier la valeur d'un élément
* ajouter ou supprimer des éléments
* changer l'ordre des éléments.

```py
>>> b = [2, 3, 7, 8, 9, 15]
>>> b[3]
8
>>> b[3] = 20
>>> b
[2, 3, 7, 20, 9, 15]
```

# 3. La fonction `len()`
La fonction `len()` renvoie le nombre d’éléments d'une collection. Par exemple :

```py
>>> a = [7, 8, 9]
>>> len(a)
3
```

# 4. Parcourir tous les éléments d'une liste
Pour afficher les valeurs d'une liste, on peut utiliser une boucle `for .. in .. :`

```py
>>> liste = ["a","d","m"]
>>> for lettre in liste:
...     print(lettre)
... 
a
d
m
```

Sin on a besoin de récupérer aussi les indices :
```py
>>> liste = ["a","d","m"]
>>> for ind, lettre in enumerate(liste):
...     print(f"{ind} : {lettre}")
... 
0 : a
1 : d
2 : m
```


# 5. Ajouter des éléments à une liste
Les listes possèdent une méthode .**append()** qui permet d'ajouter un seul élément à la fin d'une liste.

```py
>>> liste1 = []
>>> liste1.append(13)
>>> liste1.append(-5)
>>> liste1.append(15)
>>> liste1
[13, -5, 15]
```

Tout comme les chaînes de caractères, les listes supportent l'opérateur + de **concaténation**, ainsi que l'opérateur * pour la **duplication** :

```py
>>> ani1 = ["girafe", "tigre"]
>>> ani2 = ["singe", "souris"]
>>> ani1 + ani2
['girafe', 'tigre', 'singe', 'souris']
>>> ani1 * 3
['girafe', 'tigre', 'girafe', 'tigre', 'girafe', 'tigre']
```


# 6. Indiçage négatif
La liste peut également être indexée avec des nombres négatifs selon le modèle suivant :

```py
liste          : ["A", "B", "C", "D", "E", "F"]
indice positif :   0    1    2    3    4    5
indice négatif :  -6   -5   -4   -3   -2   -1
```

Le principal avantage est que vous pouvez accéder au dernier élément d'une liste à l'aide de l'indice `-1` sans pour autant connaître la longueur de cette liste. L'avant-dernier élément a lui l'indice `-2`, l'avant-avant dernier l'indice `-3`, etc. :

```py
>>> animaux = ["girafe", "tigre", "singe", "souris"]
>>> animaux[-1]
'souris'
>>> animaux[-2]
'singe'
```

# 7. Tranches (slices)
Un autre avantage des listes est la possibilité de sélectionner une partie d'une liste en utilisant un indiçage construit sur le modèle **`[m:n+1]`** pour récupérer tous les éléments, de l'élément m inclu à l'élément n+1 exclu. On dit alors qu'on récupère une tranche de la liste, par exemple :

```py
>>> animaux = ["girafe", "tigre", "singe", "souris"]
>>> animaux[0:2]
['girafe', 'tigre']
>>> animaux[0:3]
['girafe', 'tigre', 'singe']
>>> animaux[0:]
['girafe', 'tigre', 'singe', 'souris']
>>> animaux[:]
['girafe', 'tigre', 'singe', 'souris']
>>> animaux[1:]
['tigre', 'singe', 'souris']
>>> animaux[1:-1]
['tigre', 'singe']
>>> animaux[-2:] 
['singe', 'souris']
```

> Notez que lorsqu'aucun indice n'est indiqué à gauche ou à droite du symbole deux-points :, Python prend par défaut tous les éléments depuis le début ou tous les éléments jusqu'à la fin respectivement.

On peut aussi préciser le pas en ajoutant un symbole deux-points supplémentaire et en indiquant le pas par un entier :

```py
>>> x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
>>> x[::1]
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
>>> x[::2]
[0, 2, 4, 6, 8]
>>> x[::3]
[0, 3, 6, 9]
>>> x[1:6:3]
[1, 4]
```

Finalement, on se rend compte que l'accès au contenu d'une liste fonctionne sur le modèle liste **`[début:fin:pas]`**.


# 8. Minimum, maximum et somme d'une liste
Les fonctions intégrées `min()`, `max()` et `sum()` renvoient respectivement le minimum, le maximum et la somme d'une liste passée en argument :

```py
>>> liste1 = list(range(10))
>>> liste1
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
>>> sum(liste1)
45
>>> min(liste1)
0
>>> max(liste1)
9
```

# 9. Tester si un élément existe dans la liste
Pour déterminer si un élément spécifié est présent dans une liste, on utilise `if ... in ... :`.

```py
thislist = ["apple", "banana", "cherry"]
if "apple" in thislist:
    print("Yes, 'apple' is in the fruits list")
```


# 10. Créer une suite arithmétique avec la fonction `range()`

Si vous avez besoin de créer sur une suite d’entiers, vous pouvez utiliser la fonction `range()`. Elle génère une suite arithmétique itérable (on peut parcourir les éléments avec une boucle `for ... in ...` )

```py
>>> range(10)
range(0, 10)
>>> for i in range(0,10):
        print(i, end=" ")
    
0 1 2 3 4 5 6 7 8 9
```

La fonction range() ne génère pas directement une liste mais on peut la convertir en liste :

```py
>>> list(range(10))
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
```

De manière générale, on a :

```py
range(valeur_initiale, borne_de_fin, pas)
```
* La valeur de la borne de fin n’est jamais atteinte.
* Le pas peut être positif ou négatif.


```py
>>> list(range(5, 10))
[5, 6, 7, 8, 9]
>>> list(range(0, 10, 3))
[0, 3, 6, 9]
>>> list(range(-10, -100, -30))
[-10, -40, -70]
```

# 11. Trier les éléments d'une liste
Les listes possèdent une méthode .**sort()** qui permet de trier les éléments d'une liste.

> Attention : la liste de départ est modifiée.

```py
>>> liste1 = [3, 1, 4, 0, 2]
>>> liste1.sort()
>>> print(liste1)
[0, 1, 2, 3, 4]
```

# 12. Trier les éléments d'une liste (avancé)

Pour trier il faut comparer des éléments entre eux pour les ordonner.

Si la liste contient des éléments comparables naturellement la méthode sort() fonctionne très bien. 

Cependant, pour trier des éléments plus complexes, il faut indiquer sur quel sous-élément s'effectue la comparaison.

Exemple : une liste de dictionnaires

```py
eleves = [
    {"nom": "Alice", "moyenne": 15.5},
    {"nom": "Bob", "moyenne": 12.3},
    {"nom": "Charlie", "moyenne": 17.8}
]
```

Si on veut trier les dictionnaires suivant la valeur de la moyenne, il faut utiliser la fonction `sort()` avec le paramètre `key`.\
Le paramètre key référence une fonction qui permet de choisir le sous élément de comparaison

```py
# Fct qui choisit l'élément de comparaison
def get_elem_comp(p_eleve:dict):
    return p_eleve["moyenne"]

# Tri croissant avec reverse=False
eleves.sort(key=get_elem_comp, reverse=False)

for eleve in eleves:
    print(eleve)
```

On peut faire exactement la même chose sans avoir besoin de créer la fonction get_elem_comp() en utilisant `operator.itemgetter()`

```py
from operator import itemgetter

# Tri croissant avec reverse=False
eleves.sort(key=itemgetter("moyenne"), reverse=False)

for eleve in eleves:
    print(eleve)
```



# 13. Problème avec les copies de listes
**Attention avec les instructions de ce type :**

```py
>>> liste1 = [0, 1, 2, 3, 4]
>>> liste2 = liste1
```

**L'affectation d'une liste à une autre variable n'est qu'une copie de référence d'un seul et même objet en mémoire**. `liste2` est un ALIAS du nom `liste1`

Si on modifie `liste1`, alors `liste2` sera modifiée aussi.

Pour copier correctement une liste dans une autre variable, il faut recopier chacun de ses éléments dans la nouvelle variable.

1ère technique :
```py
liste2 = list(liste1)
```
2ème technique :
```py
liste2 = liste1[0:]
```
3ème technique :
```py
liste2 = []
for e in liste1 :
    liste2.append(e)
```
4ème technique :
```py
import copy
liste2 = copy.deepcopy(liste1)
```

# 14. Des listes en paramètre de fonction
> **Attention :** si une liste est passée en paramètre d'une fonction, il n'y a pas de recopie des valeurs de la liste dans la fonction ! **Seule la "référence" de la liste est passée à la fonction**.


# 15. Méthodes associées aux listes

* `liste1.append(5)` :  ajoute un élément à la fin d'une liste
* `liste1.insert(2, -15)` : insère la valeur -15 à l'indice 2
* `del liste1[1]` : supprime un élément d'une liste à l'indice 1
* `liste1.remove(3)` : supprime la première occurence de la valeur 3
* `liste1.pop(1)` : supprime l'éléments à l'indice 1
* `liste1.sort()` : trie les éléments d'une liste du plus petit au plus grand
* `sorted(liste1)` : trie également une liste. Contrairement à la méthode précédente .sort(), cette fonction renvoie la liste triée et ne modifie pas la liste initiale
* `liste1.reverse()` : inverse l'ordre des éléments de la liste


# 16. Voir aussi
* [docs.python.org](https://docs.python.org/fr/3.12/tutorial/datastructures.html)
* [w3schools.com](https://www.w3schools.com/python/python_lists.asp)
* https://python.sdv.u-paris.fr/12_plus_sur_les_listes/
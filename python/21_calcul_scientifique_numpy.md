(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 21 : Calcul scientifique avec numpy

> * Auteur : Patrick Fuchs & Pierre Poulain https://python.sdv.u-paris.fr/20_module_numpy/
> * Adaptation : Gwénaël LAURENT
> * Date : 05/12/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

https://python.sdv.u-paris.fr/20_module_numpy/

https://numpy.org/numpy-tutorials/index.html

- [Chap. 21 : Calcul scientifique avec numpy](#chap-21--calcul-scientifique-avec-numpy)
- [1. Présentation de numpy](#1-présentation-de-numpy)
  - [1.1. Chargement du module](#11-chargement-du-module)
  - [1.2. Objets de type array](#12-objets-de-type-array)
- [2. Générer une liste](#2-générer-une-liste)


# 1. Présentation de numpy
Le module **NumPy** est incontournable en mathématique et en science. Il permet d'effectuer des calculs sur des vecteurs ou des matrices, élément par élément, via un nouveau type d'objet appelé **```array```**.

* [Documentation officielle](https://numpy.org/doc/stable/)
* [NumPy tutorials](https://numpy.org/numpy-tutorials/index.html)

## 1.1. Chargement du module
Par convention, on utilise np comme nom raccourci pour NumPy :
```py
import numpy as np
```

## 1.2. Objets de type array
Les objets de type array correspondent à des tableaux à une ou plusieurs dimensions et permettent d'effectuer du calcul vectoriel. 

La fonction `array()` convertit un conteneur (comme une liste, un range ou un tuple) en un objet de type array. Voici un exemple de conversion d'une liste à une dimension en objet array :

```py
>>> import numpy as np
>>> a = [1, 2, 3]
>>> np.array(a)
array([1, 2, 3])
>>> b = np.array(a)
>>> b
array([1, 2, 3])
>>> type(b)
numpy.ndarray
```


 Par ailleurs, lorsqu'on demande à Python d'afficher le contenu d'un objet array, le mot array et les symboles ([ et ]) sont utilisés pour le distinguer d'une liste (délimitée par les caractères [ et ]) ou d'un tuple (délimité par les caractères ( et )).

 Remarque
Un objet array ne contient que des données homogènes, c'est-à-dire d'un type identique

La différence fondamentale entre un objet array à une dimension et une liste (ou un tuple) est que celui-ci est considéré comme un vecteur. Par conséquent, on peut effectuer des opérations vectorielles élément par élément sur ce type d'objet, ce qui est bien commode lorsqu'on analyse de grandes quantités de données.

Regardez ces exemples :

On créer un array de 4 valeurs :
```py
>>> v = np.arange(4)
>>> v
array([0, 1, 2, 3])
```

On ajoute 1 à chacun des éléments de l'array v :
```py
>>> v + 1
array([1, 2, 3, 4])
```

On multiplie par 2 chacun des éléments de l'array v :
```py
>>> v * 2
array([0, 2, 4, 6])
```
Avec les listes, ces opérations n'auraient été possibles qu'en utilisant des boucles. 

# 2. Générer une liste

```py
"""
Test utilisation de numpy pour créer des array avec des valeurs réparties en décimal
La fonction numpy.linspace(start, stop, num)
Renvoie (num) nombres uniformément espacés calculés sur l'intervalle [start, stop]. 
start et stop sont inclus. Pour exclure stop, il ajouter l'argument endpoint=False
"""

import numpy as np
# La valeur du paramètre endpoint détermine si la borne supérieure est incluse ou non. La valeur par défaut est endpoint=True.

x_array = np.linspace(0, 1, 10, endpoint=False)
# [0. 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9]
# x_array = np.linspace(0, 1, 10, endpoint=True)
# [0. 0.11111111 0.22222222 0.33333333 0.44444444 0.55555556 0.66666667 0.77777778 0.88888889 1.]
# x_array = np.linspace(0, 1, 11, endpoint=True)
# [0. 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]

print(x_array)
print(type(x_array))
# <class 'numpy.ndarray'>
print(x_array[2])


x_array = np.exp(x_array)
print(x_array)

```



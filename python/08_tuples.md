(_Cours Python : [retour sommaire](readme.md#les-bases-du-langage-python)_)
# Chap. 8 : Tuples en Python

> * Auteur : David Cassagne - https://courspython.com/
> * Adaptation : Gwénaël LAURENT
> * Date : 11/04/2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 8 : Tuples en Python](#chap-8--tuples-en-python)
- [1. Généralités](#1-généralités)
- [2. Comment écrire une fonction qui renvoie un p-uplet de valeurs ?](#2-comment-écrire-une-fonction-qui-renvoie-un-p-uplet-de-valeurs-)
- [3. Comment itérer sur les éléments d’un tuple ?](#3-comment-itérer-sur-les-éléments-dun-tuple-)
- [4. Accéder à un élément du tuple](#4-accéder-à-un-élément-du-tuple)
- [5. Comment créer un tuple qui contient un seul élément ?](#5-comment-créer-un-tuple-qui-contient-un-seul-élément-)
- [6. Tuples nommés (namedtuple)](#6-tuples-nommés-namedtuple)


A partir des types de base (_int_, _float_, etc.), il est possible d’en élaborer de nouveaux. On les appelle des _types construits_.

# 1. Généralités
Un exemple de _type construit_ est le **tuple**. Il permet de créer une **collection ordonnée de plusieurs éléments**. En mathématiques, on parle de **p-uplet**. Par exemple, un quadruplet est constitué de 4 éléments.

Les tuples ressemblent aux listes, mais on ne peut pas les modifier une fois qu’ils ont été créés.

On dit qu’**un tuple est immuable** (_non mutable_), c'est une séquence non modifiable d'éléments.

On le définit avec des **parenthèses**.

```py
>>> a = (3, 4, 7)
>>> type(a)
<class 'tuple'>
```

Parfois, les tuples ne sont pas entourés de parenthèses, même s’il s’agit quand même de tuples.

Ainsi, on peut utiliser la notation suivante :

```py
>>> b, c = 5, 6
>>> b
5
>>> c
6
```

En fait, cela revient à :

```py
>>> (b, c) = (5, 6)
```

Cette syntaxe avec plusieurs variables à gauche du signe `=` peut aussi être utilisée avec une variable unique à droite si celle-ci contient un tuple.

```py
>>> a = (3, 4)
>>> u, v = a
>>> u
3
>>> v
4
```
# 2. Comment écrire une fonction qui renvoie un p-uplet de valeurs ?

Il est très facile de créer une fonction qui renvoie un tuple. Il suffit d’indiquer ce tuple après `return`.

```py
def test():
    return 3, 4

>>> a = test()
>>> a
(3, 4)
>>> b, c = test()
>>> b
3
>>> c
4
```
Note : Après **return**, il aurait été possible d’utiliser une notation avec des parenthèses pour le tuple, par exemple **return (3, 4)**.

# 3. Comment itérer sur les éléments d’un tuple ?

Comme une liste, il est possible de parcourir un tuple avec une boucle `for`.

```py
a = (3, 8, 15)
for i in a:
    print(i)
```


Affichage après exécution :
```
3
8
15
```

# 4. Accéder à un élément du tuple
La valeur d’un élément du tuple est obtenue en utilisant la même syntaxe que pour une liste : on utilise les crochets et l'indice de l'élément.

```py
>>> a = (3, 8, 15)
>>> a[0]
3
>>> a[2] 
15
```

# 5. Comment créer un tuple qui contient un seul élément ?

Si on utilise seulement des parenthèses, on n’obtient pas le résultat escompté.

```py
>>> a = (3)
>>> a
3
>>> type(a)
<class 'int'>
```
En effet, les parenthèses sont alors considérées comme celles d’une expression mathématique, comme par exemple dans `3*(4+1)`.

Pour créer un tuple contenant un seul élément, il faut donc utiliser une **syntaxe spécifique qui contient une virgule**.

```py
>>> b = (3,)
>>> b
(3,)
>>> type(b)
<class 'tuple'>
```
Si on veut récupérer l’unique valeur présente dans le tuple, on va pouvoir utiliser les approches suivantes :

_Première approche_

```py
>>> c = b[0]
>>> c
3
```

_Deuxième approche_

```py
>>> d, = b
>>> d
3
```

La deuxième approche avec une virgule `d, = b` est plus légère que la syntaxe qui utilise des crochets `c = b[0]`.

Remarque : Il est possible d’utiliser la syntaxe `nom_de_variable, =` aussi avec une liste à un seul élément.

```py
>>> u = [5]
>>> v, = u
>>> v
5
```


# 6. Tuples nommés (namedtuple)
Les tuples nommés (namedtuple) permettent de **nommer les éléments contenus dans le namedtuple** (à la place de la notation [indice] des tuples normaux).

On accède aux éléments par des noms comme `obj.nom`, ce qui est plus lisible et pratique.

**Un namedtuple est immuable** (_non mutable_) comme les tuples classiques.

```python
from collections import namedtuple

# création de la structure : nom du namedtuple + nom des éléments qu'il contient
Personne = namedtuple('Personne', ['nom', 'age'])

# création d'un objet de type Person
p = Personne(nom='Alice', age=30)

# accès aux éléments du namedtuple
print(f"Nom = {p.nom}, age = {p.age}")

# Un namedtuple est immuable
p.age = 31 # ERREUR AttributeError: can't set attribute
```

**Avantages des namedtuple:**
- Moins d'erreurs : les champs sont définis à l'avance, ils sont accessibles par l'intellisense.
- Un `namedtuple` définit une structure de données claire, (_comme une petite classe ne contenant que des attributs_), ce qui rend le code plus auto-documenté.
- Plus clair qu'un tuple : accès avec `p.nom` au lieu de `p[0]`
- Plus lisible qu'un dictionnaire : accès avec `p.nom` au lieu de `p['nom']`.

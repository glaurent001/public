(_Cours Python : [retour sommaire](readme.md#les-bases-du-langage-python)_)
# Chap. 2 : Principaux types de données

> * Auteur : David Cassagne - https://courspython.com/
> * Adaptation : Gwénaël LAURENT
> * Autres sources : 
>   * https://python.sdv.u-paris.fr/02_variables/ 
>   * https://docs.python.org/fr/3.12/library/stdtypes.html
> * Date : 27/08/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 2 : Principaux types de données](#chap-2--principaux-types-de-données)
- [1. La fonction `type()`](#1-la-fonction-type)
- [2. Le type `int` (entier)](#2-le-type-int-entier)
- [3. Le type `float` (flottant)](#3-le-type-float-flottant)
- [4. Le type `str` (chaîne de caractères)](#4-le-type-str-chaîne-de-caractères)
- [5. Le type `bool` (booléen)](#5-le-type-bool-booléen)
- [6. Le type `complex` (complexe)](#6-le-type-complex-complexe)
- [7. Conversion de types](#7-conversion-de-types)


Python est un language à **[typage dynamique](https://python.developpez.com/cours/DiveIntoPython/php/frdiveintopython/getting_to_know_python/declaring_functions.php#d0e4222)**, ce qui signifie qu’il n’est pas nécessaire de déclarer les variables avant de pouvoir leur affecter une valeur. La valeur que l’on affecte possède un **type** qui dépend de la nature des données (nombre entier, nombre à virgule, chaîne de caractères, etc). Le type du contenu d’une variable peut donc changer si on change sa valeur.

# 1. La fonction `type()` 

Pour connaître le type de la valeur d’une variable, il suffit d’utiliser la fonction `type()`.

**Exemples :**
```py
>>> type(15)
<class 'int'>
>>> a = 15
>>> type(a)
<class 'int'>
>>> a = "toto"
>>> type(a)
<class 'str'>
```
# 2. Le type `int` (entier) 

Ce type est utilisé pour stocker un **entier**, en anglais _integer_. Pour cette raison, on appelle ce type `int`.

```py
>>> type(128)
<class 'int'>
```

On peut aussi utiliser la représentation hexadécimale pour écrite un nombre :
```py
>>> type(0x41)
int
>>> print(0x41)
65
```
# 3. Le type `float` (flottant) 

Ce type est utilisé pour stocker des **nombres à virgule flottante** (nombre réel), désignés en anglais par l’expression _floating point numbers_. Pour cette raison, on appelle ce type : `float`. En français, on parle de **flottant**.

> Attention : En Python, comme dans la plupart des langages de programmation, c'est le point qui est utilisé comme séparateur décimal.

**Exemples :**
```py
>>> a = 14.5
>>> type(a)
<class 'float'>

>>> a = 11.
>>> type(a) 
<class 'float'>
>>> a
11.0

>>> a = 3.25e7
>>> type(a)
<class 'float'>
>>> a
32500000.0
```

# 4. Le type `str` (chaîne de caractères)

Sous Python, une donnée de type `str` est une **chaîne de caractères**, c'est à dire une suite quelconque de caractères délimitée soit par des apostrophes (simple quotes), soit par des guillemets (double quotes). `str` est l’abréviation de _string_, qui veut dire _chaîne_ en français.

```py
>>> a = 'Bonjour'
>>> type(a)
<class 'str'>
>>> a = "Bonjour" 
>>> type(a)       
<class 'str'>
```

Pour les chaînes de caractères, deux opérations sont possibles, l'addition et la multiplication :

```py
>>> chaine = "Salut"
>>> chaine
'Salut'
>>> chaine + " Python"
'Salut Python'
>>> chaine * 3
'SalutSalutSalut'
```

L'opérateur d'addition + concatène (assemble) deux chaînes de caractères. On parle de **concaténation**.

L'opérateur de multiplication * entre un nombre entier et une chaîne de caractères duplique (répète) plusieurs fois une chaîne de caractères. On parle de **duplication**.

Voir aussi : 
* [Formater les chaines de caractères (f-strings)](03_formater_les_chaines_de_caracteres.md)
* [Chaines de caractères](06_chaines_de_caracteres.md)

# 5. Le type `bool` (booléen) 

Le type `bool` est utilisé pour les _booléens_. Un booléen peut prendre les valeurs `True` ou `False`.

```py
>>> a = True
>>> type(a)  
<class 'bool'>
>>> b = not(a)
>>> b
False
>>> type(b)  
<class 'bool'>
```

**Remarque :** la fonction `not` est un opérateur logique qui renvoie l’opposé de la valeur booléenne transmise. Pour `True`, on obtient `False`. Réciproquement, il renvoie `False` quand on lui transmet `True`.


# 6. Le type `complex` (complexe) 

Python posséde par défaut un type pour manipuler les **nombres complexes**. La partie imaginaire est indiquée grâce à la lettre « j » ou « J ». La lettre mathématique utilisée habituellement, le « i », n’est pas utilisée en Python car la variable _i_ est souvent utilisée dans les boucles.

**Exemples :**
```py
>>> a = 2 + 3j
>>> type(a)
<class 'complex'>
>>> a
(2+3j)

>>> b = 1 + j
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
NameError: name 'j' is not defined

>>> b = 1 + 1j 
>>> a * b
(-1+5j)

>>> 1j**2
(-1+0j)
```
# 7. Conversion de types

En programmation, on est souvent amené à convertir les types, c'est-à-dire passer d'un type numérique à une chaîne de caractères ou vice-versa. En Python, rien de plus simple avec les fonctions `int()`, `float()` et `str()`. Pour vous en convaincre, regardez ces exemples :

```py
>>> i = 3
>>> str(i)
'3'
>>> i = '456'
>>> int(i)
456
>>> float(i)
456.0
>>> i = '3.1416'
>>> float(i)
3.1416
```

Toute conversion d'une variable d'un type en un autre est appelé **casting** en anglais.
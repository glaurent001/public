(_Cours Python : [retour sommaire](readme.md#les-bases-du-langage-python)_)
# Chap. 1 : Introduction à Python

> * Auteur : David Cassagne - https://courspython.com/
> * Adaptation : Gwénaël LAURENT
> * Date : 27/08/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


<!-- https://courspython.com/introduction-python.html -->
<!-- https://htmlmarkdown.com/ -->
<!-- regex : \[#\](.*) -->

- [Chap. 1 : Introduction à Python](#chap-1--introduction-à-python)
- [1. Qu'est-ce que Python ?](#1-quest-ce-que-python-)
- [2. Présentation des outils de programmation](#2-présentation-des-outils-de-programmation)
  - [2.1. Avec Microsoft VScode](#21-avec-microsoft-vscode)
  - [2.2. Avec Python Tutor](#22-avec-python-tutor)
- [3. Quelques bases rapides en Python](#3-quelques-bases-rapides-en-python)
  - [3.1. Premiers calculs](#31-premiers-calculs)
  - [3.2. L’opérateur `/`](#32-lopérateur-)
  - [3.3. L’opérateur `%`](#33-lopérateur-)
  - [3.4. Variables](#34-variables)
  - [3.5. Affichage - la fonction `print()`](#35-affichage---la-fonction-print)
  - [3.6. Lecture d’informations au clavier - la fonction `input()`](#36-lecture-dinformations-au-clavier---la-fonction-input)
- [4. Règles générales d’écriture](#4-règles-générales-décriture)
  - [4.1. Les identificateurs](#41-les-identificateurs)
  - [4.2. Les mots-clés](#42-les-mots-clés)
  - [4.3. Les commentaires](#43-les-commentaires)
  - [4.4. PEP 8 – Style Guide for Python Code](#44-pep-8--style-guide-for-python-code)


# 1. Qu'est-ce que Python ?
Le langage de programmation Python a été créé en 1989 par Guido van Rossum, aux Pays-Bas. La dernière version de Python est la version 3. 

Python est un **langage de programmation interprété** : Le code est exécuté par un interpréteur, ce qui signifie que le code Python est lu et exécuté ligne par ligne par l'interpréteur Python.


# 2. Présentation des outils de programmation
## 2.1. Avec Microsoft VScode
Les exemples de code python peuvent être testés dans **VScode** (cf la [configuration de VScode pour Python](https://gitlab.com/gwenael.laurent/public/-/blob/master/vscode/vscode-python.md)). Vous avez alors deux possibilités :
* **Créer un fichier de script** python et l'exécuter en mode normal ou debug
* **Utiliser directement l'interpréteur interactif** de python, reconnaissable à l'invite de commande ```>>>```  (on appelle ça le REPL = read–eval–print loop).\
  * Pour lancer l'interpréteur interactif dans VScode :
    1. Ouvrir le Palette de commandes: Ctrl+Shift+P (ou F1).
    2. Taper "**Python: Start Terminal REPL**".



## 2.2. Avec Python Tutor
Les exemples de bases peuvent aussi être testés grâce au site web **[Python Tutor](https://pythontutor.com/)**.

Exemple d'utilisation de Python Tutor pour ce programme :

```py
for i in [0, 1, 2]:
    print("valeur :", i)
print("Fin")
```

[Exécuter dans Python Tutor](http://pythontutor.com/visualize.html#code=for%20i%20in%20%5B0,%201,%202%5D%3A%0A%20%20%20%20print%28%22valeur%20%3A%22,%20i%29%0Aprint%28%22Fin%22%29&cumulative=false&curInstr=0&heapPrimitives=false&mode=display&origin=opt-frontend.js&py=3&rawInputLstJSON=%5B%5D&textReferences=false)

> *Note :*\
> Pour exécuter ce code pas à pas, utiliser le bouton "Next".\
> La prochaine ligne à exécuter est indiquée par une flèche rouge.\
> Une flèche verte signale la ligne qui vient d’être exécutée.


# 3. Quelques bases rapides en Python

## 3.1. Premiers calculs

Testez les calculs suivants :

```py
>>> 4 + 5
>>> 3 - 7            # les espaces sont optionnels
>>> 5 + 2 * 3        # la priorité des opérations mathématiques est-elle respectée ?
>>> (6 + 3) * 2
```

Pour calculer une puissance, on utilise `**`.

```py
>>> 5**2
25
```

## 3.2. L’opérateur `/` 
L'opérateur `/` réalise une division.\
Pour réaliser une division entière (euclidienne), il faut utiliser `//` :

```py
>>> 7 / 23.5  
0.2978723404255319
>>> 7 // 23.5 
0.0
```

## 3.3. L’opérateur `%` 

L’opérateur `%` (appelé **opérateur modulo**) fournit le reste de la division entière d’un nombre par un autre.

```py
>>> 7 % 2
1
>>> 6 % 2
0
```


## 3.4. Variables

> Une **variable** est une zone de la mémoire de l'ordinateur dans laquelle une **valeur** est stockée. Aux yeux du programmeur, cette variable est définie par un **nom**, alors que pour l'ordinateur, il s'agit en fait d'une adresse, c'est-à-dire d'une zone particulière de la mémoire.

En Python, la déclaration d'une variable et son initialisation (c'est-à-dire la première valeur que l'on va stocker dedans) se font en même temps.

```py
>>> a = 2
>>> a
2
>>> b = a + 3
>>> b
5
```  

Le symbole **`=`** est appelé **opérateur d'affectation**. Il permet d'assigner une valeur à une variable. Cet opérateur s'utilise toujours de la droite vers la gauche. Par exemple, dans l’instruction `a = 2`, Python attribue la **valeur** située à droite (ici, 2) à la **variable** située à gauche (ici, a)

> Python a « deviné » que la variable était un entier. On dit que Python est un langage au **typage dynamique**.

Voir aussi : Principaux types de données

## 3.5. Affichage - la fonction `print()`

Pour afficher, on utilise la fonction [`print()`](#print).

```py
>>> print("bonjour")
bonjour
>>> a = 5
>>> print(a)
5
```

Il est possible de réaliser plusieurs affichages à la suite. Pour cela, on sépare les éléments par des virgules.

```py
>>> a = 5
>>> print("a vaut ", a)
a vaut  5
```

Pour ne pas aller à la ligne et continuer sur la même ligne lors du prochain `print`, on ajoute le paramètre `end=" "` :

```py
>>> print("a vaut ", a, end=" ") 
a vaut  5 >>> 
```

Voir aussi : 
* [Formater les chaines de caractères (f-strings)](03_formater_les_chaines_de_caracteres.md)
* [https://python.developpez.com/cours/apprendre-python3/?page=page\_4#L4](https://python.developpez.com/cours/apprendre-python3/?page=page_4#L4)


 ## 3.6. Lecture d’informations au clavier - la fonction `input()`

```py
>>> x = input("Donner un mot : ")
Donner un mot : Tarte
>>> x
'Tarte'
>>> y = int(input("Donner un entier : "))
Donner un entier : 25
>>> y
25
```

Par défaut, la fonction [`input()`](#input) renvoie une chaîne de caractères. Il faut donc utiliser la fonction `int()` qui permet d’obtenir un entier.


# 4. Règles générales d’écriture 

 ## 4.1. Les identificateurs 

Un identificateur est une suite de caractères servant à désigner les différentes entitées manipulées par un programme : variables, fonctions, classes…

En Python, un identificateur est formé de lettres ou de chiffres. Il ne contient pas d’espace. Le premier caractère doit obligatoirement être une lettre. Il peut contenir le caractère « _ » (underscore, en français « souligné »). Il est sensible à la casse (distinction entre majuscule et minuscule), ce qui signifie que les variables TesT, test et TEST sont différentes.

 ## 4.2. Les mots-clés 

Les mots réservés par le langage Python (`if`, `for`, etc.) ne peuvent pas être utilisés comme identificateurs.

> Liste des mots-clés : [https://python.developpez.com/cours/apprendre-python3/?page=page\_4#L4-C](https://python.developpez.com/cours/apprendre-python3/?page=page_4#L4-C)

 ## 4.3. Les commentaires 

Les commentaires usuels :
```py
# Ceci est un commentaire sur une ligne
```

Les commentaires en fin de ligne :
```py
a = 2 # Ceci est un commentaire en fin de ligne
```
Les commentaires sur plusieurs lignes :

```py
"""
Ceci est un commentaire
Sur plusieurs lignes
"""
```

## 4.4. PEP 8 – Style Guide for Python Code
Toutes les conventions de nommage suivent les directives de la PEP8

[PEP 8 – Style Guide for Python Code](https://peps.python.org/pep-0008/)

Voir aussi : https://python.sdv.u-paris.fr/16_bonnes_pratiques/
(_Cours Python : [retour sommaire](readme.md#les-bases-du-langage-python)_)
# Chap. 9 : Dictionnaires en Python

> * Auteur : David Cassagne - https://courspython.com/
> * Adaptation : Gwénaël LAURENT
> * Date : 27/08/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


- [Chap. 9 : Dictionnaires en Python](#chap-9--dictionnaires-en-python)
- [1. Généralités](#1-généralités)
- [2. Comment construire une entrée dans un dictionnaire ?](#2-comment-construire-une-entrée-dans-un-dictionnaire-)
- [3. Comment créer un dictionnaire ?](#3-comment-créer-un-dictionnaire-)
- [4. Comment parcourir un dictionnaire ?](#4-comment-parcourir-un-dictionnaire-)


Comme on l’a vu avec les listes et les tuples, à partir des types de base (_int_, _float_, etc.) il est possible d’élaborer de nouveaux types qu’on appelle des _types construits_.

# 1. Généralités
Un nouvel exemple de _type construit_ est le **dictionnaire**.

Les éléments d’une liste ou d’un tuple sont ordonnés et on accéde à un élément grâce à sa position en utilisant un numéro qu’on appelle l’indice de l’élément.

Un **dictionnaire** en Python va aussi permettre de rassembler des éléments mais ceux-ci seront identifiés par une **clé**. On peut faire l’analogie avec un dictionnaire de français où on accède à une définition avec un mot.

Contrairement aux listes qui sont délimitées par des crochets, on utilise des **accolades** pour les dictionnaires.

```py
>>> mon_dictionnaire = {"voiture": "véhicule à quatre roues", "vélo": "véhicule à deux roues"}
```

Un élément a été défini ci-dessus dans le dictionnaire en précisant une **clé** au moyen d’une chaîne de caractères suivie de `:` puis de la **valeur** associée

**_clé_: _valeur_**

On accède à une **valeur** du dictionnaire en utilisant la **clé** entourée par des crochets avec la syntaxe suivante :

```py
>>> mon_dictionnaire["voiture"]
'véhicule à quatre roues'
```

# 2. Comment construire une entrée dans un dictionnaire ? 

Il est très facile d’ajouter un élément à un dictionnaire. Il suffit d’affecter une **valeur** pour la nouvelle **clé**.

```py
>>> mon_dictionnaire["tricycle"] = "véhicule à trois roues"
>>> mon_dictionnaire           
{'voiture': 'véhicule à quatre roues', 'vélo': 'véhicule à deux roues', 'tricycle': 'véhicule à trois roues'}
```

Le _type_ d’un dictionnaire est `dict`.

```py
>>> type(mon_dictionnaire)
<class 'dict'>
```

Il est aussi possible d’utiliser des valeurs d’autres types.

Voici un exemple où les valeurs sont des entiers.

```py
>>> nombre_de_roues = {"voiture": 4, "vélo": 2}
>>> type(nombre_de_roues)
<class 'dict'>
>>> nombre_de_roues["vélo"]
2
```

# 3. Comment créer un dictionnaire ? 

Nous avons vu ci-dessus qu’il était possible de créer un dictionnaire avec des **accolades** qui entourent les éléments. Une autre approche possible consiste à créer un dictionnaire vide et à ajouter les éléments au fur et à mesure.

```py
>>> nombre_de_pneus = {}
>>> nombre_de_pneus["voiture"] = 4
>>> nombre_de_pneus["vélo"] = 2
>>> nombre_de_pneus
{'voiture': 4, 'vélo': 2}
```

# 4. Comment parcourir un dictionnaire ? 

On utilise `items()`.

**Exemple pour une boucle for avec un indice i**
```py
nombre_de_roues = {"voiture": 4, "vélo": 2, "tricycle": 3}
for i in nombre_de_roues.items():
    print(i)
```

Affichage après exécution :
```
('voiture', 4)
('vélo', 2)
('tricycle', 3)
```

**Autre exemple pour une boucle for avec deux indices : cle et valeur**
```py
nombre_de_roues = {"voiture": 4, "vélo": 2, "tricycle": 3}
for cle, valeur in nombre_de_roues.items():
    print("l'élément de clé", cle, "vaut", valeur)
```

Affichage après exécution :
```
l'élément de clé voiture vaut 4
l'élément de clé vélo vaut 2
l'élément de clé tricycle vaut 3
```

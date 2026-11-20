(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 17 : Nombres pseudo-aléatoires en Python

> * Auteur : Gwénaël LAURENT
> * Date : 11/02/2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 17 : Nombres pseudo-aléatoires en Python](#chap-17--nombres-pseudo-aléatoires-en-python)
- [1. Le module `random`](#1-le-module-random)
- [2. Générer un nombre aléatoire](#2-générer-un-nombre-aléatoire)
  - [2.1. Générer un entier aléatoire dans une plage spécifique avec `randint()`](#21-générer-un-entier-aléatoire-dans-une-plage-spécifique-avec-randint)
  - [2.2. Générer un nombre flottant aléatoire entre 0 et 1 avec `random()`](#22-générer-un-nombre-flottant-aléatoire-entre-0-et-1-avec-random)
  - [2.3. Générer un nombre flottant dans une plage spécifique avec `uniform()`](#23-générer-un-nombre-flottant-dans-une-plage-spécifique-avec-uniform)
  - [2.4. Choisir un élément aléatoire dans une liste avec `choice()`](#24-choisir-un-élément-aléatoire-dans-une-liste-avec-choice)
  - [2.5. Mélanger une liste aléatoirement avec `shuffle()`](#25-mélanger-une-liste-aléatoirement-avec-shuffle)
- [3. Créer une liste contenant une séquence aléatoire de nombres entiers](#3-créer-une-liste-contenant-une-séquence-aléatoire-de-nombres-entiers)
  - [3.1. `randint()` pour obtenir une séquence aléatoire](#31-randint-pour-obtenir-une-séquence-aléatoire)
  - [3.2. `sample()` pour obtenir une séquence aléatoire unique](#32-sample-pour-obtenir-une-séquence-aléatoire-unique)
  - [3.3. `choices()` pour une séquence avec répétition](#33-choices-pour-une-séquence-avec-répétition)
- [4. Documentation](#4-documentation)


# 1. Le module `random`
Ce module implémente des générateurs de nombres pseudo-aléatoires.

* Pour les entiers, le module utilise une distribution à partir d'une plage.

* Pour l'ensemble des réels, il y a des fonctions pour calculer des distributions uniformes, normales (gaussiennes), log-normales, exponentielles négatives, gamma et bêta. 

> **Avertissement :** Les générateurs pseudo-aléatoires de ce module ne doivent pas être utilisés à des fins de sécurité. Pour des utilisations de sécurité ou cryptographiques, voir le [module `secrets`](https://docs.python.org/fr/3/library/secrets.html#module-secrets).

# 2. Générer un nombre aléatoire


## 2.1. Générer un entier aléatoire dans une plage spécifique avec `randint()`
Utilisez la fonction `randint()` pour générer un entier aléatoire entre deux bornes (inclusives).

> **`randint(a, b)`**  : Génère un entier aléatoire entre `a` et `b` (inclus).

```python
import random

nombre = random.randint(1, 100)
print(nombre)
```

## 2.2. Générer un nombre flottant aléatoire entre 0 et 1 avec `random()`
Utilisez la fonction `random()` pour générer un nombre flottant aléatoire entre 0.0 et 1.0.

> **`random()`** : Génère un float aléatoire entre 0.0 (inclus) et 1.0 (exclus)

```python
import random

nombre = random.random()
print(nombre)
```

## 2.3. Générer un nombre flottant dans une plage spécifique avec `uniform()`
Utilisez la fonction `uniform()` pour obtenir un nombre flottant aléatoire entre deux valeurs spécifiques.

> **`uniform(a, b)`** : Génère un entier aléatoire entre `a` et `b` (inclus).

```python
import random

nombre = random.uniform(1.5, 10.5)
print(nombre)
```

## 2.4. Choisir un élément aléatoire dans une liste avec `choice()`
Pour sélectionner un élément aléatoire dans une liste, utilisez `choice()`.

> **`choice(seq)`** : Renvoie un élément aléatoire de la séquence non vide *seq*. 

```python
import random

elements = [1, 2, 3, 4, 5]
element = random.choice(elements)
print(element)
```

Vous pouvez aussi utiliser `randrange()`

> **`randrange(start, stop[, step])`** : Renvoie un élément aléatoire de la séquence *range(start, stop, step)* 

```python
import random

element = random.randrange(1, 6, 1)
print(element)
```

## 2.5. Mélanger une liste aléatoirement avec `shuffle()`
Pour mélanger les éléments d'une liste, utilisez `shuffle()`.

> **`shuffle(seq)`** : Mélange la séquence *seq* sans créer de nouvelle instance (« sur place »).

```python
import random

elements = [1, 2, 3, 4, 5]
random.shuffle(elements)
print(elements)
```

# 3. Créer une liste contenant une séquence aléatoire de nombres entiers
Pour créer une liste Python contenant une séquence aléatoire de nombres entiers, on peut utiliser le module `random` de plusieurs manières.

## 3.1. `randint()` pour obtenir une séquence aléatoire
Si vous voulez une liste contenant des entiers aléatoires dans une plage spécifique, utilisez la fonction `randint()` dans une boucle.

> **`randint(a, b)`**  : Génère un entier aléatoire entre `a` et `b` (inclus).

Pour créer une liste de 10 entiers aléatoires entre 1 et 100.

```python
import random

liste_aleatoire = []
for i in range(10):
    liste_aleatoire.append(random.randint(1, 100))
print(liste_aleatoire)
```

## 3.2. `sample()` pour obtenir une séquence aléatoire unique
Si vous voulez une liste de nombres uniques aléatoires dans une plage donnée, utilisez la fonction `random.sample()`. Cela sélectionne un sous-ensemble sans répétition à partir d'une séquence ou d'un intervalle donné.

> **`sample(population, k)`**  : Renvoie une liste de `k` éléments uniques choisis aléatoirement dans la population (sans répétition).

Pour créer une liste de 10 nombres entiers uniques entre 1 et 100.

```python
import random

liste_aleatoire = random.sample(range(1, 101), 10)
print(liste_aleatoire)
```

## 3.3. `choices()` pour une séquence avec répétition
Si vous voulez une liste aléatoire où des éléments peuvent être répétés, utilisez `random.choices()`.

> **`choices(population, k)`**  : Renvoie une liste de `k` éléments choisis aléatoirement dans la population (avec répétition possible).

Pour créer une liste de 10 entiers aléatoires avec répétition possible entre 1 et 100.

```python
import random

liste_aleatoire = random.choices(range(1, 101), k=10)
print(liste_aleatoire)
```


# 4. Documentation
* [docs.python.org > Generate pseudo-random numbers](https://docs.python.org/fr/3/library/random.html)
* [w3schools.com > Random Module](https://www.w3schools.com/python/module_random.asp)


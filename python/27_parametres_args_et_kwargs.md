(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 27 : Utilisation de `*args` et `**kwargs` en Python

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 27 : Utilisation de `*args` et `**kwargs` en Python](#chap-27--utilisation-de-args-et-kwargs-en-python)
- [1. Introduction](#1-introduction)
- [2. `*args` : arguments positionnels variables](#2-args--arguments-positionnels-variables)
  - [2.1. Syntaxe](#21-syntaxe)
  - [2.2. Exemple](#22-exemple)
- [3. `**kwargs` : arguments nommés variables](#3-kwargs--arguments-nommés-variables)
  - [3.1. Syntaxe](#31-syntaxe)
  - [3.2. Exemple](#32-exemple)
- [4. Combiner `*args` et `**kwargs`](#4-combiner-args-et-kwargs)
- [5. Note : `*args` n'accepte pas les arguments nommés](#5-note--args-naccepte-pas-les-arguments-nommés)
  - [5.1. Rappel](#51-rappel)
  - [5.2. Exemple concret](#52-exemple-concret)
  - [5.3. Comment gérer les deux en même temps ?](#53-comment-gérer-les-deux-en-même-temps-)


# 1. Introduction

En Python, lorsqu’on définit une fonction, on peut parfois ne pas connaître à l’avance **le nombre exact d’arguments** que la fonction recevra. C’est là que `*args` et `**kwargs` deviennent utiles :

* `*args` → pour passer un nombre **variable d’arguments positionnels**.
* `**kwargs` → pour passer un nombre **variable d’arguments nommés (key-value)**.



# 2. `*args` : arguments positionnels variables

## 2.1. Syntaxe

```python
def ma_fonction(*args):
    for arg in args:
        print(arg)
```

## 2.2. Exemple

```python
def addition(*nombres):
    total = 0
    for n in nombres:
        total += n
    return total

print(addition(1, 2, 3))   # Affiche 6
print(addition(5, 10))     # Affiche 15
```

📌 Points clés :

* `args` est une **tuple**.
* Le nom `args` est conventionnel, mais on peut mettre n’importe quel nom.
* Utile quand on ne sait pas combien de paramètres seront passés.


# 3. `**kwargs` : arguments nommés variables

## 3.1. Syntaxe

```python
def ma_fonction(**kwargs):
    for cle, valeur in kwargs.items():
        print(f"{cle} = {valeur}")
```

## 3.2. Exemple

```python
def presentation(**infos):
    for cle, valeur in infos.items():
        print(f"{cle}: {valeur}")

presentation(nom="Alice", age=20, ville="Paris")
# Affiche :
# nom: Alice
# age: 20
# ville: Paris
```

📌 Points clés :

* `kwargs` est un **dictionnaire** (`dict`).
* Permet de gérer un nombre **variable de paramètres avec nom**.
* Utile pour créer des fonctions flexibles.



# 4. Combiner `*args` et `**kwargs`

```python
def exemple(*args, **kwargs):
    print("Args :", args)
    print("Kwargs :", kwargs)

exemple(1, 2, 3, nom="Alice", age=20)
# Args : (1, 2, 3)
# Kwargs : {'nom': 'Alice', 'age': 20}
```

📌 Règle importante :

* Toujours **`*args` avant `**kwargs`** dans la définition de la fonction.


# 5. Note : `*args` n'accepte pas les arguments nommés

## 5.1. Rappel

* `*args` → capture **les arguments positionnels** sous forme de tuple.
* `**kwargs` → capture **les arguments nommés** sous forme de dictionnaire.

Donc, si tu essaies de passer **des arguments nommés** (`nom=..., age=...`) à une fonction qui **n’accepte que `*args`**, Python va lever une erreur.


## 5.2. Exemple concret

```python
def test_args(*args):
    print(args)

# Appel avec arguments positionnels → OK
test_args(1, 2, 3)
# Sortie : (1, 2, 3)

# Appel avec arguments nommés → ERREUR
test_args(a=1, b=2)
# TypeError: test_args() got an unexpected keyword argument 'a'
```

**Explication :**
`*args` ne sait pas gérer les arguments avec des **clés**, donc Python bloque.


## 5.3. Comment gérer les deux en même temps ?

Si on veut accepter **tout type d’argument**, il faut combiner `*args` et `**kwargs` :

```python
def test_args_kwargs(*args, **kwargs):
    print("Args :", args)
    print("Kwargs :", kwargs)

test_args_kwargs(1, 2, nom="Alice", age=20)
# Args : (1, 2)
# Kwargs : {'nom': 'Alice', 'age': 20}
```

* Les arguments **sans nom** vont dans `args`
* Les arguments **avec nom** vont dans `kwargs`



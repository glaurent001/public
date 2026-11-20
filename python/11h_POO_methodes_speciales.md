(_Cours Python : [retour sommaire](readme.md#les-bases-du-langage-python)_)
# Chap. 11h - POO : Méthodes spéciales associées aux classes

> * Auteur :  Gwénaël LAURENT
> * Date : 13-04-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 11h - POO : Méthodes spéciales associées aux classes](#chap-11h---poo--méthodes-spéciales-associées-aux-classes)
- [1. Méthodes spéciales](#1-méthodes-spéciales)
- [2. Différence entres `__str__()` et `__repr__()`](#2-différence-entres-__str__-et-__repr__)
- [3. Le Destructeur `__del__()`](#3-le-destructeur-__del__)
  - [3.1. Destruction d'un objet avec l'instruction `del`](#31-destruction-dun-objet-avec-linstruction-del)
  - [3.2. Destruction avec le ramasse-miettes (garbage collector)](#32-destruction-avec-le-ramasse-miettes-garbage-collector)
  - [3.3. `__del__()` n'est pas forcément appelée immédiatement](#33-__del__-nest-pas-forcément-appelée-immédiatement)
- [4. Trier des objets avec la méthode `__lt__()`](#4-trier-des-objets-avec-la-méthode-__lt__)
- [5. Comparer des objets avec `@functools.total_ordering`](#5-comparer-des-objets-avec-functoolstotal_ordering)

 



# 1. Méthodes spéciales
Toutes les classes peuvent définir des **méthodes spéciales** dont le nom est encadré par des double-underscores.

Les méthodes spéciales permettent de modifier le comportement des objets. Les plus courantes sont :

- `__init__()` : constructeur, appelé automatiquemt lors de la création de l'objet.
- `__del__()` : destructeur, appelé automatiquemt lors de la destruction de l'objet.
- `__str__()` : définit l’affichage (`print(objet)`).
- `__repr__()` : définit la représentation officielle de l’objet.
- `__eq__()`, `__ne__()` : définit l’égalité entre objets (`==`) et l'inégalité (`!=`).
- `__lt__()`, `__gt__()` : définissent `<` et `>` entre objets.
- `__le__()`, `__ge__()` : définissent `<=` et `>=` entre objets.


# 2. Différence entres `__str__()` et `__repr__()`

- **`__str__()`** (appelée avec `str(objet)`) : fournit une **représentation lisible** pour l’utilisateur final (utilisée par `print(objet)`).  
- **`__repr__()`** (appelée avec `repr(objet)`) : fournit une représentation textuelle du code python qui permet de reconstruire l'objet. Le texte doit être dans un format **évaluable par Python** (`eval(repr(objet))` doit recréer l’objet).


**Exemple :**
```python
class Personne:
    def __init__(self, nom: str, age: int) -> None:
        self.nom: str = nom
        self.age: int = age

    def __str__(self):
        return f"{self.nom}, {self.age} ans"

    def __repr__(self) -> str:
        return f"Personne(nom='{self.nom}', age={self.age})"

# Utilisation
p = Personne("Alice", 25)
print(str(p))   # Alice, 25 ans
print(repr(p))  # Personne('Alice', 25)
```
**Dans quels cas `__repr__()` est utile ?**
* pour stocker des objets dans un fichier ou une base de données sous forme texte lisible, puis les recharger facilement
* pour logger des objets (ex: debug ou audit) de manière reconstructible
* c’est une bonne habitude d’écrire __repr__() de façon à ce que ça marche avec eval()

**Remarques :** eval() est dangereux si on évalue du texte venant de l’utilisateur (risque d'exécution de code arbitraire).

**Affichage avec la fonction `print(objet)` :**
* print() utilise `__str__()` pour afficher l'objet.
* si `__str__()` n'est pas implémentée, c'est `__repr__()` qui sera utilisé
* si aucune des deux n'est implémentée, c'est l'adresse mémoire qui sera affichée

# 3. Le Destructeur `__del__()`
## 3.1. Destruction d'un objet avec l'instruction `del`
La méthode `__del__()` est appelée **automatiquement** quand un objet est **détruit** (c’est-à-dire quand il n’a plus de références).

En python, on demande la destruction d'un objet avec la commande `del objet`.

**Exemple de base**
```python
class Exemple:
    def __init__(self, p_nom:str):
        self.nom:str = p_nom
        print(f"Objet {self.nom} créé.")

    def __del__(self):
        print(f"Objet {self.nom} détruit.")

# Création et suppression d'un objet
e = Exemple("Test")  # Objet Test créé.
del e  # Objet Test détruit.
```


## 3.2. Destruction avec le ramasse-miettes (garbage collector)
Python utilise un **ramasse-miettes (garbage collector)** qui détruit automatiquement les objets **sans références**.

C'est le cas, par exemple, pour les variables locales (déclarées dans une fonction). **L’objet est détruit dès qu’il sort du scope** (scope = "portée". La portée désigne l’endroit d’un programme où une variable est accessible).

```python
def creer_objet():
    obj = Exemple("Temporaire")

creer_objet()  # L’objet est détruit dès la fin de la fonction
```
**Sortie :**
```
Objet Temporaire créé.
Objet Temporaire détruit.
```

## 3.3. `__del__()` n'est pas forcément appelée immédiatement
⚠️ Si un objet fait partie d’une **référence circulaire**, il ne sera pas immédiatement détruit par Python.


**Exemple :**
```python
from __future__ import annotations

class A:
    def __init__(self, p_nom: str):
        self.nom: str = p_nom
        self.autre: A | None = None

    def associer(self, p_a: A):
        self.autre = p_a

    def __del__(self):
        print(f"Objet {self.nom} détruit.")


a1 = A("a1")
a2 = A("a2")
a1.associer(a2)  # Référence circulaire
a2.associer(a1)  # Référence circulaire


del a1  # L'objet n'est pas détruit immédiatement
del a2  # Toujours pas détruit, car ils se référencent mutuellement
# a1 et a2 sont inaccesibles mais leur destructeur n'a pas été appelé !
```

La commande `del objet` correspond plus à une demande de suppression.\
C'est le garbage collector qui supprime réellement les ressources : soit quand le script se termine, soit quand on l'invoque expressément.

**On peut forcer la libération des ressources** en utilisant `gc.collect()`

```python
import gc

gc.collect()  # Force la suppression des objets non référencés
```

**Remarque :** C'est une bonne pratique de ne pas dépendre de `__del__()` pour libérer des ressources critiques (fichiers, connexions…).  



# 4. Trier des objets avec la méthode `__lt__()`
En Python, pour permettre à une liste d'objets d'une classe `Personne` d'être triée automatiquement avec `sort()`, il faut implémenter la méthode spéciale `__lt__` (`less than`) dans la classe.  

> Il n'est pas nécessaire d'implémenter `__gt__` (`>`) ou `__eq__` (`==`) pour que `sort()` fonctionne. Python utilise uniquement `__lt__` (`<`) pour trier les objets.

**Exemple :**

```python
from __future__ import annotations

class Personne:
    def __init__(self, p_nom: str, p_age: int) -> None:
        self.nom: str = p_nom
        self.age: int = p_age

    def __lt__(self, other: Personne) -> bool:
        return self.nom < other.nom  # Comparaison basée sur l'attribut nom

    def __repr__(self) -> str:
        return f"Personne(nom='{self.nom}', age={self.age})"

# Exemple d'utilisation
personnes: list[Personne] = [
    Personne("Zoe", 25),
    Personne("Alice", 30),
    Personne("Bob", 22)
]

personnes.sort()  # Trie les objets en fonction de leur attribut 'nom'

for p in personnes:
    print(p)
```
**Sortie :**
```sh
Personne(nom='Alice', age=30)
Personne(nom='Bob', age=22)
Personne(nom='Zoe', age=25)
```


# 5. Comparer des objets avec `@functools.total_ordering`
 
Si vous voulez que vos objets soient complètement ordonnables et comparables pour des opérations comme :
- `obj1 == obj2` (égalité)
- `obj1 > obj2` (supériorité)
- `obj1 <= obj2` (infériorité ou égalité)

Alors, vous pouvez soit définir toutes les méthodes (`__lt__`, `__le__`, `__eq__`, `__ne__`, `__gt__`, `__ge__`), soit utiliser le décorateur **`@functools.total_ordering`**, qui permet d'implémenter une seule méthode (`__lt__` ou `__gt__`) et `__eq__`, et Python déduira les autres :

```python
from __future__ import annotations
from functools import total_ordering

@total_ordering
class Personne:
    def __init__(self, p_nom: str, p_age: int) -> None:
        self.nom: str = p_nom
        self.age: int = p_age

    def __lt__(self, other: Personne) -> bool:
        return self.nom < other.nom  # Comparaison basée sur l'attribut nom

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Personne):
            return NotImplemented
        return self.nom == other.nom

    def __repr__(self) -> str:
        return f"Personne(nom='{self.nom}', age={self.age})"

# Exemple d'utilisation
p1 = Personne("Alice", 30)
p2 = Personne("Bob", 22)
p3 = Personne("Alice", 25)

print(p1 < p2)  # True, car "Alice" < "Bob"
print(p1 == p3) # True, car les noms sont identiques
print(p1 > p2)  # False, car "Alice" < "Bob"
print(p2 >= p3) # True, car "Bob" >= "Alice"
```

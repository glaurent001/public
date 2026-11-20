(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Chapitre 1 : Différences fondamentales entre Python et C++

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chapitre 1 : Différences fondamentales entre Python et C++](#chapitre-1--différences-fondamentales-entre-python-et-c)
  - [1. Typage](#1-typage)
  - [2. Compilation vs interprétation](#2-compilation-vs-interprétation)
  - [3. Gestion de la mémoire](#3-gestion-de-la-mémoire)


## 1. Typage

* **Python** : typage dynamique, pas besoin de déclarer un type.
* **C++** : typage statique, chaque variable doit avoir un type connu à la compilation.

**Exemple :**

```python
# Python
x = 5          # entier
x = "bonjour"  # la même variable peut devenir une chaîne
```

```cpp
// C++
int x = 5;        // entier
x = "bonjour";    // ❌ Erreur : on ne peut pas changer de type
std::string y = "bonjour"; // ✅
```

---

## 2. Compilation vs interprétation

* **Python** : code exécuté directement par l’interpréteur.
* **C++** : code compilé en exécutable.

**Exemple :**

```bash
# En Python
python3 monscript.py
```

```bash
# En C++
g++ programme.cpp -o programme
./programme
```

---

## 3. Gestion de la mémoire

* **Python** : le ramasse-miettes (garbage collector) libère automatiquement la mémoire.
* **C++** : possibilité d’allocation/libération manuelle.

**Exemple :**

```python
# Python
ma_liste = [1, 2, 3]
# Quand la variable n'est plus utilisée, Python libère la mémoire.
```

```cpp
// C++
int* ptr = new int(42);   // allocation dynamique
delete ptr;               // libération manuelle
```


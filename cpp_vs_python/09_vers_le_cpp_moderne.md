(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Chapitre 9 : Vers le C++ moderne

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chapitre 9 : Vers le C++ moderne](#chapitre-9--vers-le-c-moderne)
  - [1. Type auto](#1-type-auto)
  - [2. nullptr](#2-nullptr)
  - [3. Boucles modernes (range-based for)](#3-boucles-modernes-range-based-for)
  - [4. Fonctions lambda](#4-fonctions-lambda)
  - [5. Gestion des exceptions](#5-gestion-des-exceptions)
  - [6. Smart pointers et RAII](#6-smart-pointers-et-raii)
  - [7. Résumé comparatif Python / C++ moderne](#7-résumé-comparatif-python--c-moderne)

> 📌 **Points clés :**
> 
> * Le **C++ moderne** se rapproche de Python par sa **syntaxe plus concise** (auto, for simplifié, lambdas).
> * Mais il garde une **rigueur forte** (typage statique, gestion explicite des exceptions, mémoire maîtrisée).
> * Python = rapidité de prototypage, C++ moderne = performance et contrôle.

## 1. Type auto

En **Python**, le typage est dynamique : on n’écrit pas les types.
En **C++ moderne**, on peut utiliser `auto` pour demander au compilateur **d’inférer le type** (mais il reste statique).

```python
# Python
x = 42      # entier
y = 3.14    # flottant
```

```cpp
// C++ moderne
auto x = 42;      // int
auto y = 3.14;    // double
```

✅ Pratique, mais le type reste figé après la compilation (contrairement à Python).


## 2. nullptr

En **Python**, la valeur spéciale `None` représente "rien".
En **C++ moderne**, on utilise `nullptr` au lieu de `NULL` (ancienne écriture).

```python
# Python
val = None
if val is None:
    print("Vide")
```

```cpp
// C++
int* p = nullptr;
if (p == nullptr) {
    cout << "Vide" << endl;
}
```


## 3. Boucles modernes (range-based for)

En **Python**, `for … in` est très utilisé.
En **C++11**, on a ajouté une version similaire :

```python
# Python
nombres = [1, 2, 3, 4]
for n in nombres:
    print(n)
```

```cpp
// C++11
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nombres = {1, 2, 3, 4};
    for (int n : nombres) {
        cout << n << endl;
    }
    return 0;
}
```


## 4. Fonctions lambda

En **Python**, on peut écrire des petites fonctions anonymes avec `lambda`.
En **C++11**, on a introduit la même chose avec `[](){}`.

```python
# Python
f = lambda x: x * 2
print(f(5))   # 10
```

```cpp
// C++11
#include <iostream>
using namespace std;

int main() {
    auto f = [](int x) { return x * 2; };
    cout << f(5) << endl;   // 10
    return 0;
}
```


## 5. Gestion des exceptions

En **Python**, on utilise `try … except`.
En **C++**, on utilise `try … catch … throw`.

```python
# Python
try:
    x = int("abc")
except ValueError:
    print("Erreur de conversion")
```

```cpp
// C++
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        throw invalid_argument("Erreur de conversion");
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
    }
    return 0;
}
```


## 6. Smart pointers et RAII

> RAII =  Resource Acquisition Is Initialization\
> (L'acquisition d'une ressource est une initialisation)\
> Ça veut dire qu'un objet acquerra ses ressources lors de l'initialisation et les libérera lors de sa destruction.

Déjà vus au chapitre 7 :

* `unique_ptr` : pointeur unique, détruit automatiquement quand il sort du scope.
* `shared_ptr` : pointeur partagé entre plusieurs objets.

C’est l’équivalent du **garbage collector de Python**, mais en **C++ explicite et contrôlé**.


## 7. Résumé comparatif Python / C++ moderne

| Fonctionnalité    | Python            | C++ moderne (C++11 et +)   |
| ----------------- | ----------------- | -------------------------- |
| Inférence de type | Automatique       | `auto`                     |
| Valeur nulle      | `None`            | `nullptr`                  |
| Boucles modernes  | `for x in liste:` | `for (auto x : vecteur)`   |
| Lambda            | `lambda x: ...`   | `[ ](int x){ ... }`        |
| Exceptions        | `try/except`      | `try/catch/throw`          |
| Gestion mémoire   | Garbage collector | `unique_ptr`, `shared_ptr` |






(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Chapitre 7 : Gestion mémoire et pointeurs

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chapitre 7 : Gestion mémoire et pointeurs](#chapitre-7--gestion-mémoire-et-pointeurs)
  - [1. Références en Python vs C++](#1-références-en-python-vs-c)
  - [2. Pointeurs](#2-pointeurs)
  - [3. Allocation dynamique](#3-allocation-dynamique)
  - [4. Tableaux dynamiques](#4-tableaux-dynamiques)
  - [5. Smart pointers (C++ moderne)](#5-smart-pointers-c-moderne)
  - [6. Comparaison Python vs C++](#6-comparaison-python-vs-c)

> 📌 **Points clés :**
> 
> * Python **cache la mémoire**, C++ **la rend visible et contrôlable**.
> * Les pointeurs permettent une gestion fine, mais attention aux erreurs.
> * Le C++ moderne (C++11 et +) réduit les risques grâce aux smart pointers.

## 1. Références en Python vs C++

En **Python**, toutes les variables sont en réalité des **références vers des objets**, même si on ne le voit pas.
En **C++**, on peut avoir :

* des **valeurs** (copiées),
* des **références** (alias avec `&`),
* des **pointeurs** (adresses mémoire avec `*`).

```python
# Python
a = [1, 2, 3]
b = a          # b référence la même liste
b.append(4)
print(a)       # [1, 2, 3, 4]
```

```cpp
// C++
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int &b = a;    // b est une référence vers a
    b = 20;
    cout << a << endl; // 20 (a a changé aussi)
    return 0;
}
```


## 2. Pointeurs

Un **pointeur** est une variable qui contient **l’adresse mémoire** d’une autre variable.
C’est une notion absente de Python mais centrale en C++.

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 42;
    int *p = &x;   // p contient l’adresse de x

    cout << "x = " << x << endl;     // 42
    cout << "Adresse de x = " << p << endl;
    cout << "Valeur pointée = " << *p << endl; // 42 (déréférencement)

    *p = 100;   // on modifie x via le pointeur
    cout << "x = " << x << endl;     // 100
    return 0;
}
```


## 3. Allocation dynamique

En **Python**, la mémoire est gérée automatiquement par le garbage collector.
En **C++**, on peut réserver et libérer de la mémoire manuellement.

```cpp
#include <iostream>
using namespace std;

int main() {
    int *p = new int;   // allocation dynamique
    *p = 5;
    cout << *p << endl; // 5
    delete p;           // libération obligatoire
    return 0;
}
```

⚠️ Si on oublie `delete`, on crée une **fuite mémoire** (mémoire perdue mais pas libérée).


## 4. Tableaux dynamiques

Avec `new`, on peut créer un tableau dont la taille est décidée à l’exécution.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Taille ? ";
    cin >> n;

    int *tab = new int[n];   // tableau dynamique
    for (int i = 0; i < n; i++) {
        tab[i] = i * 2;
    }
    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }

    delete[] tab;  // libération mémoire
    return 0;
}
```


## 5. Smart pointers (C++ moderne)

Comme la gestion manuelle est risquée, le **C++ moderne** (C++11 et +) introduit les **pointeurs intelligents**, qui libèrent la mémoire automatiquement (comme Python).

```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<int> p1 = make_unique<int>(42);  // pointeur unique
    cout << *p1 << endl;

    shared_ptr<int> p2 = make_shared<int>(99);  // pointeur partagé
    cout << *p2 << endl;

    return 0;  // pas besoin de delete, libération automatique
}
```


## 6. Comparaison Python vs C++

| Concept                | Python (automatique)           | C++ (manuel + moderne)              |
| ---------------------- | ------------------------------ | ----------------------------------- |
| Références             | Implémentées par défaut        | `&` explicite                       |
| Pointeurs              | Cachés à l’utilisateur         | `*` et `&`                          |
| Allocation             | Automatique                    | `new` et `delete`                   |
| Fuites mémoire         | Impossible                     | Possible si oubli de `delete`       |
| Pointeurs intelligents | Par défaut (garbage collector) | `unique_ptr`, `shared_ptr` (C++11+) |



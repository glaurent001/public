(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Chapitre 3 : Structures de contrôle

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chapitre 3 : Structures de contrôle](#chapitre-3--structures-de-contrôle)
  - [1. Conditions (`if`, `else if`, `else`)](#1-conditions-if-else-if-else)
  - [2. Boucles](#2-boucles)
    - [a) Boucle `while`](#a-boucle-while)
    - [b) Boucle `for`](#b-boucle-for)
    - [c) Boucle `do…while`](#c-boucle-dowhile)
  - [3. Switch-case](#3-switch-case)


## 1. Conditions (`if`, `else if`, `else`)

En **Python**, l’indentation délimite les blocs.
En **C++**, on utilise des **parenthèses** autour des conditions et des **accolades** `{}` pour les blocs.

```python
# Python
x = 10

if x > 0:
    print("Positif")
elif x == 0:
    print("Nul")
else:
    print("Négatif")
```

```cpp
// C++
#include <iostream>
using namespace std;

int main() {
    int x = 10;

    if (x > 0) {
        cout << "Positif" << endl;
    } else if (x == 0) {
        cout << "Nul" << endl;
    } else {
        cout << "Négatif" << endl;
    }

    return 0;
}
```

⚠️ Remarque : en C++, il faut mettre des `==` pour tester l’égalité, comme en Python.


## 2. Boucles

### a) Boucle `while`

```python
# Python
i = 0
while i < 5:
    print(i)
    i += 1
```

```cpp
// C++
#include <iostream>
using namespace std;

int main() {
    int i = 0;
    while (i < 5) {
        cout << i << endl;
        i++;
    }
    return 0;
}
```


### b) Boucle `for`

En **Python**, `for` parcourt une séquence (liste, chaîne, range…).
En **C++**, `for` sert plutôt à répéter un compteur (comme `while` avec incrémentation).

```python
# Python
for i in range(5):
    print(i)
```

```cpp
// C++
#include <iostream>
using namespace std;

int main() {
    for (int i = 0; i < 5; i++) {
        cout << i << endl;
    }
    return 0;
}
```


### c) Boucle `do…while`

⚠️ **N’existe pas en Python**.
En **C++**, c’est une boucle qui s’exécute **au moins une fois**, puis teste la condition.

```cpp
// C++
#include <iostream>
using namespace std;

int main() {
    int i = 0;
    do {
        cout << i << endl;
        i++;
    } while (i < 5);
    return 0;
}
```


## 3. Switch-case

⚠️ **Pas de switch-case en Python** (on utilise souvent `if/elif`).
En **C++**, `switch` est pratique pour choisir parmi plusieurs cas **entiers ou caractères**.

```cpp
// C++
#include <iostream>
using namespace std;

int main() {
    int jour = 3;

    switch (jour) {
        case 1:
            cout << "Lundi" << endl;
            break;
        case 2:
            cout << "Mardi" << endl;
            break;
        case 3:
            cout << "Mercredi" << endl;
            break;
        default:
            cout << "Jour inconnu" << endl;
    }

    return 0;
}
```

⚠️ Attention :

* Chaque `case` doit finir par un `break` (sinon le programme continue dans le `case` suivant).
* Pas possible de tester des chaînes (`switch` ne fonctionne qu’avec des entiers ou `char`).


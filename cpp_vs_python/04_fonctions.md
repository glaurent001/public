(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Chapitre 4 : Fonctions

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chapitre 4 : Fonctions](#chapitre-4--fonctions)
  - [1. Définition et appel simple](#1-définition-et-appel-simple)
  - [2. Fonctions sans retour](#2-fonctions-sans-retour)
  - [3. Passage de paramètres](#3-passage-de-paramètres)
  - [4. Surcharge de fonctions](#4-surcharge-de-fonctions)
  - [5. Paramètres par défaut](#5-paramètres-par-défaut)

> 📌 **Points clés :**
> 
> * Python simplifie les fonctions (pas de typage obligatoire, retour flexible).
> * C++ est plus strict (déclaration des types, surcharge possible, passage par valeur/référence/pointeur).

## 1. Définition et appel simple

En **Python**, on définit une fonction avec `def` et on ne précise pas les types.
En **C++**, il faut indiquer le **type de retour** et les **types des paramètres**.

```python
# Python
def bonjour(nom):
    return "Bonjour " + nom

print(bonjour("Alice"))
```

```cpp
// C++
#include <iostream>
#include <string>
using namespace std;

string bonjour(string nom) {
    return "Bonjour " + nom;
}

int main() {
    cout << bonjour("Alice") << endl;
    return 0;
}
```



## 2. Fonctions sans retour

En **Python**, si on ne met pas `return`, la fonction renvoie `None`.
En **C++**, on utilise le type `void` pour dire qu’il n’y a pas de valeur de retour.

```python
# Python
def afficher(x):
    print("Valeur :", x)

afficher(10)
```

```cpp
// C++
#include <iostream>
using namespace std;

void afficher(int x) {
    cout << "Valeur : " << x << endl;
}

int main() {
    afficher(10);
    return 0;
}
```



## 3. Passage de paramètres

En **Python**, tout est transmis par référence (en réalité, par "référence à l’objet").
En **C++**, on peut passer :

* **par valeur** (copie de la variable),
* **par référence** (le `&` permet de modifier l’original),
* **par pointeur** (plus bas niveau).

```python
# Python
def incrementer(x):
    x += 1
    return x

val = 5
print(incrementer(val))  # 6
print(val)               # 5 (non modifié)
```

```cpp
// C++
#include <iostream>
using namespace std;

// Par valeur (copie)
int incrementer(int x) {
    x++;
    return x;
}

// Par référence (modifie l’original)
void incrementer_ref(int &x) {
    x++;
}

int main() {
    int val = 5;

    cout << incrementer(val) << endl; // 6
    cout << val << endl;              // 5

    incrementer_ref(val);
    cout << val << endl;              // 6 (modifié)

    return 0;
}
```



## 4. Surcharge de fonctions

⚠️ **En Python, impossible** de définir deux fonctions avec le même nom et des paramètres différents (il faut ruser avec `*args`, `**kwargs`).
En **C++**, on peut créer plusieurs fonctions du même nom si leurs signatures diffèrent.

```cpp
// C++
#include <iostream>
using namespace std;

int somme(int a, int b) {
    return a + b;
}

double somme(double a, double b) {
    return a + b;
}

int main() {
    cout << somme(3, 4) << endl;       // appelle la version int
    cout << somme(2.5, 3.7) << endl;   // appelle la version double
    return 0;
}
```



## 5. Paramètres par défaut

Les **paramètres par défaut** existent aussi bien en Python qu’en C++.

```python
# Python
def bonjour(nom="inconnu"):
    print("Bonjour", nom)

bonjour()
bonjour("Alice")
```

```cpp
// C++
#include <iostream>
#include <string>
using namespace std;

void bonjour(string nom = "inconnu") {
    cout << "Bonjour " << nom << endl;
}

int main() {
    bonjour();
    bonjour("Alice");
    return 0;
}
```


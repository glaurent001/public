(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Chapitre 2 : Syntaxe de base

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chapitre 2 : Syntaxe de base](#chapitre-2--syntaxe-de-base)
  - [1. Structure d’un programme](#1-structure-dun-programme)
  - [2. Variables et constantes](#2-variables-et-constantes)
  - [3. Entrées / sorties](#3-entrées--sorties)


## 1. Structure d’un programme

En **Python**, un script peut être réduit à une seule ligne.
En **C++**, tout doit être dans une fonction `main()`.

```python
# Python
print("Bonjour")
```

```cpp
// C++
#include <iostream>     // bibliothèque pour cout
using namespace std;

int main() {
    cout << "Bonjour" << endl;
    return 0;           // fin du programme
}
```


## 2. Variables et constantes

```python
# Python
a = 10
pi = 3.14
nom = "Alice"
```

```cpp
// C++
int a = 10;            // entier
double pi = 3.14;      // flottant
std::string nom = "Alice"; // chaîne
const int AGE = 18;    // constante
```


## 3. Entrées / sorties

```python
# Python
nom = input("Ton nom ? ")
print("Bonjour", nom)
```

```cpp
// C++
#include <iostream>
using namespace std;

int main() {
    string nom;
    cout << "Ton nom ? ";
    cin >> nom;
    cout << "Bonjour " << nom << endl;
    return 0;
}
```


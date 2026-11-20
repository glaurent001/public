(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Chapitre 5 : Tableaux, listes et chaînes

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chapitre 5 : Tableaux, listes et chaînes](#chapitre-5--tableaux-listes-et-chaînes)
  - [1. Tableaux (taille fixe en C++)](#1-tableaux-taille-fixe-en-c)
  - [2. Vecteurs (`std::vector`) : l’équivalent dynamique](#2-vecteurs-stdvector--léquivalent-dynamique)
  - [3. Parcours des collections](#3-parcours-des-collections)
    - [Avec un index](#avec-un-index)
    - [Parcours direct (plus moderne)](#parcours-direct-plus-moderne)
  - [4. Chaînes de caractères](#4-chaînes-de-caractères)
  - [5. Comparaison rapide](#5-comparaison-rapide)

> 📌 **Points clés :**
> 
> * **Python** propose des listes très flexibles, sans se soucier du type.
> * **C++** impose le choix entre **tableau fixe** et **vector dynamique**, avec typage statique.
> * Les **chaînes** fonctionnent comme des vecteurs de caractères, mais en plus pratique grâce à `std::string`.

## 1. Tableaux (taille fixe en C++)

En **Python**, une liste est dynamique (on peut ajouter/enlever des éléments).
En **C++**, un tableau classique (`array`) a une **taille fixe** définie à la compilation.

```python
# Python
notes = [12, 15, 9]
print(notes[0])    # 12
notes[1] = 16      # modification
```

```cpp
// C++
#include <iostream>
using namespace std;

int main() {
    int notes[3] = {12, 15, 9}; // tableau de 3 entiers

    cout << notes[0] << endl;   // 12
    notes[1] = 16;              // modification
    cout << notes[1] << endl;   // 16

    return 0;
}
```

⚠️ Limitation : en C++, les tableaux classiques ne peuvent pas changer de taille.


## 2. Vecteurs (`std::vector`) : l’équivalent dynamique

Pour avoir un comportement similaire aux **listes Python**, on utilise `std::vector`.

```python
# Python
nombres = [1, 2, 3]
nombres.append(4)      # ajout
print(nombres)         # [1, 2, 3, 4]
```

```cpp
// C++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nombres = {1, 2, 3};
    nombres.push_back(4);   // ajout
    cout << nombres[0] << " " << nombres[3] << endl; // 1 4
    cout << "Taille : " << nombres.size() << endl;   // 4
    return 0;
}
```

✅ `std::vector` est très proche des listes Python, mais avec typage statique.


## 3. Parcours des collections

### Avec un index

```python
# Python
for i in range(len(nombres)):
    print(nombres[i])
```

```cpp
// C++
for (int i = 0; i < nombres.size(); i++) {
    cout << nombres[i] << endl;
}
```

### Parcours direct (plus moderne)

```python
# Python
for x in nombres:
    print(x)
```

```cpp
// C++ (C++11 et +)
for (int x : nombres) {
    cout << x << endl;
}
```


## 4. Chaînes de caractères

En **Python**, les chaînes (`str`) sont dynamiques et puissantes.
En **C++**, on distingue :

* les **chaînes en C** (`char[]`, peu utilisées pour débuter),
* les **chaînes modernes** (`std::string`).

```python
# Python
nom = "Alice"
print(nom[0])        # A
print(len(nom))      # 5
print(nom + " Bob")  # Alice Bob
```

```cpp
// C++
#include <iostream>
#include <string>
using namespace std;

int main() {
    string nom = "Alice";
    cout << nom[0] << endl;         // A
    cout << nom.size() << endl;     // 5
    cout << nom + " Bob" << endl;   // Alice Bob
    return 0;
}
```


## 5. Comparaison rapide

| Concept             | Python         | C++ (moderne)  |
| ------------------- | -------------- | -------------- |
| Liste dynamique     | `list`         | `std::vector`  |
| Tableau taille fixe | (rare) `array` | `int tab[10];` |
| Chaîne              | `str`          | `std::string`  |



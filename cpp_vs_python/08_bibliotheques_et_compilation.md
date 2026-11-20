(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Chapitre 8 : Bibliothèques et compilation

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chapitre 8 : Bibliothèques et compilation](#chapitre-8--bibliothèques-et-compilation)
  - [1. Import de bibliothèques](#1-import-de-bibliothèques)
  - [2. Organisation des fichiers](#2-organisation-des-fichiers)
    - [Exemple : classe `Personne`](#exemple--classe-personne)
  - [3. Compilation et exécution](#3-compilation-et-exécution)
  - [4. Compilation multi-fichiers](#4-compilation-multi-fichiers)
  - [5. Résumé comparatif](#5-résumé-comparatif)

> 📌 **Points clés :**
> 
> * Python est **rapide à écrire et exécuter**.
> * C++ demande **plus de discipline** : séparer `.h` et `.cpp`, compiler avant d’exécuter.
> * Ne pas oublier l’importance de la **phase de compilation** en C++.

## 1. Import de bibliothèques

En **Python**, on importe un module avec `import` ou `from ... import`.
En **C++**, on utilise `#include` pour ajouter une bibliothèque ou un fichier d’en-tête.

```python
# Python
import math
print(math.sqrt(16))   # 4.0
```

```cpp
// C++
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    cout << sqrt(16) << endl;   // 4
    return 0;
}
```

⚠️ Différence :

* Python charge le module à l’exécution.
* C++ insère le code du fichier d’en-tête au moment de la compilation.


## 2. Organisation des fichiers

En **Python**, tout peut être dans un seul fichier `.py`, ou bien organisé en **modules/packages**.
En **C++**, on sépare souvent :

* les **fichiers d’en-tête** (`.h`) → déclarations des classes et fonctions,
* les **fichiers source** (`.cpp`) → implémentations.

### Exemple : classe `Personne`

**Personne.h**

```cpp
#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>
using namespace std;

class Personne {
private:
    string nom;
public:
    Personne(string n);
    void bonjour();
};

#endif
```

**Personne.cpp**

```cpp
#include "Personne.h"
#include <iostream>
using namespace std;

Personne::Personne(string n) {
    nom = n;
}

void Personne::bonjour() {
    cout << "Bonjour, je m'appelle " << nom << endl;
}
```

**main.cpp**

```cpp
#include "Personne.h"

int main() {
    Personne p("Alice");
    p.bonjour();
    return 0;
}
```


## 3. Compilation et exécution

En **Python**, pas besoin de compilation :

```bash
python3 programme.py
```

En **C++**, il faut compiler d’abord, puis exécuter l’exécutable généré :

```bash
g++ main.cpp Personne.cpp -o programme
./programme
```


## 4. Compilation multi-fichiers

Quand un projet grossit, il faut compiler plusieurs fichiers `.cpp` en même temps :

```bash
g++ main.cpp fichier1.cpp fichier2.cpp -o monProgramme
```

Ou utiliser un **Makefile** (équivalent d’un script de compilation).

Exemple de `Makefile` simple :

```make
programme: main.o Personne.o
	g++ main.o Personne.o -o programme

main.o: main.cpp Personne.h
	g++ -c main.cpp

Personne.o: Personne.cpp Personne.h
	g++ -c Personne.cpp
```

Puis lancer :

```bash
make
```


## 5. Résumé comparatif

| Concept                 | Python                       | C++                                     |
| ----------------------- | ---------------------------- | --------------------------------------- |
| Import de bibliothèques | `import module`              | `#include <lib>` ou `"fichier.h"`       |
| Organisation fichiers   | `.py` modules/packages       | `.h` (déclarations) + `.cpp` (code)     |
| Compilation             | Automatique (interprétation) | Obligatoire avec `g++`                  |
| Exécution               | `python3 script.py`          | `./programme` après compilation         |
| Outils projets          | Virtuelenv, pip, etc.        | Makefile, CMake, gestionnaires de build |




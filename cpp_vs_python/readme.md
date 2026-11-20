# Découvrir le C++ à partir du Python

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Découvrir le C++ à partir du Python](#découvrir-le-c-à-partir-du-python)
- [Introduction](#introduction)
- [Aide-mémoire Python vs C++](#aide-mémoire-python-vs-c)
  - [1. Généralités](#1-généralités)
  - [2. Syntaxe de base](#2-syntaxe-de-base)
  - [3. Structures de contrôle](#3-structures-de-contrôle)
  - [4. Fonctions](#4-fonctions)
  - [5. Collections et chaînes](#5-collections-et-chaînes)
  - [6. POO](#6-poo)
  - [7. Gestion mémoire](#7-gestion-mémoire)
  - [8. Bibliothèques et compilation](#8-bibliothèques-et-compilation)
  - [9. C++ moderne (C++11 et +)](#9-c-moderne-c11-et-)
  - [10. Comparaisons C++ classique vs Arduino](#10-comparaisons-c-classique-vs-arduino)


# Introduction
> * Python = **simplicité, rapidité d’écriture, flexibilité**.
> * C++ = **performance, contrôle fin, rigueur**.
> * Le C++ moderne réduit l’écart avec Python (syntaxe simplifiée, sécurité mémoire améliorée).

Vous touverez ici des exemples comparatifs Python vs C++. Chaque chapitre comporte des exemples concrets côte-à-côte de code Python vs C++.

On part des acquis en Python et on met en parallèle la syntaxe et la logique de C++.

- [Aide-mémoire Python vs C++](readme.md#aide-mémoire-python-vs-c)
- [Chapitre 1 : Différences fondamentales entre Python et C++](01_differences_fondamentales.md)
- [Chapitre 2 : Syntaxe de base](02_syntaxe_de_base.md)
- [Chapitre 3 : Structures de contrôle](03_structures_de_controle.md)
- [Chapitre 4 : Fonctions](04_fonctions.md)
- [Chapitre 5 : Tableaux, listes et chaînes](05_tableau_liste_chaine.md)
- [Chapitre 6 : Programmation orientée objet](06_programmation_orientee_objet.md)
- [Chapitre 7 : Gestion mémoire et pointeurs](07_gestion_memoire_et_pointeurs.md)
- [Chapitre 8 : Bibliothèques et compilation](08_bibliotheques_et_compilation.md)
- [Chapitre 9 : Vers le C++ moderne](09_vers_le_cpp_moderne.md)
- [Particularités d’un programme C++ sous Arduino](10_particularites_cpp_sous_arduino.md)




# Aide-mémoire Python vs C++


## 1. Généralités

| Aspect            | Python                          | C++                                       |
| ----------------- | ------------------------------- | ----------------------------------------- |
| Nature du langage | Interprété                      | Compilé                                   |
| Typage            | Dynamique                       | Statique (types déclarés)                 |
| Exécution         | `python3 script.py`             | `g++ prog.cpp -o prog` puis `./prog`      |
| Gestion mémoire   | Automatique (garbage collector) | Manuelle (`new/delete`) ou smart pointers |

---
[> voir Chapitre 1 : Différences fondamentales entre Python et C++](01_differences_fondamentales.md)

## 2. Syntaxe de base

| Concept      | Python                  | C++                              |
| ------------ | ----------------------- | -------------------------------- |
| Affichage    | `print("Hello")`        | `cout << "Hello" << endl;`       |
| Entrée       | `nom = input()`         | `cin >> nom;`                    |
| Commentaires | `# commentaire`         | `// commentaire` ou `/* bloc */` |
| Bloc de code | Indentation obligatoire | Accolades `{}`                   |

---
[> voir Chapitre 2 : Syntaxe de base](02_syntaxe_de_base.md)

## 3. Structures de contrôle

| Python               | C++                                      |
| -------------------- | ---------------------------------------- |
| `if x > 0:`          | `if (x > 0) { ... }`                     |
| `elif x == 0:`       | `else if (x == 0) { ... }`               |
| `else:`              | `else { ... }`                           |
| `for i in range(5):` | `for (int i = 0; i < 5; i++) { ... }`    |
| `for x in liste:`    | `for (auto x : vecteur) { ... }` (C++11) |
| `while condition:`   | `while (condition) { ... }`              |
| ❌ pas de `do…while`  | ✅ `do { ... } while (cond);`             |
| ❌ pas de `switch`    | ✅ `switch (var) { case ... }`            |

---
[> voir Chapitre 3 : Structures de contrôle](03_structures_de_controle.md)

## 4. Fonctions

| Python                                | C++                                                                          |
| ------------------------------------- | ---------------------------------------------------------------------------- |
| `def f(x): return x+1`                | `int f(int x) { return x+1; }`                                               |
| Paramètres par défaut : `def f(x=10)` | `void f(int x=10)`                                                           |
| Tout est référence d’objet            | Passage par valeur, par référence (`&`), par pointeur (`*`)                  |
| Pas de surcharge                      | ✅ Surcharge possible (`int somme(int,int)` et `double somme(double,double)`) |

---
[> voir Chapitre 4 : Fonctions](04_fonctions.md)

## 5. Collections et chaînes

| Python            | C++                        |
| ----------------- | -------------------------- |
| `liste = [1,2,3]` | `vector<int> v = {1,2,3};` |
| `liste.append(4)` | `v.push_back(4);`          |
| `len(liste)`      | `v.size()`                 |
| `chaine = "abc"`  | `string s = "abc";`        |
| `chaine + "def"`  | `s + "def"`                |

---
[> voir Chapitre 5 : Tableaux, listes et chaînes](05_tableau_liste_chaine.md)

## 6. POO

| Python                           | C++                                           |
| -------------------------------- | --------------------------------------------- |
| `class MaClasse:`                | `class MaClasse { ... };`                     |
| Constructeur : `__init__`        | Constructeur : `NomClasse(...)`               |
| Destructeur : `__del__` (rare)   | `~NomClasse()` automatique                    |
| Tout public par défaut           | `public`, `private`, `protected` obligatoires |
| Héritage : `class Fille(Mere)`   | `class Fille : public Mere { ... };`          |
| Méthodes virtuelles automatiques | Faut écrire `virtual` et utiliser pointeurs   |

---
[> voir Chapitre 6 : Programmation orientée objet](06_programmation_orientee_objet.md)

## 7. Gestion mémoire

| Python                    | C++                                          |
| ------------------------- | -------------------------------------------- |
| Variables = références    | Variables = valeurs / références / pointeurs |
| Pas de pointeurs visibles | Pointeurs (`int* p = &x;`)                   |
| Allocation auto           | `new` / `delete` (manuel)                    |
| GC automatique            | Smart pointers (`unique_ptr`, `shared_ptr`)  |

---
[> voir Chapitre 7 : Gestion mémoire et pointeurs](07_gestion_memoire_et_pointeurs.md)

## 8. Bibliothèques et compilation
| Concept                 | Python                       | C++                                     |
| ----------------------- | ---------------------------- | --------------------------------------- |
| Import de bibliothèques | `import module`              | `#include <lib>` ou `"fichier.h"`       |
| Organisation fichiers   | `.py` modules/packages       | `.h` (déclarations) + `.cpp` (code)     |
| Compilation             | Automatique (interprétation) | Obligatoire avec `g++`                  |
| Exécution               | `python3 script.py`          | `./programme` après compilation         |
| Outils projets          | Virtuelenv, pip, etc.        | Makefile, CMake, gestionnaires de build |

---
[> voir Chapitre 8 : Bibliothèques et compilation](08_bibliotheques_et_compilation.md)

## 9. C++ moderne (C++11 et +)

| Python            | C++ moderne                                |
| ----------------- | ------------------------------------------ |
| Typage implicite  | `auto`                                     |
| `None`            | `nullptr`                                  |
| `for x in liste:` | `for (auto x : vecteur)`                   |
| `lambda x: x*2`   | `[](int x){ return x*2; }`                 |
| `try/except`      | `try { ... } catch (exception &e) { ... }` |

---
[> voir Chapitre 9 : Vers le C++ moderne](09_vers_le_cpp_moderne.md)

## 10. Comparaisons C++ classique vs Arduino

| Concept                 | C++ classique        | C++ Arduino                             |
| ----------------------- | -------------------- | --------------------------------------- |
| Point d’entrée          | `int main()`         | `setup()` et `loop()`                   |
| Boucle principale       | `while(true)`        | `loop()` appelée automatiquement        |
| Entrée / sortie         | `cin` / `cout`       | `digitalRead`, `digitalWrite`, `Serial` |
| Bibliothèques           | Standard C++ / STL   | Arduino.h, Wire.h, Servo.h, etc.        |
| Gestion du temps        | `sleep()` / `chrono` | `delay(ms)`                             |
| Retour de fonction main | `return 0;`          | Non nécessaire                          |

---
[> voir Particularités d’un programme C++ sous Arduino](10_particularites_cpp_sous_arduino.md)


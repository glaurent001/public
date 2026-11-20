(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Chapitre 6 : Programmation orientée objet

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chapitre 6 : Programmation orientée objet](#chapitre-6--programmation-orientée-objet)
  - [1. Déclaration d’une classe simple](#1-déclaration-dune-classe-simple)
  - [2. Constructeurs et destructeurs](#2-constructeurs-et-destructeurs)
  - [3. Encapsulation et accès aux attributs](#3-encapsulation-et-accès-aux-attributs)
  - [4. Héritage](#4-héritage)
  - [5. Polymorphisme](#5-polymorphisme)
  - [6. Comparaison Python vs C++](#6-comparaison-python-vs-c)

> 📌 **Points clés :**
> 
> * La POO est plus **stricte** en C++ (visibilité, constructeurs, destructeurs).
> * Le polymorphisme demande une **déclaration explicite** (`virtual`).
> * La syntaxe est plus lourde mais permet un **contrôle fin** des objets et de la mémoire.

## 1. Déclaration d’une classe simple

En **Python**, on définit une classe avec `class`, et on utilise `__init__` comme constructeur.
En **C++**, on déclare la classe avec ses attributs et méthodes, et on précise les niveaux d’accès (`public`, `private`, `protected`).

```python
# Python
class Personne:
    def __init__(self, nom, age):
        self.nom = nom
        self.age = age

    def bonjour(self):
        print("Bonjour, je m'appelle", self.nom)

p = Personne("Alice", 20)
p.bonjour()
```

```cpp
// C++
#include <iostream>
#include <string>
using namespace std;

class Personne {
private:
    string nom;
    int age;

public:
    // Constructeur
    Personne(string n, int a) {
        nom = n;
        age = a;
    }

    // Méthode
    void bonjour() {
        cout << "Bonjour, je m'appelle " << nom << endl;
    }
};

int main() {
    Personne p("Alice", 20);
    p.bonjour();
    return 0;
}
```

⚠️ Différences notables :

* **Python** : tout est public par défaut.
* **C++** : distinction stricte entre `private`, `public`, `protected`.
* Le constructeur porte le nom de la classe.


## 2. Constructeurs et destructeurs

En **Python**, on a `__init__`, et rarement besoin de destructeur (`__del__`).
En **C++**, on a :

* le **constructeur** (initialise l’objet),
* le **destructeur** (libère la mémoire quand l’objet est détruit).

```cpp
// C++
#include <iostream>
using namespace std;

class Exemple {
public:
    Exemple() {
        cout << "Constructeur appelé" << endl;
    }
    ~Exemple() {
        cout << "Destructeur appelé" << endl;
    }
};

int main() {
    Exemple e;   // constructeur exécuté
}               // destructeur exécuté automatiquement
```


## 3. Encapsulation et accès aux attributs

En **Python**, on accède directement aux attributs (`p.nom`).
En **C++**, on utilise souvent des **getters** et **setters** pour respecter l’encapsulation.

```cpp
class Personne {
private:
    string nom;

public:
    Personne(string n) : nom(n) {}

    string getNom() {
        return nom;
    }

    void setNom(string n) {
        nom = n;
    }
};
```


## 4. Héritage

L’héritage fonctionne dans les deux langages, mais la syntaxe diffère.

```python
# Python
class Animal:
    def parler(self):
        print("Je suis un animal")

class Chien(Animal):
    def parler(self):
        print("Wouf !")

c = Chien()
c.parler()
```

```cpp
// C++
#include <iostream>
using namespace std;

class Animal {
public:
    void parler() {
        cout << "Je suis un animal" << endl;
    }
};

class Chien : public Animal {
public:
    void parler() {
        cout << "Wouf !" << endl;
    }
};

int main() {
    Chien c;
    c.parler();
    return 0;
}
```

⚠️ En C++, il faut préciser `: public` (ou `private` / `protected`) lors de l’héritage.


## 5. Polymorphisme

En **Python**, les méthodes sont virtuelles par défaut (on peut les redéfinir librement).
En **C++**, il faut utiliser le mot-clé `virtual` pour permettre le polymorphisme dynamique.

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void parler() {  // virtual pour permettre la redéfinition
        cout << "Je suis un animal" << endl;
    }
};

class Chien : public Animal {
public:
    void parler() override { // override pour plus de clarté
        cout << "Wouf !" << endl;
    }
};

int main() {
    Animal* a = new Chien();
    a->parler();  // Appelle "Wouf !" grâce au virtual
    delete a;
    return 0;
}
```


## 6. Comparaison Python vs C++

| Concept         | Python              | C++                                   |
| --------------- | ------------------- | ------------------------------------- |
| Classe          | `class` simple      | `class` avec `public`/`private`       |
| Constructeur    | `__init__`          | Fonction portant le nom de la classe  |
| Destructeur     | Rare (`__del__`)    | Automatique (`~NomClasse`)            |
| Accès attributs | Direct (`p.nom`)    | Contrôlé (`getNom()`, `setNom()`)     |
| Héritage        | `class Fille(Mere)` | `class Fille : public Mere`           |
| Polymorphisme   | Automatique         | Nécessite `virtual` et pointeurs/réfs |



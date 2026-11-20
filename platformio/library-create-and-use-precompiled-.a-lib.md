# PlatformIO : Créer et distribuer une bibliothèque précompilée pour ESP

> * Auteur : Gwénaël LAURENT
> * Date : 01/02/2022

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


- [PlatformIO : Créer et distribuer une bibliothèque précompilée pour ESP](#platformio--créer-et-distribuer-une-bibliothèque-précompilée-pour-esp)
- [1. Création de la bibliothèque](#1-création-de-la-bibliothèque)
  - [1.1 Création du projet](#11-création-du-projet)
  - [1.2 Compilation](#12-compilation)
  - [1.3 Préparation de la bibliothèque à distribuer](#13-préparation-de-la-bibliothèque-à-distribuer)
- [2. Utilisation de la bibliothèque précompilée](#2-utilisation-de-la-bibliothèque-précompilée)
  - [2.1 Création d'un projet](#21-création-dun-projet)
  - [2.2 Copier la bibliothèque précompilée](#22-copier-la-bibliothèque-précompilée)
  - [2.3 Ajouter une inclusion](#23-ajouter-une-inclusion)

# 1. Création de la bibliothèque
## 1.1 Création du projet
> La bibliothèque créée ici est une classe C++, d'où les extensions .hpp et .cpp pour les fichiers de la classe.

Créez un nouveau projet PlatformIO pour ESP8266 :
* Board : **```NodeMCU 1.0 (ESP-12E Module)```**
* Framework : **```Arduino```**

Création d'une classe dans le dossier ./lib du projet en respectant l'arborescence préconisée (le nom du sous-dossier de la lib doit être identique au nom de la classe et des fichiers .h et .cpp entre autre).\
Ici c'est une classe de test **```Personne```**
```
|--lib
|  |--Personne
|  |  |--docs
|  |     |- readme.md
|  |  |--examples
|  |     |- test.cpp
|  |  |--src
|  |     |- Personne.cpp
|  |     |- Personne.hpp
|- platformio.ini
|--src
   |- main.c
```

Contenu de ``` Personne.hpp``` :
```cpp
#ifndef Personne_h
#define Personne_h

#include <Arduino.h>

class Personne
{

private:
    String nom = "Gwénaël";

public:
    Personne();
    ~Personne();
    String LireNom();
};

#endif
```

Contenu de ``` Personne.cpp``` :
```cpp
#include "Personne.hpp"

Personne::Personne()
{
}
Personne::~Personne()
{
}
String Personne::LireNom()
{
    return nom;
}
```

Le fichier ```./docs/readme.md``` contient la documentation sur l'utilisation de la classe. Préférez le format [markdown](../vscode/vscode-markdown.md) :
```md
# Bibliothèque de test "Personne"

* Auteur : Gwénaël LAURENT

Pour illustrer la création et la distribution de bibliothèque précompilée ...
```

Les fichiers dans ```./examples``` sont des fichiers d'exmple d'utilisation de la bibliothèque.

Utilisation de la classe dans ```main.cpp```
```cpp
#include <Arduino.h>
#include "Personne.hpp"

// Création d'un objet de la classe
Personne objPers;

void setup() {
  Serial.begin(9600);
}

void loop() {
  String msg = "Bonjour " + objPers.LireNom();
  Serial.println(msg);
  delay(1000);
}
```

## 1.2 Compilation
**Compilez et uploader** le programme sur un ESP8266. Testez avec le moniteur série.

Dans le dossier ./pio/build/nodemcuv2/lib93d/ vous trouverez le fichier **libPersonne.a** : **c'est le fichier précompilé** de la bibliothèque.

> Le fichier précompilé contient le code précompilé des 2 fichiers Personne.hpp et Personne.cpp

## 1.3 Préparation de la bibliothèque à distribuer
Pour distribuer la bibliothèque il faut fournir **le dossier ./lib/Personne** :
* mais il faut supprimer le fichier Personne.cpp
* et le remplacer par le fichier **libPersonne.a**
* et ajouter le fichier manifest de la bibliothèque **library.json** directement sous la racine du dossier /lib/Personne

**Ce qui donne l'arborescence suivante à distribuer :**
```
|--Personne
|  |--docs
|     |- readme.md
|  |--examples
|     |- test.cpp
|  |--src
|     |- libPersonne.a
|     |- Personne.hpp
|  |--library.json
```
> **Note** : le fichier Personne.hpp ne sert qu'a donner des indications sur l'utilisation de la bibliothèque (car il est intégré à la bibliothèque précompilée libPersonne.a) Vous pouvez donc simplifiez le fichier que vous distribuez, par exemple en retirant les méthodes privées, etc ...

Contenu du fichier manifest de la bibliothèque **library.json**
```json
{
    "name": "Personne",
    "version": "0.0.1",
    "authors": {
        "name": "Gwenael LAURENT",
        "email": "me@john-smith.com",
        "url": "https://gitlab.com/gwenael.laurent/public"
    },
    "build": {
        "flags": [
            "-L src",
            "-llibPersonne.a"
        ]
    }
}
```
La seule partie obligatoire de ce fichier est la **clé "build" > "flags"**
* "-L src" : Ajoute le dossier *src* aux dossiers de recherche des bibliothèques.
* "-llibPersonne.a" : Ajoute la bibliothèque *libPersonne* pendant le linkage (attention, il y a bien 2 lettres "l" à suivre dans "-llibPersonne.a")

Documentation :
* [sur le fichier manifest de bibliothèque library.json](https://docs.platformio.org/en/latest/librarymanager/config.html)
* [sur les build_flags](https://docs.platformio.org/en/latest/projectconf/section_env_build.html#projectconf-build-flags)

# 2. Utilisation de la bibliothèque précompilée
## 2.1 Création d'un projet
Créez un nouveau projet pour utiliser la bibliothèque précompilée.

> **Les bibliothèques précompilée ne peuvent être utilisées que pour les mêmes types d'ESP (même "board", même "Framework" dans les projets PlatformIO)**

## 2.2 Copier la bibliothèque précompilée
Copiez le dossier contenant la bibliothèque précompilée dans le dossier ./lib:
```
|--Personne
|  |--docs
|     |- readme.md
|  |--examples
|     |- test.cpp
|  |--src
|     |- libPersonne.a
|     |- Personne.hpp
|  |--library.json
```

## 2.3 Ajouter une inclusion
Utilisation de la bibliothèque précompilée dans main.cpp :
```cpp
#include <Arduino.h>
#include <Personne.hpp>

// Création d'un objet de la classe
Personne objPers;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  String msg = "Bonjour " + objPers.LireNom();
  Serial.println(msg);
  delay(1000);
}
```
> **Ne pas oublier d'utiliser les ```<``` et ```>``` dans le ```#include <Personne.hpp>``` car c'est une bibliothèque précompilée !**

**Compilez et uploader** le programme sur un ESP8266. Testez avec le moniteur série.

Pendant le linkage, vous verrez apparaitre :

```shell
Scanning dependencies...
Dependency Graph
|-- <Personne> 0.0.1
Building in release mode
```
# VScode : Création et distribution d'une bibliothèque C++ statique

> * Auteur : Gwénaël LAURENT
> * Date : 02/02/2022

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [VScode : Création et distribution d'une bibliothèque C++ statique](#vscode--création-et-distribution-dune-bibliothèque-c-statique)
- [1. Pré-requis](#1-pré-requis)
- [2. Création de la bibliothèque statique](#2-création-de-la-bibliothèque-statique)
  - [2.1 Création d'un projet](#21-création-dun-projet)
  - [2.2 Création de la bibliothèque](#22-création-de-la-bibliothèque)
  - [2.3 Préparation de la bibliothèque à distribuer](#23-préparation-de-la-bibliothèque-à-distribuer)
  - [2.4 Remarques sur les fichiers inclus dans la bibliothèque](#24-remarques-sur-les-fichiers-inclus-dans-la-bibliothèque)
- [3. Utilisation de la bibliothèque statique](#3-utilisation-de-la-bibliothèque-statique)
- [4. Docs pour la création des bibliothèques C++](#4-docs-pour-la-création-des-bibliothèques-c)
- [5. Docs sur le makefile C++](#5-docs-sur-le-makefile-c)
- [6. Modification de l'extension IBgenerator pour Windows](#6-modification-de-lextension-ibgenerator-pour-windows)
  - [Modification du Makefile de IBgenerator version Windows](#modification-du-makefile-de-ibgenerator-version-windows)
  - [Modification du tasks.json de IBgenerator version Windows](#modification-du-tasksjson-de-ibgenerator-version-windows)

# 1. Pré-requis
Ces informations concernent la création d'un bibliothèque C++ statique dans VScode, à l'aide de MinGW et de l'extension IBGenerator (ProfesseurIssou). [cf configuration de VScode ici](vscode-cpp-mingw64.md#3-installation-des-extensions-dans-vscode).

> **Avant de demander à Alix de faire des changements** dans l'extension, créez le projet avec IBgenerator et remplacez ensuite le conteneu des 2 fichiers ./Makefile et ./.vscode/tasks.json avec le code fourni en bas du document

# 2. Création de la bibliothèque statique
## 2.1 Création d'un projet
1. Créez un projet C++ avec IBgenerator
2. Créez la ou les classes qui doivent être inclues dans la bibliothèque finale
3. Testez le fonctionnement des classes

## 2.2 Création de la bibliothèque
1. Donnez un nom à votre bibliothèque
   * Editez le **./Makefile** du projet
   * Modifiez la valeur de la variable **SLIB_NAME**. Par exemple :
        ```makefile
        SLIB_NAME := Personne
        ```
1. Affichez la liste des tâches disponible : **Ctrl+Alt+T**
2. Sélectionnez la tâche "**Create static Library**"

La bibliothèque est disponible dans le dossier ./lib :**```libPersonne.a```**

## 2.3 Préparation de la bibliothèque à distribuer
Pour distribuer la bibliothèque il faut fournir :
* le fichier libPersonne.a (c'est la lib statique précompilée)
* les fichiers header des classes inclues dans la lib

## 2.4 Remarques sur les fichiers inclus dans la bibliothèque
* Tous les fichiers .cpp du dossier ./src (sauf main.cpp) sont inclus dans la lib, donc tous les .cpp des classes ainsi que leur .hpp associé.
* A l'utilisation de la lib, les .hpp des classes doivent être fournis avec la lib .a (pour l'intellisense et la recherche des erreurs dans VScode). 
  * MAIS c'est la version inclue dans la lib qui est linkée dans l'exécutable final. 
  * DONC les changements dans les .hpp des classes n'ont aucun effet
  * ET AUSSI : on peut distribuer des versions des .hpp sans les méthodes privées sans aucun problème
* Les fichiers .h ne sont pas inclus (donc on peut y stocker des #define etc)


# 3. Utilisation de la bibliothèque statique
1. Créez un nouveau projet C++ avec IBgenerator
2. Copiez les fichiers header (.hpp et éventuellement .h) dans ./include
3. Copiez la bibliothèque libPersonne.a dans ./lib
4. Ajouter la bibliothèque au linkage du projet :
   * Editez le **./Makefile** du projet
   * Modifiez la valeur de la variable **LIBRARIES**. Par exemple :
        ```makefile
        LIBRARIES	:= -lPersonne
        ```

        > Remarque : le nom de la bibliothèque est préfixé par "-l" et ne commence pas par "lib" contrairement au nom du fichier "libPersonne.a"

5. Build & run



# 4. Docs pour la création des bibliothèques C++

* [Create and use static and shared C++ libraries](https://www.iram.fr/~roche/code/c++/AddNumbers.html)
* [Creating static library and linking using a Makefile](https://stackoverflow.com/questions/31421616/c-creating-static-library-and-linking-using-a-makefile/31421842)
* [Building a Static Library with GNU Make](https://www.oreilly.com/library/view/c-cookbook/0596007612/ch01s17.html)




# 5. Docs sur le makefile C++

* [GNU make](http://www.gnu.org/software/make/manual/make.html)
* [Introduction aux Makefiles](https://sites.uclouvain.be/SystInfo/notes/Outils/make.html#introduction-aux-makefiles)
* [Introduction à Makefile](https://gl.developpez.com/tutoriel/outil/makefile/)
* [Compilation, édition de liens, makefile](https://leria-info.univ-angers.fr/~jeanmichel.richer/ens_inra_crs1_compile.php)

# 6. Modification de l'extension IBgenerator pour Windows
## Modification du Makefile de IBgenerator version Windows

Toutes les modifications sont à la fin du  fichier ./Makefile. Ce qui donne le fichier complet suivant :

```makefile
CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

# nom des bibliothèques à linker au projet (préfixées par -l)
LIBRARIES	:= 
EXECUTABLE	:= main.exe

all: $(BIN)/$(EXECUTABLE)

run: clean all
	cls
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
#CMD
	-del $(BIN) /F /Q
#POWERSHELL
#	-del $(BIN)/* -Force

######### pour créer une lib statique ############
# nom de la lib statique à créer
SLIB_NAME := dummy
# dossier des fichiers .o
SLIB_OBJ	:= obj
# sélectionner tous les fichiers .cpp du dossier src
SLIB_CPPFILES:= $(wildcard $(SRC)/*.cpp)
# exclure main.cpp
SLIB_CPPFILES := $(filter-out $(SRC)/main.cpp, $(SLIB_CPPFILES))
# créer la liste des noms de fichier qui servira à la création des .o
# substring pour retirer du nom des fichiers le dossier et l'extension
SLIB_OBJFILES := $(subst $(SRC)/,$(SLIB_OBJ)/,$(subst .cpp,.o,$(SLIB_CPPFILES)))

# target du makefile pour créer une lib statique
static-lib: clean_obj $(SLIB_OBJFILES)
#	-echo $(SLIB_CPPFILES)
#	-echo $(SLIB_OBJFILES)
	ar rcs $(LIB)/lib$(SLIB_NAME).a $(SLIB_OBJFILES)

# règles génériques pour créer les fichiers .o
$(SLIB_OBJ)/%.o: $(SRC)/%.cpp
#	-echo $<
#	-echo $@
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c $< -o $@

# création et nettoyage du dossier des .o
clean_obj : 
	-if not exist "$(SLIB_OBJ)" mkdir $(SLIB_OBJ)
	-del $(SLIB_OBJ) /F /Q
	-del $(LIB) /F /Q
```

## Modification du tasks.json de IBgenerator version Windows
Il faut juste ajouter la tâche "Create Static Library" dans le fichier ./.vscode/tasks.json. Ce qui donne le fichier complet suivant :

```json
{
	"version": "2.0.0",
	"tasks": [
		{
			"label": "Build C++ project",
			"type": "shell",
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"command": "make",
			//"command": "mingw32-make",
		},
		{
			"label": "Build & run C++ project",
			"type": "shell",
			"group": {
				"kind": "test",
				"isDefault": true
			},
			"command": "make",
			//"command": "mingw32-make",
			"args": [
				"run"
			]
		},
		{
			"label": "Create Static Library",
			"type": "shell",
			"group": "build",
			"command": "make",
			//"command": "mingw32-make",
			"args": [
				"static-lib"
			]
		}
	]
}
```

Lancement de la tâche avec **Ctrl+Alt+T** > Sélectionner "Create Static Library"
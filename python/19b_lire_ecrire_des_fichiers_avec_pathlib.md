(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 19b : Lire et écrire des fichiers avec le module `pathlib`
> * Auteur : Gwénaël LAURENT
> * Date : 05/10/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 19b : Lire et écrire des fichiers avec le module `pathlib`](#chap-19b--lire-et-écrire-des-fichiers-avec-le-module-pathlib)
- [1. Introduction](#1-introduction)
- [2. Localiser un fichier](#2-localiser-un-fichier)
- [3. Les bases de la gestion des fichiers](#3-les-bases-de-la-gestion-des-fichiers)
  - [3.1. Ouvrir un fichier avec `Path.open()`](#31-ouvrir-un-fichier-avec-pathopen)
  - [3.2. Fermer un fichier avec `close()`](#32-fermer-un-fichier-avec-close)
  - [3.3. Utilisation de `with` à la place de `close()`](#33-utilisation-de-with-à-la-place-de-close)
- [4. Les fichiers texte](#4-les-fichiers-texte)
  - [4.1. Lecture des fichiers texte](#41-lecture-des-fichiers-texte)
    - [4.1.1. Lire tout le contenu du fichier avec `read()` ou `read_text()`](#411-lire-tout-le-contenu-du-fichier-avec-read-ou-read_text)
    - [4.1.2. Lire ligne par ligne avec `readline()`](#412-lire-ligne-par-ligne-avec-readline)
    - [4.1.3. Lire un certain nombre de caractères](#413-lire-un-certain-nombre-de-caractères)
  - [4.2. Écriture dans les fichiers texte](#42-écriture-dans-les-fichiers-texte)
    - [4.2.1. Écriture avec `write()` ou `write_text()`](#421-écriture-avec-write-ou-write_text)
    - [4.2.2. Ajout avec `write()`](#422-ajout-avec-write)
- [5. Les fichiers binaires](#5-les-fichiers-binaires)
  - [5.1. Lecture d’un fichier binaire avec `read()` ou `read_bytes()`](#51-lecture-dun-fichier-binaire-avec-read-ou-read_bytes)
  - [5.2. Écriture dans un fichier binaire avec `write()` ou `write_bytes()`](#52-écriture-dans-un-fichier-binaire-avec-write-ou-write_bytes)
  - [5.3. Ajout dans un fichier binaire avec `write()`](#53-ajout-dans-un-fichier-binaire-avec-write)


# 1. Introduction
La gestion des fichiers est une compétence essentielle en programmation, car elle permet de lire et écrire des données de manière persistante.

Python supporte plusieurs types de fichiers, mais nous allons nous concentrer ici sur les **fichiers texte** (.txt, .log, .conf, ...) et les **fichiers binaires** (qui ne contiennent pas que des caractères).

<br>

# 2. Localiser un fichier
Pour localiser les fichiers, il faut utiliser la classe `pathlib.Path`

```py
from pathlib import Path
```

Plus d'informations dans l'article [Accéder au système de fichiers avec Python](19a_acceder_au_systeme_de_fichiers.md)

<br>

# 3. Les bases de la gestion des fichiers
## 3.1. Ouvrir un fichier avec `Path.open()`
La première étape pour interagir avec un fichier est de l'ouvrir. Pour cela, on utilise la fonction `open()`, qui prend 3 arguments principaux : 
* **Nom du fichier**  : Le chemin vers le fichier (relatif ou absolu).
 
* **Mode d'ouverture**  : Indique l'action à effectuer sur le fichier (lecture, écriture, etc.).

* **Encodage** : Spécifie l'encodage des caractères à utiliser s'il s'agit d'un fichier texte (cet argument n'est pas utilisé s'il s'agit d'un fichier binaire)

Les modes d'ouverture les plus courants sont :
 
- `'r'` : Lecture seule (read). Le fichier doit exister.
- `'w'` : Écriture (write). Si le fichier existe, il est écrasé ; sinon, un nouveau fichier est créé.
- `'a'` : Ajout (append). Écrit à la fin du fichier sans effacer son contenu.
- `'b'` : Mode binaire. Utilisé pour ouvrir des fichiers non texte (images, vidéos, etc.).

La méthode open() retourne un "**flux de fichier**" ("File Stream" ou "Object File") qui **permet d'accéder** au fichier sur le disque, mais pas encore à son contenu (ça se fera avec les méthodes read() et write()).

<!-- 
Pour du texte : open() renvoie un type [io.TextIOWrapper](https://docs.python.org/fr/3.11/library/io.html#io.TextIOWrapper) qui dérive de [io.TextIOBase](https://docs.python.org/fr/3.11/library/io.html#io.TextIOBase)

Pour un fichier binaire : open() renvoie un type io.[BufferedReader](https://docs.python.org/fr/3.11/library/io.html#io.BufferedReader)  ou [io.BufferedWriter](https://docs.python.org/fr/3.11/library/io.html#io.BufferedWriter) qui dérivent de [io.BufferedIOBase](https://docs.python.org/fr/3.11/library/io.html#io.BufferedIOBase) qui dérive de [io.IOBase](https://docs.python.org/fr/3.11/library/io.html#io.IOBase)

 -->



**Exemples :** 

* Ouvrir un fichier texte en lecture seule :
  ```python
  from pathlib import Path

  fichier = Path("monfichier.txt")
  fs = fichier.open("r", encoding="utf-8")
  ```
* Ouvrir un fichier binaire en lecture seule :
  ```python
  from pathlib import Path
   
  fichier = Path("monfichier.jpg")
  fs = fichier.open("rb")
  ```

## 3.2. Fermer un fichier avec `close()`
Il est important de fermer un fichier après l'avoir utilisé pour libérer les ressources. On utilise la méthode `close()` pour cela.

**Exemple :** 

```python
fs.close()
```

## 3.3. Utilisation de `with` à la place de `close()`
Une bonne pratique est d’utiliser le mot-clé `with` pour ouvrir un fichier. Cela garantit que le fichier sera automatiquement fermé, même en cas d'erreur.

**Exemple :** 

```python
from pathlib import Path

fichier = Path("monfichier.txt")
with fichier.open("r", encoding="utf-8") as fs:
    ...
# En sortant du bloc with, le fichier est automatiquement fermé
```

**Exemple complet :** avec vérification de l'existence du fichier

```python
from pathlib import Path

fichier = Path("monfichier.txt")
if fichier.exists():
    with fichier.open("r", encoding="utf-8") as fs:
        ...
else:
    print(f"Le fichier {fichier} n'existe pas")
```

<br>

# 4. Les fichiers texte
## 4.1. Lecture des fichiers texte
### 4.1.1. Lire tout le contenu du fichier avec `read()` ou `read_text()`
Il s'agit ici de **lire tout** le contenu du fichier texte **en une seule étape**.

> **ATTENTION** : Ces méthodes ne conviennent pas pour les gros fichiers car ça surcharge trop la RAM.

* Avec with et un flux de fichier, on utilise la méthode `read()` :

  Il faut ouvrir le fichier en **mode 'r'** (read).

  ```python
  from pathlib import Path

  fichier = Path("monfichier.txt")
  with fichier.open("r", encoding="utf-8") as fs:
      contenu = fs.read()
      print(contenu)
  ```

* Autre possibilité en utilisant directement l'objet path, on utilise la méthode `read_text()` :
  ```python
  from pathlib import Path

  fichier = Path("monfichier.txt")
  contenu = fichier.read_text(encoding="utf-8")
  print(contenu)
  ```

### 4.1.2. Lire ligne par ligne avec `readline()`
Pour lire un fichier ligne par ligne, on peut utiliser la méthode `readline()` ou itérer directement sur le flux de fichier.

> **Remarque** : Ces méthodes sont adaptées aussi bien aux petits fichiers comme aux fichiers très volumineux.

* Exemple avec `readline()` :

  ```python
  from pathlib import Path

  fichier = Path("monfichier.txt")
  with fichier.open("r", encoding="utf-8") as fs:
      ligne = fs.readline()
      while ligne:
          print(ligne, end="")  # `end=''` pour éviter les lignes vides supplémentaires
          ligne = fs.readline()
  ```

  **Note** : le `end=''` dans le print permet d'éviter d'ajouter des retour-chariots supplémentaires (`\n`).

* Exemple avec une boucle `for` :

  ```python
  from pathlib import Path

  fichier = Path("monfichier.txt")
  with fichier.open("r", encoding="utf-8") as fs:
      for ligne in fs:
          print(ligne, end="")
  ```

### 4.1.3. Lire un certain nombre de caractères
 On peut également spécifier un nombre de caractères à lire en passant un argument à la méthode `read()`.
 
 Exemple : Lire par paquet de 5 caractères

```python
from pathlib import Path

fichier = Path("monfichier.txt")
with fichier.open("r", encoding="utf-8") as fs:
    contenu = fs.read(5)
    while contenu:
        print(contenu, end="")
        contenu = fs.read(5)
```


## 4.2. Écriture dans les fichiers texte
### 4.2.1. Écriture avec `write()` ou `write_text()`
Il s'agit de **remplacer tout le contenu** du fichier par un nouveau texte.

Si le fichier n'existe pas, Python le crée automatiquement.


* Avec with et un flux de fichier, on utilise la méthode `write()` :

  Il faut ouvrir le fichier en **mode 'w'** (write).\
  La méthode `write()` permet d'écrire dans un fichier.

  ```py
  from pathlib import Path

  fichier = Path("monfichier.txt")
  with fichier.open("w", encoding="utf-8") as fs:
      fs.write("Ceci est un test\nréussi.")
  ```

* Autre possibilité en utilisant directement l'objet path, on utilise la méthode `write_text()` :

  ```py
  from pathlib import Path

  fichier = Path("monfichier.txt")
  fichier.write_text("Ceci est un test\nréussi.", encoding="utf-8")
  ```

**Remarque** : Le texte est fourni en chaîne standard pour que les retours à la ligne soient bien interprétés (*ne pas utiliser de chaine raw*).

**Note** : les retours à la ligne `\n` sont automatiquement convertis pour correspondre au système d'exploitation. Sur Windows, les `\n` du texte sont convertis en `\r\n`.

### 4.2.2. Ajout avec `write()`
Il s'agit d'**écrire à la fin du fichier, sans effacer le contenu précédent**.

Si le fichier n'existe pas, Python le crée automatiquement.

Il faut ouvrir le fichier en **mode 'a'** (append).\
La méthode `write()` permet d'ajouter du contenu à la fin du fichier.

```py
from pathlib import Path

fichier = Path("monfichier.txt")
with fichier.open("a", encoding="utf-8") as fs:
    fs.write("\nNouvelle ligne ajoutée.")
```

**Remarque** : Le texte est fourni en chaîne standard pour que les retours à la ligne soient bien interprétés (*ne pas utiliser de chaine raw*).

**Note** : les retours à la ligne `\n` sont automatiquement convertis pour correspondre au système d'exploitation. Sur Windows, les `\n` du texte sont convertis en `\r\n`.

<br>

# 5. Les fichiers binaires
Les fichiers binaires sont utilisés pour des données autres que du texte, comme des images ou des fichiers audio. Lors de la manipulation de ces fichiers, il faut spécifier le mode binaire en ajoutant un **'b'** après le mode d'ouverture ('rb', 'wb', etc.).

En Python, les données binaires utilisent le type **`<class 'bytes'>`**. C'est un type immuable qui contient une séquence d'octets (valeurs comprises entre 0 et 255). [Doc sur python.org](https://docs.python.org/fr/3/library/stdtypes.html#bytes-objects)

> Les données de type bytes peuvent être créés avec une **chaîne littérale préfixée par b** (`b"..."`). Cette chaîne peut contenir des caractères ASCII (valeur de 0 à 127), les valeurs de 128 à 255 doivent être notées en hexa préfixées par `\x` (ex: \xc3\xa9)

## 5.1. Lecture d’un fichier binaire avec `read()` ou `read_bytes()`
Il s'agit ici de **lire tout** le contenu binaire du fichier **en une seule étape**.

* Avec with et un flux de fichier, on utilise la méthode `read()` :

  Il faut ouvrir le fichier en **mode 'rb'** (read bytes).

  ```py
  from pathlib import Path

  fichier = Path("my_binary_file")
  with fichier.open("rb") as fs:
      contenu = fs.read()
      print(contenu[:100], end="") # Affiche les 100 premiers octets
  ```

* Autre possibilité en utilisant directement l'objet path, on utilise la méthode `read_bytes()` :

  ```py
  from pathlib import Path

  fichier = Path("my_binary_file")
  contenu = fichier.read_bytes()
  ```

## 5.2. Écriture dans un fichier binaire avec `write()` ou `write_bytes()`
Il s'agit de **remplacer tout le contenu** du fichier par des nouvelles données binaires.

Si le fichier n'existe pas, Python le crée automatiquement.

* Avec with et un flux de fichier, on utilise la méthode `write()` :

  Il faut ouvrir le fichier en **mode 'wb'** (write bytes).

  ```py
  from pathlib import Path

  fichier = Path("my_binary_file")
  with fichier.open("wb") as fs:
      fs.write(b"Bonjour \x54\x6f\x74\x6f\x0d\x0a")
  ```

* Autre possibilité en utilisant directement l'objet path, on utilise la méthode `write_bytes()` :

  ```py
  from pathlib import Path

  fichier = Path("my_binary_file")
  fichier.write_bytes(b"Bonjour \x54\x6f\x74\x6f\x0d\x0a")
  ```

## 5.3. Ajout dans un fichier binaire avec `write()`
Il s'agit d'**écrire à la fin du fichier, sans effacer le contenu précédent**.

Si le fichier n'existe pas, Python le crée automatiquement.

Il faut ouvrir le fichier en **mode 'ab'** (append bytes).

  ```py
  from pathlib import Path

  fichier = Path("my_binary_file")
  with fichier.open("ab") as fs:
      fs.write(b"Bonjour \x54\x6f\x74\x6f\x0d\x0a")
  ```

(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 25 : Script python et arguments de la ligne de commande

> * Auteur : Gwénaël LAURENT
> * Date : 23/02/2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


- [Chap. 25 : Script python et arguments de la ligne de commande](#chap-25--script-python-et-arguments-de-la-ligne-de-commande)
- [1. Rendre un script Python exécutable dans la console](#1-rendre-un-script-python-exécutable-dans-la-console)
  - [1.1. Ajouter le shebang](#11-ajouter-le-shebang)
  - [1.2. Donner les permissions d’exécution](#12-donner-les-permissions-dexécution)
  - [1.3. Exécuter le script](#13-exécuter-le-script)
- [2. Gestion des arguments de la ligne de commande](#2-gestion-des-arguments-de-la-ligne-de-commande)
  - [2.1. Utilisation de `sys.argv` (basique)](#21-utilisation-de-sysargv-basique)
    - [2.1.1. Présentation](#211-présentation)
    - [2.1.2. Affichage de l'aide et validation des arguments](#212-affichage-de-laide-et-validation-des-arguments)
  - [2.2. Utilisation de `argparse` (avancé)](#22-utilisation-de-argparse-avancé)
    - [2.2.1. Présentation](#221-présentation)
    - [2.2.2. Utilisation des arguments positionnels](#222-utilisation-des-arguments-positionnels)
    - [2.2.3. Utilisation de commutateurs (flags) : les options nommées](#223-utilisation-de-commutateurs-flags--les-options-nommées)
- [3. Transformer un script Python en exécutable autonome](#3-transformer-un-script-python-en-exécutable-autonome)


# 1. Rendre un script Python exécutable dans la console

## 1.1. Ajouter le shebang
Le *shebang* permet de spécifier l'interpréteur Python utilisé pour exécuter le script. Placez cette ligne tout en haut de votre script :

```python
#!/usr/bin/env python3
```


## 1.2. Donner les permissions d’exécution
Sous Linux/Mac, après avoir enregistré le script (ex. `script.py`), il faut lui attribuer les droits d’exécution :

```bash
chmod +x script.py
```

## 1.3. Exécuter le script
- Sous Linux/Mac :
  ```bash
  ./script.py
  ```
- Sous Windows :
  ```cmd
  python script.py
  ```

Pour exécuter directement un script sans préciser `python`, placez-le dans un répertoire défini dans la variable d’environnement `PATH`.



# 2. Gestion des arguments de la ligne de commande

## 2.1. Utilisation de `sys.argv` (basique)
### 2.1.1. Présentation
Le module `sys` permet de récupérer les arguments passés au script :
- `sys.argv` est une liste contenant les arguments passés au script Python.
- `sys.argv[0]` est toujours le nom du script.
- `sys.argv[1:]` contient les arguments fournis par l’utilisateur.

```python
import sys

print(f"Nom du script : {sys.argv[0]}")
if len(sys.argv) > 1:
    print(f"Arguments : {sys.argv[1:]}")
```

Exécution :

```bash
python script.py arg1 arg2
```

Sortie :
```
Nom du script : script.py
Arguments : ['arg1', 'arg2']
```

### 2.1.2. Affichage de l'aide et validation des arguments
Avec `sys.argv`, on doit gérer l'affichage de l'aide et la validation du nombre d'arguments manuellement.

Voici un exemple qui affiche un message d’aide lorsque `-help` est utilisé et un autre message si le nombre d’arguments est incorrect.

```python
import sys

# Message d'aide
help_text = """Utilisation : python script.py arg1 arg2 arg3
Description : Ce script attend exactement 3 arguments.
Arguments :
  - arg1 : Premier argument (exemple : nom)
  - arg2 : Deuxième argument (exemple : age)
  - arg3 : Troisième argument (exemple : ville)
"""

# Vérifier si l'utilisateur demande de l'aide
if "-help" in sys.argv:
    print(help_text)
    sys.exit(0)  # Quitter proprement

# Vérifier le nombre d'arguments (sys.argv inclut le nom du script en premier)
if len(sys.argv) != 4:
    print("Erreur : Ce script nécessite exactement 3 arguments.\n")
    print(help_text)
    sys.exit(1)  # Quitter avec un code d'erreur

# Récupérer les arguments
arg1 = sys.argv[1]
arg2 = sys.argv[2]
arg3 = sys.argv[3]

print(f"Argument 1 : {arg1}")
print(f"Argument 2 : {arg2}")
print(f"Argument 3 : {arg3}")
```

**Note :** L'instruction `sys.exit(0)` génère la fin classique d'un programme exécutable qui s'exécute sans erreur. Terminer le programme par `sys.exit(1)` indique au système d'exploitation qu'une erreur est survenue pendant l'exécution du programme. [Documentation](https://docs.python.org/3/library/sys.html#sys.exit)

## 2.2. Utilisation de `argparse` (avancé)
### 2.2.1. Présentation
Le module `argparse` facilite la gestion des arguments avec descriptions et options.

Pourquoi `argparse` est préférable à `sys.argv` ?
* Génère automatiquement `--help`.  
* Gère les erreurs (nombre d’arguments, types incorrects, etc.).  
* Rend le code plus lisible et structuré.  


Documentation :

- [Documentation officielle argparse](https://docs.python.org/3/library/argparse.html)

- [Python Docs en français (non officiel](https://docs.python.org/fr/3/library/argparse.html)


### 2.2.2. Utilisation des arguments positionnels
```python
import argparse

# Création du parser
parser = argparse.ArgumentParser(
    description="Ce script attend exactement 3 arguments : un nom, un âge et une ville."
)

# Ajout des arguments positionnels
parser.add_argument("nom", type=str, help="Votre nom")
parser.add_argument("age", type=int, help="Votre âge")
parser.add_argument("ville", type=str, help="Votre ville")

# Analyse des arguments
args = parser.parse_args()

# Affichage des arguments fournis
print(f"Nom : {args.nom}")
print(f"Age : {args.age} ans")
print(f"Ville : {args.ville}")
```

Explication du script :
1. Création d’un parser `argparse.ArgumentParser`
   - Ajoute une description du script qui sera affichée avec `--help`.
2. Ajout des arguments positionnels (`add_argument()`)
   - `nom` : Une chaîne de caractères.
   - `age` : Un entier.
   - `ville` : Une chaîne de caractères.
3. Analyse des arguments (`parse_args()`)
   - `argparse` vérifie automatiquement la présence et le type des arguments.
   - Si le nombre d’arguments est incorrect, un message d'erreur s'affiche automatiquement.
4. Affichage des arguments
   - Si tout est correct, les valeurs sont affichées.



Exécutions possibles

**Avec 3 arguments valides :**
```bash
python script.py Alice 30 Paris
```
Sortie :
```
Nom : Alice
Âge : 30 ans
Ville : Paris
```

**Sans arguments ou avec un mauvais nombre :**
```bash
python script.py Alice 30
```
Sortie (automatique avec `argparse`) :
```
usage: script.py [-h] nom age ville
script.py: error: the following arguments are required: ville
```

**Avec `--help` :**
```bash
python script.py --help
```
Sortie :
```
usage: script.py [-h] nom age ville

Ce script attend exactement 3 arguments : un nom, un âge et une ville.

positional arguments:
  nom         Votre nom
  age         Votre âge
  ville       Votre ville

optional arguments:
  -h, --help  show this help message and exit
```


### 2.2.3. Utilisation de commutateurs (flags) : les options nommées

`argparse` permet d'utiliser des **commutateurs (flags)** pour identifier chaque argument. On va remplacer les arguments positionnels (`nom`, `age`, `ville`) par des arguments avec des options **nommées** :  

- `-n` (ou `--n`) pour le nom.
- `-a` (ou `--a`) pour l'age.
- `-v` (ou `--v`) pour la ville.

> L’ordre des arguments n’a plus d’importance tant qu'ils sont bien identifiés.

```python
import argparse

# Création du parser
parser = argparse.ArgumentParser(
    description="Ce script attend exactement 3 arguments : un nom, un âge et une ville."
)

# Arguments nommés avec des commutateurs
parser.add_argument("-n", "--n", metavar="NOM", type=str, required=True, help="Votre nom")
parser.add_argument("-a", "--a", metavar="AGE",type=int, required=True, help="Votre âge")
parser.add_argument("-v", "--v", metavar="VILLE",type=str, required=True, help="Votre ville")

# Analyse des arguments
args = parser.parse_args()

# Affichage des arguments fournis
print(f"Nom : {args.n}")
print(f"Age : {args.a} ans")
print(f"Ville : {args.v}")
```

> Par défaut, les options nommées sont facultatives quand on appelle le script. Elles peuvent cependant être rendues obligatoires en ajoutant  `required=True`

Exécutions possibles

**Avec 3 arguments valides :**
```bash
python script.py -n Alice -a 30 -v Paris
```
Sortie :
```
Nom : Alice
Age : 30 ans
Ville : Paris
```

**Sans arguments ou avec un mauvais nombre :**
```bash
python script.py -n Alice -a 30 
```
Sortie (automatique avec `argparse`) :
```
usage: test4.py [-h] -n NOM -a AGE -v VILLE
test4.py: error: the following arguments are required: -v/--v
```

**Avec `--help` :**
```bash
python script.py --help
```
Sortie :
```
usage: test4.py [-h] -n NOM -a AGE -v VILLE

Ce script attend exactement 3 arguments : un nom, un age et une ville.

options:
  -h, --help           show this help message and exit
  -n NOM, --n NOM      Votre nom
  -a AGE, --a AGE      Votre age
  -v VILLE, --v VILLE  Votre ville
```



# 3. Transformer un script Python en exécutable autonome
Si vous voulez créer un exécutable qui fonctionne sans Python installé, utilisez **PyInstaller** :

1. Installez PyInstaller :
   ```bash
   pip install pyinstaller
   ```
2. Générez l'exécutable :
   ```bash
   pyinstaller --onefile script.py
   ```
3. L’exécutable est généré dans `dist/script` sous Linux/Mac et `dist/script.exe` sous Windows.


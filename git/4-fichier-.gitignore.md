# GIT : Le fichier `.gitignore`

> * Auteur : Gwénaël LAURENT
> * Date : 20/09/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [GIT : Le fichier `.gitignore`](#git--le-fichier-gitignore)
- [1. Introduction](#1-introduction)
- [2. À quoi sert le fichier `.gitignore` ?](#2-à-quoi-sert-le-fichier-gitignore-)
- [3. Comment créer et utiliser un fichier `.gitignore` ?](#3-comment-créer-et-utiliser-un-fichier-gitignore-)
- [4. Exemples de règles dans un `.gitignore`](#4-exemples-de-règles-dans-un-gitignore)
  - [4.1. Ignorer un fichier spécifique](#41-ignorer-un-fichier-spécifique)
  - [4.2. Ignorer un dossier et tout son contenu](#42-ignorer-un-dossier-et-tout-son-contenu)
  - [4.3. Ignorer tous les fichiers d'un type particulier](#43-ignorer-tous-les-fichiers-dun-type-particulier)
  - [4.4. Ignorer un fichier ou un dossier généré automatiquement](#44-ignorer-un-fichier-ou-un-dossier-généré-automatiquement)
  - [4.5. Ignorer des fichiers de configuration d'IDE](#45-ignorer-des-fichiers-de-configuration-dide)
  - [4.6. Ne pas ignorer un fichier spécifique dans un dossier ignoré](#46-ne-pas-ignorer-un-fichier-spécifique-dans-un-dossier-ignoré)
  - [4.7. Ignorer tous les fichiers dans un dossier sauf un type spécifique](#47-ignorer-tous-les-fichiers-dans-un-dossier-sauf-un-type-spécifique)
- [5. Quelques bonnes pratiques](#5-quelques-bonnes-pratiques)
- [6. Que faire si un fichier est déjà suivi par Git mais doit être ignoré ?](#6-que-faire-si-un-fichier-est-déjà-suivi-par-git-mais-doit-être-ignoré-)


# 1. Introduction

Le fichier **Le fichier `.gitignore`**  est un élément clé dans un projet Git. Il permet de définir quels fichiers ou dossiers doivent être **exclus** du contrôle de version, c'est-à-dire qu'ils ne seront ni suivis ni ajoutés au dépôt Git.

# 2. À quoi sert le fichier `.gitignore` ?

Lors du développement, il existe de nombreux fichiers temporaires, logs, fichiers de configuration locaux ou fichiers générés automatiquement par des outils (compilateurs, éditeurs) qui ne sont pas pertinents pour tous les membres de l'équipe et n'ont pas besoin d'être partagés dans le dépôt. Le fichier `.gitignore` sert à **ignorer ces fichiers** .

Par exemple :
 
- Fichiers de **configuration** spécifiques à votre IDE (comme `.vscode/`, `.idea/` pour Visual Studio Code ou IntelliJ).
- Fichiers de **compilation** (comme les fichiers `.class` en Java ou `.pyc` en Python).
- Dossiers de **dépendances** (comme `node_modules/` pour les projets Node.js).
- Fichiers **sensibles** (comme les fichiers contenant des mots de passe ou des configurations locales).

# 3. Comment créer et utiliser un fichier `.gitignore` ?

1. Créez un fichier nommé `.gitignore`  à la racine de votre projet (ou dans n'importe quel sous-répertoire si vous voulez des règles spécifiques à certains dossiers).

2. Ajoutez dans ce fichier la liste des fichiers ou dossiers que vous souhaitez ignorer. Chaque règle correspond à un fichier ou dossier à ignorer.


# 4. Exemples de règles dans un `.gitignore`

Voici quelques exemples de contenu typique d'un fichier `.gitignore` :

## 4.1. Ignorer un fichier spécifique

```bash
secret.txt
```

Cela va ignorer le fichier nommé `secret.txt`.

## 4.2. Ignorer un dossier et tout son contenu

```bash
node_modules/
```

Cela va ignorer tout le dossier `node_modules/` et son contenu (très utile pour les projets Node.js, car ce dossier contient des milliers de fichiers installés via npm).

## 4.3. Ignorer tous les fichiers d'un type particulier

```bash
*.log
```

Cela va ignorer tous les fichiers ayant l'extension `.log` (par exemple `debug.log`, `error.log`).

## 4.4. Ignorer un fichier ou un dossier généré automatiquement

```bash
/build/
/dist/
```

Cela va ignorer les dossiers `build/` et `dist/`, souvent générés par des outils de compilation.

## 4.5. Ignorer des fichiers de configuration d'IDE

```bash
.vscode/
.idea/
```

Cela va ignorer les fichiers de configuration générés par Visual Studio Code ou IntelliJ.

## 4.6. Ne pas ignorer un fichier spécifique dans un dossier ignoré

Si vous ignorez un dossier entier mais souhaitez suivre un fichier spécifique dans ce dossier, vous pouvez le spécifier ainsi :

```bash
node_modules/
!node_modules/package.json
```

Cela va ignorer tout le dossier `node_modules/`, sauf le fichier `package.json`.

## 4.7. Ignorer tous les fichiers dans un dossier sauf un type spécifique

```bash
tmp/*
!tmp/*.txt
```

Cela va ignorer tout le contenu du dossier `tmp/`, sauf les fichiers `.txt`


# 5. Quelques bonnes pratiques
- **Généralisez vos règles**  : Par exemple, si vous utilisez plusieurs outils qui créent des fichiers journaux, il est plus pratique d'ignorer tous les fichiers `.log` plutôt que de lister chaque fichier un par un.
 
- **Partagez votre `.gitignore`**  : Le fichier `.gitignore` fait partie du projet. Il doit être versionné pour s'assurer que tous les développeurs du projet respectent les mêmes règles d'exclusion.
 
- **Utilisez des templates `.gitignore`**  : 
  - GitHub propose des templates `.gitignore` adaptés à différents langages et environnements (Java, Python, Node.js, etc.). Vous pouvez trouver ces templates ici : [GitHub Gitignore Templates](https://github.com/github/gitignore).
  - Le site [https://www.gitignore.io](https://www.gitignore.io) permet de générer votre fichier `.gitignore` en indiquant les systèmes d'exploitations, les langages de programmation, les framworks, ... que vous utilisez ... puis de cliquer sur "Create".


# 6. Que faire si un fichier est déjà suivi par Git mais doit être ignoré ?
Si vous avez déjà commité un fichier et que vous souhaitez l'ignorer dans le futur :
 
1. Ajoutez le fichier au `.gitignore`.

2. Supprimez-le du suivi tout en le conservant localement :

    ```bash
    git rm --cached fichier-a-ignorer
    ```

3. Ensuite, vous pouvez commiter cette suppression :

    ```bash
    git commit -m "Supprime le suivi du fichier fichier-a-ignorer"
    ```

Après cela, Git cessera de suivre ce fichier, mais il restera sur votre disque dur.

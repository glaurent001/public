# GIT : Gérer les commits locaux

> * Auteur : Gwénaël LAURENT
> * Date : 27/09/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [GIT : Gérer les commits locaux](#git--gérer-les-commits-locaux)
- [1. Voir les commits enregistrés localement](#1-voir-les-commits-enregistrés-localement)
- [2. Charger un commit dans le dossier de travail](#2-charger-un-commit-dans-le-dossier-de-travail)
  - [2.1. Regarder un commit (sans modifier l'historique)  : `git checkout`](#21-regarder-un-commit-sans-modifier-lhistorique---git-checkout)
  - [2.2. Revenir définitivement à un ancien commit (reset)  : `git reset`](#22-revenir-définitivement-à-un-ancien-commit-reset---git-reset)
- [3. Voir l'état des fichiers après avoir chargé un commit](#3-voir-létat-des-fichiers-après-avoir-chargé-un-commit)


# 1. Voir les commits enregistrés localement
La commande pour lister tous les commits est :

```bash
git log
```

Cela affichera l'historique des commits dans l'ordre chronologique inverse (du plus récent au plus ancien). 

Chaque commit est accompagné d'un identifiant unique (un hash, généralement les 7 premiers caractères suffisent), d'un message de commit, de l'auteur, de la date, et des modifications associées.

Exemple de sortie :

```sql
commit e1e9c2a
Author: Alice <alice@example.com>
Date:   Tue Sep 14 14:35:20 2024 +0200

    Correction des bugs sur la page d'accueil
```

Pour une version plus concise, on peut utiliser :


```bash
git log --oneline
```

Cela affiche chaque commit sous une seule ligne avec un identifiant abrégé et le message du commit :


```
e1e9c2a Correction des bugs sur la page d'accueil
c7f8a1b Ajout de la fonctionnalité de recherche
```

# 2. Charger un commit dans le dossier de travail
Pour charger un commit dans le dossier de travail, il existe deux approches principales selon ce que vous voulez faire :

## 2.1. Regarder un commit (sans modifier l'historique)  : `git checkout`

Si vous voulez **examiner**  un commit particulier (par exemple, revenir temporairement à un état antérieur), vous pouvez utiliser la commande `git checkout`. Cela place les fichiers dans l'état du commit choisi, mais sans modifier l'historique. Vous entrez dans un état appelé **"détaché" (detached HEAD)** , car vous ne travaillez plus sur une branche, mais sur un commit spécifique.

```bash
git checkout <identifiant_du_commit>
```

Exemple :

```bash
git checkout e1e9c2a
```

Dans cet état, vous pouvez voir ou tester votre projet tel qu'il était à ce moment précis, mais les nouveaux commits que vous faites ne seront pas attachés à la branche actuelle, sauf si vous créez une nouvelle branche à partir de ce commit.

**Pour revenir à l'état précédent** (votre branche actuelle) après avoir utilisé `checkout` :

```bash
git checkout <nom_de_la_branche>
```

Exemple :

```bash
git checkout master
```

## 2.2. Revenir définitivement à un ancien commit (reset)  : `git reset`

Si vous voulez **annuler des commits récents**  et revenir définitivement à un ancien commit, en réécrivant l'historique, vous pouvez utiliser `git reset`. Cela modifie l'historique des commits et replace la tête (HEAD) sur un commit antérieur.

```bash
git reset --hard <identifiant_du_commit>
```

Exemple :

```bash
git reset --hard e1e9c2a
```

> ⚠️ Attention : Cette commande supprime les commits suivants et les modifications non sauvegardées seront également perdues.


---

# 3. Voir l'état des fichiers après avoir chargé un commit
Après avoir utilisé l'une des méthodes ci-dessus pour charger un commit, vous pouvez vérifier l'état de vos fichiers et voir les modifications avec :

```bash
git status
```


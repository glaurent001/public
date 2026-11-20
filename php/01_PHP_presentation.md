# Introduction à PHP

> * Auteur : Gwénaël LAURENT
> * Date : 28/04/2026

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


- [Introduction à PHP](#introduction-à-php)
- [1. Qu'est-ce que PHP ?](#1-quest-ce-que-php-)
- [2. Sites statiques vs sites dynamiques](#2-sites-statiques-vs-sites-dynamiques)
  - [2.1. Site statique](#21-site-statique)
  - [2.2. Site dynamique](#22-site-dynamique)
- [3. Le développement backend](#3-le-développement-backend)
- [4. Un langage interprété](#4-un-langage-interprété)
- [5. Code exécuté sur le serveur](#5-code-exécuté-sur-le-serveur)
- [6. L'extension de fichier `.php`](#6-lextension-de-fichier-php)
  - [6.1. Exemples de nommage courant](#61-exemples-de-nommage-courant)
  - [6.2. Fonctionnement côté serveur web](#62-fonctionnement-côté-serveur-web)
- [7. Résumé](#7-résumé)


# 1. Qu'est-ce que PHP ?

**PHP** (*PHP : Hypertext Preprocessor*) est un langage de programmation conçu pour le développement web. Il est aujourd'hui l'un des langages côté serveur les plus utilisés au monde, notamment grâce à des plateformes comme WordPress, Symfony ou Laravel.

---

# 2. Sites statiques vs sites dynamiques

## 2.1. Site statique

Un site statique est composé de fichiers HTML fixes, envoyés tels quels au navigateur. Le contenu ne change pas en fonction de l'utilisateur ou du contexte.

```
Navigateur  ──────GET /index.html──────▶  Serveur
            ◀─────index.html (fixe)──────
```

**Caractéristiques :**
- Contenu identique pour tous les visiteurs
- Pas d'interaction avec une base de données
- Rapide à servir, mais difficile à maintenir si le site est volumineux

## 2.2. Site dynamique

Un site dynamique génère son contenu **à la volée**, en fonction de paramètres (utilisateur connecté, données en base, heure, etc.).

```
Navigateur  ──────GET /profil.php──────▶  Serveur PHP
                                              │
                                         Exécution du script
                                              │
            ◀─────HTML généré────────────────┘
```

**Caractéristiques :**
- Contenu personnalisé selon le contexte
- Interaction possible avec des bases de données
- Formulaires, sessions, authentification, etc.

> PHP est un langage de choix pour créer des sites dynamiques.

---

# 3. Le développement backend

Le développement web se divise en deux grandes parties :

| Côté | Nom | Langages courants | Rôle |
|------|-----|-------------------|------|
| Navigateur | **Frontend** | HTML, CSS, JavaScript | Affichage, interactions côté utilisateur |
| Serveur | **Backend** | PHP, Python, Node.js, Java | Logique métier, accès aux données |

**PHP est un langage backend.** Il s'exécute côté serveur et produit du HTML qui est ensuite envoyé au navigateur. L'utilisateur ne voit jamais le code PHP, uniquement le résultat HTML généré.

---

# 4. Un langage interprété

PHP est un **langage interprété** : le code source n'est pas compilé en amont en code machine. À chaque requête, l'interpréteur PHP lit et exécute le fichier `.php` ligne par ligne.

```
Fichier .php  ──▶  Interpréteur PHP  ──▶  HTML généré  ──▶  Navigateur
```

**Avantages :**
- Pas d'étape de compilation → développement rapide
- Modifications immédiatement visibles sans recompilation

**Inconvénient principal :**
- Légèrement plus lent qu'un langage compilé (compensé par des systèmes de cache comme OPcache)

> À comparer avec C ou C++ qui nécessitent une compilation avant exécution.

---

# 5. Code exécuté sur le serveur

C'est un point fondamental : **le code PHP s'exécute sur le serveur, jamais dans le navigateur.**

**Illustration** : Considérons ce fichier `bonjour.php` hébergé sur un serveur :

```php
<?php
$heure = date("H");
if ($heure < 12) {
    echo "Bonjour !";
} else {
    echo "Bonsoir !";
}
?>
```

**Ce que le serveur fait :** il exécute le script, détermine l'heure, et renvoie uniquement `Bonjour !` ou `Bonsoir !`.

**Ce que le navigateur reçoit :** uniquement le HTML résultant, par exemple :

```html
Bonjour !
```

Le navigateur n'a aucune connaissance du code PHP. Cette séparation est importante pour la **sécurité** : la logique métier et les accès à la base de données restent côté serveur, hors de portée de l'utilisateur.

---

# 6. L'extension de fichier `.php`

Les fichiers PHP ont l'extension **`.php`**.

## 6.1. Exemples de nommage courant

| Fichier | Rôle typique |
|---------|-------------|
| `index.php` | Page d'accueil |
| `connexion.php` | Formulaire de connexion |
| `db_connect.php` | Connexion à la base de données |
| `header.php` | Fragment HTML réutilisable (en-tête) |
| `api.php` | Point d'entrée d'une API |

## 6.2. Fonctionnement côté serveur web

Lorsqu'un navigateur demande un fichier `.php`, le serveur web (Apache, Nginx…) le transmet à l'interpréteur PHP avant de renvoyer le résultat :

```
Requête GET /index.php
        │
        ▼
   Serveur web (Apache/Nginx)
        │  reconnaît l'extension .php
        ▼
   Interpréteur PHP
        │  exécute le script
        ▼
   Réponse HTML  ──▶  Navigateur
```

> Un fichier `.html` serait renvoyé directement sans interprétation PHP.

---

# 7. Résumé

| Notion | Définition |
|--------|-----------|
| **PHP** | Langage de programmation pour le web, côté serveur |
| **Site dynamique** | Contenu généré à la volée selon le contexte |
| **Backend** | Partie serveur d'une application web |
| **Langage interprété** | Exécuté ligne par ligne sans compilation préalable |
| **Exécution serveur** | Le code PHP tourne sur le serveur, l'utilisateur ne le voit pas |
| **Extension `.php`** | Format des fichiers contenant du code PHP |



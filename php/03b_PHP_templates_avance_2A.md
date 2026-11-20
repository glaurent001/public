# PHP - Moteur de templates avec `ob_start` / `ob_get_clean`

> * Auteur : Gwénaël LAURENT
> * Date : 28/04/2026
> * **Prérequis :** Ce document fait suite au cours de 1ère année sur la séparation header/footer avec `require`. On suppose que vous maîtrisez `require`, les variables, les tableaux et les bases de PDO.

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


- [PHP - Moteur de templates avec `ob_start` / `ob_get_clean`](#php---moteur-de-templates-avec-ob_start--ob_get_clean)
- [1. Rappel : la limite de l'approche header/footer](#1-rappel--la-limite-de-lapproche-headerfooter)
- [2. Le buffer de sortie PHP](#2-le-buffer-de-sortie-php)
  - [2.1. Fonctions principales](#21-fonctions-principales)
  - [2.2. Principe illustré](#22-principe-illustré)
- [3. Architecture avec un layout unique](#3-architecture-avec-un-layout-unique)
  - [3.1. Structure du projet](#31-structure-du-projet)
- [4. Mise en œuvre](#4-mise-en-œuvre)
  - [4.1. `templates/layout.php` - Le squelette HTML complet](#41-templateslayoutphp---le-squelette-html-complet)
  - [4.2. Fonction helper `render()`](#42-fonction-helper-render)
  - [4.3. `views/home.php` - Vue de la page d'accueil](#43-viewshomephp---vue-de-la-page-daccueil)
  - [4.4. `views/produits.php` - Vue avec CSS spécifique](#44-viewsproduitsphp---vue-avec-css-spécifique)
  - [4.5. Points d'entrée - `public/index.php` et `public/produits.php`](#45-points-dentrée---publicindexphp-et-publicproduitsphp)
- [5. Passer des données depuis le contrôleur vers la vue](#5-passer-des-données-depuis-le-contrôleur-vers-la-vue)
- [6. Comparaison des deux approches](#6-comparaison-des-deux-approches)
- [7. Vers les frameworks : la même idée dans Twig](#7-vers-les-frameworks--la-même-idée-dans-twig)
- [8. Résumé](#8-résumé)


# 1. Rappel : la limite de l'approche header/footer

En 1ère année, la séparation reposait sur deux fragments inclus en début et fin de page :

```php
<?php
$pageTitle = "Accueil"; // Doit être défini AVANT le header
require 'templates/header.php';
?>
<!-- contenu -->
<?php require 'templates/footer.php'; ?>
```

Cette approche fonctionne, mais présente une contrainte importante : **le header est envoyé au navigateur immédiatement** lors du `require`. Cela implique que :

- Le `<title>` et les balises `<meta>` doivent être connus *avant* d'exécuter la logique de la page
- Il est impossible d'ajouter dynamiquement des feuilles CSS ou scripts JS spécifiques à une page *après* que le `<head>` a été envoyé
- Un `header()` HTTP (redirection, cookie…) après le premier `echo` provoque une erreur

---

# 2. Le buffer de sortie PHP

PHP dispose d'un mécanisme appelé **buffer de sortie** (*output buffer*) : au lieu d'envoyer immédiatement le HTML au navigateur, on peut demander à PHP de le **stocker en mémoire**, puis de le récupérer sous forme de chaîne pour le manipuler.

## 2.1. Fonctions principales

| Fonction | Rôle |
|----------|------|
| `ob_start()` | Démarre la capture du buffer de sortie |
| `ob_get_clean()` | Récupère le contenu capturé ET vide le buffer |
| `ob_get_contents()` | Récupère le contenu sans vider le buffer |
| `ob_end_clean()` | Vide et arrête la capture sans récupérer |
| `ob_flush()` | Envoie le buffer au navigateur immédiatement |

## 2.2. Principe illustré

```
Sans ob_start :
  echo "..." ──▶ Navigateur (immédiat, irrévocable)

Avec ob_start :
  echo "..." ──▶ Buffer (mémoire)
                    │
              ob_get_clean()
                    │
                    ▼
              $html = "..."  ──▶ Navigateur (quand on le décide)
```

---

# 3. Architecture avec un layout unique

L'idée est d'inverser le flux :

1. La **page de contenu** s'exécute entièrement en mémoire (buffer)
2. Elle définit ses métadonnées (`$pageTitle`, CSS additionnels, etc.)
3. Le **layout** est inclus en dernier et injecte le contenu capturé

## 3.1. Structure du projet

```
projet/
├── public/
│   ├── index.php           ← Point d'entrée : logique + appel au router
│   ├── produits.php
│   └── contact.php
├── templates/
│   └── layout.php          ← Squelette HTML complet (UN seul fichier)
├── views/
│   ├── home.php            ← Vue : contenu de la page d'accueil
│   ├── produits.php        ← Vue : contenu de la page produits
│   └── contact.php         ← Vue : contenu de la page contact
└── css/
    └── style.css
```

---

# 4. Mise en œuvre

## 4.1. `templates/layout.php` - Le squelette HTML complet

```php
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?= htmlspecialchars($pageTitle ?? 'Mon Site') ?></title>
    <link rel="stylesheet" href="/css/style.css">
    <?= $extraCss ?? '' ?>
</head>
<body>
<header>
    <nav>
        <a href="/index.php">Accueil</a>
        <a href="/produits.php">Produits</a>
        <a href="/contact.php">Contact</a>
    </nav>
</header>
<main>
    <?= $content ?>
</main>
<footer>
    <p>&copy; <?= date('Y') ?> Mon Site.</p>
</footer>
<?= $extraJs ?? '' ?>
</body>
</html>
```

Le layout utilise trois variables injectées par la page :

| Variable | Rôle | Obligatoire |
|----------|------|-------------|
| `$content` | HTML du contenu de la page | ✅ Oui |
| `$pageTitle` | Titre de l'onglet | Recommandé |
| `$extraCss` | Balises `<link>` CSS spécifiques | Non |
| `$extraJs` | Balises `<script>` spécifiques | Non |

---

## 4.2. Fonction helper `render()`

Pour éviter de répéter le code `ob_start` / `ob_get_clean` dans chaque page, on encapsule la logique dans une fonction réutilisable, placée dans un fichier partagé :

**`config/helpers.php`**

```php
<?php
declare(strict_types=1);

/**
 * Rend une vue dans le layout principal.
 *
 * @param string $view     Chemin de la vue (ex: 'views/home.php')
 * @param array  $data     Variables à injecter dans la vue
 * @param string $layout   Chemin du layout (par défaut : layout.php)
 */
function render(string $view, array $data = [], string $layout = 'templates/layout.php'): void
{
    // Rendre les clés du tableau disponibles comme variables
    extract($data, EXTR_SKIP); // EXTR_SKIP : ne pas écraser les variables existantes

    // 1. Capturer le rendu de la vue
    ob_start();
    require $view;
    $content = ob_get_clean();

    // 2. Injecter $content dans le layout et l'afficher
    require $layout;
}
```

> **`extract($data)`** transforme `['pageTitle' => 'Accueil']` en variable `$pageTitle = 'Accueil'`. Le flag `EXTR_SKIP` empêche d'écraser des variables déjà définies, ce qui limite les risques d'injection de variables inattendues.

---

## 4.3. `views/home.php` - Vue de la page d'accueil

```php
<?php
// Métadonnées de la page - disponibles dans le layout
$pageTitle = "Accueil";
?>

<h1>Bienvenue sur le site</h1>
<p>Contenu spécifique à la page d'accueil.</p>
```

## 4.4. `views/produits.php` - Vue avec CSS spécifique

```php
<?php
$pageTitle = "Nos produits";

// CSS chargé uniquement sur cette page
$extraCss = '<link rel="stylesheet" href="/css/produits.css">';

$produits = [
    ["nom" => "Raspberry Pi 5",  "prix" => 60],
    ["nom" => "ESP32 DevKit",    "prix" => 8],
    ["nom" => "Arduino Uno R4",  "prix" => 25],
];
?>

<h1>Nos produits</h1>
<ul>
    <?php foreach ($produits as $produit): ?>
        <li>
            <?= htmlspecialchars($produit["nom"]) ?> -
            <?= $produit["prix"] ?> €
        </li>
    <?php endforeach; ?>
</ul>
```

---

## 4.5. Points d'entrée - `public/index.php` et `public/produits.php`

```php
<?php
// public/index.php
declare(strict_types=1);
require_once 'config/helpers.php';

render('views/home.php');
```

```php
<?php
// public/produits.php
declare(strict_types=1);
require_once 'config/helpers.php';

render('views/produits.php');
```

Les points d'entrée sont désormais **minimalistes** : ils ne font qu'appeler `render()`. La logique métier (requêtes BDD, traitement de formulaires…) peut être ajoutée avant l'appel à `render()` et passée via le tableau `$data`.

---

# 5. Passer des données depuis le contrôleur vers la vue

La fonction `render()` accepte un tableau de données. C'est le mécanisme propre pour transmettre des informations sans polluer l'espace de nommage global :

```php
<?php
// public/profil.php
declare(strict_types=1);

require_once 'config/helpers.php';
require_once 'config/db_connect.php';

// Logique métier : récupération en base
$pdo = getConnection();
$stmt = $pdo->prepare("SELECT nom, prenom, moyenne FROM etudiants WHERE id = :id");
$stmt->execute([':id' => (int)($_GET['id'] ?? 0)]);
$etudiant = $stmt->fetch();

if (!$etudiant) {
    http_response_code(404);
    render('views/404.php', ['pageTitle' => 'Page introuvable']);
    exit;
}

// Rendu : les données sont injectées proprement dans la vue
render('views/profil.php', [
    'pageTitle' => htmlspecialchars($etudiant['prenom']) . ' ' . htmlspecialchars($etudiant['nom']),
    'etudiant'  => $etudiant,
]);
```

```php
<?php
// views/profil.php
// $etudiant est disponible grâce à extract() dans render()
?>

<h1>Profil de <?= htmlspecialchars($etudiant['prenom']) ?></h1>
<table>
    <tr><th>Nom</th>     <td><?= htmlspecialchars($etudiant['nom'])     ?></td></tr>
    <tr><th>Prénom</th>  <td><?= htmlspecialchars($etudiant['prenom'])  ?></td></tr>
    <tr><th>Moyenne</th> <td><?= $etudiant['moyenne'] ?>/20</td></tr>
</table>
```

---

# 6. Comparaison des deux approches

| Critère | Header/Footer (1ère année) | Layout + `ob_start` (2ème année) |
|---------|---------------------------|----------------------------------|
| Complexité | Simple | Modérée |
| Fichiers template | 2 (header + footer) | 1 (layout complet) |
| Définir `<title>` dynamiquement | ⚠️ Avant le `require header` uniquement | ✅ N'importe où dans la vue |
| CSS/JS spécifiques par page | ⚠️ Difficile | ✅ Via `$extraCss` / `$extraJs` |
| Redirections HTTP après logique | ❌ Impossible après echo | ✅ Possible (rien n'est envoyé avant `render()`) |
| Passage de données | Variables globales implicites | Tableau `$data` explicite |
| Proximité des frameworks | Éloignée | Proche (Twig, Blade) |

---

# 7. Vers les frameworks : la même idée dans Twig

Ce mécanisme est exactement ce que font les moteurs de templates des frameworks PHP. En **Twig** (Symfony), le layout s'appelle un *parent template* et le contenu est injecté via des *blocs* :

```twig
{# templates/base.html.twig #}
<!DOCTYPE html>
<html>
<head>
    <title>{% block title %}Mon Site{% endblock %}</title>
</head>
<body>
    <main>{% block content %}{% endblock %}</main>
</body>
</html>
```

```twig
{# templates/produits.html.twig #}
{% extends 'base.html.twig' %}

{% block title %}Nos produits{% endblock %}

{% block content %}
    <h1>Nos produits</h1>
    ...
{% endblock %}
```

Le principe est identique : **le contenu est capturé puis injecté dans le layout**. Maîtriser `ob_start` / `ob_get_clean` permet de comprendre ce que Twig ou Blade font en coulisses.

---

# 8. Résumé

```
Point d'entrée (produits.php)
    │
    ├── Logique métier (BDD, session, validation…)
    │
    └── render('views/produits.php', $data)
              │
              ├── ob_start()
              ├── require 'views/produits.php'  ← s'exécute, définit $pageTitle, $extraCss…
              ├── $content = ob_get_clean()      ← HTML capturé
              │
              └── require 'templates/layout.php' ← injecte $content dans le squelette HTML
                        │
                        └── Envoi au navigateur
```


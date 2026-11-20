# PHP et la séparation structure / contenu

> * Auteur : Gwénaël LAURENT
> * Date : 28/04/2026

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [PHP et la séparation structure / contenu](#php-et-la-séparation-structure--contenu)
- [1. Le problème : tout mélanger](#1-le-problème--tout-mélanger)
- [2. La solution : le template (gabarit)](#2-la-solution--le-template-gabarit)
- [3. `include` et `require`](#3-include-et-require)
- [4. Architecture recommandée](#4-architecture-recommandée)
- [5. Mise en œuvre](#5-mise-en-œuvre)
  - [5.1. `templates/header.php`](#51-templatesheaderphp)
  - [5.2. `templates/footer.php`](#52-templatesfooterphp)
  - [5.3. `index.php` - Page d'accueil](#53-indexphp---page-daccueil)
  - [5.4. `produits.php` - Page produits](#54-produitsphp---page-produits)
- [6. Syntaxe alternative dans les templates](#6-syntaxe-alternative-dans-les-templates)
- [7. Aller plus loin : passer des données au template](#7-aller-plus-loin--passer-des-données-au-template)
- [8. Règles de sécurité](#8-règles-de-sécurité)
- [9. Résumé - Avantages de la séparation](#9-résumé---avantages-de-la-séparation)
- [10. Structure finale du projet](#10-structure-finale-du-projet)


# 1. Le problème : tout mélanger

Quand on débute, il est tentant d'écrire tout le HTML et tout le PHP dans un seul fichier :

```php
<!-- ❌ Mauvaise pratique : tout dans un seul fichier -->
<!DOCTYPE html>
<html>
<head>
    <title>Mon site</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <header>
        <nav>
            <a href="index.php">Accueil</a>
            <a href="produits.php">Produits</a>
            <a href="contact.php">Contact</a>
        </nav>
    </header>
    <main>
        <h1>Bienvenue !</h1>
        <p>Contenu de la page d'accueil...</p>
    </main>
    <footer>
        <p>&copy; 2025 Mon Site</p>
    </footer>
</body>
</html>
```

Si ce code est dupliqué dans chaque page (`index.php`, `contact.php`, `produits.php`…), une modification du menu oblige à éditer **tous les fichiers**. C'est long, source d'erreurs et non maintenable.

---

# 2. La solution : le template (gabarit)

L'idée est de **découper le HTML en fragments réutilisables** grâce à `include` ou `require`, et de séparer clairement :

- Le **squelette HTML** (layout / template)
- Le **contenu spécifique** à chaque page

---

# 3. `include` et `require`

PHP permet d'insérer le contenu d'un fichier dans un autre :

| Instruction | Comportement si fichier absent |
|-------------|-------------------------------|
| `include 'fichier.php'` | Avertissement, exécution continue |
| `require 'fichier.php'` | Erreur fatale, exécution arrêtée |
| `include_once 'fichier.php'` | Inclus une seule fois maximum |
| `require_once 'fichier.php'` | Requis, inclus une seule fois |

> **Bonne pratique :** Utiliser `require` (ou `require_once`) pour les fichiers critiques (templates, connexion BDD) afin que l'absence du fichier arrête le script plutôt que d'afficher une page incomplète.

---

# 4. Architecture recommandée

```
projet/
├── index.php           ← Page d'accueil
├── produits.php        ← Page produits
├── contact.php         ← Page contact
└── templates/
    ├── header.php      ← En-tête HTML + nav
    └── footer.php      ← Pied de page
```

---

# 5. Mise en œuvre

## 5.1. `templates/header.php`

```php
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?= htmlspecialchars($pageTitle ?? 'Mon Site') ?></title>
    <link rel="stylesheet" href="/css/style.css">
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
```

## 5.2. `templates/footer.php`

```php
</main>
<footer>
    <p>&copy; <?= date('Y') ?> Mon Site. Tous droits réservés.</p>
</footer>
</body>
</html>
```

## 5.3. `index.php` - Page d'accueil

```php
<?php
declare(strict_types=1);

$pageTitle = "Accueil";     // Variable disponible dans header.php

require 'templates/header.php';
?>

<h1>Bienvenue sur le site</h1>
<p>Contenu spécifique à la page d'accueil.</p>

<?php require 'templates/footer.php'; ?>
```

## 5.4. `produits.php` - Page produits

```php
<?php
declare(strict_types=1);

$pageTitle = "Nos produits";

require 'templates/header.php';

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

<?php require 'templates/footer.php'; ?>
```

---

# 6. Syntaxe alternative dans les templates

Dans les fichiers de template mélangés avec du HTML, la **syntaxe alternative** des structures de contrôle est plus lisible :

| Syntaxe classique | Syntaxe alternative (dans templates) |
|-------------------|--------------------------------------|
| `if ($c) {` | `if ($c):` |
| `}` | `endif;` |
| `foreach ($t as $v) {` | `foreach ($t as $v):` |
| `}` | `endforeach;` |
| `while ($c) {` | `while ($c):` |
| `}` | `endwhile;` |

**Exemple :**

```php
<?php if ($utilisateurConnecte): ?>
    <p>Bonjour, <?= htmlspecialchars($nomUtilisateur) ?> !</p>
<?php else: ?>
    <p><a href="connexion.php">Se connecter</a></p>
<?php endif; ?>
```

La balise courte `<?= ... ?>` est un raccourci pour `<?php echo ... ?>`.

---

# 7. Aller plus loin : passer des données au template

On peut passer des variables complexes aux templates avant de les inclure :

```php
<?php
declare(strict_types=1);

// Données préparées avant inclusion du header
$pageTitle    = "Profil étudiant";
$etudiant     = [
    "nom"     => "Dupont",
    "prenom"  => "Marie",
    "moyenne" => 13.5
];

require 'templates/header.php';
?>

<h1>Profil de <?= htmlspecialchars($etudiant['prenom']) ?></h1>
<table>
    <tr><th>Nom</th><td><?= htmlspecialchars($etudiant['nom']) ?></td></tr>
    <tr><th>Prénom</th><td><?= htmlspecialchars($etudiant['prenom']) ?></td></tr>
    <tr><th>Moyenne</th><td><?= $etudiant['moyenne'] ?>/20</td></tr>
</table>

<?php require 'templates/footer.php'; ?>
```

---

# 8. Règles de sécurité

> ⚠️ **Toujours échapper les données avant affichage.**

`htmlspecialchars()` convertit les caractères spéciaux HTML (`<`, `>`, `"`, `&`) en entités HTML, empêchant les attaques **XSS (Cross-Site Scripting)**.

```php
// ❌ Dangereux si $nom vient de l'utilisateur
echo $nom;

// ✅ Sécurisé
echo htmlspecialchars($nom, ENT_QUOTES, 'UTF-8');
```

---

# 9. Résumé - Avantages de la séparation

| Avantage | Explication |
|----------|-------------|
| **Maintenabilité** | Modifier le menu → éditer un seul fichier `header.php` |
| **Lisibilité** | Chaque fichier a un rôle clair |
| **Réutilisabilité** | Les templates sont partagés entre toutes les pages |
| **Séparation des responsabilités** | Structure HTML séparée de la logique PHP |

---

# 10. Structure finale du projet

```
projet/
├── index.php           ← require header + contenu + footer
├── produits.php        ← require header + contenu + footer
├── contact.php         ← require header + contenu + footer
├── templates/
│   ├── header.php      ← <!DOCTYPE> ... <main>
│   └── footer.php      ← </main> ... </html>
└── css/
    └── style.css
```


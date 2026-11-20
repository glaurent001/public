# Les bases du langage PHP

> * Auteur : Gwénaël LAURENT
> * Date : 28/04/2026

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Les bases du langage PHP](#les-bases-du-langage-php)
- [1. Les balises PHP `<?php ... ?>`](#1-les-balises-php-php--)
  - [1.1. Règles importantes](#11-règles-importantes)
- [2. `echo` - Afficher du contenu](#2-echo---afficher-du-contenu)
  - [2.1. `echo` vs `print`](#21-echo-vs-print)
- [3. Variables, types et annotations de type](#3-variables-types-et-annotations-de-type)
  - [3.1. Déclaration de variables](#31-déclaration-de-variables)
  - [3.2. Les types principaux](#32-les-types-principaux)
  - [3.3. Vérifier le type d'une variable](#33-vérifier-le-type-dune-variable)
  - [3.4. Annotations de type (PHP 7+)](#34-annotations-de-type-php-7)
- [4. Structures de contrôle](#4-structures-de-contrôle)
  - [4.1. `if` / `elseif` / `else`](#41-if--elseif--else)
  - [4.2. `for`](#42-for)
  - [4.3. `while`](#43-while)
  - [4.4. `foreach`](#44-foreach)
- [5. Tableaux (`array`)](#5-tableaux-array)
  - [5.1. Tableaux indexés](#51-tableaux-indexés)
  - [5.2. Tableaux associatifs](#52-tableaux-associatifs)
  - [5.3. Fonctions de base sur les tableaux](#53-fonctions-de-base-sur-les-tableaux)
- [6. Quelques fonctions internes couramment utilisées](#6-quelques-fonctions-internes-couramment-utilisées)
  - [6.1. Chaînes de caractères](#61-chaînes-de-caractères)
  - [6.2. Mathématiques](#62-mathématiques)
  - [6.3. Date et heure](#63-date-et-heure)
  - [6.4. Exemple complet](#64-exemple-complet)
- [7. Variables superglobales](#7-variables-superglobales)
  - [7.1. Les principales superglobales](#71-les-principales-superglobales)
  - [7.2. `$_SERVER` - informations sur la requête](#72-_server---informations-sur-la-requête)
  - [7.3. `$_GET` - paramètres d'URL](#73-_get---paramètres-durl)
  - [7.4. `$_POST` - données de formulaire](#74-_post---données-de-formulaire)
- [8. La constante `__DIR__` et les chemins de fichiers](#8-la-constante-__dir__-et-les-chemins-de-fichiers)
  - [8.1. Le problème des chemins relatifs](#81-le-problème-des-chemins-relatifs)
  - [8.2. `__DIR__` - chemin absolu du fichier courant](#82-__dir__---chemin-absolu-du-fichier-courant)
  - [8.3. Utilisation dans les `require`](#83-utilisation-dans-les-require)
- [9. Opérateurs `?:` et `??`](#9-opérateurs--et-)
  - [9.1. L'opérateur ternaire `? :`](#91-lopérateur-ternaire--)
  - [9.2. L'opérateur `??` (null coalescing)](#92-lopérateur--null-coalescing)
  - [9.3. Comparaison `?:` vs `??`](#93-comparaison--vs-)
  - [9.4. Chaînage de `??`](#94-chaînage-de-)
- [10. Résumé](#10-résumé)


# 1. Les balises PHP `<?php ... ?>`

Pour insérer du code PHP dans un fichier, on utilise les **balises d'ouverture et de fermeture** :

```php
<?php
// Votre code PHP ici
?>
```

## 1.1. Règles importantes

- La balise ouvrante `<?php` est **obligatoire**.
- La balise fermante `?>` est **optionnelle** en fin de fichier PHP pur (et même recommandée de l'omettre pour éviter les espaces parasites avant les headers HTTP).
- PHP peut être **mélangé avec du HTML** :

```php
<!DOCTYPE html>
<html>
<body>
    <h1><?php echo "Bonjour !"; ?></h1>
    <p>Nous sommes le <?php echo date("d/m/Y"); ?></p>
</body>
</html>
```

> **Bonne pratique :** Dans les fichiers PHP purs (sans HTML), omettre la balise fermante `?>`.

---

# 2. `echo` - Afficher du contenu

`echo` permet d'envoyer du texte ou du HTML vers le navigateur.

```php
<?php
echo "Hello, World!";
echo "<p>Un paragraphe HTML</p>";
echo "Résultat : " . 42;       // Concaténation avec le point .
echo "Résultat : $variable";   // Interpolation dans les guillemets doubles
?>
```

## 2.1. `echo` vs `print`

| | `echo` | `print` |
|-|--------|---------|
| Retourne une valeur | Non | Oui (1) |
| Plusieurs arguments | Oui | Non |
| Performance | Légèrement plus rapide | - |

> **En pratique**, `echo` est quasi-toujours utilisé.

---

# 3. Variables, types et annotations de type

## 3.1. Déclaration de variables

En PHP, les variables commencent par le symbole **`$`** et sont **non typées par défaut** (typage dynamique).

```php
<?php
$nom     = "Alice";          // string
$age     = 20;               // int
$moyenne = 14.5;             // float
$majeur  = true;             // bool
$rien    = null;             // null
?>
```

## 3.2. Les types principaux

| Type | Exemple | Description |
|------|---------|-------------|
| `string` | `"Bonjour"` | Chaîne de caractères |
| `int` | `42` | Entier |
| `float` | `3.14` | Nombre décimal |
| `bool` | `true` / `false` | Booléen |
| `null` | `null` | Absence de valeur |
| `array` | `[1, 2, 3]` | Tableau |

## 3.3. Vérifier le type d'une variable

```php
<?php
$valeur = 42;
echo gettype($valeur);   // "integer"
var_dump($valeur);       // int(42)
?>
```

## 3.4. Annotations de type (PHP 7+)

Depuis PHP 7, il est possible (et recommandé) d'annoter le type des **paramètres** et **valeurs de retour** des fonctions. Cela améliore la lisibilité et détecte les erreurs.

```php
<?php
declare(strict_types=1); // Active la vérification stricte des types

function additionner(int $a, int $b): int {
    return $a + $b;
}

function saluer(string $prenom): string {
    return "Bonjour, $prenom !";
}

function diviser(float $a, float $b): float|false {
    if ($b === 0.0) return false;
    return $a / $b;
}

echo additionner(3, 5);    // 8
echo saluer("Bob");        // Bonjour, Bob !
?>
```

> **Bonne pratique de sécurité :** Toujours utiliser `declare(strict_types=1)` en tête de fichier pour éviter les conversions de types implicites inattendues.

---

# 4. Structures de contrôle

## 4.1. `if` / `elseif` / `else`

```php
<?php
$note = 14;

if ($note >= 16) {
    echo "Très bien";
} elseif ($note >= 12) {
    echo "Bien";
} elseif ($note >= 10) {
    echo "Passable";
} else {
    echo "Insuffisant";
}
?>
```

## 4.2. `for`

```php
<?php
for ($i = 0; $i < 5; $i++) {
    echo "Ligne $i <br>";
}
?>
```

## 4.3. `while`

```php
<?php
$compteur = 0;
while ($compteur < 3) {
    echo "Tour $compteur <br>";
    $compteur++;
}
?>
```

## 4.4. `foreach`

`foreach` est conçu pour parcourir les tableaux (voir section suivante).

```php
<?php
$fruits = ["pomme", "banane", "cerise"];

foreach ($fruits as $fruit) {
    echo $fruit . "<br>";
}

// Avec index
foreach ($fruits as $index => $fruit) {
    echo "$index : $fruit <br>";
}
?>
```

---

# 5. Tableaux (`array`)

## 5.1. Tableaux indexés

Les indices commencent à `0` par défaut.

```php
<?php
$notes = [12, 15, 9, 17];

echo $notes[0];    // 12
echo $notes[2];    // 9
echo count($notes); // 4
?>
```

## 5.2. Tableaux associatifs

Les clés sont des chaînes de caractères (comme un dictionnaire).

```php
<?php
$etudiant = [
    "nom"     => "Dupont",
    "prenom"  => "Marie",
    "moyenne" => 13.5
];

echo $etudiant["nom"];     // Dupont
echo $etudiant["moyenne"]; // 13.5
?>
```

## 5.3. Fonctions de base sur les tableaux

| Fonction | Description | Exemple |
|----------|-------------|---------|
| `count($tab)` | Nombre d'éléments | `count([1,2,3])` → `3` |
| `array_push($tab, $val)` | Ajouter en fin | `array_push($tab, 4)` |
| `array_pop($tab)` | Supprimer le dernier | `array_pop($tab)` |
| `in_array($val, $tab)` | Tester la présence | `in_array(2, [1,2,3])` → `true` |
| `array_keys($tab)` | Retourner les clés | `array_keys($etudiant)` |
| `array_values($tab)` | Retourner les valeurs | `array_values($etudiant)` |
| `sort($tab)` | Trier (valeurs, ordre croissant) | `sort($notes)` |
| `ksort($tab)` | Trier par clés | `ksort($etudiant)` |
| `array_merge($a, $b)` | Fusionner deux tableaux | `array_merge($a, $b)` |

```php
<?php
$notes = [14, 9, 17, 12];
sort($notes);
print_r($notes); // Array ( [0] => 9 [1] => 12 [2] => 14 [3] => 17 )

$noms = ["Bob", "Alice", "Claire"];
if (in_array("Alice", $noms)) {
    echo "Alice est dans la liste";
}
?>
```

---

# 6. Quelques fonctions internes couramment utilisées

## 6.1. Chaînes de caractères

| Fonction | Description | Exemple |
|----------|-------------|---------|
| `strlen($s)` | Longueur | `strlen("hello")` → `5` |
| `strtolower($s)` | Minuscules | `strtolower("HELLO")` → `"hello"` |
| `strtoupper($s)` | Majuscules | `strtoupper("hello")` → `"HELLO"` |
| `trim($s)` | Supprimer espaces | `trim("  hello  ")` → `"hello"` |
| `str_contains($s, $sub)` | Contient ? (PHP 8) | `str_contains("bonjour", "jour")` → `true` |
| `str_replace($old, $new, $s)` | Remplacer | `str_replace("o", "0", "bonjour")` |
| `substr($s, $start, $len)` | Sous-chaîne | `substr("bonjour", 0, 3)` → `"bon"` |
| `explode($sep, $s)` | Découper en tableau | `explode(",", "a,b,c")` → `["a","b","c"]` |
| `implode($sep, $tab)` | Tableau → chaîne | `implode("-", ["a","b"])` → `"a-b"` |
| `htmlspecialchars($s)` | Échapper HTML | **Indispensable avant affichage !** |

## 6.2. Mathématiques

| Fonction | Description |
|----------|-------------|
| `abs($n)` | Valeur absolue |
| `round($n, $dec)` | Arrondi |
| `ceil($n)` | Arrondi supérieur |
| `floor($n)` | Arrondi inférieur |
| `rand($min, $max)` | Nombre aléatoire |
| `max($a, $b)` | Maximum |
| `min($a, $b)` | Minimum |

## 6.3. Date et heure

```php
<?php
echo date("d/m/Y");         // 28/04/2025
echo date("H:i:s");         // 14:30:00
echo time();                // Timestamp Unix (secondes depuis 01/01/1970)
?>
```

## 6.4. Exemple complet

```php
<?php
declare(strict_types=1);

$etudiants = [
    ["nom" => "Dupont",  "note" => 14],
    ["nom" => "Martin",  "note" => 9],
    ["nom" => "Bernard", "note" => 17],
];

$total = 0;
foreach ($etudiants as $etudiant) {
    $total += $etudiant["note"];
}
$moyenne = round($total / count($etudiants), 2);

echo "Moyenne de la classe : $moyenne/20";

foreach ($etudiants as $etudiant) {
    $nom  = htmlspecialchars($etudiant["nom"]); // Sécurisation avant affichage
    $note = $etudiant["note"];
    $mention = $note >= 10 ? "Reçu" : "Ajourné";
    echo "<p>$nom : $note/20 - $mention</p>";
}
?>
```

> **Règle de sécurité :** Toujours utiliser `htmlspecialchars()` avant d'afficher une donnée provenant de l'utilisateur ou d'une source externe, pour prévenir les attaques **XSS** (Cross-Site Scripting).

---

# 7. Variables superglobales

Les **variables superglobales** sont des tableaux associatifs prédéfinis par PHP, accessibles **partout** dans le script (fonctions, classes…) sans avoir besoin de les déclarer ni de les passer en paramètre.

## 7.1. Les principales superglobales

| Variable | Contenu |
|----------|---------|
| `$_SERVER` | Informations sur le serveur et la requête HTTP |
| `$_GET` | Paramètres transmis dans l'URL (`?clé=valeur`) |
| `$_POST` | Données envoyées par un formulaire en méthode POST |
| `$_COOKIE` | Cookies envoyés par le navigateur |
| `$_SESSION` | Données de session (après `session_start()`) |
| `$_FILES` | Fichiers uploadés via un formulaire |
| `$_ENV` | Variables d'environnement du système |
| `$_REQUEST` | Fusion de `$_GET`, `$_POST` et `$_COOKIE` (à éviter) |

## 7.2. `$_SERVER` - informations sur la requête

```php
<?php
echo $_SERVER['HTTP_HOST'];       // ex: localhost ou www.monsite.fr
echo $_SERVER['REQUEST_URI'];     // ex: /produits.php?id=3
echo $_SERVER['REQUEST_METHOD'];  // GET ou POST
echo $_SERVER['REMOTE_ADDR'];     // IP du client
echo $_SERVER['SCRIPT_FILENAME']; // Chemin absolu du fichier en cours
?>
```

## 7.3. `$_GET` - paramètres d'URL

L'URL `produit.php?id=5&couleur=rouge` rend disponible :

```php
<?php
$id      = (int) ($_GET['id']      ?? 0);
$couleur = $_GET['couleur'] ?? 'inconnu';

echo "Produit $id, couleur : " . htmlspecialchars($couleur);
?>
```

## 7.4. `$_POST` - données de formulaire

```php
<!-- Formulaire HTML -->
<form method="POST" action="traitement.php">
    <input type="text" name="nom">
    <input type="submit" value="Envoyer">
</form>
```

```php
<?php
// traitement.php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $nom = filter_input(INPUT_POST, 'nom', FILTER_SANITIZE_SPECIAL_CHARS);
    echo "Bonjour, " . htmlspecialchars($nom ?? '');
}
?>
```

> **Règle de sécurité :** Ne jamais faire confiance aux données de `$_GET`, `$_POST` ou `$_COOKIE`. Toujours **valider** avec `filter_input()` et **échapper** avec `htmlspecialchars()` avant affichage.

---

# 8. La constante `__DIR__` et les chemins de fichiers

## 8.1. Le problème des chemins relatifs

`require 'config/db_connect.php'` est un chemin **relatif**. Il est résolu par rapport au **répertoire de travail courant** (le dossier depuis lequel PHP est lancé), qui peut varier selon la façon dont le script est appelé - et provoquer des erreurs difficiles à déboguer.

```
projet/
├── public/
│   └── index.php         ← appelé par le navigateur
└── config/
    └── db_connect.php
```

Depuis `index.php`, écrire `require '../config/db_connect.php'` fonctionne *en général*, mais si un autre script dans un sous-dossier inclut `index.php`, le chemin relatif `..` ne pointe plus au bon endroit.

## 8.2. `__DIR__` - chemin absolu du fichier courant

`__DIR__` est une **constante magique** PHP qui contient le **chemin absolu du dossier** du fichier en cours d'exécution. Elle ne dépend jamais du répertoire de travail.

```php
<?php
echo __DIR__;
// /var/www/html/projet/public   (chemin absolu, toujours fiable)
?>
```

## 8.3. Utilisation dans les `require`

```php
<?php
// public/index.php

// ✅ Chemin absolu, toujours correct quel que soit le contexte d'appel
require_once __DIR__ . '/../config/db_connect.php';
require_once __DIR__ . '/../config/helpers.php';
require_once __DIR__ . '/../templates/layout.php';
?>
```

La concaténation `__DIR__ . '/..` remonte d'un niveau depuis le dossier du fichier courant, de façon **absolue et portable**.

> **Bonne pratique :** Utiliser systématiquement `__DIR__` dans tous les `require` et `require_once` pour garantir des chemins fiables, quel que soit l'environnement (développement, production, tests).

---

# 9. Opérateurs `?:` et `??`

## 9.1. L'opérateur ternaire `? :`

C'est une version compacte du `if / else` sur une seule ligne :

```php
$variable = (condition) ? valeur_si_vrai : valeur_si_faux;
```

**Exemple :**

```php
<?php
$note = 12;

// Écriture longue
if ($note >= 10) {
    $mention = "Reçu";
} else {
    $mention = "Ajourné";
}

// Écriture ternaire équivalente
$mention = ($note >= 10) ? "Reçu" : "Ajourné";

echo $mention; // Reçu
?>
```

**Version courte `?:` (Elvis operator)** - quand la valeur testée est aussi la valeur retournée si vraie :

```php
<?php
$nom = $_GET['nom'] ?: 'Anonyme';
// Équivalent à : $nom = $_GET['nom'] ? $_GET['nom'] : 'Anonyme';
?>
```

## 9.2. L'opérateur `??` (null coalescing)

`??` retourne la valeur de gauche si elle **existe et n'est pas `null`**, sinon retourne la valeur de droite. C'est l'outil idéal pour les superglobales et les valeurs optionnelles.

```php
$variable = $valeur_possible ?? valeur_par_defaut;
```

**Exemple :**

```php
<?php
// Sans ?? : verbeux et risqué
if (isset($_GET['page'])) {
    $page = (int) $_GET['page'];
} else {
    $page = 1;
}

// Avec ?? : concis et lisible
$page = (int) ($_GET['page'] ?? 1);

echo $page; // 1 si ?page= absent de l'URL, sinon la valeur fournie
?>
```

## 9.3. Comparaison `?:` vs `??`

| Opérateur | Retourne la valeur par défaut si… | Cas d'usage typique |
|-----------|----------------------------------|---------------------|
| `?:` | La valeur est **falsy** (`0`, `""`, `false`, `null`…) | Valeur calculée ou booléenne |
| `??` | La valeur est **`null` ou non définie** | Clés de tableaux, paramètres optionnels |

```php
<?php
$valeur = 0;

echo $valeur ?: 'défaut';   // "défaut"  ← 0 est falsy
echo $valeur ?? 'défaut';   // "0"       ← 0 existe et n'est pas null
?>
```

> **Bonne pratique :** Préférer `??` pour les superglobales (`$_GET`, `$_POST`, `$_SERVER`…) car une clé absente génère un `null`, pas forcément un falsy. Utiliser `?:` quand on veut aussi couvrir les valeurs vides (`""`, `0`, `false`).

## 9.4. Chaînage de `??`

On peut enchaîner plusieurs `??` pour tester plusieurs sources dans l'ordre :

```php
<?php
// Cherche d'abord dans $_POST, puis $_GET, sinon valeur par défaut
$recherche = $_POST['q'] ?? $_GET['q'] ?? '';
?>
```

---

# 10. Résumé

| Élément | Syntaxe clé |
|---------|------------|
| Balises | `<?php ... ?>` |
| Affichage | `echo "texte";` |
| Variable | `$nom = valeur;` |
| Annotation type | `function f(int $x): string` |
| Condition | `if / elseif / else` |
| Boucle compteur | `for ($i=0; $i<n; $i++)` |
| Boucle conditionnelle | `while (condition)` |
| Parcours tableau | `foreach ($tab as $val)` |
| Tableau indexé | `$t = [1, 2, 3];` |
| Tableau associatif | `$t = ["cle" => "val"];` |
| Superglobales | `$_GET`, `$_POST`, `$_SERVER`, `$_SESSION`… |
| Chemin absolu | `__DIR__ . '/chemin/fichier.php'` |
| Ternaire | `$v = (cond) ? vrai : faux;` |
| Null coalescing | `$v = $a ?? 'défaut';` |


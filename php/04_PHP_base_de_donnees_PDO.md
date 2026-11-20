# PHP et les bases de données avec PDO

> * Auteur : Gwénaël LAURENT
> * Date : 06/05/2026

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [PHP et les bases de données avec PDO](#php-et-les-bases-de-données-avec-pdo)
- [1. Pourquoi PDO ?](#1-pourquoi-pdo-)
- [2. Enregistrer les credentials dans un fichier `.env`](#2-enregistrer-les-credentials-dans-un-fichier-env)
  - [2.1. Pourquoi ?](#21-pourquoi-)
  - [2.2. Le fichier `.env`](#22-le-fichier-env)
  - [2.3. Lire le fichier `.env` avec `parse_ini_file()`](#23-lire-le-fichier-env-avec-parse_ini_file)
- [3. Fichier de connexion à la base](#3-fichier-de-connexion-à-la-base)
  - [3.1. `config/db_connect.php`](#31-configdb_connectphp)
- [4. Requêtes SELECT sans paramètre](#4-requêtes-select-sans-paramètre)
  - [4.1. Récupérer une seule ligne](#41-récupérer-une-seule-ligne)
- [5. Requêtes SELECT avec paramètres - Requêtes préparées](#5-requêtes-select-avec-paramètres---requêtes-préparées)
  - [5.1. Pourquoi les requêtes préparées ?](#51-pourquoi-les-requêtes-préparées-)
  - [5.2. Syntaxe avec marqueurs nommés (recommandée)](#52-syntaxe-avec-marqueurs-nommés-recommandée)
  - [5.3. Syntaxe avec marqueurs positionnels `?`](#53-syntaxe-avec-marqueurs-positionnels-)
  - [5.4. Résumé des méthodes de récupération](#54-résumé-des-méthodes-de-récupération)
- [6. Requête INSERT](#6-requête-insert)
- [7. Requête UPDATE](#7-requête-update)
- [8. Requête DELETE](#8-requête-delete)
- [9. Gestion des erreurs avec try/catch](#9-gestion-des-erreurs-avec-trycatch)
- [10. Résumé des opérations CRUD](#10-résumé-des-opérations-crud)
- [11. Règles de sécurité - Récapitulatif](#11-règles-de-sécurité---récapitulatif)


# 1. Pourquoi PDO ?

**PDO** (*PHP Data Objects*) est l'extension PHP standard pour accéder aux bases de données. Elle présente plusieurs avantages majeurs :

| Avantage | Détail |
|----------|--------|
| **Portabilité** | Compatible MySQL, MariaDB, PostgreSQL, SQLite… sans changer le code |
| **Sécurité** | Support natif des requêtes préparées (protection contre les injections SQL) |
| **Gestion d'erreurs** | Système d'exceptions unifié |

> ⚠️ L'ancienne extension `mysql_*` est **supprimée** depuis PHP 7. `mysqli` n'est utilisable qu'avec MySQL/MariaDB. **Utilisez toujours PDO.**

---

# 2. Enregistrer les credentials dans un fichier `.env`

## 2.1. Pourquoi ?

Les identifiants de base de données (hôte, nom de BDD, login, mot de passe) **ne doivent jamais être écrits en dur dans le code source**, notamment pour éviter de les exposer dans un dépôt Git.

## 2.2. Le fichier `.env`

Créez un fichier `.env` à la **racine du projet**.

> ⚠️ Il est impératif que le fichier `.env` soit situé hors de la racine web. Il ne doit pas être accessible depuis une requête HTTP directe.

```ini
# .env
DB_HOST=localhost
DB_NAME=ma_base
DB_USER=app_user
DB_PASS=MotDePasseSecurise!
DB_CHARSET=utf8mb4
```

> ⚠️ **Ce fichier ne doit JAMAIS être versionné.** Ajoutez-le impérativement au `.gitignore` :
>
> ```
> # .gitignore
> .env
> ```

## 2.3. Lire le fichier `.env` avec `parse_ini_file()`

```php
<?php
// Lecture du fichier .env
$env = parse_ini_file(__DIR__ . '/../.env');  // Un niveau au-dessus de la racine web
```

> **Alternative recommandée en production :** utiliser la bibliothèque [`vlucas/phpdotenv`](https://github.com/vlucas/phpdotenv) (installable via Composer).

---

# 3. Fichier de connexion à la base

Créez un fichier dédié `db_connect.php` dans un dossier `config/` :

```
projet/                    ← ✅ Racine du  projet
├── config/                ← ⚠️ Ne jamais exposer ce dossier publiquement
│   └── db_connect.php     ← Connexion à la base de données
├── public/                ← ✅ Racine web (VirtualHost)
│   ├── css/
│   ├── img/
│   └── index.php          ← Page d'accueil
├── .env                   ← ⚠️ Identifiants d'accès à la base de données
└── .gitignore             ← ⚠️ Pour ne JAMAIS versionner le .env
```


## 3.1. `config/db_connect.php`

```php
<?php
declare(strict_types=1);

function getConnection(): PDO {
    // Chargement des credentials depuis .env
    $env = parse_ini_file(__DIR__ . '/../.env');

    // Data Source Name
    $dsn = sprintf(
        "mysql:host=%s;dbname=%s;charset=%s",
        $env['DB_HOST'],
        $env['DB_NAME'],
        $env['DB_CHARSET']
    );

    //Options de connexion
    $options = [
        PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,  // Lancer des exceptions
        PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,        // Résultats en tableau associatif
        PDO::ATTR_EMULATE_PREPARES   => false,                   // Désactiver l'émulation (sécurité)
    ];

    try {
        return new PDO($dsn, $env['DB_USER'], $env['DB_PASS'], $options);
    } catch (PDOException $e) {
        // Ne jamais afficher le message d'erreur complet à l'utilisateur
        error_log("Erreur de connexion BDD : " . $e->getMessage());
        throw new RuntimeException("Impossible de se connecter à la base de données.");
    }
}
```

> **Règle de sécurité :** Ne jamais afficher les messages d'erreur PDO à l'utilisateur final. Utilisez `error_log()` pour les journaliser côté serveur.

---

# 4. Requêtes SELECT sans paramètre

Pour récupérer **toutes** les lignes d'une table sans condition :

```php
<?php
declare(strict_types=1);
require_once __DIR__ . '/../config/db_connect.php';

$pdo = getConnection();

// Requête sans paramètre : utiliser query()
$stmt = $pdo->query("SELECT id, nom, email FROM utilisateurs ORDER BY nom");
$utilisateurs = $stmt->fetchAll();  // Tableau de tous les résultats

foreach ($utilisateurs as $user) {
    echo htmlspecialchars($user['nom']) . " - " . htmlspecialchars($user['email']) . "<br>";
}
?>
```

## 4.1. Récupérer une seule ligne

```php
<?php
$stmt = $pdo->query("SELECT COUNT(*) AS total FROM utilisateurs");
$result = $stmt->fetch();  // Une seule ligne
echo "Nombre d'utilisateurs : " . $result['total'];
?>
```

---

# 5. Requêtes SELECT avec paramètres - Requêtes préparées

## 5.1. Pourquoi les requêtes préparées ?

Une **injection SQL** est une attaque où l'utilisateur insère du code SQL malveillant dans une entrée.

**Exemple d'attaque sans requête préparée :**

```php
// ❌ DANGEREUX - Ne jamais faire ça !
$id = $_GET['id'];  // L'utilisateur envoie : 1 OR 1=1
$stmt = $pdo->query("SELECT * FROM utilisateurs WHERE id = $id");
// Requête exécutée : SELECT * FROM utilisateurs WHERE id = 1 OR 1=1
// → Retourne TOUS les utilisateurs !
```

**Avec une requête préparée, le paramètre et la requête sont envoyés séparément au SGBD.** Il n'y a aucune concaténation de chaînes : le paramètre ne peut jamais être interprété comme du SQL.

## 5.2. Syntaxe avec marqueurs nommés (recommandée)

```php
<?php
declare(strict_types=1);
require_once __DIR__ . '/../config/db_connect.php';

$pdo = getConnection();
$id  = (int) $_GET['id'];  // Cast en int pour sécurité supplémentaire

// 1. Préparer la requête (avec marqueur :id)
$stmt = $pdo->prepare("SELECT id, nom, email FROM utilisateurs WHERE id = :id");

// 2. Lier le paramètre et exécuter
$stmt->execute([':id' => $id]);

// 3. Récupérer le résultat
$utilisateur = $stmt->fetch();

if ($utilisateur) {
    echo "Nom : " . htmlspecialchars($utilisateur['nom']);
} else {
    echo "Utilisateur introuvable.";
}
?>
```

## 5.3. Syntaxe avec marqueurs positionnels `?`

```php
<?php
$stmt = $pdo->prepare(
    "SELECT * FROM utilisateurs WHERE email = ? AND actif = ?"
);
$stmt->execute([$email, 1]);
$user = $stmt->fetch();
?>
```

## 5.4. Résumé des méthodes de récupération

| Méthode | Retourne |
|---------|----------|
| `$stmt->fetch()` | Une seule ligne (ou `false`) |
| `$stmt->fetchAll()` | Toutes les lignes |
| `$stmt->fetchColumn()` | Une seule valeur (1ère colonne) |

---

# 6. Requête INSERT

Ajouter un enregistrement en base :

```php
<?php
declare(strict_types=1);
require_once __DIR__ . '/../config/db_connect.php';

$pdo = getConnection();

// Données provenant d'un formulaire (toujours valider/filtrer avant !)
$nom   = filter_input(INPUT_POST, 'nom',   FILTER_SANITIZE_SPECIAL_CHARS);
$email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);

if ($nom === null || $email === false) {
    die("Données invalides.");
}

$stmt = $pdo->prepare(
    "INSERT INTO utilisateurs (nom, email, date_creation) VALUES (:nom, :email, NOW())"
);

$stmt->execute([
    ':nom'   => $nom,
    ':email' => $email,
]);

$nouvelId = $pdo->lastInsertId(); // Récupérer l'ID généré
echo "Utilisateur créé avec l'ID : $nouvelId";
?>
```

> **Règle de sécurité :** Toujours **valider et filtrer** les données de formulaire avec `filter_input()` ou une bibliothèque de validation avant de les insérer en base.

---

# 7. Requête UPDATE

Modifier un enregistrement existant :

```php
<?php
declare(strict_types=1);
require_once __DIR__ . '/../config/db_connect.php';

$pdo = getConnection();

$id      = (int) $_POST['id'];
$nouveau_email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);

if ($id <= 0 || $nouveau_email === false) {
    die("Données invalides.");
}

$stmt = $pdo->prepare(
    "UPDATE utilisateurs SET email = :email WHERE id = :id"
);

$stmt->execute([
    ':email' => $nouveau_email,
    ':id'    => $id,
]);

$lignesModifiees = $stmt->rowCount();
echo "$lignesModifiees ligne(s) modifiée(s).";
?>
```

`rowCount()` retourne le nombre de lignes effectivement modifiées.

---

# 8. Requête DELETE

Supprimer un enregistrement :

```php
<?php
declare(strict_types=1);
require_once __DIR__ . '/../config/db_connect.php';

$pdo = getConnection();

$id = (int) $_POST['id'];

if ($id <= 0) {
    die("ID invalide.");
}

$stmt = $pdo->prepare("DELETE FROM utilisateurs WHERE id = :id");
$stmt->execute([':id' => $id]);

$lignesSupprimees = $stmt->rowCount();
echo "$lignesSupprimees ligne(s) supprimée(s).";
?>
```

---

# 9. Gestion des erreurs avec try/catch

Pour les opérations critiques, encapsuler dans un `try/catch` :

```php
<?php
declare(strict_types=1);
require_once __DIR__ . '/../config/db_connect.php';

try {
    $pdo = getConnection();

    $stmt = $pdo->prepare(
        "INSERT INTO produits (nom, prix) VALUES (:nom, :prix)"
    );
    $stmt->execute([
        ':nom'  => 'ESP32 DevKit',
        ':prix' => 8.90,
    ]);

    echo "Produit ajouté (ID : " . $pdo->lastInsertId() . ")";

} catch (PDOException $e) {
    error_log("Erreur SQL : " . $e->getMessage());
    echo "Une erreur est survenue. Veuillez réessayer.";
}
?>
```

---

# 10. Résumé des opérations CRUD

| Opération | SQL | Méthode PDO |
|-----------|-----|-------------|
| **Create** | `INSERT INTO ... VALUES (...)` | `prepare()` + `execute()` + `lastInsertId()` |
| **Read** | `SELECT ... FROM ... WHERE ...` | `prepare()` + `execute()` + `fetch()` / `fetchAll()` |
| **Update** | `UPDATE ... SET ... WHERE ...` | `prepare()` + `execute()` + `rowCount()` |
| **Delete** | `DELETE FROM ... WHERE ...` | `prepare()` + `execute()` + `rowCount()` |

# 11. Règles de sécurité - Récapitulatif

| Règle | Justification |
|-------|--------------|
| Stocker les credentials dans `.env` | Ne pas exposer les mots de passe dans le code |
| Ajouter `.env` au `.gitignore` | Éviter la fuite de credentials sur Git |
| Toujours utiliser des requêtes préparées | Protection contre les injections SQL |
| Ne jamais concaténer des données utilisateur dans une requête SQL | Même protection |
| Utiliser `PDO::ERRMODE_EXCEPTION` | Détecter toutes les erreurs SQL |
| Désactiver `PDO::ATTR_EMULATE_PREPARES` | Utiliser les vraies requêtes préparées du SGBD |
| Journaliser les erreurs avec `error_log()` | Ne pas exposer les détails techniques à l'utilisateur |
| Valider/filtrer les entrées avec `filter_input()` | Valider avant d'insérer |


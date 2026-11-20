# PHP - Authentification des utilisateurs

> * Auteur : Gwénaël LAURENT
> * Date : 28/04/2026
> * **Prérequis :** PDO (04_PHP_base_de_donnees_PDO.md), formulaires (05_PHP_formulaires.md), sessions (06_PHP_sessions.md).

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


- [PHP - Authentification des utilisateurs](#php---authentification-des-utilisateurs)
- [1. Vue d'ensemble](#1-vue-densemble)
- [2. Structure du projet](#2-structure-du-projet)
- [3. Préparation de la base de données](#3-préparation-de-la-base-de-données)
- [4. Hashage des mots de passe](#4-hashage-des-mots-de-passe)
- [5. Inscription (`inscription.php`)](#5-inscription-inscriptionphp)
- [6. Connexion (`connexion.php`)](#6-connexion-connexionphp)
- [7. Protéger une page](#7-protéger-une-page)
- [8. Déconnexion (`deconnexion.php`)](#8-déconnexion-deconnexionphp)
- [9. Résumé du flux complet](#9-résumé-du-flux-complet)
- [10. Règles de sécurité - Récapitulatif](#10-règles-de-sécurité---récapitulatif)


# 1. Vue d'ensemble

L'authentification permet de vérifier l'identité d'un utilisateur avant de lui donner accès à des pages ou des fonctionnalités protégées.

```
Utilisateur
    │
    ▼
Formulaire de connexion
    │
    ▼
Vérification en base de données (PDO)
    │
    ▼
Création de la session
    │
    ▼
Accès aux pages protégées
    │
    ▼
Déconnexion
```

---

# 2. Structure du projet

```
projet/
├── .env                        ← Credentials BDD (jamais dans Git)
├── .gitignore
├── config/
│   └── db_connect.php          ← Connexion PDO
├── public/
│   ├── connexion.php           ← Formulaire de connexion + traitement
│   ├── deconnexion.php         ← Déconnexion
│   ├── inscription.php         ← Création de compte
│   └── tableau_de_bord.php     ← Exemple de page protégée
└── templates/
    └── layout.php
```

---

# 3. Préparation de la base de données

```sql
CREATE TABLE utilisateurs (
    id           INT AUTO_INCREMENT PRIMARY KEY,
    nom          VARCHAR(100)         NOT NULL,
    email        VARCHAR(255) UNIQUE  NOT NULL,
    mot_de_passe VARCHAR(255)         NOT NULL,  -- Hash bcrypt, JAMAIS le mot de passe en clair
    role         ENUM('user','admin') NOT NULL DEFAULT 'user',
    cree_le      DATETIME             NOT NULL DEFAULT CURRENT_TIMESTAMP
);
```

> **Règle fondamentale :** Ne jamais stocker un mot de passe en clair. Uniquement son **hash** produit par `password_hash()`.

---

# 4. Hashage des mots de passe

PHP intègre nativement `password_hash()` qui utilise l'algorithme **bcrypt** par défaut. Bcrypt est conçu pour être lent, ce qui le rend résistant aux attaques par force brute. Il intègre automatiquement un **sel aléatoire** : deux appels avec le même mot de passe produisent des hashs différents.

```php
<?php
// Créer un hash (lors de l'inscription)
$hash = password_hash("MonMotDePasse123!", PASSWORD_DEFAULT);
// Résultat : "$2y$12$abc123..." (60 caractères environ)

// Vérifier un mot de passe (lors de la connexion)
if (password_verify("MonMotDePasse123!", $hash)) {
    echo "Mot de passe correct";
} else {
    echo "Mot de passe incorrect";
}
?>
```

> **Important :** Ne jamais comparer les mots de passe avec `==` ou `===`. Toujours utiliser `password_verify()`.

---

# 5. Inscription (`inscription.php`)

```php
<?php
declare(strict_types=1);
session_start();
require_once __DIR__ . '/../config/db_connect.php';

$erreurs = [];
$succes  = false;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    // Récupération et validation
    $nom  = trim(filter_input(INPUT_POST, 'nom',   FILTER_SANITIZE_SPECIAL_CHARS) ?? '');
    $email = trim(filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL)        ?? '');
    $mdp  =      $_POST['mot_de_passe']  ?? '';
    $mdp2 =      $_POST['mot_de_passe2'] ?? '';

    if (strlen($nom) < 2)   $erreurs['nom']  = "Nom trop court (2 caractères minimum).";
    if (!$email)             $erreurs['email'] = "Adresse email invalide.";
    if (strlen($mdp) < 8)   $erreurs['mdp']  = "Mot de passe : 8 caractères minimum.";
    if ($mdp !== $mdp2)      $erreurs['mdp2'] = "Les mots de passe ne correspondent pas.";

    if (empty($erreurs)) {
        try {
            $pdo = getConnection();

            // Vérifier si l'email est déjà utilisé
            $stmt = $pdo->prepare("SELECT id FROM utilisateurs WHERE email = :email");
            $stmt->execute([':email' => $email]);

            if ($stmt->fetch()) {
                $erreurs['email'] = "Cette adresse email est déjà utilisée.";
            } else {
                // Hasher le mot de passe avant stockage
                $hash = password_hash($mdp, PASSWORD_DEFAULT);

                $stmt = $pdo->prepare(
                    "INSERT INTO utilisateurs (nom, email, mot_de_passe)
                     VALUES (:nom, :email, :hash)"
                );
                $stmt->execute([
                    ':nom'   => $nom,
                    ':email' => $email,
                    ':hash'  => $hash,
                ]);

                $succes = true;
            }
        } catch (\PDOException $e) {
            error_log("Erreur inscription : " . $e->getMessage());
            $erreurs['global'] = "Une erreur est survenue. Réessayez.";
        }
    }
}
?>
<!DOCTYPE html>
<html lang="fr">
<head><meta charset="UTF-8"><title>Inscription</title></head>
<body>
<h1>Créer un compte</h1>

<?php if ($succes): ?>
    <p style="color:green">Compte créé ! <a href="connexion.php">Se connecter</a></p>
<?php else: ?>

    <?php if (isset($erreurs['global'])): ?>
        <p style="color:red"><?= htmlspecialchars($erreurs['global']) ?></p>
    <?php endif; ?>

    <form method="POST" action="">
        <div>
            <label>Nom :
                <input type="text" name="nom"
                       value="<?= htmlspecialchars($_POST['nom'] ?? '') ?>">
            </label>
            <?php if (isset($erreurs['nom'])): ?>
                <span style="color:red"><?= htmlspecialchars($erreurs['nom']) ?></span>
            <?php endif; ?>
        </div>
        <div>
            <label>Email :
                <input type="email" name="email"
                       value="<?= htmlspecialchars($_POST['email'] ?? '') ?>">
            </label>
            <?php if (isset($erreurs['email'])): ?>
                <span style="color:red"><?= htmlspecialchars($erreurs['email']) ?></span>
            <?php endif; ?>
        </div>
        <div>
            <label>Mot de passe (8 car. min.) :
                <input type="password" name="mot_de_passe">
            </label>
            <?php if (isset($erreurs['mdp'])): ?>
                <span style="color:red"><?= htmlspecialchars($erreurs['mdp']) ?></span>
            <?php endif; ?>
        </div>
        <div>
            <label>Confirmer le mot de passe :
                <input type="password" name="mot_de_passe2">
            </label>
            <?php if (isset($erreurs['mdp2'])): ?>
                <span style="color:red"><?= htmlspecialchars($erreurs['mdp2']) ?></span>
            <?php endif; ?>
        </div>
        <button type="submit">Créer le compte</button>
    </form>

<?php endif; ?>
</body>
</html>
```

---

# 6. Connexion (`connexion.php`)

```php
<?php
declare(strict_types=1);
session_start();
require_once __DIR__ . '/../config/db_connect.php';

// Déjà connecté ? Redirection directe
if (isset($_SESSION['utilisateur_id'])) {
    header('Location: tableau_de_bord.php');
    exit;
}

$erreur = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    $email = trim(filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL) ?? '');
    $mdp   = $_POST['mot_de_passe'] ?? '';

    if ($email && $mdp) {
        try {
            $pdo  = getConnection();
            $stmt = $pdo->prepare(
                "SELECT id, nom, mot_de_passe, role
                 FROM utilisateurs WHERE email = :email"
            );
            $stmt->execute([':email' => $email]);
            $user = $stmt->fetch();

            if ($user && password_verify($mdp, $user['mot_de_passe'])) {

                // Connexion réussie - régénérer l'ID de session
                session_regenerate_id(true);

                $_SESSION['utilisateur_id']  = $user['id'];
                $_SESSION['utilisateur_nom'] = $user['nom'];
                $_SESSION['role']            = $user['role'];
                $_SESSION['connexion_le']    = time();

                header('Location: tableau_de_bord.php');
                exit;

            } else {
                // Message générique : ne pas préciser si c'est l'email ou le mot de passe
                $erreur = "Email ou mot de passe incorrect.";
            }

        } catch (\PDOException $e) {
            error_log("Erreur connexion : " . $e->getMessage());
            $erreur = "Une erreur est survenue. Réessayez.";
        }

    } else {
        $erreur = "Email ou mot de passe incorrect.";
    }
}
?>
<!DOCTYPE html>
<html lang="fr">
<head><meta charset="UTF-8"><title>Connexion</title></head>
<body>
<h1>Connexion</h1>

<?php if ($erreur): ?>
    <p style="color:red"><?= htmlspecialchars($erreur) ?></p>
<?php endif; ?>

<form method="POST" action="">
    <div>
        <label>Email :
            <input type="email" name="email" required
                   value="<?= htmlspecialchars($_POST['email'] ?? '') ?>">
        </label>
    </div>
    <div>
        <label>Mot de passe :
            <input type="password" name="mot_de_passe" required>
        </label>
    </div>
    <button type="submit">Se connecter</button>
</form>
<p><a href="inscription.php">Créer un compte</a></p>
</body>
</html>
```

**Points importants :**
- Le message d'erreur est **générique** : on ne précise jamais si c'est l'email ou le mot de passe qui est faux - cela évite l'énumération des comptes existants
- `session_regenerate_id(true)` est appelé juste après la connexion réussie pour prévenir la **fixation de session**

---

# 7. Protéger une page

Chaque page réservée aux utilisateurs connectés doit vérifier la session en tout début de script :

```php
<?php
declare(strict_types=1);
session_start();

// Garde : redirige vers la connexion si non connecté
if (!isset($_SESSION['utilisateur_id'])) {
    header('Location: /connexion.php');
    exit;
}

// Garde par rôle (optionnel)
if ($_SESSION['role'] !== 'admin') {
    http_response_code(403);
    die("Accès refusé.");
}

$nom = htmlspecialchars($_SESSION['utilisateur_nom']);
?>
<!DOCTYPE html>
<html lang="fr">
<head><meta charset="UTF-8"><title>Tableau de bord</title></head>
<body>
<h1>Bienvenue, <?= $nom ?> !</h1>
<p>Rôle : <?= htmlspecialchars($_SESSION['role']) ?></p>
<a href="deconnexion.php">Se déconnecter</a>
</body>
</html>
```

> **Bonne pratique :** Centraliser la garde dans une fonction `exigerConnexion()` dans un fichier `config/auth.php` inclus dans toutes les pages protégées (voir document 07b).

---

# 8. Déconnexion (`deconnexion.php`)

```php
<?php
declare(strict_types=1);
session_start();

// Destruction propre en 3 étapes (voir document 06)
$_SESSION = [];

if (ini_get('session.use_cookies')) {
    $params = session_get_cookie_params();
    setcookie(
        session_name(), '',
        time() - 42000,
        $params['path'],
        $params['domain'],
        $params['secure'],
        $params['httponly']
    );
}

session_destroy();

header('Location: connexion.php');
exit;
?>
```

---

# 9. Résumé du flux complet

```
INSCRIPTION
  Formulaire ──▶ Validation PHP ──▶ password_hash() ──▶ INSERT en BDD

CONNEXION
  Formulaire ──▶ SELECT en BDD ──▶ password_verify() ──▶ session_regenerate_id()
             ──▶ $_SESSION['utilisateur_id'] = ...    ──▶ Redirection

PAGE PROTÉGÉE
  session_start() ──▶ isset($_SESSION['utilisateur_id']) ? ──▶ Accès ou redirection

DÉCONNEXION
  $_SESSION = [] ──▶ Suppression cookie ──▶ session_destroy() ──▶ Redirection
```

---

# 10. Règles de sécurité - Récapitulatif

| Règle | Justification |
|-------|--------------|
| `password_hash()` / `password_verify()` | Hashage sécurisé bcrypt - jamais MD5 ou SHA1 |
| Message d'erreur générique au login | Évite de révéler les comptes existants |
| `session_regenerate_id(true)` à la connexion | Protection contre la fixation de session |
| Vérifier `$_SESSION['utilisateur_id']` en tête de chaque page protégée | Empêche l'accès sans authentification |
| Destruction de session en 3 étapes | Nettoyage complet côté serveur ET navigateur |
| Ne jamais stocker le mot de passe en clair | En cas de fuite BDD, les mots de passe restent protégés |


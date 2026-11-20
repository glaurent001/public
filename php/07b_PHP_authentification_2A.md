# PHP - Authentification avancée

> * Auteur : Gwénaël LAURENT
> * Date : 28/04/2026
> * **Prérequis :** Password_hash, sessions, PDO (07a_PHP_authentification_1A.md).  
> * Ce document enrichit le système existant avec : protection CSRF, fonctions centralisées, *remember me* et mise à jour automatique des hashs.

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


- [PHP - Authentification avancée](#php---authentification-avancée)
- [1. Limites du système 07a\_PHP\_authentification\_1A](#1-limites-du-système-07a_php_authentification_1a)
- [2. Nouvelle structure du projet](#2-nouvelle-structure-du-projet)
- [3. Mise à jour de la table `utilisateurs`](#3-mise-à-jour-de-la-table-utilisateurs)
- [4. Protection CSRF](#4-protection-csrf)
  - [4.1. Principe](#41-principe)
  - [4.2. `config/auth.php` - Fonctions centralisées](#42-configauthphp---fonctions-centralisées)
- [5. Connexion mise à jour (`connexion.php`)](#5-connexion-mise-à-jour-connexionphp)
- [6. Page protégée avec `exigerConnexion()`](#6-page-protégée-avec-exigerconnexion)
- [7. Déconnexion mise à jour (`deconnexion.php`)](#7-déconnexion-mise-à-jour-deconnexionphp)
- [8. Récapitulatif des apports de 07b vs 07a](#8-récapitulatif-des-apports-de-07b-vs-07a)
- [9. Règles de sécurité - Récapitulatif](#9-règles-de-sécurité---récapitulatif)


# 1. Limites du système 07a_PHP_authentification_1A

Le système de 07a est fonctionnel mais présente deux lacunes :

| Lacune | Risque |
|--------|--------|
| Pas de token CSRF sur les formulaires | Un site tiers peut forcer la soumission d'un formulaire au nom de l'utilisateur |
| Code de garde dupliqué dans chaque page | Erreur d'oubli sur une page = faille d'accès |
| Pas de persistance de connexion | L'utilisateur doit se reconnecter à chaque fermeture du navigateur |

---

# 2. Nouvelle structure du projet

```
projet/
├── .env
├── .gitignore
├── config/
│   ├── db_connect.php          ← Connexion PDO (inchangé)
│   └── auth.php                ← Fonctions centralisées (nouveau)
├── public/
│   ├── connexion.php           ← Mis à jour (CSRF + remember me)
│   ├── deconnexion.php         ← Mis à jour (suppression token BDD)
│   ├── inscription.php         ← Inchangé (07a)
│   └── tableau_de_bord.php     ← Mis à jour (exigerConnexion)
└── templates/
    └── layout.php
```

---

# 3. Mise à jour de la table `utilisateurs`

Ajouter les colonnes nécessaires au *remember me* :

```sql
ALTER TABLE utilisateurs
    ADD COLUMN remember_token    VARCHAR(64) NULL,
    ADD COLUMN token_expiration  DATETIME    NULL;
```

---

# 4. Protection CSRF

## 4.1. Principe

Une attaque **CSRF** (*Cross-Site Request Forgery*) consiste à faire soumettre à l'insu d'un utilisateur connecté une requête vers votre application, depuis un site tiers.

```
Site malveillant                     Votre application
       │                                    │
       │── <img src="monsite.fr/delete?id=5"> ──▶ Requête avec cookie de session
       │                                    │    L'utilisateur ne voit rien
       │                             Suppression exécutée !
```

**La parade :** inclure dans chaque formulaire un **token secret** connu uniquement du serveur et de la session en cours. Un site tiers ne peut pas le connaître.

```
Formulaire légitime :
  Session génère token ──▶ Champ caché dans le formulaire
  Soumission ──▶ PHP compare token soumis et token en session ──▶ OK

Attaque CSRF :
  Le site tiers ne connaît pas le token ──▶ Champ absent ou invalide ──▶ Rejeté
```

## 4.2. `config/auth.php` - Fonctions centralisées

```php
<?php
declare(strict_types=1);

// ============================================================
// CSRF
// ============================================================

/**
 * Génère un token CSRF et le stocke en session.
 * Retourne le token pour l'insérer dans le formulaire.
 */
function genererTokenCsrf(): string
{
    if (empty($_SESSION['csrf_token'])) {
        $_SESSION['csrf_token'] = bin2hex(random_bytes(32)); // 64 caractères hex
    }
    return $_SESSION['csrf_token'];
}

/**
 * Vérifie le token CSRF soumis.
 * Arrête le script avec une erreur 403 si invalide.
 */
function verifierTokenCsrf(): void
{
    $tokenSoumis  = $_POST['csrf_token']   ?? '';
    $tokenAttendu = $_SESSION['csrf_token'] ?? '';

    // hash_equals : comparaison en temps constant (résistant aux attaques temporelles)
    if (!hash_equals($tokenAttendu, $tokenSoumis)) {
        http_response_code(403);
        die("Requête invalide (token CSRF incorrect).");
    }

    // Token à usage unique : régénérer après vérification
    unset($_SESSION['csrf_token']);
}

// ============================================================
// GARDES D'ACCÈS
// ============================================================

/**
 * Redirige vers la connexion si l'utilisateur n'est pas connecté.
 * Mémorise l'URL demandée pour y revenir après login.
 */
function exigerConnexion(): void
{
    if (!isset($_SESSION['utilisateur_id'])) {
        $_SESSION['redirect_apres_login'] = $_SERVER['REQUEST_URI'];
        header('Location: /connexion.php');
        exit;
    }
}

/**
 * Vérifie qu'un utilisateur connecté possède le rôle requis.
 */
function exigerRole(string $role): void
{
    exigerConnexion();
    if ($_SESSION['role'] !== $role) {
        http_response_code(403);
        die("Accès refusé.");
    }
}

// ============================================================
// REMEMBER ME
// ============================================================

/**
 * Vérifie si un cookie "remember_me" valide est présent.
 * Si oui, reconnecte automatiquement l'utilisateur et effectue
 * une rotation du token (usage unique).
 */
function verifierRememberMe(PDO $pdo): void
{
    // Déjà connecté via session : rien à faire
    if (isset($_SESSION['utilisateur_id'])) {
        return;
    }

    $cookie = $_COOKIE['remember_me'] ?? '';
    if (!$cookie) {
        return;
    }

    // Format attendu : "userId:token"
    $parties = explode(':', $cookie, 2);
    if (count($parties) !== 2) {
        supprimerCookieRememberMe();
        return;
    }

    [$userId, $token] = $parties;
    $userId    = (int) $userId;
    $tokenHash = hash('sha256', $token);

    $stmt = $pdo->prepare(
        "SELECT id, nom, role FROM utilisateurs
         WHERE id = :id
           AND remember_token = :token
           AND token_expiration > NOW()"
    );
    $stmt->execute([':id' => $userId, ':token' => $tokenHash]);
    $user = $stmt->fetch();

    if ($user) {
        // Reconnexion automatique
        session_regenerate_id(true);
        $_SESSION['utilisateur_id']  = $user['id'];
        $_SESSION['utilisateur_nom'] = $user['nom'];
        $_SESSION['role']            = $user['role'];
        $_SESSION['connexion_le']    = time();

        // Rotation : générer un nouveau token (invalide l'ancien)
        enregistrerRememberMe($pdo, $user['id']);

    } else {
        // Token invalide ou expiré
        supprimerCookieRememberMe();
    }
}

/**
 * Génère un nouveau token remember_me, le stocke en BDD (hashé)
 * et envoie le cookie au navigateur.
 */
function enregistrerRememberMe(PDO $pdo, int $userId): void
{
    $token       = bin2hex(random_bytes(32));          // Token brut (jamais stocké en BDD)
    $tokenHash   = hash('sha256', $token);             // Hash stocké en BDD
    $expiration  = date('Y-m-d H:i:s', time() + 30 * 24 * 3600); // 30 jours

    $stmt = $pdo->prepare(
        "UPDATE utilisateurs
         SET remember_token = :token, token_expiration = :exp
         WHERE id = :id"
    );
    $stmt->execute([':token' => $tokenHash, ':exp' => $expiration, ':id' => $userId]);

    setcookie('remember_me', $userId . ':' . $token, [
        'expires'  => time() + 30 * 24 * 3600,
        'path'     => '/',
        'secure'   => true,      // HTTPS uniquement
        'httponly' => true,      // Non accessible via JavaScript
        'samesite' => 'Strict',  // Protection CSRF supplémentaire
    ]);
}

/**
 * Supprime le cookie remember_me et invalide le token en BDD.
 */
function supprimerRememberMe(PDO $pdo, int $userId): void
{
    $stmt = $pdo->prepare(
        "UPDATE utilisateurs
         SET remember_token = NULL, token_expiration = NULL
         WHERE id = :id"
    );
    $stmt->execute([':id' => $userId]);
    supprimerCookieRememberMe();
}

/**
 * Supprime uniquement le cookie côté navigateur.
 */
function supprimerCookieRememberMe(): void
{
    setcookie('remember_me', '', [
        'expires'  => time() - 3600,
        'path'     => '/',
        'secure'   => true,
        'httponly' => true,
        'samesite' => 'Strict',
    ]);
}
```

---

# 5. Connexion mise à jour (`connexion.php`)

```php
<?php
declare(strict_types=1);
session_start();
require_once __DIR__ . '/../config/db_connect.php';
require_once __DIR__ . '/../config/auth.php';

// Vérifier le cookie remember_me avant tout
try {
    $pdo = getConnection();
    verifierRememberMe($pdo);
} catch (\PDOException $e) {
    error_log("Erreur remember_me : " . $e->getMessage());
}

// Déjà connecté (session ou remember_me) ?
if (isset($_SESSION['utilisateur_id'])) {
    header('Location: tableau_de_bord.php');
    exit;
}

$erreur = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    verifierTokenCsrf();

    $email     = trim(filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL) ?? '');
    $mdp       = $_POST['mot_de_passe'] ?? '';
    $rememberMe = isset($_POST['remember_me']);

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

                session_regenerate_id(true);

                $_SESSION['utilisateur_id']  = $user['id'];
                $_SESSION['utilisateur_nom'] = $user['nom'];
                $_SESSION['role']            = $user['role'];
                $_SESSION['connexion_le']    = time();

                // Mise à jour silencieuse du hash si l'algorithme a évolué
                if (password_needs_rehash($user['mot_de_passe'], PASSWORD_DEFAULT)) {
                    $nouveauHash = password_hash($mdp, PASSWORD_DEFAULT);
                    $stmt = $pdo->prepare(
                        "UPDATE utilisateurs SET mot_de_passe = :hash WHERE id = :id"
                    );
                    $stmt->execute([':hash' => $nouveauHash, ':id' => $user['id']]);
                }

                // Activer le remember me si demandé
                if ($rememberMe) {
                    enregistrerRememberMe($pdo, $user['id']);
                }

                $redirect = $_SESSION['redirect_apres_login'] ?? 'tableau_de_bord.php';
                unset($_SESSION['redirect_apres_login']);
                header('Location: ' . $redirect);
                exit;

            } else {
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
    <input type="hidden" name="csrf_token" value="<?= genererTokenCsrf() ?>">

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
    <div>
        <label>
            <input type="checkbox" name="remember_me" value="1">
            Se souvenir de moi (30 jours)
        </label>
    </div>
    <button type="submit">Se connecter</button>
</form>
<p><a href="inscription.php">Créer un compte</a></p>
</body>
</html>
```

---

# 6. Page protégée avec `exigerConnexion()`

```php
<?php
declare(strict_types=1);
session_start();
require_once __DIR__ . '/../config/auth.php';

exigerConnexion();          // Redirige si non connecté
// exigerRole('admin');     // Décommenter pour restreindre aux admins

$nom = htmlspecialchars($_SESSION['utilisateur_nom']);
?>
<!DOCTYPE html>
<html lang="fr">
<head><meta charset="UTF-8"><title>Tableau de bord</title></head>
<body>
<h1>Bienvenue, <?= $nom ?> !</h1>
<p>Rôle : <?= htmlspecialchars($_SESSION['role']) ?></p>

<form method="POST" action="deconnexion.php">
    <input type="hidden" name="csrf_token" value="<?= genererTokenCsrf() ?>">
    <button type="submit">Se déconnecter</button>
</form>
</body>
</html>
```

> Le bouton de déconnexion est un formulaire `POST` avec token CSRF pour empêcher une déconnexion forcée depuis un site tiers.

---

# 7. Déconnexion mise à jour (`deconnexion.php`)

```php
<?php
declare(strict_types=1);
session_start();
require_once __DIR__ . '/../config/auth.php';
require_once __DIR__ . '/../config/db_connect.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    verifierTokenCsrf();
}

// Supprimer le token remember_me en BDD et le cookie
if (isset($_SESSION['utilisateur_id'])) {
    try {
        $pdo = getConnection();
        supprimerRememberMe($pdo, (int) $_SESSION['utilisateur_id']);
    } catch (\PDOException $e) {
        error_log("Erreur déconnexion : " . $e->getMessage());
    }
}

// Destruction propre de la session (3 étapes)
$_SESSION = [];
if (ini_get('session.use_cookies')) {
    $p = session_get_cookie_params();
    setcookie(session_name(), '', time() - 42000,
        $p['path'], $p['domain'], $p['secure'], $p['httponly']);
}
session_destroy();

header('Location: connexion.php');
exit;
?>
```

---

# 8. Récapitulatif des apports de 07b vs 07a

| Fonctionnalité | 07a (1ère année) | 07b (2ème année) |
|----------------|-----------------|-----------------|
| `password_hash` / `password_verify` | ✅ | ✅ |
| `session_regenerate_id` | ✅ | ✅ |
| Message d'erreur générique | ✅ | ✅ |
| Token CSRF sur les formulaires | ❌ | ✅ |
| `hash_equals` (anti timing-attack) | ❌ | ✅ |
| Fonctions centralisées `auth.php` | ❌ | ✅ |
| `exigerConnexion()` / `exigerRole()` | ❌ | ✅ |
| Redirection post-login mémorisée | ❌ | ✅ |
| Remember me (token rotatif, hashé) | ❌ | ✅ |
| `password_needs_rehash()` | ❌ | ✅ |
| CSRF sur la déconnexion | ❌ | ✅ |

---

# 9. Règles de sécurité - Récapitulatif

| Règle | Justification |
|-------|--------------|
| Token CSRF dans chaque formulaire sensible | Protection contre les requêtes forgées depuis un site tiers |
| `hash_equals()` pour comparer les tokens | Comparaison en temps constant - résistant aux attaques temporelles |
| Token CSRF à usage unique (régénéré après vérification) | Un token intercepté ne peut pas être réutilisé |
| `bin2hex(random_bytes(32))` pour générer les tokens | Source cryptographiquement sûre |
| Token remember_me hashé (SHA-256) en BDD | En cas de fuite BDD, les tokens sont inutilisables |
| Rotation du token à chaque utilisation | Un token volé ne peut servir qu'une fois |
| Cookie `httponly` + `secure` + `samesite=Strict` | Protection XSS, MITM et CSRF sur les cookies |
| `password_needs_rehash()` | Mise à jour silencieuse vers un algorithme plus récent |
| `exigerConnexion()` centralisée | Garantit qu'aucune page protégée n'est oubliée |


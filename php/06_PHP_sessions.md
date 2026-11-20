# PHP - Les sessions

> * Auteur : Gwénaël LAURENT
> * Date : 28/04/2026

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [PHP - Les sessions](#php---les-sessions)
- [1. Pourquoi les sessions ?](#1-pourquoi-les-sessions-)
- [2. Fonctionnement technique](#2-fonctionnement-technique)
- [3. Démarrer et utiliser une session](#3-démarrer-et-utiliser-une-session)
  - [3.1. `session_start()`](#31-session_start)
  - [3.2. Lire les données de session](#32-lire-les-données-de-session)
  - [3.3. Modifier et supprimer des variables de session](#33-modifier-et-supprimer-des-variables-de-session)
- [4. Détruire une session](#4-détruire-une-session)
- [5. Durée de vie d'une session](#5-durée-de-vie-dune-session)
  - [5.1. Par défaut](#51-par-défaut)
  - [5.2. Configurer la durée dans le code](#52-configurer-la-durée-dans-le-code)
  - [5.3. Détecter et gérer l'expiration par inactivité](#53-détecter-et-gérer-lexpiration-par-inactivité)
- [6. Régénérer l'ID de session](#6-régénérer-lid-de-session)
- [7. Exemple complet : compteur de visites](#7-exemple-complet--compteur-de-visites)
- [8. Stockage des sessions : au-delà des fichiers](#8-stockage-des-sessions--au-delà-des-fichiers)
- [9. Règles de sécurité - Récapitulatif](#9-règles-de-sécurité---récapitulatif)


# 1. Pourquoi les sessions ?

HTTP est un protocole **sans état** (*stateless*) : chaque requête est indépendante, le serveur ne se souvient pas des requêtes précédentes. Sans mécanisme supplémentaire, il est impossible de reconnaître un utilisateur d'une page à l'autre.

```
Sans session :
  Page 1 : utilisateur s'identifie    ──▶ Serveur (oublie immédiatement)
  Page 2 : "Qui êtes-vous ?"          ──▶ Serveur (ne sait pas)

Avec session :
  Page 1 : utilisateur s'identifie    ──▶ Serveur crée une session (ID unique)
                                           Envoie un cookie avec l'ID
  Page 2 : navigateur envoie le cookie ──▶ Serveur retrouve les données de session
                                           "C'est Alice !"
```

Les **sessions PHP** permettent de **stocker des données côté serveur** associées à un visiteur identifié par un identifiant de session (*session ID*) transmis via un cookie.

---

# 2. Fonctionnement technique

```
Navigateur                          Serveur PHP
    │                                    │
    │── GET /index.php ─────────────────▶│
    │                              session_start()
    │                              Crée un fichier session
    │                              Génère un ID unique
    │◀── Set-Cookie: PHPSESSID=abc123 ───│
    │                                    │
    │── GET /profil.php ────────────────▶│
    │   Cookie: PHPSESSID=abc123         │
    │                              session_start()
    │                              Charge le fichier session abc123
    │                              $_SESSION disponible
    │◀── HTML personnalisé ──────────────│
```

Par défaut, PHP stocke les fichiers de session dans `/tmp/` (Linux) ou dans le dossier temporaire système (Windows). Chaque session correspond à un fichier `sess_<id>`.

---

# 3. Démarrer et utiliser une session

## 3.1. `session_start()`

**`session_start()` doit être appelé en tout premier**, avant tout affichage HTML, dans chaque page qui utilise les sessions.

```php
<?php
session_start(); // Toujours en première instruction
declare(strict_types=1);

// Stockage de données en session
$_SESSION['utilisateur'] = 'Alice';
$_SESSION['role']        = 'admin';
$_SESSION['connexion']   = time(); // Timestamp de connexion

echo "Session démarrée. ID : " . session_id();
?>
```

## 3.2. Lire les données de session

```php
<?php
session_start();

if (isset($_SESSION['utilisateur'])) {
    echo "Bonjour, " . htmlspecialchars($_SESSION['utilisateur']);
} else {
    echo "Vous n'êtes pas connecté.";
}
?>
```

## 3.3. Modifier et supprimer des variables de session

```php
<?php
session_start();

// Modifier
$_SESSION['role'] = 'moderateur';

// Supprimer une seule variable
unset($_SESSION['connexion']);

// Vérifier l'existence
if (isset($_SESSION['utilisateur'])) {
    echo $_SESSION['utilisateur'];
}
?>
```

---

# 4. Détruire une session

La destruction propre d'une session (déconnexion) se fait en **trois étapes** :

```php
<?php
session_start();

// 1. Vider le tableau $_SESSION
$_SESSION = [];

// 2. Supprimer le cookie de session côté navigateur
if (ini_get('session.use_cookies')) {
    $params = session_get_cookie_params();
    setcookie(
        session_name(),
        '',
        time() - 42000,
        $params['path'],
        $params['domain'],
        $params['secure'],
        $params['httponly']
    );
}

// 3. Détruire les données côté serveur
session_destroy();

// Redirection vers la page de connexion
header('Location: /connexion.php');
exit;
?>
```

> `session_destroy()` seul ne suffit pas : il supprime le fichier session côté serveur, mais le cookie reste dans le navigateur. Sans les trois étapes, la session peut sembler active jusqu'à l'expiration du cookie.

---

# 5. Durée de vie d'une session

## 5.1. Par défaut

La session expire quand le navigateur est fermé (cookie de session = cookie de session sans durée d'expiration). Côté serveur, le fichier de session est nettoyé après un délai défini dans `php.ini` (`session.gc_maxlifetime`, 1440 secondes par défaut).

## 5.2. Configurer la durée dans le code

```php
<?php
// À appeler AVANT session_start()
ini_set('session.gc_maxlifetime', 3600); // 1 heure côté serveur

session_set_cookie_params([
    'lifetime' => 3600,       // 1 heure côté navigateur
    'path'     => '/',
    'secure'   => true,       // HTTPS uniquement
    'httponly' => true,       // Inaccessible via JavaScript
    'samesite' => 'Strict',   // Protection CSRF
]);

session_start();
?>
```

## 5.3. Détecter et gérer l'expiration par inactivité

```php
<?php
session_start();

$delai_inactivite = 1800; // 30 minutes

if (isset($_SESSION['derniere_activite'])) {
    $inactivite = time() - $_SESSION['derniere_activite'];

    if ($inactivite > $delai_inactivite) {
        // Session expirée par inactivité
        session_unset();
        session_destroy();
        header('Location: /connexion.php?raison=expiration');
        exit;
    }
}

$_SESSION['derniere_activite'] = time(); // Mise à jour à chaque requête
?>
```

---

# 6. Régénérer l'ID de session

L'**usurpation de session** (*session fixation*) est une attaque où un pirate force sa propre valeur de PHPSESSID à la victime. Pour s'en protéger, on **régénère l'ID de session** à chaque changement de niveau de privilège (connexion, élévation de droits…).

```php
<?php
session_start();

// Après vérification des identifiants :
session_regenerate_id(true); // true = supprimer l'ancienne session

$_SESSION['utilisateur'] = 'Alice';
$_SESSION['role']        = 'admin';
?>
```

> **Bonne pratique de sécurité :** Toujours appeler `session_regenerate_id(true)` juste après une connexion réussie.

---

# 7. Exemple complet : compteur de visites

```php
<?php
session_start();

// Initialisation si première visite
if (!isset($_SESSION['visites'])) {
    $_SESSION['visites'] = 0;
}

$_SESSION['visites']++;

echo "Vous avez visité cette page " . $_SESSION['visites'] . " fois.";
echo "<br><a href='?reset=1'>Réinitialiser</a>";

if (isset($_GET['reset'])) {
    $_SESSION['visites'] = 0;
    header('Location: ' . $_SERVER['PHP_SELF']);
    exit;
}
?>
```

---

# 8. Stockage des sessions : au-delà des fichiers

Par défaut, PHP stocke les sessions dans des fichiers. En production ou en environnement distribué (plusieurs serveurs), on préfère un stockage en base de données ou en cache :

| Stockage | Cas d'usage |
|----------|-------------|
| Fichiers (défaut) | Développement, serveur unique |
| Base de données | Partage entre serveurs, persistance |
| Redis / Memcached | Haute performance, expiration automatique |

La configuration se fait via `session.save_handler` et `session.save_path` dans `php.ini`.

---

# 9. Règles de sécurité - Récapitulatif

| Règle | Justification |
|-------|--------------|
| `session_start()` en première ligne | Évite l'erreur "headers already sent" |
| `session_regenerate_id(true)` à la connexion | Protection contre la fixation de session |
| `httponly: true` sur le cookie | Le cookie n'est pas accessible via JavaScript (protection XSS) |
| `secure: true` sur le cookie | Cookie transmis uniquement via HTTPS |
| `samesite: Strict` ou `Lax` | Protection contre les attaques CSRF |
| Détruire la session en 3 étapes | Nettoyage complet côté serveur ET navigateur |
| Ne pas stocker de données sensibles en clair en session | Préférer stocker un ID utilisateur et recharger depuis la BDD |
| Gérer l'expiration par inactivité | Limiter la fenêtre d'attaque en cas de vol de session |


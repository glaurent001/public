# PHP - Traitement des formulaires HTML

> * Auteur : Gwénaël LAURENT
> * Date : 28/04/2026

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [PHP - Traitement des formulaires HTML](#php---traitement-des-formulaires-html)
- [1. Principe général](#1-principe-général)
  - [1.1. Méthode GET vs POST](#11-méthode-get-vs-post)
- [2. Structure recommandée : formulaire auto-soumis](#2-structure-recommandée--formulaire-auto-soumis)
- [3. Champs texte, email et password](#3-champs-texte-email-et-password)
  - [3.1. Le formulaire HTML](#31-le-formulaire-html)
  - [3.2. Traitement PHP complet avec validation](#32-traitement-php-complet-avec-validation)
- [4. Cases à cocher et boutons radio](#4-cases-à-cocher-et-boutons-radio)
  - [4.1. Cases à cocher (`checkbox`)](#41-cases-à-cocher-checkbox)
  - [4.2. Boutons radio (`radio`)](#42-boutons-radio-radio)
  - [4.3. Conserver l'état après soumission](#43-conserver-létat-après-soumission)
- [5. Listes déroulantes (`select`)](#5-listes-déroulantes-select)
  - [5.1. Liste simple (un seul choix)](#51-liste-simple-un-seul-choix)
  - [5.2. Liste multiple (plusieurs choix)](#52-liste-multiple-plusieurs-choix)
- [6. Upload de fichier](#6-upload-de-fichier)
  - [6.1. Formulaire HTML](#61-formulaire-html)
  - [6.2. La superglobale `$_FILES`](#62-la-superglobale-_files)
  - [6.3. Codes d'erreur `$_FILES['champ']['error']`](#63-codes-derreur-_fileschamperror)
  - [6.4. Traitement sécurisé complet](#64-traitement-sécurisé-complet)
  - [6.5. Pourquoi renommer le fichier ?](#65-pourquoi-renommer-le-fichier-)
  - [6.6. Configuration `php.ini` à connaître](#66-configuration-phpini-à-connaître)
- [7. Fonctions de validation et filtrage utiles](#7-fonctions-de-validation-et-filtrage-utiles)
- [8. Règles de sécurité - Récapitulatif](#8-règles-de-sécurité---récapitulatif)


# 1. Principe général

Un formulaire HTML permet à l'utilisateur d'envoyer des données au serveur. PHP récupère ces données via les superglobales `$_GET` ou `$_POST` selon la méthode utilisée.

```
Navigateur                          Serveur PHP
    │                                    │
    │── <form method="POST"> ──────────▶ │
    │   (données saisies)                │
    │                              Traitement PHP
    │                              $_POST['champ']
    │                                    │
    │◀─────── Réponse HTML ─────────────│
```

## 1.1. Méthode GET vs POST

| Critère | `GET` | `POST` |
|---------|-------|--------|
| Données dans | L'URL (`?nom=val`) | Le corps de la requête |
| Visibilité | Visible dans la barre d'adresse | Non visible |
| Longueur | Limitée (~2000 caractères) | Illimitée |
| Mise en cache | Oui | Non |
| Usage typique | Recherche, filtres, pagination | Login, inscription, modification |

> **Règle de sécurité :** Toujours utiliser `POST` pour les données sensibles (mots de passe, données personnelles) et pour toute action qui modifie des données en base.

---

# 2. Structure recommandée : formulaire auto-soumis

Le pattern le plus courant est d'utiliser **un seul fichier PHP** qui affiche le formulaire ET traite les données. On teste la méthode HTTP pour distinguer les deux cas :

```php
<?php
declare(strict_types=1);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Traitement des données
} else {
    // Affichage du formulaire
}
?>
```

---

# 3. Champs texte, email et password

## 3.1. Le formulaire HTML

```html
<form method="POST" action="">
    <label for="nom">Nom :</label>
    <input type="text" id="nom" name="nom" required>

    <label for="email">Email :</label>
    <input type="email" id="email" name="email" required>

    <label for="password">Mot de passe :</label>
    <input type="password" id="password" name="password" required>

    <button type="submit">Envoyer</button>
</form>
```

> `action=""` signifie que le formulaire est soumis vers le fichier courant.

## 3.2. Traitement PHP complet avec validation

```php
<?php
declare(strict_types=1);

$erreurs = [];
$succes  = false;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    // --- Récupération et nettoyage des données ---
    $nom      = trim(filter_input(INPUT_POST, 'nom',      FILTER_SANITIZE_SPECIAL_CHARS) ?? '');
    $email    = trim(filter_input(INPUT_POST, 'email',    FILTER_VALIDATE_EMAIL)         ?? '');
    $password =      filter_input(INPUT_POST, 'password', FILTER_DEFAULT)                ?? '';

    // --- Validation ---
    if (strlen($nom) < 2) {
        $erreurs['nom'] = "Le nom doit contenir au moins 2 caractères.";
    }

    if ($email === '' || $email === false) {
        $erreurs['email'] = "L'adresse email est invalide.";
    }

    if (strlen($password) < 8) {
        $erreurs['password'] = "Le mot de passe doit contenir au moins 8 caractères.";
    }

    // --- Traitement si pas d'erreur ---
    if (empty($erreurs)) {
        // Ici : insertion en BDD, envoi email, etc.
        $succes = true;
    }
}
?>
<!DOCTYPE html>
<html lang="fr">
<head><meta charset="UTF-8"><title>Inscription</title></head>
<body>

<?php if ($succes): ?>
    <p style="color:green">Inscription réussie !</p>
<?php else: ?>

<form method="POST" action="">
    <div>
        <label for="nom">Nom :</label>
        <input type="text" id="nom" name="nom"
               value="<?= htmlspecialchars($_POST['nom'] ?? '') ?>">
        <?php if (isset($erreurs['nom'])): ?>
            <span style="color:red"><?= htmlspecialchars($erreurs['nom']) ?></span>
        <?php endif; ?>
    </div>

    <div>
        <label for="email">Email :</label>
        <input type="email" id="email" name="email"
               value="<?= htmlspecialchars($_POST['email'] ?? '') ?>">
        <?php if (isset($erreurs['email'])): ?>
            <span style="color:red"><?= htmlspecialchars($erreurs['email']) ?></span>
        <?php endif; ?>
    </div>

    <div>
        <label for="password">Mot de passe :</label>
        <input type="password" id="password" name="password">
        <?php if (isset($erreurs['password'])): ?>
            <span style="color:red"><?= htmlspecialchars($erreurs['password']) ?></span>
        <?php endif; ?>
    </div>

    <button type="submit">S'inscrire</button>
</form>

<?php endif; ?>
</body>
</html>
```

**Points importants :**
- `value="<?= htmlspecialchars($_POST['nom'] ?? '') ?>"` : les champs conservent leur valeur après une soumission invalide (confort utilisateur)
- Le mot de passe n'est **jamais** ré-affiché dans le champ `value` pour des raisons de sécurité
- Les messages d'erreur sont échappés avec `htmlspecialchars()`

---

# 4. Cases à cocher et boutons radio

## 4.1. Cases à cocher (`checkbox`)

Une case cochée envoie sa valeur ; une case non cochée **n'envoie rien** (la clé est absente de `$_POST`). On utilise donc `isset()` ou `??` pour la tester.

```html
<form method="POST" action="">
    <fieldset>
        <legend>Centres d'intérêt :</legend>
        <label><input type="checkbox" name="interets[]" value="reseau"> Réseau</label>
        <label><input type="checkbox" name="interets[]" value="cyber">  Cybersécurité</label>
        <label><input type="checkbox" name="interets[]" value="dev">    Développement</label>
        <label><input type="checkbox" name="interets[]" value="iot">    IoT</label>
    </fieldset>
    <button type="submit">Envoyer</button>
</form>
```

> Le suffixe `[]` dans `name="interets[]"` indique à PHP de regrouper toutes les valeurs cochées dans un **tableau**.

```php
<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    // $interets est un tableau des valeurs cochées, ou tableau vide si rien n'est coché
    $interets = $_POST['interets'] ?? [];

    // Valeurs autorisées (liste blanche)
    $valeurs_autorisees = ['reseau', 'cyber', 'dev', 'iot'];

    // Filtrer pour ne garder que les valeurs connues
    $interets = array_filter($interets, fn($v) => in_array($v, $valeurs_autorisees, true));

    if (empty($interets)) {
        echo "Aucun centre d'intérêt sélectionné.";
    } else {
        echo "Centres d'intérêt : " . implode(', ', array_map('htmlspecialchars', $interets));
    }
}
?>
```

## 4.2. Boutons radio (`radio`)

Un seul bouton radio peut être sélectionné par groupe (même `name`). Comme pour les cases, si aucun bouton n'est sélectionné, la clé est absente de `$_POST`.

```html
<form method="POST" action="">
    <fieldset>
        <legend>Niveau :</legend>
        <label><input type="radio" name="niveau" value="debutant">   Débutant</label>
        <label><input type="radio" name="niveau" value="intermediaire"> Intermédiaire</label>
        <label><input type="radio" name="niveau" value="avance">     Avancé</label>
    </fieldset>
    <button type="submit">Envoyer</button>
</form>
```

```php
<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    $niveaux_autorises = ['debutant', 'intermediaire', 'avance'];
    $niveau = $_POST['niveau'] ?? '';

    if (!in_array($niveau, $niveaux_autorises, true)) {
        echo "Niveau invalide ou non sélectionné.";
    } else {
        echo "Niveau choisi : " . htmlspecialchars($niveau);
    }
}
?>
```

## 4.3. Conserver l'état après soumission

Pour que la case ou le bouton reste coché après un rechargement :

```php
<!-- Case à cocher -->
<input type="checkbox" name="interets[]" value="cyber"
       <?= in_array('cyber', $_POST['interets'] ?? [], true) ? 'checked' : '' ?>>

<!-- Bouton radio -->
<input type="radio" name="niveau" value="avance"
       <?= ($_POST['niveau'] ?? '') === 'avance' ? 'checked' : '' ?>>
```

---

# 5. Listes déroulantes (`select`)

## 5.1. Liste simple (un seul choix)

```html
<form method="POST" action="">
    <label for="annee">Année BTS :</label>
    <select id="annee" name="annee">
        <option value="">-- Choisir --</option>
        <option value="1">1ère année</option>
        <option value="2">2ème année</option>
    </select>
    <button type="submit">Envoyer</button>
</form>
```

```php
<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    $annees_autorisees = ['1', '2'];
    $annee = $_POST['annee'] ?? '';

    if (!in_array($annee, $annees_autorisees, true)) {
        echo "Veuillez sélectionner une année.";
    } else {
        echo "Année sélectionnée : " . htmlspecialchars($annee);
    }
}
?>
```

Conserver la sélection après soumission :

```php
<option value="1" <?= ($_POST['annee'] ?? '') === '1' ? 'selected' : '' ?>>
    1ère année
</option>
```

## 5.2. Liste multiple (plusieurs choix)

```html
<select name="options[]" multiple size="4">
    <option value="wifi">Wi-Fi</option>
    <option value="bluetooth">Bluetooth</option>
    <option value="zigbee">Zigbee</option>
    <option value="lora">LoRa</option>
</select>
```

Le traitement est identique aux cases à cocher : `$_POST['options'] ?? []` retourne un tableau des valeurs sélectionnées.

---

# 6. Upload de fichier

## 6.1. Formulaire HTML

L'upload nécessite deux conditions côté HTML :
- `method="POST"` obligatoire
- `enctype="multipart/form-data"` obligatoire (sans cet attribut, le fichier n'est pas transmis)

```html
<form method="POST" action="" enctype="multipart/form-data">
    <label for="avatar">Photo de profil (JPG/PNG, max 2 Mo) :</label>
    <input type="file" id="avatar" name="avatar" accept=".jpg,.jpeg,.png">
    <button type="submit">Envoyer</button>
</form>
```

## 6.2. La superglobale `$_FILES`

Quand un fichier est soumis, PHP le place dans `$_FILES` :

```php
<?php
print_r($_FILES['avatar']);
/*
Array (
    [name]     => photo.jpg       ← Nom original côté client
    [type]     => image/jpeg      ← Type MIME déclaré par le navigateur (NON FIABLE)
    [tmp_name] => /tmp/phpAb3xYz  ← Chemin temporaire côté serveur
    [error]    => 0               ← 0 = pas d'erreur
    [size]     => 153284          ← Taille en octets
)
*/
?>
```

> **Important :** Le champ `type` de `$_FILES` est fourni par le navigateur et peut être falsifié. Il ne faut **jamais** s'y fier pour déterminer le type réel du fichier.

## 6.3. Codes d'erreur `$_FILES['champ']['error']`

| Code | Constante | Signification |
|------|-----------|---------------|
| `0` | `UPLOAD_ERR_OK` | Pas d'erreur |
| `1` | `UPLOAD_ERR_INI_SIZE` | Dépasse `upload_max_filesize` dans `php.ini` |
| `2` | `UPLOAD_ERR_FORM_SIZE` | Dépasse `MAX_FILE_SIZE` du formulaire |
| `4` | `UPLOAD_ERR_NO_FILE` | Aucun fichier sélectionné |

## 6.4. Traitement sécurisé complet

```php
<?php
declare(strict_types=1);

$erreur  = '';
$succes  = '';

// Dossier de destination (hors de la racine web de préférence)
$dossierUpload = __DIR__ . '/../uploads/';

// Types MIME réellement autorisés (vérifiés côté serveur)
$typesMimeAutorises = ['image/jpeg', 'image/png'];
$extensionsAutorisees = ['jpg', 'jpeg', 'png'];
$tailleMax = 2 * 1024 * 1024; // 2 Mo en octets

if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    // 1. Vérifier qu'un fichier a bien été envoyé sans erreur
    if (!isset($_FILES['avatar']) || $_FILES['avatar']['error'] !== UPLOAD_ERR_OK) {
        $erreur = "Aucun fichier reçu ou erreur lors de l'envoi (code : " . ($_FILES['avatar']['error'] ?? '?') . ").";
    } else {
        $fichier = $_FILES['avatar'];

        // 2. Vérifier la taille
        if ($fichier['size'] > $tailleMax) {
            $erreur = "Le fichier dépasse la taille maximale autorisée (2 Mo).";
        }

        // 3. Vérifier l'extension (d'après le nom original)
        $extension = strtolower(pathinfo($fichier['name'], PATHINFO_EXTENSION));
        if (!in_array($extension, $extensionsAutorisees, true)) {
            $erreur = "Extension non autorisée. Formats acceptés : JPG, PNG.";
        }

        // 4. Vérifier le type MIME RÉEL avec finfo (côté serveur, non falsifiable)
        $finfo    = new finfo(FILEINFO_MIME_TYPE);
        $typeMime = $finfo->file($fichier['tmp_name']);
        if (!in_array($typeMime, $typesMimeAutorises, true)) {
            $erreur = "Type de fichier non autorisé.";
        }

        // 5. Déplacer le fichier si aucune erreur
        if ($erreur === '') {
            // Générer un nom de fichier aléatoire (évite l'écrasement et l'exécution de scripts)
            $nomFichier = bin2hex(random_bytes(16)) . '.' . $extension;
            $destination = $dossierUpload . $nomFichier;

            // is_uploaded_file + move_uploaded_file : protection contre les attaques de type path traversal
            if (is_uploaded_file($fichier['tmp_name']) && move_uploaded_file($fichier['tmp_name'], $destination)) {
                $succes = "Fichier uploadé avec succès : " . htmlspecialchars($nomFichier);
            } else {
                $erreur = "Impossible de déplacer le fichier. Vérifiez les permissions du dossier.";
            }
        }
    }
}
?>
<!DOCTYPE html>
<html lang="fr">
<head><meta charset="UTF-8"><title>Upload</title></head>
<body>
<?php if ($erreur): ?>
    <p style="color:red"><?= htmlspecialchars($erreur) ?></p>
<?php endif; ?>
<?php if ($succes): ?>
    <p style="color:green"><?= $succes ?></p>
<?php endif; ?>
<form method="POST" action="" enctype="multipart/form-data">
    <label for="avatar">Photo (JPG/PNG, max 2 Mo) :
        <input type="file" id="avatar" name="avatar" accept=".jpg,.jpeg,.png">
    </label>
    <button type="submit">Envoyer</button>
</form>
</body>
</html>
```

## 6.5. Pourquoi renommer le fichier ?

Un attaquant pourrait tenter d'uploader un fichier nommé `shell.php` pour l'exécuter ensuite via le navigateur. Renommer avec `bin2hex(random_bytes(16))` élimine ce risque et évite les collisions de noms.

## 6.6. Configuration `php.ini` à connaître

| Directive | Rôle | Valeur typique |
|-----------|------|----------------|
| `upload_max_filesize` | Taille max d'un fichier | `2M` |
| `post_max_size` | Taille max de la requête POST entière | `8M` (doit être > `upload_max_filesize`) |
| `upload_tmp_dir` | Dossier temporaire | `/tmp` |
| `max_file_uploads` | Nombre max de fichiers par requête | `20` |

---

# 7. Fonctions de validation et filtrage utiles

| Fonction | Usage |
|----------|-------|
| `filter_input(INPUT_POST, 'champ', FILTER_VALIDATE_EMAIL)` | Valide un email |
| `filter_input(INPUT_POST, 'champ', FILTER_VALIDATE_INT)` | Valide un entier |
| `filter_input(INPUT_POST, 'champ', FILTER_VALIDATE_FLOAT)` | Valide un flottant |
| `filter_input(INPUT_POST, 'champ', FILTER_SANITIZE_SPECIAL_CHARS)` | Échappe les caractères spéciaux |
| `trim($chaine)` | Supprime les espaces en début/fin |
| `strlen($chaine)` | Longueur de la chaîne |
| `in_array($val, $liste, true)` | Vérifie qu'une valeur est dans une liste blanche |
| `empty($variable)` | Teste si vide, `null`, `0`, `""`, `[]`… |
| `isset($variable)` | Teste si la variable existe et n'est pas `null` |

---

# 8. Règles de sécurité - Récapitulatif

| Règle | Justification |
|-------|--------------|
| Toujours utiliser `POST` pour les données sensibles | Les données GET apparaissent dans les logs serveur et l'historique navigateur |
| Valider **côté serveur** même si validation HTML5 présente | La validation HTML peut être contournée par l'utilisateur |
| Utiliser une **liste blanche** pour radio/select/checkbox | Empêche l'injection de valeurs non prévues |
| `htmlspecialchars()` avant tout affichage | Protection XSS |
| `filter_input()` plutôt que `$_POST` direct | Validation et nettoyage intégrés |
| Ne jamais réafficher un mot de passe dans un `value=` | Éviter l'exposition du mot de passe dans le HTML |
| Tester `$_SERVER['REQUEST_METHOD'] === 'POST'` | S'assurer que le formulaire a bien été soumis |


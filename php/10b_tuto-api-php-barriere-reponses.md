# Tutoriel API PHP - Corrigé des questions de réflexion

> * Auteur : Gwénaël LAURENT
> * Date : 28/04/2026

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Tutoriel API PHP - Corrigé des questions de réflexion](#tutoriel-api-php---corrigé-des-questions-de-réflexion)
- [Question 1](#question-1)
- [Question 2](#question-2)
- [Question 3](#question-3)
- [Question 4](#question-4)
- [Question 5](#question-5)


# Question 1
**Pourquoi utilise-t-on `php://input` plutôt que `$_POST` pour lire le JSON ?**

`$_POST` ne fonctionne que pour deux formats d'encodage HTTP bien précis :
- `application/x-www-form-urlencoded` (formulaires HTML classiques)
- `multipart/form-data` (formulaires avec fichiers)

L'ESP32 envoie du JSON avec le header `Content-Type: application/json`. PHP ne sait pas parser ce format automatiquement, donc `$_POST` sera **toujours vide**.

`php://input` est un flux en lecture seule qui donne accès au **corps brut de la requête HTTP**, quel que soit son format. C'est lui qu'il faut utiliser pour lire du JSON :

```php
$body = file_get_contents('php://input');  // corps brut
$data = json_decode($body, true);          // décodage JSON → tableau PHP
```

---

# Question 2
**Pourquoi la clé API est-elle dans un header HTTP plutôt que dans le JSON ?**

Plusieurs raisons :

**Séparation des responsabilités** : le header transporte les informations *sur* la requête (qui parle, comment, avec quelle autorisation), le corps transporte les *données métier* (l'état de la barrière). Mélanger les deux rendrait le code moins lisible.

**Cohérence avec les standards** : les mécanismes d'authentification HTTP (Basic Auth, Bearer token, clé API) passent conventionnellement par les headers. Les outils comme Postman, curl ou les passerelles API s'appuient sur cette convention.

**Cas du GET** : une requête GET n'a pas de corps. Si la clé était dans le JSON, elle ne pourrait pas être envoyée en GET sans la mettre dans l'URL (ce qui l'exposerait dans les logs du serveur).

---

# Question 3
**Que se passerait-il si on écrivait directement `WHERE api_key = '$api_key'` ?**

Ce serait une faille d'**injection SQL**.

Un attaquant pourrait envoyer comme clé API la valeur :

```
' OR '1'='1
```

La requête construite deviendrait :

```sql
SELECT id, nom FROM barriere WHERE api_key = '' OR '1'='1'
```

Cette condition est **toujours vraie** : l'attaquant s'authentifie sans connaître aucune clé, et récupère la première barrière de la table.

Avec une requête préparée (`prepare` + `execute`), la valeur est transmise séparément du SQL. Le moteur MariaDB traite `$api_key` comme une **donnée**, jamais comme du code SQL. L'injection devient impossible.

```php
// Vulnérable ❌
$stmt = $pdo->query("SELECT id, nom FROM barriere WHERE api_key = '$api_key'");

// Sécurisé ✅
$stmt = $pdo->prepare('SELECT id, nom FROM barriere WHERE api_key = ?');
$stmt->execute([$api_key]);
```

---

# Question 4
**Pourquoi l'`id_barriere` vient-il de la base de données et non du JSON ?**

Parce qu'on ne fait **jamais confiance aux données envoyées par le client**.

Si on utilisait le `device_id` du JSON pour identifier la barrière, un attaquant pourrait :
- envoyer `"device_id": "2"` avec la clé API de la barrière 1
- enregistrer des faux logs sur n'importe quelle barrière

En utilisant l'`id` récupéré **après vérification de la clé API en base**, on garantit que :
- la barrière identifiée est bien celle qui correspond à la clé présentée
- aucune substitution n'est possible, même avec une requête forgée

```php
// On ignore $data['device_id'] du JSON
// On utilise $barriere['id'] issu de la vérification en BDD
$stmt->execute([$etat_bdd, $barriere['id']]);
```

C'est le principe du **zéro confiance côté client** : toute donnée venant du réseau est considérée comme potentiellement malveillante.

---

# Question 5
**Quelles améliorations pour un déploiement sur internet ?**

Plusieurs niveaux d'amélioration sont envisageables :

**HTTPS obligatoire**
En HTTP, la clé API transite en clair sur le réseau. N'importe qui capable d'intercepter le trafic (attaque man-in-the-middle) peut la récupérer. HTTPS chiffre la communication de bout en bout.

**Stockage sécurisé de la clé API côté serveur**
La clé devrait être stockée **hachée** en base (avec `password_hash()` / `password_verify()`), comme un mot de passe. Ainsi, même en cas de fuite de la base, les clés restent inutilisables.

**Rate limiting**
Limiter le nombre de requêtes par clé et par unité de temps pour éviter le flood ou le brute-force de clés.

**Journalisation des erreurs d'authentification**
Enregistrer les tentatives échouées (IP, timestamp) pour détecter des attaques.

**Clés API plus robustes**
Utiliser des clés générées aléatoirement et suffisamment longues :
```php
$api_key = bin2hex(random_bytes(32)); // 64 caractères hexadécimaux
```

**Validation de l'origine (optionnel)**
Filtrer les requêtes par adresse IP si les ESP32 ont des IP fixes ou connues.

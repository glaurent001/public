# ⏱️ Temporisation non-bloquante sur ESP32

> * Auteur : Gwénaël LAURENT
> * Date : 05/04/2026

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [⏱️ Temporisation non-bloquante sur ESP32](#️-temporisation-non-bloquante-sur-esp32)
- [1. Le problème avec `delay()`](#1-le-problème-avec-delay)
- [2. La solution : `millis()`](#2-la-solution--millis)
- [3. Exemple minimal - clignoter une LED](#3-exemple-minimal---clignoter-une-led)
- [4. Gérer plusieurs délais indépendants](#4-gérer-plusieurs-délais-indépendants)
- [5. Délai one-shot déclenché par un événement](#5-délai-one-shot-déclenché-par-un-événement)
  - [5.1. Activer le délai](#51-activer-le-délai)
  - [5.2. Variantes utiles](#52-variantes-utiles)
- [6. Débordement de `millis()` - faut-il s'inquiéter ?](#6-débordement-de-millis---faut-il-sinquiéter-)
- [7. ⚠️ Pièges courants](#7-️-pièges-courants)
- [8. Résumé du pattern](#8-résumé-du-pattern)
  - [8.1. Pour une exécution périodique](#81-pour-une-exécution-périodique)
  - [8.2. Pour une exécution une seule fois (One-shot)](#82-pour-une-exécution-une-seule-fois-one-shot)


# 1. Le problème avec `delay()`

```cpp
void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);  // ❌ Le µC est GELÉ pendant 1 seconde
    digitalWrite(LED_PIN, LOW);
    delay(1000);  // ❌ Impossible de faire autre chose pendant ce temps
}
```

`delay()` bloque complètement l'exécution : aucune lecture de capteur, aucune réponse réseau, aucun autre traitement ne peut avoir lieu.



# 2. La solution : `millis()`

`millis()` retourne le nombre de **millisecondes écoulées depuis le démarrage** du programme. L'idée est simple :

> "Est-ce que le temps écoulé depuis mon dernier événement dépasse ma durée d'attente ?"

```
temps actuel - temps du dernier événement  >=  durée souhaitée
```



# 3. Exemple minimal - clignoter une LED

```cpp
const uint8_t LED_PIN = 2;
const unsigned long INTERVALLE = 1000; // ms

unsigned long dernierChangement = 0;
bool etatLed = false;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    unsigned long maintenant = millis();

    if (maintenant - dernierChangement >= INTERVALLE) {
        dernierChangement = maintenant;   // on "recharge" le timer
        etatLed = !etatLed;
        digitalWrite(LED_PIN, etatLed);
    }

    // ✅ Tout ce qui suit s'exécute SANS attendre
}
```

> **Important :** on stocke `millis()` dans une variable locale `maintenant` en début de `loop()` pour avoir une valeur cohérente sur toute l'itération.



# 4. Gérer plusieurs délais indépendants

Chaque action a **sa propre variable de référence temporelle** :

```cpp
unsigned long tLed     = 0;
unsigned long tCapteur = 0;

const unsigned long DELAI_LED     = 500;
const unsigned long DELAI_CAPTEUR = 2000;

void loop() {
    unsigned long maintenant = millis();

    // Clignotement LED toutes les 500 ms
    if (maintenant - tLed >= DELAI_LED) {
        tLed = maintenant;
        // ... toggle LED
    }

    // Lecture capteur toutes les 2 s
    if (maintenant - tCapteur >= DELAI_CAPTEUR) {
        tCapteur = maintenant;
        // ... lire capteur
    }

    // Les deux s'exécutent indépendamment, sans se bloquer mutuellement
}
```



# 5. Délai one-shot déclenché par un événement
## 5.1. Activer le délai
Pour déclencher une **attente unique** à la suite d'un événement (mesure capteur, appui bouton, réception réseau…), on ajoute un **booléen d'armement** qui active le délai à la demande.

```cpp
unsigned long tDepart  = 0;
const unsigned long DELAI = 3000; // ms
bool attente = false;

void loop() {
    unsigned long maintenant = millis();

    // --- Déclenchement (ici : bouton, mais peut être n'importe quoi) ---
    if (evenementDetecte()) {
        tDepart = maintenant;  // on arme le one-shot
        attente = true;
        // 👉 Actions à exécuter AU DEBUT du délai
    }

    // --- Expiration du délai ---
    if (attente && (maintenant - tDepart >= DELAI)) {
        attente = false;       // on désarme
        // 👉 Actions à exécuter APRES le délai
    }
}
```

Ce qui se passe :

```
événement → attente = true → [3 secondes s'écoulent] → action → attente = false
```

## 5.2. Variantes utiles

**Re-armer à chaque nouvel événement** (repart de zéro si l'événement se reproduit) :

```cpp
if (evenementDetecte()) {
    tDepart = maintenant;  // remet le compteur à zéro
    attente = true;
}
```

**Ignorer les événements pendant l'attente** (one-shot strict) :

```cpp
if (evenementDetecte() && !attente) {  // ← on n'accepte que si inactif
    tDepart = maintenant;
    attente = true;
}
```

> Le booléen `attente` joue le rôle d'un **flag d'armement**, exactement comme un timer one-shot matériel.



# 6. Débordement de `millis()` - faut-il s'inquiéter ?

`millis()` est un `unsigned long` (32 bits) : il déborde au bout de **~49 jours** et repart à 0.

La soustraction `maintenant - dernierChangement` reste **mathématiquement correcte** même au débordement, grâce à l'arithmétique non signée :

```
// Exemple de débordement :
maintenant        = 5           // vient de repartir à 0
dernierChangement = 4294967290  // juste avant le débordement

// Calcul en unsigned long (modulo 2^32) :
5 - 4294967290 = 11  ✅  (et non -4294967285)
```

✅ Le pattern `maintenant - dernierRef >= DELAI` est **robuste au débordement**, à condition d'utiliser `unsigned long` pour toutes les variables.



# 7. ⚠️ Pièges courants

| Piège | Problème | Correction |
|---|---|---|
| `int` à la place de `unsigned long` | Débordement incorrect | Toujours `unsigned long` |
| `if (millis() >= dernierRef + DELAI)` | Plante au débordement | Utiliser la soustraction |
| Oublier de mettre à jour la référence | Le délai se redéclenche immédiatement | `dernierRef = maintenant;` à chaque déclenchement |
| Appeler `millis()` plusieurs fois dans `loop()` | Valeurs légèrement différentes | Stocker dans `maintenant` en début de `loop()` |
| Oublier de désarmer le flag one-shot | L'action se redéclenche en boucle | `attente = false;` dès l'expiration |



# 8. Résumé du pattern
> C'est le pattern de base de tout code Arduino/ESP32 **réactif et non-bloquant**.

## 8.1. Pour une exécution périodique

```cpp
unsigned long tRef = 0;
const unsigned long DELAI = 1000;

void loop() {
    unsigned long maintenant = millis();

    if (maintenant - tRef >= DELAI) {
        tRef = maintenant;
        // 👉 Action répétée périodiquement
    }
}
```

## 8.2. Pour une exécution une seule fois (One-shot)

```cpp
unsigned long tDepart = 0;
const unsigned long DELAI = 1000;
bool attente = false;

void loop() {
    unsigned long maintenant = millis();

    if (evenementDetecte() && !attente) {
        tDepart = maintenant;
        attente = true;
        // 👉 Actions à exécuter une seule fois AU DEBUT du délai
    }

    if (attente && (maintenant - tDepart >= DELAI)) {
        attente = false;
        // 👉 Actions à exécuter une seule fois APRES le délai
    }
}
```


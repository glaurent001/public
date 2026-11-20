(_Cours C++ vs Python : [retour sommaire](readme.md#introduction)_)
# Particularités d’un programme C++ sous Arduino

> * Auteur : Gwénaël LAURENT
> * Date : 07-09-2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Particularités d’un programme C++ sous Arduino](#particularités-dun-programme-c-sous-arduino)
  - [1. Structure principale : `setup()` et `loop()`](#1-structure-principale--setup-et-loop)
  - [2. Bibliothèques spécifiques](#2-bibliothèques-spécifiques)
  - [3. Fonctions pour l’E/S](#3-fonctions-pour-les)
  - [4. Pas de `main()`](#4-pas-de-main)
  - [5. Limitations et particularités](#5-limitations-et-particularités)
  - [6. Résumé comparatif C++ classique vs Arduino](#6-résumé-comparatif-c-classique-vs-arduino)
  - [7. Exemple : clignotement LED](#7-exemple--clignotement-led)
    - [1. Version Python (avec Raspberry Pi / GPIO)](#1-version-python-avec-raspberry-pi--gpio)
    - [2. Version Arduino (C++)](#2-version-arduino-c)
    - [3. Comparatif Python vs Arduino C++](#3-comparatif-python-vs-arduino-c)

> 📌 **Points clés :**
> 
> * L’Arduino simplifie la structure du programme, mais **tous les concepts C++ restent valides** : variables, fonctions, classes, pointeurs, types…
> * La particularité est la **boucle infinie via `loop()`** et l’utilisation d’**API matérielles Arduino** au lieu des entrées/sorties classiques.

## 1. Structure principale : `setup()` et `loop()`

Contrairement à un programme C++ classique qui commence par `int main()`, **Arduino** impose **deux fonctions principales** :

```cpp
void setup() {
    // Code exécuté une seule fois au démarrage
}

void loop() {
    // Code exécuté en boucle infinie
}
```

* `setup()` : initialisation des composants (broches, communication, variables, capteurs…).
* `loop()` : corps principal, s’exécute **en boucle infinie**, remplaçant la structure `while(true)` d’un programme C++ classique.


## 2. Bibliothèques spécifiques

Arduino possède ses propres bibliothèques pour gérer le matériel :

```cpp
#include <Arduino.h>       // inclus automatiquement
#include <Wire.h>          // communication I2C
#include <Servo.h>         // contrôle des servomoteurs
```

* Ces bibliothèques sont souvent **précompilées** et optimisées pour la carte Arduino.
* L’import se fait avec `#include`, comme en C++ classique.


## 3. Fonctions pour l’E/S

* **Entrées/Sorties numériques** :

```cpp
pinMode(13, OUTPUT);    // configure la broche 13 en sortie
digitalWrite(13, HIGH); // met la broche à l’état haut
digitalWrite(13, LOW);  // met la broche à l’état bas
```

* **Entrées analogiques** :

```cpp
int valeur = analogRead(A0);  // lit la tension sur la broche analogique A0
```

* **Sorties analogiques** (PWM) :

```cpp
analogWrite(9, 128);  // met la broche 9 à 50% de la tension
```


## 4. Pas de `main()`

* Arduino génère automatiquement une fonction `main()` qui appelle `setup()` puis `loop()`.
* Pour l’étudiant, il **n’a jamais besoin d’écrire `main()`**.

```cpp
// Programme Arduino minimal
void setup() {
    pinMode(13, OUTPUT);
}

void loop() {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
```

* `delay(ms)` : suspend le programme pendant un certain nombre de millisecondes (similaire à `time.sleep()` en Python).


## 5. Limitations et particularités

* Pas de console classique (`cin` / `cout`) : pour communiquer, on utilise **Serial** :

```cpp
void setup() {
    Serial.begin(9600);       // initialisation du port série
}

void loop() {
    Serial.println("Bonjour Arduino");
    delay(1000);
}
```

* Attention à la **mémoire limitée** (RAM, Flash).
* Le programme tourne **en continu**, donc pas de `return 0;`.


## 6. Résumé comparatif C++ classique vs Arduino

| Concept                 | C++ classique        | C++ Arduino                             |
| ----------------------- | -------------------- | --------------------------------------- |
| Point d’entrée          | `int main()`         | `setup()` et `loop()`                   |
| Boucle principale       | `while(true)`        | `loop()` appelée automatiquement        |
| Entrée / sortie         | `cin` / `cout`       | `digitalRead`, `digitalWrite`, `Serial` |
| Bibliothèques           | Standard C++ / STL   | Arduino.h, Wire.h, Servo.h, etc.        |
| Gestion du temps        | `sleep()` / `chrono` | `delay(ms)`                             |
| Retour de fonction main | `return 0;`          | Non nécessaire                          |




## 7. Exemple : clignotement LED
Voici un **exemple concret comparatif Python vs Arduino C++** pour illustrer le clignotement d’une LED.

### 1. Version Python (avec Raspberry Pi / GPIO)

```python
# Python (Raspberry Pi)
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)  # broche 18 en sortie

try:
    while True:
        GPIO.output(18, GPIO.HIGH)  # LED allumée
        time.sleep(1)               # 1 seconde
        GPIO.output(18, GPIO.LOW)   # LED éteinte
        time.sleep(1)
except KeyboardInterrupt:
    GPIO.cleanup()  # remet les broches à l'état initial
```

✅ Points à noter :

* Python utilise un **while True** pour la boucle infinie.
* `time.sleep(1)` pour temporiser (similaire à `delay()` en Arduino).
* Utilisation de bibliothèques matérielles spécifiques (`RPi.GPIO`).


### 2. Version Arduino (C++)

```cpp
// Arduino C++
void setup() {
    pinMode(13, OUTPUT);  // broche 13 en sortie (LED intégrée)
}

void loop() {
    digitalWrite(13, HIGH); // LED allumée
    delay(1000);             // 1 seconde
    digitalWrite(13, LOW);  // LED éteinte
    delay(1000);             // 1 seconde
}
```

✅ Points à noter :

* Pas besoin de `main()`, Arduino gère la boucle principale via `loop()`.
* `pinMode` initialise les broches, `digitalWrite` contrôle la LED.
* `delay(ms)` temporise en millisecondes.


### 3. Comparatif Python vs Arduino C++

| Concept                 | Python                        | Arduino C++                   |
| ----------------------- | ----------------------------- | ----------------------------- |
| Boucle infinie          | `while True:`                 | `loop()`                      |
| Initialisation GPIO     | `GPIO.setup(pin, GPIO.OUT)`   | `pinMode(pin, OUTPUT)`        |
| Allumer la LED          | `GPIO.output(pin, GPIO.HIGH)` | `digitalWrite(pin, HIGH)`     |
| Temporisation           | `time.sleep(1)`               | `delay(1000)`                 |
| Nettoyage / fin         | `GPIO.cleanup()`              | Non nécessaire                |
| Bibliothèque matérielle | `RPi.GPIO`                    | Incluse Arduino (`Arduino.h`) |




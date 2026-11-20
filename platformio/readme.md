# Ressources pour la programmation embarquée avec PlatformIO

> * Auteur : Gwénaël LAURENT
> * Date : 29/03/2026

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

![PlatformIO logo](img/logo-pio.png)

> Toutes ces ressources sont disponibles en ligne à cette adresse :\
https://gitlab.com/gwenael.laurent/public/ > "platformio"

## Tutoriels
### Installation de PlatformIO
* 0- [VScode - Installation de PlatformIO (arduino, ESP8266, ESP32)](../vscode/vscode-platformio.md)

### Présentation des kits de dévelopement
* 01- [Présentation des cartes ESP](01.presentation_cartes_esp.md)

### Kits de dévelopement - Brochage
* 01a- [Présentation de l'ESP8266 NodeMCU](01a.presentation-esp8266-nodemcu.md)
* 01b- [Présentation de l'ESP32 Wemos lolin-32 avec OLED](01b.presentation-esp32-wemos-lolin-32-OLED.md)
* 01c- [Présentation de l'ESP32-DevKitC V2](01c.presentation-esp32-devkitc-v2.md)
* 01d- [Présentation de l'ESP32-DevKitC V4](01d.presentation-esp32-devkitc-v4.md)
* 01e- [Présentation de l'ESP32-DevKit V1](01e.presentation-esp32-devkit-v1.md)
* 01z- [Créer un projet PlatformIO pour Arduino nano](01z.pio-arduinonano-start.md)

### Création de projet avec PlatformIO
* 02a-  [Créer un projet PlatformIO pour ESP8266](02a.projet-pio-esp8266-digital-io.md)
* 02b- [Créer un projet PlatformIO pour l'ESP32 Wemos lolin-32 avec OLED](02b.esp32-wemos-lolin-32-projet-digital-io.md)
* 02c- [Créer un projet PlatformIO pour l'ESP32-DevKitC V2](02c.esp32-devkitc-v2-projet-digital-io.md)
* 02d- [Créer un projet PlatformIO pour l'ESP32-DevKitC V4](02d.esp32-devkitc-v4-projet-digital-io.md)
* 02e- [Créer un projet PlatformIO pour l'ESP32-DevKit V1](02e.esp32-devkit-v1-projet-digital-io.md)
* 17- [ESP32 : Débogage](17.esp32-debogage.md)


### Gestion des bibliothèques
* 03- [PlatformIO : Gestion des bibliothèques](03.pio-gestion-des-bibliotheques.md)
* 04- [PlatformIO : ajouter une bibliothèque disponible dans les dépôts (ArduinoJson)](04.pio-ajouter-bibliotheque-arduinojson.md)
* [Créer et distribuer une bibliothèque précompilée pour ESP](library-create-and-use-precompiled-.a-lib.md)

### Ecrans et LEDs
* 05a- [Affichage sur écran OLED SSD1306 128x64](05a.pio-esp-OLED-ssd1306.md)
* 05b- [Affichage sur écran LCD12864 128x64](05b.pio-esp-LCD-lcd12864.md)
* 05c- [Affichage sur écran TFT ST7789 240x240 1.3"](05c.pio-ESP32-ecran-TFT-ST7789.md)
* 05d- [Affichage sur écran tactile TFT ILI9341 240*320 3.2"](05d.pio-ESP32-ecran-TFT-ILI9341.md)
* 05e- [Affichage sur écran e-paper](05e.pio-ESP32-ecran-e-paper.md)
* 09a- [Ruban de LEDs adressables WS2812 sur ESP8266](09a.pio-esp8266-led-strip.md)
* 09b- [Ruban de LEDs adressables WS2812 sur ESP32](09b.pio-esp32-led-strip.md)

### Gestion des communications
* 08- [Le PWM sur ESP32](08.pio-esp-pwm.md)
* 13- [ESP Serial et SoftwareSerial](13.pio-esp-serial.md)
* 14- [Bluetooth LE sur ESP32](14.pio-esp32-ble.md)
* 15a- [Client WiFi et client HTTP sur ESP8266](15a.pio-esp8266-wifi-http.md)
* 15b- [Client WiFi et client HTTP sur ESP32](15b.pio-esp32-wifi-http.md)
* 15c- [Annexe : Requête HTTP POST avec données](15c.Annexe-requete-http-post-avec-donnee.md)
* 16- [Client MQTT sur ESP](16.pio-esp-mqtt-client.md)

### Gestion de la mémoire flash
* 18- [ESP32 : Organisation de la mémoire flash](18.esp32-organisation-memoire-flash.md)
* 19- [ESP32 NVS - Stocker les paramètres de façon non volatile](19.esp32-non-volatile-storage.md)
* 20- [ESP32 SPIFFS - Stocker des fichiers sur la flash](20.esp32-spiffs-file-system.md)

### Optimiser la consommation électrique
* 21- [ESP32 Deep Sleep and Wake Up Sources](21.esp32-deep-sleep.md)
* 23- [Alimenter l'ESP32 sur batterie](23.alimenter-esp32-sur-batterie.md)
* 24- [Carte support pour le module ESP-WROOM-32](24.carte-support-esp-wroom-32.md)
* 25- [Mesurer la consommation de courant avec le kit NRF-PPK2](25.mesure-courant-avec-ppk2.md)

### Capteurs et actionneurs divers
* 06- [Capteur de température / pression BMP280 sur ESP32](06.pio-esp32-bmp280.md)
* 11- [Capteur de température TMP102 sur ESP8266](11.esp8266-tmp102.md)
* 07- [Télémètre à ultrasons SRF02 sur ESP32](07.pio-esp32-srf02.md)
* 30- [Télémètre de proximité ToF VL6180X](30.telemetre-VL6180.md)
* 10- [Lecteur de tag RFID MFRC522 sur ESP32](10.pio-esp32-RC522.md)
* 12- [Accéléromètre ADXL345 sur ESP32](12.pio-esp-adxl345.md)
* 26- [ESP32-CAM : Détection d'objets avec TinyML](26.esp32-cam-detection-d-objets.md)
* 27- [Gestion des interruptions sur ESP32](27.interruptions.md)
* 28- [Utilisation des Timers sur ESP32](28.timers.md)
* 29- [Utilisation un compteur d'impulsions sur ESP32](29.compteur-impulsions.md)



### Cours et généralités

* [Temporisation non-bloquante sur ESP32](temporisation-non-bloquante.md)
* [Le Bus I2C (Inter-Integrated Circuit)](bus-I2C.md)
* [Le Bus SPI (Serial Peripheral Interface) ](bus-SPI.md)
* 22- [Transistor de commutation MOSFET](22.transistor_mosfet.md)
* [ESP32 Erreur : Brownout detector was triggered](Error-ESP32-Brownout-detector-was-triggered.md)
* [Maintenance prédictive et analyse vibratoire](analyse-vibratoire.md)



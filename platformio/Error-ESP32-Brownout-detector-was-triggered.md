# ESP32 Erreur : Brownout detector was triggered

> * Auteur : Gwénaël LAURENT
> * Date : 06/04/2022

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


# Identification du problème
Ce problème peut apparaitre à l'exécution du programme. Le message **```Brownout detector was triggered```** est visible dans le moniteur série de cette façon :

```cmd
Brownout detector was triggered

ets Jun  8 2016 00:22:57

rst:0xc (SW_CPU_RESET),boot:0x17 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0018,len:4
load:0x3fff001c,len:1044
load:0x40078000,len:10124
load:0x40080400,len:5828
entry 0x400806a8
```

# Cause du problème
C'est un problème de consommation de courant. La plupart du temps il apparaît au démarrage de l'ESP, pendant l'initialisation du WiFi ou du Bluetooth.

Cela produit un pic de courant que l'alimentation n'est pas capable de fournir.

# Résolution du problème
Plusieurs solutions :
* Branchez le kit de développement sur un port USB2
* Changez le cable USB par un de meilleure qualité (avec une résistance plus faible)
* Utilisez un hub USB avec alimentation externe
* Branchez directement le cable USB sur une prise secteur (mais vous n'aurez plus de moniteur série)
* Dans votre code, démarrez progressivement les périphériques WiFi, Bluetooth, capteurs, actionneurs ... en insérant des delay() entre chaque démarrage.
* Changez de kit de développement (les régulateurs de tension intégrés ne sont pas toujours de bonne qualité et introduisent une perte de puissance)
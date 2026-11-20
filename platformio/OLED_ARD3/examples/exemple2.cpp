#include <Arduino.h>
#include "OLED_ARD3.hpp" //inclusion de la lib OLED_ARD3
#include "WiFi.h"        //pour afficher adresse MAC

OLED_ARD3 u8g2(/* addrI2C=*/ 0x78, /* sda=*/ 5, /* scl=*/ 4); //création d'un objet de la lib

void setup(void) {
  //initialisation de l'afficheur OLED
  u8g2.begin();
  //initialisation du WiFi en station
  WiFi.mode(WIFI_MODE_STA);
  //affichage sur les 5 lignes
  u8g2.SetLine(WiFi.macAddress(), 0);
  u8g2.ShowLogo();
  delay(2000);
  u8g2.SetLine("LAURENT", 1);
  u8g2.SetLine("Gwénaël", 2);
  u8g2.SetLine("BTS SNIR Armentières", 3);
  u8g2.SetLine(String(millis()), 4);
  delay(2000);
}

void loop(void) {
  //scroll sur les 4 dernières lignes
  u8g2.AddLineScroll(String(millis()));
  delay(1000);
}
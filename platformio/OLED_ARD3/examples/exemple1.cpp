#include <Arduino.h>
#include "OLED_ARD3.hpp" //inclusion de la lib OLED_ARD3

OLED_ARD3 u8g2(/* addrI2C=*/ 0x78, /* sda=*/ 5, /* scl=*/ 4); //création d'un objet de la lib

void setup(void)
{
  //initialisation de l'afficheur OLED
  u8g2.begin();
  //affichage sur les 4 premières lignes
  u8g2.SetLine("Lib OLED_ARD3", 0);
  u8g2.SetLine("LAURENT", 1);
  u8g2.SetLine("Gwénaël", 2);
  u8g2.SetLine("BTS SNIR - Armentières", 3);
}

void loop(void)
{
  //affichage sur la 5ème ligne
  u8g2.SetLine(String(millis()), 4);
  delay(1000);
}
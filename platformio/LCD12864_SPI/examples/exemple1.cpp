#include <Arduino.h>
#include "LCD12864_SPI.hpp" //inclusion de la lib LCD12864_SPI

//création d'un objet de la lib pour ESP-WROOM-32 :
// LCD12864_SPI u8g2( _clock, _data, _cs, _dc, _reset);
LCD12864_SPI u8g2(14, 13, 15, 16, 2);

void setup(void)
{
  //initialisation de l'afficheur OLED
  u8g2.begin();
  u8g2.setContrast(60);

  //affichage sur les 4 premières lignes
  u8g2.SetLine("Lib LCD12864_SPI", 0);
  u8g2.SetLine("LAURENT", 1);
  u8g2.SetLine("Gwénaël", 2);
  u8g2.SetLine("BTS SNIR Armentières", 3);
}

void loop(void)
{
  //affichage sur la 5ème ligne
  u8g2.SetLine(String(millis()), 4);
  delay(1000);
}
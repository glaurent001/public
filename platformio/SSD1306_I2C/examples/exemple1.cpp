#include <Arduino.h>
#include "SSD1306_I2C.hpp" //inclusion de la lib SSD1306_I2C

//création d'un objet de la lib : SSD1306_I2C u8g2(addrI2C, sda_pin, scl_pin);
SSD1306_I2C u8g2(0x78, 5, 4);

void setup(void)
{
  //initialisation de l'afficheur OLED
  u8g2.begin();
  //affichage sur les 4 premières lignes
  u8g2.SetLine("Lib SSD1306_I2C", 0);
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
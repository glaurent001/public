#include <Arduino.h>
#include "SSD1306_I2C.hpp" //inclusion de la lib SSD1306_I2C
#include "WiFi.h"          //pour afficher adresse MAC

//création d'un objet de la lib : SSD1306_I2C u8g2(addrI2C, sda_pin, scl_pin);
SSD1306_I2C u8g2(0x78, 5, 4);

void setup(void)
{
  //initialisation de l'afficheur OLED
  u8g2.begin();
  //initialisation du WiFi en station
  WiFi.mode(WIFI_MODE_STA);
  //Affichage de l'image XBM
  u8g2.ShowLogo();
  delay(2000);
  //affichage sur les 5 lignes
  u8g2.SetLine(WiFi.macAddress(), 0);
  u8g2.SetLine("LAURENT", 1);
  u8g2.SetLine("Gwénaël", 2);
  u8g2.SetLine("BTS SNIR Armentières", 3);
  u8g2.SetLine(String(millis()), 4);
  delay(2000);
}

void loop(void)
{
  //scroll sur les 4 dernières lignes
  u8g2.AddLineScroll(String(millis()));
  delay(1000);
}
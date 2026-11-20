#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

//création d'un objet de la lib U8G2 pour l'écran OLED SSD1306 connecté en I2C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, /*scl_pin=*/ 4, /*sda_pin=*/ 5);

void setup(void)
{
  u8g2.setI2CAddress(/*i2c_addr*/ 0x78); // Pour adapter l'adresse du périphérique I2C
  u8g2.begin();
}

void loop(void)
{
  //effacer le buffer d'affichage
  u8g2.clearBuffer();

  //Choisir la police de caractères et écrire du texte
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawUTF8(0, 15, "BTS SNIR");

  u8g2.setFont(u8g2_font_t0_12b_me); //21 caractères par ligne (8 Pixel Height +2 -2)
  u8g2.drawUTF8(0, 60, "Armentières");

  //Envoyer le buffer (affichage sur écran)
  u8g2.sendBuffer();
  delay(1000);
}

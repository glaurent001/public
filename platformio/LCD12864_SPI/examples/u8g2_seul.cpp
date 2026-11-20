#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

//création d'un objet de la lib U8G2 pour l'écran LCD 12864 connecté en SPI sur un ESP-WROOM-32 :
U8G2_ST7565_ZOLEN_128X64_F_4W_SW_SPI u8g2(U8G2_MIRROR, /*clock=*/14, /*data=*/13, /*cs=*/15, /*dc=*/16, /*reset=*/2);

void setup()
{
  u8g2.begin();
  u8g2.setContrast(60);
}

void loop()
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
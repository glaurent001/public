/**
 * Author : GwénaëlLAURENT 
 * Repository : https://gitlab.com/gwenael.laurent/public/-/tree/master/platformio
 * Date : 20/03/2022
 * Licence CC-BY-NC-SA (https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)
 * */

#include "LCD12864_SPI.hpp"

LCD12864_SPI::LCD12864_SPI(uint8_t _clock, uint8_t _data, uint8_t _cs, uint8_t _dc, uint8_t _reset) : U8G2_ST7565_ZOLEN_128X64_F_4W_SW_SPI(U8G2_MIRROR, _clock, _data, _cs, _dc, _reset)
{
    // Initialisation avec "U8g2 C Setup" 
    // https://github.com/olikraus/u8g2/wiki/u8g2setupc 
}

void LCD12864_SPI::show5lines()
{
    //effacer le buffer
    clearBuffer();
    if (whiteBackground == true)
    {
        setDrawColor(0); //fond "blanc"
        drawBox(0, 0, 128, 64);
        setFontMode(1);  // activate transparent font mode
        setDrawColor(2); //0 (clear pixel value in the display RAM), 1 (set pixel value) or 2 (XOR mode)
    }
    else
    {
        setDrawColor(1); //fond noir
        drawBox(0, 0, 128, 64);
        setFontMode(1);  // activate transparent font mode
        setDrawColor(2); //0 (clear pixel value in the display RAM), 1 (set pixel value) or 2 (XOR mode)
    }
    //Fixer la police de caractères
    setFont(u8g2_font_t0_12_me); //21 caractères par ligne (8 Pixel Height +2 -2)

    //Ligne 1
    drawUTF8(0, 10, bufferLines[0].c_str());
    drawHLine(0, 13, 128);

    //Ligne 2 à 5
    drawUTF8(0, 23, bufferLines[1].c_str());
    drawUTF8(0, 36, bufferLines[2].c_str());
    drawUTF8(0, 49, bufferLines[3].c_str());
    drawUTF8(0, 62, bufferLines[4].c_str());

    //Envoyer le buffer (affichage sur écran)
    sendBuffer();
}

void LCD12864_SPI::SetFirstLine(String prmText)
{
    SetLine(prmText, 0);
}

void LCD12864_SPI::SetLine(String prmText, int prmNumLigne)
{
    if (prmNumLigne >= 0 && prmNumLigne <= NBLIGNES)
    {
        bufferLines[prmNumLigne] = prmText;
    }
    show5lines();
}

void LCD12864_SPI::AddLineScroll(String prmText)
{
    AddLineScrollFrom(prmText, 1);
}

void LCD12864_SPI::AddLineScrollFrom(String prmText, int prmNumLigneDebut)
{
    if (prmNumLigneDebut >= 0 && prmNumLigneDebut < NBLIGNES)
    {
        for (int i = prmNumLigneDebut; i < NBLIGNES - 1; i++)
        {
            bufferLines[i] = bufferLines[i + 1];
        }

        bufferLines[NBLIGNES - 1] = prmText;
    }
    show5lines();
}

void LCD12864_SPI::ClearScreen()
{
    clearBuffer();
    sendBuffer();
}

void LCD12864_SPI::SetWhiteBackGround(bool prmColor)
{
    if (prmColor == false)
    {
        whiteBackground = false;
    }
    else
    {
        whiteBackground = true;
    }

    show5lines();
}

void LCD12864_SPI::ShowLogo()
{
    // cf https://gitlab.com/gwenael.laurent/public/blob/master/platformio/7.pio-ESP32-ecran-TFT-ILI9341.md#35-afficher-une-image-au-format-x-bitmap-xbm
    // et "how to create and use xbm files" //https://github.com/olikraus/u8g2/wiki/u8g2reference#drawxbm
    drawXBM(32, 0, eiffel_logo_width, eiffel_logo_height, (uint8_t *)eiffel_logo_bits);
    sendBuffer();
}

void LCD12864_SPI::Test()
{
    /***** accueil lib ready ****/
    /*********************************************************/
    ClearScreen();
    //https://github.com/olikraus/u8g2/wiki/u8g2reference#setfont
    // 14 Pixel Height
    setFont(u8g2_font_ncenB14_te);
    drawStr(10, 17, "BTS SNIR");

    //https://github.com/olikraus/u8g2/wiki/u8g2reference#drawglyph
    //u8g2_SetFont(&u8g2, u8g2_font_unifont_t_symbols);
    //u8g2_DrawGlyph(&u8g2, 56, 41, 0x23f3); /* sablier */

    setFont(u8g2_font_ncenB14_tr);
    drawStr(32, 60, "Ready");
    sendBuffer();

    delay(1000);

    /***** barre de progression ****/
    /*********************************************************/
    ClearScreen();

    //Affichage première ligne de texte
    setFont(u8g2_font_ncenB14_tr);
    drawStr(2, 17, "BTS SNIR");

    //Affichage ligne de progression
    drawBox(0, 26, 80, 6);
    drawFrame(0, 26, 100, 6);

    //Envoi de la maj de l'affichage
    sendBuffer();
    clearBuffer();
}

void LCD12864_SPI::PrintInCenter(String prmMessage)
{
    clearBuffer();
    //https://github.com/olikraus/u8g2/wiki/u8g2reference#setfont
    // 14 Pixel Height
    setFont(u8g2_font_ncenB18_tr);
    drawUTF8(20, 40, prmMessage.c_str());
    sendBuffer();
}

void LCD12864_SPI::PrintTwoValues(String txt1, String val1, String txt2, String val2)
{
    clearBuffer();
    //texte 1
    setFont(u8g2_font_t0_12_me);
    drawUTF8(0, 10, txt1.c_str());
    //drawHLine(0, 13, 128);

    //valeur 1
    setFont(u8g2_font_helvR14_tf);
    drawUTF8(15, 30, val1.c_str());

    //texte 2
    setFont(u8g2_font_t0_12_me);
    drawUTF8(0, 43, txt2.c_str());
    //drawHLine(0, 35, 128);

    //valeur 2
    setFont(u8g2_font_helvR14_tf);
    drawUTF8(15, 63, val2.c_str());

    sendBuffer();
}
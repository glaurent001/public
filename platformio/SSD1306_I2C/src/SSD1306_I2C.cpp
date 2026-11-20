/**
 * Author : GwénaëlLAURENT 
 * Repository : https://gitlab.com/gwenael.laurent/public/-/tree/master/platformio
 * Date : 20/03/2022
 * Licence CC-BY-NC-SA (https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)
 * */

#include "SSD1306_I2C.hpp"

SSD1306_I2C::SSD1306_I2C(uint8_t _address, uint8_t _sda, uint8_t _scl) : U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, _scl, _sda)
{
    /**** Initialisation avec "U8g2 C Setup" ******************/
    /**** https://github.com/olikraus/u8g2/wiki/u8g2setupc ****/
    /**********************************************************/
    setI2CAddress(_address); // Pour modifier l'adresse de l'esclave
}

void SSD1306_I2C::show5lines()
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

void SSD1306_I2C::SetFirstLine(String prmText)
{
    SetLine(prmText, 0);
}

void SSD1306_I2C::SetLine(String prmText, int prmNumLigne)
{
    if (prmNumLigne >= 0 && prmNumLigne <= NBLIGNES)
    {
        bufferLines[prmNumLigne] = prmText;
    }
    show5lines();
}

void SSD1306_I2C::AddLineScroll(String prmText)
{
    AddLineScrollFrom(prmText, 1);
}

void SSD1306_I2C::AddLineScrollFrom(String prmText, int prmNumLigneDebut)
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

void SSD1306_I2C::ClearScreen()
{
    clearBuffer();
    sendBuffer();
}

void SSD1306_I2C::SetWhiteBackGround(bool prmColor)
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

void SSD1306_I2C::ShowLogo()
{
    // cf https://gitlab.com/gwenael.laurent/public/blob/master/platformio/7.pio-ESP32-ecran-TFT-ILI9341.md#35-afficher-une-image-au-format-x-bitmap-xbm
    // et "how to create and use xbm files" //https://github.com/olikraus/u8g2/wiki/u8g2reference#drawxbm
    drawXBM(32, 0, eiffel_logo_width, eiffel_logo_height, (uint8_t *)eiffel_logo_bits);
    sendBuffer();
}

void SSD1306_I2C::Test()
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

void SSD1306_I2C::PrintInCenter(String prmMessage)
{
    clearBuffer();
    //https://github.com/olikraus/u8g2/wiki/u8g2reference#setfont
    // 14 Pixel Height
    setFont(u8g2_font_ncenB18_tr);
    drawUTF8(20, 40, prmMessage.c_str());
    sendBuffer();
}

void SSD1306_I2C::PrintTwoValues(String txt1, String val1, String txt2, String val2)
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
/**
 * Author : GwénaëlLAURENT 
 * Repository : https://gitlab.com/gwenael.laurent/public/-/tree/master/platformio
 * Date : 07/02/2022
 * Licence CC-BY-NC-SA (https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)
 * */

#include "OLED_ARD3.hpp"

OLED_ARD3::OLED_ARD3(uint8_t _address, uint8_t _sda, uint8_t _scl)
{
        /**** Initialisation avec "U8g2 C Setup" ****/
    /**** https://github.com/olikraus/u8g2/wiki/u8g2setupc ****/
    /*********************************************************/
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_arduino_sw_i2c, u8x8_gpio_and_delay_arduino); // init u8g2 structure
    u8x8_SetPin_SW_I2C(u8g2_GetU8x8(&u8g2), /* clock=*/_scl, /* data=*/_sda, /* reset=*/U8X8_PIN_NONE);
    u8x8_SetI2CAddress(&u8g2.u8x8, _address);   // 0x78 
    u8g2_InitDisplay(&u8g2);                    // send init sequence to the display, display is in sleep mode after this,
    u8g2_SetPowerSave(&u8g2, 0);                // wake up display
}

void OLED_ARD3::show5lines()
{
    //effacer le buffer
    clearBuffer();
    if (whiteBackground == true)
    {
        setDrawColor(1); //
        drawBox(0, 0, 128, 64);
        setFontMode(1);  // activate transparent font mode
        setDrawColor(2); //0 (clear pixel value in the display RAM), 1 (set pixel value) or 2 (XOR mode)
    }
    else
    {
        setDrawColor(0); //
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

void OLED_ARD3::SetFirstLine(String prmText)
{
    SetLine(prmText, 0);
}

void OLED_ARD3::SetLine(String prmText, int prmNumLigne)
{
    if (prmNumLigne >= 0 && prmNumLigne <= NBLIGNES)
    {
        bufferLines[prmNumLigne] = prmText;
    }
    show5lines();
}

void OLED_ARD3::AddLineScroll(String prmText)
{
    AddLineScrollFrom(prmText, 1);
}

void OLED_ARD3::AddLineScrollFrom(String prmText, int prmNumLigneDebut)
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

void OLED_ARD3::ClearScreen()
{
    clearBuffer();
    sendBuffer();
}

void OLED_ARD3::SetWhiteBackGround(bool prmColor)
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

void OLED_ARD3::ShowLogo()
{
    // see https://giltesa.com/en/2020/08/30/convert-images-to-xbm-for-showing-it-on-arduino-oled-screen
    // and https://convertio.co/fr/png-xbm/ (Convertisseur de PNG en XBM)
    // on how to create and use xbm files
    //https://github.com/olikraus/u8g2/wiki/u8g2reference#drawxbm
    drawXBM(32, 0, eiffel_logo_width, eiffel_logo_height, (uint8_t *)eiffel_logo_bits);
    sendBuffer();
}

void OLED_ARD3::Test()
{
    /***** accueil lib ready ****/
    /*********************************************************/
    ClearScreen();
    //https://github.com/olikraus/u8g2/wiki/u8g2reference#setfont
    // 14 Pixel Height
    setFont(u8g2_font_ncenB14_te);
    drawStr(10, 17, "OLED_ARD");

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
    drawStr(2, 17, "OLED_ARD");

    //Affichage ligne de progression
    drawBox(0, 26, 80, 6);
    drawFrame(0, 26, 100, 6);

    //Envoi de la maj de l'affichage
    sendBuffer();
    clearBuffer();
}

void  OLED_ARD3::PrintInCenter(String prmMessage){
    clearBuffer();
    //https://github.com/olikraus/u8g2/wiki/u8g2reference#setfont
    // 14 Pixel Height
    setFont(u8g2_font_ncenB18_tr);
    drawStr(20, 40, prmMessage.c_str());
    sendBuffer();

}

void OLED_ARD3::PrintTwoValues(String txt1, String val1, String txt2, String val2)
{
    clearBuffer();
    //texte 1
    setFont(u8g2_font_t0_12_me);
    drawUTF8(0, 10, txt1.c_str());
    //drawHLine(0, 13, 128);

    //valeur 1
    setFont(u8g2_font_helvR14_tf);
    drawStr(15,30, val1.c_str());

    //texte 2
    setFont(u8g2_font_t0_12_me);
    drawUTF8(0, 43, txt2.c_str());
    //drawHLine(0, 35, 128);

    //valeur 2
    setFont(u8g2_font_helvR14_tf);
    drawStr(15, 63, val2.c_str());

    sendBuffer();
}
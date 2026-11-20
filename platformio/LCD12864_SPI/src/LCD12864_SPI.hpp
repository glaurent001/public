/**
 * Author : GwénaëlLAURENT 
 * Repository : https://gitlab.com/gwenael.laurent/public/-/tree/master/platformio
 * Date : 20/03/2022
 * Licence CC-BY-NC-SA (https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)
 * */

#ifndef LCD12864_SPI_H
#define LCD12864_SPI_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include "eiffel-logo-64-64.h"

#define NBLIGNES 5

/**
	 * @brief  Classe d'affichage sur l'écran 
   * LCD12864 connecté en SPI (128x64 pixels)
   * Adaptation pour fonctionner sur ESP32 et ESP8266
   * avec le framework Arduino
   * Affichage avec buffer.
   * 
   * Dépendance : U8g2 by oliver (olikraus@gmail.com)
   * 
	 */
class LCD12864_SPI : public U8G2_ST7565_ZOLEN_128X64_F_4W_SW_SPI
{

private:

    /**
   *  @brief Tableau contenant le texte de chacune des lignes
   */
    String bufferLines[NBLIGNES];

    /**
   *  @brief état de couleur de fond
   */
    bool whiteBackground = true;

    /**
	 * @brief   Affiche les textes contenus dans bufferLines[]
	 * @return  Rien
	 */
    void show5lines();

public:
    /**
	 * @brief   Constructeur : Initialise l'accès de l'écran LCD
	 * @param   _clock SPI Clock line (14)
	 * @param   _data SPI MOSI (13)
	 * @param   _cs SPI Chip Select (15)
	 * @param   _dc SPI MISO (12)
     * @param   _reset Reset (16)
	 */
    LCD12864_SPI(uint8_t _clock, uint8_t _data, uint8_t _cs, uint8_t _dc, uint8_t _reset);

    /**
	 * @brief   Modifie le texte de la première ligne
	 * @param   prmText  Le nouveau texte
	 * @return  Rien
	 */
    void SetFirstLine(String prmText);

    /**
	 * @brief   Modifie le texte d'une ligne
	 * @param   prmText  Le nouveau texte
	 * @param   prmNumLigne  Le numéro de la ligne à modifier (0 à NBLIGNES)
	 * @return  Rien
	 */
    void SetLine(String prmText, int prmNumLigne = 0);

    /**
	 * @brief   Ajoute une nouvelle ligne en bas de l'écran. 
     * Les 4 anciennes lignes "scrollent" vers le haut
	 * @param   prmText  Le nouveau texte à afficher
	 * @return  Rien
	 */
    void AddLineScroll(String prmText);

    /**
	 * @brief   Ajoute une nouvelle ligne en bas de l'écran. 
     * Les anciennes lignes "scrollent" vers le haut
	 * @param   prmText  Le nouveau texte à afficher
	 * @param   prmNumLigneDebut  Le scroll des lignes s'effectue entre la ligne 
     * prmNumLigneDebut et NBLIGNES (par défaut, les 4 dernières lignes de l'écran "scrollent")
	 * @return  Rien
	 */
    void AddLineScrollFrom(String prmText, int prmNumLigneDebut = 1);

    /**
	 * @brief   Efface l'écran et le buffer d'affichage
	 * @return  Rien
	 */
    void ClearScreen();

    /**
	 * @brief   Modifie la couleur du fond
   *  @param prmColor : 0 pour texte Blanc/fond Noir
   *         prmColor : 1 pour texte Noir/fond Blanc 
	 * @return  Rien
	 */
    void SetWhiteBackGround(bool prmColor = false);

    /**
	 * @brief   Affiche le logo contenu dans logo.h.
     * Attention : il faut avoir de la RAM disponible sur l'ESP. Ne fonctionne pas sur ESP8266.
	 * @return  Rien
	 */
    void ShowLogo();

    void Test();
    
    /**
	 * @brief   Affichage d'un texte en gros au centre de l'écran
     * Utilisation : ex pour la température
     * u8g2.PrintInCenter((String)temperature + " " + "\xb0" + "C");
	 * @param   prmMessage  Texte à afficher
	 * @return  Rien
	 */
    void PrintInCenter(String prmMessage);

    /**
	 * @brief   Affichage de 2 valeurs avec 2 textes
     * Utilisation : ex pour la pression et la température
     * u8g2.PrintTwoValues("Pression atmos.", (String)pression + " hPa", "Température", (String)temperature + " " + "\xb0" + "C");
	 * @param   txt1  Texte accompagnant la 1ère valeur
     * @param   val1  1ère valeur
     * @param   txt2  Texte accompagnant la 2ème valeur
     * @param   val2  2ème valeur
	 * @return  Rien
	 */
    void PrintTwoValues(String txt1 = "", String val1 = "", String txt2 = "", String val2 = "");
};

#endif
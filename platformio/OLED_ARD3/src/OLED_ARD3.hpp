/**
 * Author : GwénaëlLAURENT 
 * Repository : https://gitlab.com/gwenael.laurent/public/-/tree/master/platformio
 * Date : 07/02/2022
 * Licence CC-BY-NC-SA (https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)
 * */

#ifndef OLED_ARD3_H
#define OLED_ARD3_H

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "eiffel-logo-64-64.h"

#define NBLIGNES 5

/**
	 * @brief  Classe d'affichage sur l'écran 
   * OLED sd1306 128x64 
   * Adaptation pour fonctionner sur ESP32 et ESP8266
   * WEMOS lolin 32 + OLED connecté en I2C (addr=0x78, SDA=GPIO5, SCL=GPIO4) 
   * avec le framework Arduino
   * Affichage avec buffer.
   * 
   * Dépendance : U8g2 by oliver (olikraus@gmail.com)
   * 
	 */
class OLED_ARD3 : public U8G2
{

private:

    /**
   *  @brief Tableau contenant le texte de chacune des lignes
   */
    String bufferLines[NBLIGNES];

    /**
   *  @brief état de couleur de fond
   */
    bool whiteBackground = false;

    /**
	 * @brief   Affiche les textes contenus dans bufferLines[]
	 * @return  Rien
	 */
    void show5lines();

public:
    /**
	 * @brief   Constructeur : Initialise l'accès de l'écran OLED
	 * @param   _address Adresse I2C de l'afficheur (0x78)
	 * @param   _sda broche SDA (5)
	 * @param   _scl Broche SCL (4)
	 */
    OLED_ARD3(uint8_t _address, uint8_t _sda, uint8_t _scl);

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
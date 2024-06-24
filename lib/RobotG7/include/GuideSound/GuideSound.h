/***********************************************************************************
 ***********************************************************************************
 ** @author : André MUTOKE MUSULE & Japhet TSHIMANGA BWENDE                       **
 ** @date : Mardi 29 Mai 2024                                                     **
 ** @name : GuideSound.h                                                          **
 ** @details : Ce fichier implémente le capteur ultra son                         **
 * *********************************************************************************
 * *********************************************************************************
*/


#pragma once
#ifndef GUIDE_SOUND_H
#define GUIDE_SOUND_H

#include <Arduino.h>
#include <Wire.h>

/// @brief GuideSound est la classe qui gere le capteur Ultra Son
class GuideSound
{
public :

    /// @brief Guidesound est le constructeur
    /// @param trig parametre de la pin trigger
    /// @param echo parametre de la pin echo
    GuideSound(uint8_t trig = 0, uint8_t echo = 0);
    /// @brief begin initialise la capteur ultra son
    void begin(); // Initialiser le programme;
    
    /// @brief recuperer la distance
    /// @return int la distance de l'obstacle
    uint32_t getDistance(){ captureDistance_and_Delay(); return this->m_distance;} 

    /// @brief Verifie le delay d'aller et retour du son emi
    /// @return uint32_t la duree du trajet
    uint32_t getDelayEcho(){ captureDistance_and_Delay(); return this->m_duree;} // POur nous retourner le temps de voyage capturé
private:
    uint8_t m_echo_pin; // Le pin pour recevoir les echos retours
    uint8_t m_trig_pin; // Le pin pour Emettre le son 

    uint32_t m_distance; // Pour calculer et concerver la distance
    uint32_t m_duree; 


    /// @brief Capturer la durer et calculer la distance
    void captureDistance_and_Delay();
    /// @brief Emettre un son
    /// @return int le son 
    int pulseEmit();

};

#endif // GUIDE_SOUND_H
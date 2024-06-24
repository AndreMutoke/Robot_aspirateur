/***********************************************************************************
 ***********************************************************************************
 ** @author : André MUTOKE MUSULE & Japhet TSHIMANGA BWENDE                       **
 ** @date : Mardi 29 Mai 2024                                                     **
 ** @name : CtrlWay.h                                                             **
 ** @details : Ce fichier implémente la prise de décison du chemin                **
 * *********************************************************************************
 * *********************************************************************************
*/

#pragma once
#ifndef CTRL_WAY
#define CTRL_WAY

#include <Arduino.h>
#include <ESP32Servo.h>

#include "../GuideSound/GuideSound.h"

/// @brief La structure Way contient les différents chemins de navigation
/// Nous avons DEVANT, DERRIERE, GAUCHE et DROITE
enum Way
{
    DEVANT,
    DERRIERE, 
    GAUCHE, 
    DROITE
};
typedef enum Way WAY;

/// @brief La class CtrlWay pour gerer la facon de réagir face à l'obstacle
class CtrlWay
{
public : 
    /// @brief CtrlWay(...) : constructeur de la classe
    /// @param pinAttached la pin de control
    CtrlWay(int pinAttached = 15);
    /// @brief Pour initialiser tout les composant attachés
    void begin();
    /// @brief POur choisir quel cote prendre après analyse des deux c\^otés
    /// @param CaptureObstacle Un objet de la classe GuideSound implémentant le capteur Ultra son
    /// @return WAY, le chemin choisit
    WAY theWayToget(GuideSound *CaptureObstacle); 

private :
    /// @brief La composante implementant le Servomoteur
    Servo m_pServo;

    uint8_t m_pin_to_attach;
    int posMotor;
    /// @brief Pour verifier la distance de l'obstacle à gauche
    /// @param CaptureObstacle Un objet de la classe GuideSound implémentant le capteur Ultra son
    /// @return int, la distnace de l'obstacle à gauche
    int seeToLeft(GuideSound *CaptureObstacle);
    /// @brief Pour verifier la distance de l'obstacle à droite
    /// @param CaptureObstacle Un objet de la classe GuideSound implémentant le capteur Ultra son
    /// @return int, la distnace de l'obstacle à droite
    int seeToRight(GuideSound *CaptureObstacle);
    /// @brief Pour calculer la moyenne
    /// @param tab Un tableau des valueur prise durant la phase d'analyse
    /// @return int, la moyenne des valeurs
    int MoyenneDistances(int tab[]);

};

#endif // CTRL_WAY
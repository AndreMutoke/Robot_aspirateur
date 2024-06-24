/***********************************************************************************
 ***********************************************************************************
 ** @author : André MUTOKE MUSULE & Japhet TSHIMANGA BWENDE                       **
 ** @date : Mardi 29 Mai 2024                                                     **
 ** @name : RobotG7.h                                                             **
 ** @details : Ce fichier implémente les élément composant le robot du système    **
 * *********************************************************************************
 * *********************************************************************************
*/




#ifndef ROBOT_GROUPE_7_L4_TLC
#define ROBOT_GROUPE_7_L4_TLC

#pragma once
#include <Arduino.h>

///Dabble bluetooth////
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULEpowerChannel
#include <DabbleESP32.h>
///FIN Dabble bluetooth////

#include "include/GuideSound/GuideSound.h"
#include "include/MotorControl/MotorControl.h"
#include "include/CtrlWay/CtrlWay.h"

#define ROBOTG7_FALSE 0
#define ROBOTG7_TRUE 1


enum Navigation
{
    MODE_START,
    MODE_AUTOMATIQUE,
    MODE_MANUEL
};
typedef enum Navigation MODE;

/// @brief La class RobotG7 pour gerer le Système du robot
class RobotG7
{
public :
    
    /// @brief RobotG7
    /// @param roue1 Pour lier le robot à la prémière roue du système
    /// @param roue2 Pour lier le robot à la seconde roue du système
    RobotG7(MOTOR *roue1 = NULL,
            MOTOR *roue2  = NULL, 
            int pinCtlMode = 5
            );
    /// @brief Methode begin() pour initialiser le système
    void begin();
    /// @brief Methode getDistanceObstacle() nous retournant la distance entre le robot et l'obstacle
    /// @return uint32_t (int)
    uint32_t getDistanceObstacle(){return this->m_gdSound->getDistance();}
    /// @brief pour récuperer le canal pwm de la roue 1
    /// @return int,  le numero du canal pwm
    int getpwmChannelRoue1(){return this->m_rouesRobots->getRoue1()->pwmChannel;}
    /// @brief pour récuperer le canal pwm de la roue 2
    /// @return int, le numéro du canal pwm
    int getpwmChannelRoue2(){return this->m_rouesRobots->getRoue2()->pwmChannel;}
    /// @brief Déplacement en avant
    void deplacementAvant();
    /// @brief Déplacement en arrière
    void deplacementArriere();
    /// @brief Tourner à gauche en avant
    void tourner_a_GaucheAvant();
    /// @brief Tourner à droite en avant
    void tourner_a_DroiteAvant();
    /// @brief Tourner à gauche en arrière
    void tourner_a_GaucheArriere();
    /// @brief Tourner à droite en arrière
    void tourner_a_DroiteArriere();
    /// @brief Stopper le déplacement
    void stopRobotG7();
    /// @brief Donner la commande de déplacement suivant les vitesses des roues
    /// @param vitesseChannel1 , la vitesse au prémier canal
    /// @param vitesseChannel2 , la vitesse au second canal
    void writeSpeedOnChannel(int vitesseChannel1, int vitesseChannel2);

    // ++++++++++++++++++++++++++ Control VITESSE ++++++++++++++++++++++++++++++++
    /// @brief retourner la vitesse du canal 1
    ///@return int, la vitesse du canal 1
    int getVitesseGauche(){return this->m_vitesseGauche;}
    /// @brief Retourner la vietesse du second canal
    /// @return int, la vitesse du second canal
    int getVitesseDroite(){return this->m_vitesseDroite;}
    /// @brief Insérer la vitesse au canal de gauche
    /// @param vit , la vitesse à insérer
    void setVitesseGauche(int vit){this->m_vitesseGauche = vit;}
    /// @brief Insérer la vitesse au canal de droite
    /// @param vit , la vitesse à insérer
    void setVitesseDroite(int vit){this->m_vitesseDroite = vit;}

    // ++++++++++++++++++ Control Navigation +++++++++++++++++++
    
    /// @brief Insérer le mode de navigation
    /// @param modeNav , le type de navigation
    void setNavigation(MODE modeNav){this->m_modeNav = modeNav;}

    // ++++++++++++++++ to control movement ++++++++++++++++++++++++++++

    /// @brief Savoir le type de chemin actuel
    /// @return WAY, le chemin de parcours
    WAY getSystemNavDirect(){return this->systemNav;}

    /// @brief La navigation su système
    void navigation();

    /// @brief Insérer le type de chemin à parcourir
    /// @param direction , la direction du chemin
    void setSystemNavDirect(WAY direction){ this->systemNav = direction;}
    // ++++++++++++++++++ Control Chemin +++++++++++++++++++++++++++++++

    /// @brief Ici le système fonctionne en mode automatique
    void systemRunningAuto();
    /// @brief Ici le système fonction en mode Manuel
    void systemRunningManual();
private :

    GuideSound *m_gdSound;
    MotorControl *m_rouesRobots;

    CtrlWay *cheminAprendre;

    MODE m_modeNav;

    WAY systemNav;

    int m_vitesseGauche;
    int m_vitesseDroite;
    /// @brief verifier l'etat de connection
    void inputProcess();
    /// @brief obtenir la vitesse de nagivation via le joystick
    void obtenirVitesseJoystick();

    /// @brief Gestion des command input
    void gamePadGestionCommand();
    void gamePadAutoGoStart();

    /// @brief etablir l'etat de connection
    void prepareRunningManual(){
        if(this->modeManualnotPrepared)
        {
            Dabble.begin("RobotG7");
            this->modeManualnotPrepared = ROBOTG7_FALSE; // 
        }
        
    }

    int modeManualnotPrepared;

    int enableCleanning;


    // int ctrlMode;

    // void runningAutoMode(uint32_t PreviousTime );

    // MODE m_modeNCaptureObstacleav;
};

#endif // ROBOT_GROUPE_7_L4_TLC
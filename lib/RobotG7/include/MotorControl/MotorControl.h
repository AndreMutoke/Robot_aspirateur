/***********************************************************************************
 ***********************************************************************************
 ** @author : André MUTOKE MUSULE & Japhet TSHIMANGA BWENDE                       **
 ** @date : Mardi 29 Mai 2024                                                     **
 ** @name : MotorControl.h                                                        **
 ** @details : Ce fichier implémente les engrenages moteurs pour les roues        **
 * *********************************************************************************
 * *********************************************************************************
*/

#pragma once
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>


/**
 * PROPRIETIES PWM
*/
#define FREQENCE_CONTROL 30000
#define PWMCHANNEL 0
#define PWMCHANNEL2 1
#define RESOLUTION 8
#define DUTY_CYCLE 170

/// @brief Structure MOTOR, pour gerer les moteurs des roues

struct Motor
{
    /// @brief Pin control 1
    uint8_t cPin1; // Pin Control 1

    /// @brief Pin control 2
    uint8_t cPin2; // Pin Control 2
    
    /// @brief Pin de perminssion
    uint8_t enablePin; // Pin four enabling


    /// @brief Définition du canal PWM
    int pwmChannel; // PWMChannel
};

typedef struct Motor MOTOR;

/// @brief MotorControl pour gerer les moteur des roues
class MotorControl
{
public :
    
    /// @brief Le constructeur de la classe MotorControl
    /// @param roue1 la premiere roue
    /// @param roue2 la seconde roue
    MotorControl(MOTOR *roue1 = NULL,
                 MOTOR *roue2  = NULL                
                 );
    /// @brief begin initialise les moteurs
    void begin();

    /// @brief Recupere la roue 1
    /// @return MOTOR
    MOTOR *getRoue1(){return this->m_roue1;}

    /// @brief Recupere la roue 2
    /// @return MOTOR
    MOTOR *getRoue2(){return this->m_roue2;}
private:
    MOTOR *m_roue1; // Moteur de la roue 1
    MOTOR *m_roue2; // Moteur de la roue 2

    /// @brief Configurer le systeme de pilotage des roues
    void configurationMotor();
};

#endif // MOTOR_CONTROL_H
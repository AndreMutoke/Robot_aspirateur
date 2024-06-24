/***********************************************************************************
 ***********************************************************************************
 ** @author : André MUTOKE MUSULE & Japhet TSHIMANGA BWENDE                       **
 ** @date : Mardi 29 Mai 2024                                                     **
 ** @name : MotorControl.cpp                                                      **
 ** @details : Ce fichier implémente les engrenages moteurs pour les roues        **
 * *********************************************************************************
 * *********************************************************************************
*/


#include "MotorControl.h"

MotorControl::MotorControl(MOTOR *roue1, MOTOR *roue2)
{
    this->m_roue1 = roue1;
    this->m_roue2 = roue2;
}

void MotorControl::configurationMotor()
{
    pinMode(this->m_roue1->cPin1, OUTPUT);
    pinMode(this->m_roue1->cPin2, OUTPUT);
    pinMode(this->m_roue1->enablePin, OUTPUT);

    pinMode(this->m_roue2->cPin1, OUTPUT);
    pinMode(this->m_roue2->cPin2, OUTPUT);
    pinMode(this->m_roue2->enablePin, OUTPUT);

    ledcSetup(PWMCHANNEL, FREQENCE_CONTROL, RESOLUTION);

    ledcAttachPin(this->m_roue1->enablePin, this->m_roue1->pwmChannel);
    ledcAttachPin(this->m_roue2->enablePin, this->m_roue2->pwmChannel);
}

void MotorControl::begin()
{
    configurationMotor();
}
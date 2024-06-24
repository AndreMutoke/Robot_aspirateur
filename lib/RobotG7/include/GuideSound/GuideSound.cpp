/***********************************************************************************
 ***********************************************************************************
 ** @author : André MUTOKE MUSULE & Japhet TSHIMANGA BWENDE                       **
 ** @date : Mardi 29 Mai 2024                                                     **
 ** @name : GuideSound.cpp                                                        **
 ** @details : Ce fichier implémente le capteur ultra son                         **
 * *********************************************************************************
 * *********************************************************************************
*/


#include "GuideSound.h"

#define __PULSE_DOWN__ 2
#define __PULSE_UP__ 10

#define __PIN_OK__ 1
#define __PIN_NOT_OK__ 0

GuideSound::GuideSound(uint8_t trig, uint8_t echo)
{
    this->m_trig_pin = trig;
    this->m_echo_pin= echo;
}


void GuideSound::begin()
{
    
    pinMode(this->m_trig_pin, OUTPUT);
    pinMode(this->m_echo_pin, INPUT);

    digitalWrite(this->m_trig_pin, LOW);
}

int GuideSound::pulseEmit()
{
    if(this->m_trig_pin != 0)
    {
        digitalWrite(this->m_trig_pin, LOW); delayMicroseconds(__PULSE_DOWN__);
        digitalWrite(this->m_trig_pin, HIGH); delayMicroseconds(__PULSE_UP__);
        digitalWrite(this->m_trig_pin, LOW);

        return __PIN_OK__;
    
    }
    return __PIN_NOT_OK__;
    
}

void GuideSound::captureDistance_and_Delay()
{
    if(this->pulseEmit())
    {
        if(this->m_echo_pin)
        {
            this->m_duree = pulseIn(this->m_echo_pin, HIGH);
            this->m_distance = this->m_duree / 58.2;
        }
        
    }
}
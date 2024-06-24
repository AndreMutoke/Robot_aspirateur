/*******************************************************************
 *******************************************************************
 ** @author : André MUTOKE MUSULE & Japhet TSHIMANGA BWENDE       **
 ** @date : Mardi 29 Mai 2024                                     **
 ** @name : main.cpp                                              **
 ** @details : Ce fichier implémente le déroulement du système    **
 * *****************************************************************
 * *****************************************************************
*/


#pragma once

/// Le système est implémenté dans ce fichier 

#include <Arduino.h>

#include <DabbleESP32.h>
#include <ESP32Servo.h>

#include <RobotG7.h>

#define INTERVAL_TIME 1000



/**
 * Put to PIN 2 the ECHO PIN of U-S
 * Put to PIN 4 the TRIG PIN of U-S
 * 
*/

/// @brief Definitions des roues
MOTOR roue1 = {27, 26, 14, PWMCHANNEL};  // Premiere Roue ( cPin1, cPin2, enable)
MOTOR roue2 = {25, 33, 32, PWMCHANNEL2}; //  Seconde Roue


/// @brief Instantiation du robot
RobotG7 *myrobot = new RobotG7(&roue1, &roue2); // Notre Robot

int PIN_MODE_CTRL = 5;
int tempctrl;

/// @brief Gestion du temps
unsigned long previouMillis;

/// @brief Fonction de parametrage
void setup()
{
    tempctrl = 1;
    previouMillis = 0;
    Serial.begin(115200);
    myrobot->begin();

    pinMode(PIN_MODE_CTRL, INPUT_PULLUP);
    
}

/// @brief Fonction du déroulement du système
void loop()
{
    unsigned long currentMillis = millis();
    // Serial.print("On veut lire le bp :  ");
    int temp = digitalRead(PIN_MODE_CTRL); delay(100);
    // Serial.println(temp);


    if(temp == 0)
    {
        delay(1000);

        tempctrl++;
        if(tempctrl > 3) {tempctrl = 1;}

    }

    switch (tempctrl)
    {
    case 1:
        myrobot->setNavigation(MODE_START);
        break;
    case 2:
        myrobot->setNavigation(MODE_MANUEL);
        break;
    case 3:
        myrobot->setNavigation(MODE_AUTOMATIQUE);
        break;
    
    default:
        break;
    }

    if(currentMillis - previouMillis >= INTERVAL_TIME)
    {
        Serial.println(myrobot->getDistanceObstacle());
        myrobot->navigation();

        previouMillis = currentMillis;

    }
  
}
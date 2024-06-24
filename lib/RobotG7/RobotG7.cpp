/***********************************************************************************
 ***********************************************************************************
 ** @author : André MUTOKE MUSULE & Japhet TSHIMANGA BWENDE                       **
 ** @date : Mardi 29 Mai 2024                                                     **
 ** @name : RobotG7.cpp                                                           **
 ** @details : Ce fichier implémente les élément composant le robot du système    **
 * *********************************************************************************
 * *********************************************************************************
*/

#include "RobotG7.h"



#define DEFAULT_TRIG_PIN 4
#define DEFAULT_ECHO_PIN 2
#define PIN_CLEANNIG 18

#define LIMIT_GET_OBSTACLE 35 // 10 cm
extern unsigned long previouMillis;

extern int tempctrl;

RobotG7::RobotG7(MOTOR *roue1, MOTOR *roue2, int pinCtrlMode)
{
    this->m_gdSound = new GuideSound(DEFAULT_TRIG_PIN, DEFAULT_ECHO_PIN); // (triger, echo)
    this->m_rouesRobots = new MotorControl(roue1, roue2); 
    this->m_vitesseDroite = 255;
    this->m_vitesseGauche = 255;

    this->cheminAprendre = new CtrlWay(); // Par defaut à la pin 15

    this->systemNav = DEVANT;

    this->m_modeNav = MODE_START;
    this->modeManualnotPrepared = ROBOTG7_TRUE;

    this->enableCleanning = ROBOTG7_FALSE;

    // this->m_modeNav = MODE_AUTOMATIQUE;

    // this->ctrlMode = pinCtrlMode;
}

void RobotG7::begin()
{
    // pinMode(this->ctrlMode, INPUT_PULLUP);
    pinMode(PIN_CLEANNIG, OUTPUT);
    
    this->m_gdSound->begin();
    this->m_rouesRobots->begin();
    this->cheminAprendre->begin();
    digitalWrite(PIN_CLEANNIG, HIGH);
}

void RobotG7::writeSpeedOnChannel(int vitesseChannel1, int vitesseChannel2)
{
    this->m_vitesseDroite = vitesseChannel2;
    this->m_vitesseGauche = vitesseChannel1;

    ledcWrite(this->m_rouesRobots->getRoue1()->pwmChannel, this->m_vitesseGauche);
    ledcWrite(this->m_rouesRobots->getRoue2()->pwmChannel, this->m_vitesseDroite);
}

void RobotG7::deplacementAvant()
{
    digitalWrite(this->m_rouesRobots->getRoue1()->enablePin, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->enablePin, HIGH);

    digitalWrite(this->m_rouesRobots->getRoue1()->cPin1, LOW);
    digitalWrite(this->m_rouesRobots->getRoue1()->cPin2, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin1, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin2, LOW);


    this->writeSpeedOnChannel(255, 255);

}
void RobotG7::deplacementArriere()
{
    digitalWrite(this->m_rouesRobots->getRoue1()->enablePin, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->enablePin, HIGH);

    digitalWrite(this->m_rouesRobots->getRoue1()->cPin1, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue1()->cPin2, LOW);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin1, LOW);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin2, HIGH);

    this->writeSpeedOnChannel(255, 255);

}

void RobotG7::tourner_a_GaucheAvant()
{
    digitalWrite(this->m_rouesRobots->getRoue1()->enablePin, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->enablePin, HIGH);

    digitalWrite(this->m_rouesRobots->getRoue1()->cPin1, LOW);
    digitalWrite(this->m_rouesRobots->getRoue1()->cPin2, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin1, LOW);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin1, HIGH);

    this->writeSpeedOnChannel(255, 255);
}
void RobotG7::tourner_a_DroiteAvant()
{
    digitalWrite(this->m_rouesRobots->getRoue1()->enablePin, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->enablePin, HIGH);

    digitalWrite(this->m_rouesRobots->getRoue1()->cPin1, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue1()->cPin2, LOW);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin1, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin2, LOW);

    this->writeSpeedOnChannel(255, 255);
}


void RobotG7::tourner_a_GaucheArriere()
{
    digitalWrite(this->m_rouesRobots->getRoue1()->enablePin, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->enablePin, HIGH);

    digitalWrite(this->m_rouesRobots->getRoue1()->cPin1, LOW);
    digitalWrite(this->m_rouesRobots->getRoue1()->cPin2, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin1, LOW);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin2, HIGH);

    this->writeSpeedOnChannel(255, 255);
}
void RobotG7::tourner_a_DroiteArriere()
{
    digitalWrite(this->m_rouesRobots->getRoue1()->enablePin, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->enablePin, LOW);

    digitalWrite(this->m_rouesRobots->getRoue1()->cPin1, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue1()->cPin2, LOW);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin1, HIGH);
    digitalWrite(this->m_rouesRobots->getRoue2()->cPin1, LOW);

    this->writeSpeedOnChannel(255, 255);
}

void RobotG7::stopRobotG7()
{
    digitalWrite(this->m_rouesRobots->getRoue1()->enablePin, LOW);
    digitalWrite(this->m_rouesRobots->getRoue2()->enablePin, LOW);

    this->writeSpeedOnChannel(0, 0);

}

void RobotG7::gamePadAutoGoStart()
{
     if(GamePad.isStartPressed())
    {
        tempctrl = 1;
    }
    
}

void RobotG7::systemRunningAuto()
{
    this->prepareRunningManual();
    this->inputProcess();
    
    switch(this->systemNav)
    {
    case DEVANT :
        // Serial.println("On avance !!!");
        this->gamePadAutoGoStart();
        if(this->getDistanceObstacle() >= LIMIT_GET_OBSTACLE)
        {
            this->enableCleanning = ROBOTG7_TRUE;this->gamePadAutoGoStart();
            // Serial.println("Permit d'avancer !!!");
            this->deplacementAvant();
        }
        else
        {
            // Serial.println("Non Permit d'avancer !!!");
            this->stopRobotG7();this->gamePadAutoGoStart();
            this->enableCleanning = ROBOTG7_FALSE;
            this->systemNav = this->cheminAprendre->theWayToget(this->m_gdSound);
        }
        break;
    case DERRIERE :
        this->enableCleanning = ROBOTG7_TRUE;this->gamePadAutoGoStart();
        this->deplacementArriere();
        break;
    case GAUCHE :
        this->enableCleanning = ROBOTG7_TRUE;this->gamePadAutoGoStart();
        this->tourner_a_GaucheArriere();
        this->systemNav = DEVANT;
        break;
    case DROITE :
        this->enableCleanning = ROBOTG7_TRUE;this->gamePadAutoGoStart();
        this->tourner_a_DroiteArriere();
        this->systemNav = DEVANT;
        break;
    }

    if(this->enableCleanning)
    {
        digitalWrite(PIN_CLEANNIG, HIGH);this->gamePadAutoGoStart();
    }
    else
    {
        digitalWrite(PIN_CLEANNIG, LOW);this->gamePadAutoGoStart();
    }
    this->gamePadAutoGoStart();
}

void RobotG7::inputProcess()
{
    Dabble.processInput();
}

void RobotG7::obtenirVitesseJoystick()
{
    float xval = GamePad.getXaxisData();
  float yval = GamePad.getYaxisData();

  //Pour la calibration
  if (xval < -6) {
    xval = -6;
    this->gamePadGestionCommand();
  } else if (xval > 6) {
    xval = 6;
    this->gamePadGestionCommand();
  }
  if (yval < -6) {
    yval = -6;this->gamePadGestionCommand();
  } else if (yval > 6) {
    yval = 6;this->gamePadGestionCommand();
  }

  int yMapped = 0;
  if (yval < 0 )
  {
    this->deplacementArriere();this->gamePadGestionCommand();
    yMapped = map(yval, -6, 0, 250, 0);
  }
  else
  {
    this->deplacementAvant();this->gamePadGestionCommand();
    yMapped = map(yval, 0, 6, 0, 250);
  }

  int xMapped;
  if (xval < 0 ){
    xMapped = map(xval, -6, 0, 250, 0);this->gamePadGestionCommand();
  }
  else {
    xMapped = map(xval, 0, 6, 0, 250);this->gamePadGestionCommand();
  }

  if (xval < 0 ) {
    this->m_vitesseGauche = yMapped + xMapped;this->gamePadGestionCommand();
    if (this->m_vitesseGauche  > 250) {
      this->m_vitesseGauche  = 250;this->gamePadGestionCommand();
    }

    this->m_vitesseDroite = yMapped - xMapped;this->gamePadGestionCommand();
    if (this->m_vitesseDroite < 0) {this->gamePadGestionCommand();
      this->m_vitesseDroite = 0;
    }

  } else {
    this->m_vitesseGauche = yMapped - xMapped;this->gamePadGestionCommand();
    if (this->m_vitesseGauche < 0) {this->gamePadGestionCommand();
      this->m_vitesseGauche = 0;
    }// pwmchannel

    this->m_vitesseDroite = yMapped + xMapped;this->gamePadGestionCommand();
    if (this->m_vitesseDroite > 250) {this->gamePadGestionCommand();
      this->m_vitesseDroite = 250;
    }
  }

 
}

void RobotG7::gamePadGestionCommand()
{
    if(GamePad.isCrossPressed())
    {
        // Serial.println("On nettoie");
        this->enableCleanning = ROBOTG7_TRUE;
    }
    else
    {
        // Serial.println("On ne nettoie pas");
        this->enableCleanning = ROBOTG7_FALSE;
    }
    if(this->enableCleanning)
    {   
        // Serial.println("On nettoie ici");
        digitalWrite(PIN_CLEANNIG, HIGH);
    }
    else
    {
        // Serial.println("On ne nettoie pas ici");
        digitalWrite(PIN_CLEANNIG, LOW);
    }

    if(GamePad.isSelectPressed())
    {
        tempctrl = 3;
    }
}

void RobotG7::systemRunningManual()
{
    this->prepareRunningManual();
    this->inputProcess();
    this->obtenirVitesseJoystick();
    this->writeSpeedOnChannel(this->m_vitesseGauche, this->m_vitesseDroite);
}

// void RobotG7::runningAutoMode(uint32_t PreviousTime)
// {
   
// }

// void RobotG7::systemRunning()
// {
//     switch (this->m_modeNav)
//     {
//     case MODE_AUTOMATIQUE:
//         /* code */
//         break;
//     case MODE_MANUEL:
//         /* code */
//         break;
    
//     default:
//         break;
//     }
// }

// ++++++++++++++++++++++++ mode de navigation +++++++++++++++++++++++++
void RobotG7::navigation()
{
    switch(this->m_modeNav)
    {
    case MODE_START :
        Serial.println("Mode start !!!");
        
        this->modeManualnotPrepared = ROBOTG7_TRUE;
        
        if(this->enableCleanning)
        {
            digitalWrite(PIN_CLEANNIG, HIGH);
        }
        else
        {
            digitalWrite(PIN_CLEANNIG, LOW);
        }
        this->stopRobotG7();
        break;
    case  MODE_AUTOMATIQUE :
        Serial.println("Mode automatique !!!");
        this->systemRunningAuto();
        break;

    case MODE_MANUEL:
        Serial.println("Mode manuel !!!");
        // this->stopRobotG7();
        this->systemRunningManual();
        break;

    }
}
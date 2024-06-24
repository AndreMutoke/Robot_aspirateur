/***********************************************************************************
 ***********************************************************************************
 ** @author : André MUTOKE MUSULE & Japhet TSHIMANGA BWENDE                       **
 ** @date : Mardi 29 Mai 2024                                                     **
 ** @name : CtrlWay.cpp                                                           **
 ** @details : Ce fichier implémente la prise de décison du chemin                **
 * *********************************************************************************
 * *********************************************************************************
*/

#include "CtrlWay.h"

#define INIT_POS_MOTOR 90
#define TAILLE_TAB_DIST 5
extern unsigned long previouMillis;

CtrlWay::CtrlWay(int pinAttached)
{
    this->m_pin_to_attach = pinAttached;
    this->posMotor = INIT_POS_MOTOR;
}
void CtrlWay::begin()
{
    this->m_pServo.attach(this->m_pin_to_attach);
    this->m_pServo.write(90);

    
}
int CtrlWay::seeToLeft(GuideSound *CaptureObstacle)
{
    int tabDistance[TAILLE_TAB_DIST]; // Pour capturer les valeurs des distance
    // On tourne a gauche
    unsigned long currentTimefor = millis();
    // Serial.println("On cherche a verifier a gauche");

    delay(500);
    this->m_pServo.write(0);  
    delay(500);

    Serial.println("On a verifier a gauche");
    // On observe la distance des obstacles a gauches
    previouMillis = millis();

        for(int i=0; i<TAILLE_TAB_DIST; ++i)
        {
            tabDistance[i] = CaptureObstacle->getDistance();
        }
    delay(500);
    this->m_pServo.write(this->posMotor);
    delay(500);

    Serial.print("La valeur a gauche est : ");
    Serial.println(this->MoyenneDistances(tabDistance));
    return this->MoyenneDistances(tabDistance);
}

int CtrlWay::seeToRight(GuideSound *CaptureObstacle)
{
    int tabDistance[TAILLE_TAB_DIST]; // Pour capturer les valeurs des distance
    // On tourne a gauche
    unsigned long currentTimefor = millis();
    delay(500);
    this->m_pServo.write(INIT_POS_MOTOR + 90); 
    delay(500);
    
    // On observe la distance des obstacles a gauches
    previouMillis = millis();

    if(currentTimefor - previouMillis >= 2000)
    {
        for(int i=0; i<TAILLE_TAB_DIST; ++i)
        {
            tabDistance[i] = CaptureObstacle->getDistance();
        }
    }
    delay(500);
    this->m_pServo.write(this->posMotor);
    delay(500);

    return this->MoyenneDistances(tabDistance);
}

int CtrlWay::MoyenneDistances(int tab[])
{
    int moyenne = 0;
    for(int i = 0; i< TAILLE_TAB_DIST; ++i)
    {
        moyenne = moyenne + tab[i];
    }
    moyenne = moyenne / TAILLE_TAB_DIST;
    return moyenne;
}

WAY CtrlWay::theWayToget(GuideSound *CaptureObstacle)
{
    int way1 = this->seeToLeft(CaptureObstacle);
    int way2 = this->seeToRight(CaptureObstacle);

    if(way1 > way2) {
        Serial.println("On chisit la gauche");
        return GAUCHE;
    }
    if(way1 < way2) {
        Serial.println("On chisit la droite");
        return DROITE;
    }
    return GAUCHE;

}
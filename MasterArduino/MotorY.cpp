//
// Created by Marcellino on 03/01/2019.
//

#ifndef IPMEDTH_MOTORX_H
#define IPMEDTH_MOTORX_H

#include "MotorY.h"
#include "Settings.h"
#include <Arduino.h>

using namespace std;

void MotorY::up(int einde, int potPin){
    digitalWrite(Y_DIR, false);
    delay(1);
    
    while(1) {

      digitalWrite(Y_STP, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(Y_STP, LOW);
      delayMicroseconds(delayTime);

      Serial.println(analogRead(potPin)); 

      if(analogRead(potPin) < einde + 20 && analogRead(potPin) > einde - 20 ){
        break;
      }
    }
};

void MotorY::down(int einde, int potPin){
    digitalWrite(Y_DIR, true);
    delay(1);

    while(1) {

      digitalWrite(Y_STP, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(Y_STP, LOW);
      delayMicroseconds(delayTime);

      Serial.println(potPin); 
      
      if(analogRead(potPin) < einde + 20 && analogRead(potPin) > einde - 20){
        break;
      }
    }

};

void MotorY::getPosition(){
    Serial.println("get position");
};

void MotorY::setPosition(){
    Serial.println("set poistion");
};

#endif //IPMEDTH_MOTORX_H

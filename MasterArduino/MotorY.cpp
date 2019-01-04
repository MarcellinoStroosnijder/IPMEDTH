//
// Created by Marcellino on 03/01/2019.
//

#ifndef IPMEDTH_MOTORX_H
#define IPMEDTH_MOTORX_H

#include "MotorY.h"
#include "Settings.h"
#include <Arduino.h>

using namespace std;

void MotorY::up(int steps){
    digitalWrite(Y_DIR, false);
    delay(1);
    Serial.println("Up");
    
    for (int i = 0; i < steps; i++) {

      digitalWrite(Y_STP, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(Y_STP, LOW);
      delayMicroseconds(delayTime);
    }
};

void MotorY::down(int steps){
    digitalWrite(Y_DIR, true);
    delay(1);

    for (int i = 0; i < steps; i++) {
      
      digitalWrite(Y_STP, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(Y_STP, LOW);
      delayMicroseconds(delayTime);
    };

};

void MotorY::getPosition(){
    Serial.println("get position");
};

void MotorY::setPosition(){
    Serial.println("set poistion");
};

#endif //IPMEDTH_MOTORX_H

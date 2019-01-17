//
// Created by Marcellino on 03/01/2019.
//

#include "MotorY.h"
#include "Settings.h"
#include <Arduino.h>

using namespace std;

float coefficient1 = 0.3515625;
float constant1 = 0;

void MotorY::up(){
    digitalWrite(Y_DIR, false);
    delay(1);
    
    digitalWrite(Y_STP, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(Y_STP, LOW);
    delayMicroseconds(delayTime);

};

void MotorY::down(){
    digitalWrite(Y_DIR, true);
    delay(1);

    digitalWrite(Y_STP, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(Y_STP, LOW);
    delayMicroseconds(delayTime);  
     
};

float MotorY::getPosition(){
     return analogRead(potPinA1) * coefficient1 + constant1;
};




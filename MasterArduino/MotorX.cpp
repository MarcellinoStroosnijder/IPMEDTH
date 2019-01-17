//
// Created by Marcellino on 17/01/2019.
//

#include "MotorX.h"
#include "Settings.h"
#include <Arduino.h>

using namespace std;

float coefficient = 0.3515625;
float constant = 0;

void MotorX::up(){
    digitalWrite(X_DIR, false);
    delay(1);
    
    digitalWrite(X_STP, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(X_STP, LOW);
    delayMicroseconds(delayTime);

};

void MotorX::down(){
    digitalWrite(X_DIR, true);
    delay(1);

    digitalWrite(X_STP, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(X_STP, LOW);
    delayMicroseconds(delayTime);  
     
};

float MotorX::getPosition(){
     return analogRead(potPinA2) * coefficient + constant;

};




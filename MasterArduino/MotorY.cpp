#include "MotorY.h"
#include "Settings.h"
#include <Arduino.h>

using namespace std;

float coefficient1 = 7.655555556;

void MotorY::up(){
    digitalWrite(Y_DIR, false);
    delay(1);
    
    digitalWrite(Y_STP, HIGH);
    digitalWrite(Y_STP, LOW);
    delayMicroseconds(delayTime);
};

void MotorY::down(){
    digitalWrite(Y_DIR, true);
    delay(1);

    digitalWrite(Y_STP, HIGH);
    digitalWrite(Y_STP, LOW);
    delayMicroseconds(delayTime);  
     
};

float MotorY::getPosition(){
    // 465 = 70 graden
    // 335 = 90 graden
    // 220 = 128 graden
    return (1024 - analogRead(potPinA2)) / coefficient1;
};

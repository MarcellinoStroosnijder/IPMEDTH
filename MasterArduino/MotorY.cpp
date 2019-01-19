#include "MotorY.h"
#include "Settings.h"
#include <Arduino.h>

using namespace std;

float coefficient1 = 7.655555556;

void MotorY::up(){
    Serial.write("G91 G01 Y0.2\n");
    delay(100);
};

void MotorY::down(){
    Serial.write("G91 G01 Y-0.2\n");
    delay(100);
};

float MotorY::getPosition(){
    // 465 = 70 graden
    // 335 = 90 graden
    // 220 = 128 graden
    return (1024 - analogRead(potPinA2)) / coefficient1;
};

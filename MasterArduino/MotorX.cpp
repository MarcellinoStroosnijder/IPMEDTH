#include "MotorX.h"
#include "Settings.h"
#include <Arduino.h>

using namespace std;

float coefficient = 3.555555;
float constant = 0;

void MotorX::up(){
    Serial.write("G91 G01 X0.1\n");
    delay(100);
};

void MotorX::down(){
    Serial.write("G91 G01 X-0.1\n");
    delay(100);
};

float MotorX::getPosition(){
    // 670 = 45 graden
    // 830 = 90 graden
    // 990 = 135 graden
    // Eigenlijk de potPinA1 (de zwarte)
     return (analogRead(potPinA1) - 510) / coefficient;
};

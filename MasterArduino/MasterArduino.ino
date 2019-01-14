///////////////////////////////////////////////////////////////////////////////////////
//THIS IS A DEMO SOFTWARE JUST FOR EXPERIMENT PURPOER IN A NONCOMERTIAL ACTIVITY
//Version: 1.0 (AUG, 2016)

//Gyro - Arduino UNO R3
//VCC  -  5V
//GND  -  GND
//SDA  -  A4
//SCL  -  A5
//INT - port-2

#include <Wire.h>
#include "AnkelBand.h"
#include "Footband.h"

AnkelBand Ankle;
FootBand Foot;

void setup() {
  Serial.begin(112500);
  Ankle.setupSensor();
  Foot.setupSensor();
}

void loop(){

 Ankle.getData();
 Foot.getData();
  
}













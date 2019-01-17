#include <Wire.h>
#include "AnkelBand.h"
#include "Footband.h"
#include "MotorY.h"
#include "MotorX.h"
#include "Settings.h"

MotorY MotorY;
AnkelBand Ankle;
FootBand Foot;
MotorX MotorX;

extern float anklestrapY;
extern float anklestrapX;
extern float footstrapY;
extern float footstrapX;
float myAngleY;
float myAngleX;
float minY = 0.0;
float maxY = 70.0;


void setup() {
  Serial.begin(115200);
  Serial.println("Hallo!?");
  pinMode(EN,OUTPUT);
  digitalWrite(EN,LOW);
  Ankle.setupSensor();
  Foot.setupSensor();
}

void loop(){

 Ankle.getData();
 Foot.getData();
 myAngleY = anklestrapY + footstrapY;
 if(minY < MotorY.getPosition() < maxY){
   if(MotorY.getPosition() > myAngleY){
    MotorY.up();
   }else if(MotorY.getPosition() < myAngleY){
    MotorY.down();
   }
 }
 
// Serial.print("4pin:"); Serial.print(anklestrapY);
// Serial.print("| 5pin:"); Serial.print(footstrapY);
// Serial.print("| hoekie:"); Serial.println(myAngleY);
}













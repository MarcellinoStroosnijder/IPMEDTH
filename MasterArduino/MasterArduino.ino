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
float minY = 70;
float maxY = 118;


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
 
 if(minY < MotorY.getPosition() && MotorY.getPosition() < maxY){
   if(MotorY.getPosition() > myAngleY){
    MotorY.up();
    Serial.println("up");
   }else if(MotorY.getPosition() < myAngleY){
    MotorY.down();
    Serial.println("down");
   }
 }

 Serial.print("positie:"); Serial.println(MotorY.getPosition());
 Serial.print("hoekie:"); Serial.println(myAngleY);
}
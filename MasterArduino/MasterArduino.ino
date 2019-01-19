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
float previousPosY;
float minX = 11;
float maxX = 85;
float previousPosX;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  pinMode(EN,OUTPUT);
  digitalWrite(EN,LOW);
  Ankle.setupSensor();
  Foot.setupSensor();
  Serial.write("M03\n");
}

void loop(){

 Ankle.getData();
 Foot.getData();
 myAngleY = anklestrapY + footstrapY;
 myAngleX = footstrapX - 45;

// Enkel (motorY)
 if((previousPosY + 4) < myAngleY || (previousPosY - 4) > myAngleY) {
  if(MotorY.getPosition() > myAngleY && MotorY.getPosition() > minY){
   MotorY.up();
   Serial.println("up");
  }else if(MotorY.getPosition() < myAngleY && MotorY.getPosition() < maxY){
    MotorY.down();
      Serial.println("down");
    }
 }

 previousPosY = MotorY.getPosition();

// Voet (motorX)
 if((previousPosX + 2) < myAngleX || (previousPosX - 2) > myAngleX) {
  if(MotorX.getPosition() > myAngleX && MotorX.getPosition() > minX){
   MotorX.down();
   Serial.println("down");
  }else if(MotorX.getPosition() < myAngleX && MotorX.getPosition() < maxX){
    MotorX.up();
      Serial.println("up");
    }
 }

 previousPosX = MotorX.getPosition();

 Serial.print("positieY:"); Serial.println(MotorY.getPosition());
 Serial.print("enkelHoek:"); Serial.println(myAngleY);
 Serial.print("positieX:"); Serial.println(MotorX.getPosition());
 Serial.print("voetHoek:"); Serial.println(myAngleX);

// Serial.println(analogRead(potPinA1));
// delay(100);
// Serial.println(analogRead(potPinA2));
//  delay(100);
}

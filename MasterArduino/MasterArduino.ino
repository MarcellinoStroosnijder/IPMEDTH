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
float minY;
float maxY;
float previousPosY;
float minX = 25;
float maxX = 151;
float previousPosX;
int mode = pre;
int lr = left;
int standby = on;


void setup() {
  Serial.begin(115200);
 // Serial.println("Initializing...");
  pinMode(EN,OUTPUT);
  digitalWrite(EN,LOW);
  Ankle.setupSensor();
  Foot.setupSensor();
  Serial.write("M03\n");
  pinMode(LEDpre, OUTPUT);
  pinMode(LEDpost, OUTPUT);
  pinMode(LEDleft, OUTPUT);
  pinMode(LEDright, OUTPUT);
//  pinMode(LEDon, OUTPUT);
  pinMode(LEDoff, OUTPUT);
  pinMode(BUTTprepost, INPUT);
  pinMode(BUTTleftright, INPUT);
  pinMode(BUTTonoff, INPUT);

  digitalWrite(BUTTprepost, HIGH);
  digitalWrite(BUTTleftright, HIGH);
  digitalWrite(BUTTonoff, HIGH);
  setupMode();
}

void setupMode(){
  if(standby == off){
    digitalWrite(LEDoff, LOW);
    if(mode == pre){
     digitalWrite(LEDpre, HIGH);
     digitalWrite(LEDpost, LOW);
     minY = 70;
     maxY = 98;
     if(lr == left){
      digitalWrite(LEDleft, HIGH);
      digitalWrite(LEDright, LOW);
     }else{
      digitalWrite(LEDright, HIGH);
      digitalWrite(LEDleft, LOW);
     }
    }else{
      digitalWrite(LEDpre, LOW);
      digitalWrite(LEDpost, HIGH);
      if(lr == left){
       digitalWrite(LEDleft, HIGH);
       digitalWrite(LEDright, LOW);
       minY = 75;
       maxY = 98;
      }else{
       digitalWrite(LEDright, HIGH);
       digitalWrite(LEDleft, LOW); 
       minY = 75;
       maxY = 98;
      }
    }
  }else{
    digitalWrite(LEDpre, LOW);
    digitalWrite(LEDpost, LOW);
    digitalWrite(LEDleft, LOW);
    digitalWrite(LEDright, LOW);
    digitalWrite(LEDoff, HIGH);
  }
  
}

void moveY(){
  if(mode == pre){
   myAngleY = anklestrapY + footstrapY;
  }else if (lr == left){
    myAngleY = 90 - footstrapX;
  }else{
    myAngleY = 90 + footstrapX;
  }
   if((previousPosY + 4) < myAngleY || (previousPosY - 4) > myAngleY) {
    if(MotorY.getPosition() > myAngleY && MotorY.getPosition() > minY){
     MotorY.up();
     //Serial.println("up");
    }else if(MotorY.getPosition() < myAngleY && MotorY.getPosition() < maxY){
     MotorY.down();
     //Serial.println("down");
    }
  }
  
   previousPosY = MotorY.getPosition();
}

void moveX(){
  if(mode == pre){
    myAngleX = 90 - footstrapX;
  }else{
    myAngleX = 90;
  }
   if((previousPosX + 10) < myAngleX || (previousPosX - 10) > myAngleX) {
    if(MotorX.getPosition() > myAngleX && MotorX.getPosition() > minX){
      MotorX.down();
      Serial.println("Rechts");
    }else if(MotorX.getPosition() < myAngleX && MotorX.getPosition() < maxX){
      MotorX.up();
      Serial.println("Links");
    }
   }
  
   previousPosX = MotorX.getPosition();
}

void loop(){

 if(digitalRead(BUTTprepost) == LOW){
  mode = (mode + 1) % 2;
  setupMode();
  delay(buttonTime);
 }
 if(digitalRead(BUTTleftright) == LOW){
  lr = (lr + 1) % 2;
  setupMode();
  delay(buttonTime);
 }
 if(digitalRead(BUTTonoff) == LOW){
  standby = (standby + 1) % 2;
  setupMode();  
  delay(buttonTime);
 }
 if(standby == off){
   Ankle.getData();
   Foot.getData();
   moveY();
   moveX();
 }
 
//   Serial.print("positieY:"); Serial.println(MotorY.getPosition());
  // Serial.print("enkelHoek:"); Serial.println(myAngleY);
  // Serial.print("anglestrapY: "); Serial.println(anklestrapY);
//   Serial.print("footstrapX: "); Serial.println(footstrapX);
//   Serial.print("positieX:"); Serial.println(MotorX.getPosition());
//   Serial.print("voetHoek:"); Serial.println(myAngleX);
  
  // Serial.println(analogRead(potPinA1));
  // delay(100);
  // Serial.println(analogRead(potPinA2));
  //  delay(100);
}

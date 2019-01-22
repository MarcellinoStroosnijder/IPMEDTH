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
float minX = 11;
float maxX = 85;
float previousPosX;
int mode = 0;
int lr = 0;
int standby = 0;
#define LEDpre 1
#define LEDpost 2
#define LEDleft 3 
#define LEDright 4
//#define LEDon 5
#define LEDoff 5
#define BUTTprepost 7
#define BUTTleftright 8
#define BUTTonoff 9
#define pre 0
#define post 1
#define left 0
#define right 1

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
  setupMode();
}

void setupMode(){
  digitalWrite(LEDoff, LOW);
  if(mode == pre){
   digitalWrite(LEDpre, HIGH);
   digitalWrite(LEDpost, LOW);
   minY = 70;
   maxY = 118;
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
     minY = 70;
     maxY = 98;
    }else{
     digitalWrite(LEDright, HIGH);
     digitalWrite(LEDleft, LOW); 
     minY = 70;
     maxY = 98;
    }
  }
    
}

void moveY(){
  if(mode == pre){
   myAngleY = anklestrapY + footstrapY;
  }else if (lr == left){
    myAngleY = 90 - footstrapX;
  }else{
    myAngleY = 180 - footstrapX;
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
   if((previousPosX + 2) < myAngleX || (previousPosX - 2) > myAngleX) {
    if(MotorX.getPosition() > myAngleX && MotorX.getPosition() > minX){
      MotorX.up();
      Serial.println("Links");
    }else if(MotorX.getPosition() < myAngleX && MotorX.getPosition() < maxX){
      MotorX.down();
      Serial.println("Rechts");
    }
   }
  
   previousPosX = MotorX.getPosition();
}

void loop(){

 if(digitalRead(BUTTprepost) == HIGH){
  mode = (mode + 1) % 2;
  setupMode();
  delay(600);
 }
 if(digitalRead(BUTTleftright) == HIGH){
  lr = (lr + 1) % 2;
  setupMode();
  delay(600);
 }
 if(digitalRead(BUTTonoff) == HIGH){
  standby = (standby + 1) % 2;
  delay(600);
 }
 if(standby == 0){
   Ankle.getData();
   Foot.getData();
   moveY();
   moveX();
 }else{
  digitalWrite(LEDpre, LOW);
  digitalWrite(LEDpost, LOW);
  digitalWrite(LEDleft, LOW);
  digitalWrite(LEDright, LOW);
  digitalWrite(LEDoff, HIGH);
 }
 
//   Serial.print("positieY:"); Serial.println(MotorY.getPosition());
  // Serial.print("enkelHoek:"); Serial.println(myAngleY);
  // Serial.print("anglestrapY: "); Serial.println(anklestrapY);
  // Serial.print("footstrapX: "); Serial.println(footstrapX);
  // Serial.print("positieX:"); Serial.println(MotorX.getPosition());
  // Serial.print("voetHoek:"); Serial.println(myAngleX);
  
  // Serial.println(analogRead(potPinA1));
  // delay(100);
  // Serial.println(analogRead(potPinA2));
  //  delay(100);
}

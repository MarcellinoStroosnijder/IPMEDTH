#include <Wire.h>
#include "AnkelBand.h"
#include "FootBand.h"
#include "MotorY.h"
#include "Settings.h"

AnkelBand ankel;
FootBand foot;
MotorY motory;

void setup() {
  
  Wire.begin(); 
  Serial.begin(9600);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  ankel.registerSensor();
  foot.registerSensor();
  ankel.calibration();
  foot.calibration();


}
 
void loop() {

// motory.up(500, potPinA2);
//
//  Serial.println("down");
  
  ankel.getData(); 
  Serial.println("-------------------------------------------------------");
  foot.getData();
  Serial.println("-------------------------------------------------------");

  //ankel.share();
  //foot.share();
  
   delay(500); // only read every 0,5 seconds
}
 
 
  


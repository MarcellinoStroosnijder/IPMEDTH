#include <Wire.h>
#include "AnkelBand.h"
#include "FootBand.h"

#include "Settings.h"

AnkelBand ankel;
FootBand foot;
void setup() {
  
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600); // start serial for output. Make sure you set your Serial Monitor to the same!

  ankel.registerSensor();
  foot.registerSensor();
  ankel.calibration();
  foot.calibration();


}
 
void loop() {
  ankel.getData(); // read the x/y/z tilt
  Serial.println("-------------------------------------------------------");
  foot.getData();
  Serial.println("-------------------------------------------------------");

  delay(500); // only read every 0,5 seconds
}
 
 
  


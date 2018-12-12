#include <Wire.h>
int full;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);           // start serial for output
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void receiveEvent(int howMany) {
  full = Wire.read();
  uint8_t high = full;
  full = full << 8;
  uint8_t low = Wire.read();

  while(Wire.available()){
    Wire.read();
  }
  
  Serial.println(low);
  Serial.println(high);

  int AcX1 = high * 256 + low;
  Serial.println(AcX1);

}

//
// Created by Marcellino on 03/12/2018.
//

#include "AnkelBand.h"
#include <Wire.h>
#include <Arduino.h>
#include "Settings.h"
#include <I2Cdev.h>

int16_t AcX1,AcY1,AcZ1,Tmp1,GyX1,GyY1,GyZ1;

using namespace std;

void AnkelBand::registerSensor(){
  Wire.begin();
  Wire.beginTransmission(AnkelbandID);
  Wire.write(0x6B);// PWR_MGMT_1 register 
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Serial.println("Register Ankel Succeeded");
}

void AnkelBand::calibration(){
  this->setXAccelOffset(-146); // 1688 factory default for my test chip
  this->setYAccelOffset(-647); // 1688 factory default for my test chip
  this->setZAccelOffset(3164); // 1688 factory default for my test chi
  
  this->setXGyroOffset(37);
  this->setYGyroOffset(12);
  this->setZGyroOffset(30);

  Serial.println("Calibration Ankel Succeeded");

}

void AnkelBand::getData(){
  Wire.beginTransmission(AnkelbandID); 
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
  Wire.endTransmission(false);
  Wire.requestFrom(AnkelbandID, 14, true); // request a total of 14 registers 
  
  AcX1=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
  AcY1=Wire.read()<<8| Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ1=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
  Tmp1=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) 
  GyX1=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
  GyY1=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
  GyZ1=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 

  Serial.print("AcX = ");
  Serial.print(AcX1);
  Serial.print(" | AcY = "); 
  Serial.print(AcY1);
  Serial.print(" | AcZ = ");
  Serial.print(AcZ1); 
  Serial.print(" | GyX = ");
  Serial.print(GyX1); 
  Serial.print(" | GyY = "); 
  Serial.print(GyY1);
  Serial.print(" | GyZ = ");
  Serial.println(GyZ1);
 };


void AnkelBand::share(){
  Wire.beginTransmission(8); // transmit to device #8
  
  uint8_t xlow = lowByte(AcX1);
  uint8_t xhigh = highByte(AcX1);

  byte bytesToSend[2] = {xlow, xhigh};

  Serial.println(xlow);
  Serial.println(xhigh);
  
  Wire.write(bytesToSend[0]);
  Wire.write(bytesToSend[1]);

  
  Wire.endTransmission();    // stop transmitting

  Serial.println("verzonden");
  

  delay(500);
};

void AnkelBand::setXGyroOffset(int16_t offset) {
    I2Cdev::writeWord(AnkelbandID, MPU6050_RA_YG_OFFS_USRH, offset);
};

void AnkelBand::setYGyroOffset(int16_t offset) {
    I2Cdev::writeWord(AnkelbandID, MPU6050_RA_YG_OFFS_USRH, offset);
};

void AnkelBand::setZGyroOffset(int16_t offset) {
    I2Cdev::writeWord(AnkelbandID, MPU6050_RA_ZG_OFFS_USRH, offset);
};

void AnkelBand::setXAccelOffset(int16_t offset) {
    I2Cdev::writeWord(AnkelbandID, MPU6050_RA_XA_OFFS_H, offset);
};

void AnkelBand::setYAccelOffset(int16_t offset) {
    I2Cdev::writeWord(AnkelbandID, MPU6050_RA_YA_OFFS_H, offset);
};

void AnkelBand::setZAccelOffset(int16_t offset) {
    I2Cdev::writeWord(AnkelbandID, MPU6050_RA_ZA_OFFS_H, offset);
};

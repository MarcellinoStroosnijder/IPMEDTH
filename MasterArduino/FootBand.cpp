//
// Created by Marcellino on 03/12/2018.
// 
//

#include "FootBand.h"
#include "Settings.h"
#include <I2Cdev.h>
#include <Arduino.h>
#include <Wire.h> 

using namespace std;
int16_t AcX2,AcY2,AcZ2,Tmp2,GyX2,GyY2,GyZ2;

void FootBand::registerSensor(){
  Wire.begin(); 
  Wire.beginTransmission(FootbandID);
  Wire.write(0x6B);// PWR_MGMT_1 register 
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Serial.println("Register Foot Succeeded");

};

void FootBand::calibration(){
  this->setXAccelOffset(1858); 
  this->setYAccelOffset(-3093); 
  this->setZAccelOffset(2138); 

  this->setXGyroOffset(387);
  this->setYGyroOffset(98);
  this->setZGyroOffset(23);

  Serial.println("Calibration Foot Succeeded");

}

void FootBand::getData(){
      Wire.beginTransmission(FootbandID); 
      Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
      Wire.endTransmission(false);
      Wire.requestFrom(FootbandID, 14, true); // request a total of 14 registers 
      
      AcX2=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
      AcY2=Wire.read()<<8| Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      AcZ2=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
      Tmp2=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) 
      GyX2=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
      GyY2=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
      GyZ2=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
      
      Serial.print("AcX2 = ");
      Serial.print(AcX2);
      Serial.print(" | AcY2 = "); 
      Serial.print(AcY2);
      Serial.print(" | AcZ2 = ");
      Serial.print(AcZ2);  
      Serial.print(" | GyX2 = ");
      Serial.print(GyX2); 
      Serial.print(" | GyY2 = "); 
      Serial.print(GyY2);
      Serial.print(" | GyZ2 = ");
      Serial.println(GyZ2); 
};

void FootBand::share(){
    Wire.beginTransmission(8); // transmit to device #8
  
    uint8_t xlow = lowByte(AcX2);
    uint8_t xhigh = highByte(AcX2);
  
    byte bytesToSend[2] = {xlow, xhigh};
  
    Serial.println(xlow);
    Serial.println(xhigh);
    
    Wire.write(bytesToSend[0]);
    Wire.write(bytesToSend[1]);
  
    
    Wire.endTransmission();    // stop transmitting
  
    Serial.println("verzonden");
    
  
    delay(500);
};

void FootBand::setXGyroOffset(int16_t offset) {
    I2Cdev::writeWord(FootbandID, MPU6050_RA_XG_OFFS_USRH, offset);
};

void FootBand::setYGyroOffset(int16_t offset) {
    I2Cdev::writeWord(FootbandID, MPU6050_RA_YG_OFFS_USRH, offset);
};

void FootBand::setZGyroOffset(int16_t offset) {
    I2Cdev::writeWord(FootbandID, MPU6050_RA_ZG_OFFS_USRH, offset);
};

void FootBand::setXAccelOffset(int16_t offset) {
    I2Cdev::writeWord(FootbandID, MPU6050_RA_XA_OFFS_H, offset);
};

void FootBand::setYAccelOffset(int16_t offset) {
    I2Cdev::writeWord(FootbandID, MPU6050_RA_YA_OFFS_H, offset);
};

void FootBand::setZAccelOffset(int16_t offset) {
    I2Cdev::writeWord(FootbandID, MPU6050_RA_ZA_OFFS_H, offset);
};

/////////////////////////////////////////////////////////////////////////////////////////
//THIS IS A DEMO SOFTWARE JUST FOR EXPERIMENT PURPOER IN A NONCOMERTIAL ACTIVITY
//Version: 1.0 (AUG, 2016)

//Gyro - Arduino UNO R3
//VCC  -  5V
//GND  -  GND
//SDA  -  A4
//SCL  -  A5
//INT - port-2

#include <Wire.h>
#include <Arduino.h>
#include "FootBand.h"

//Declaring some global variables
int gyro_x2, gyro_y2, gyro_z2;
long gyro_x_cal2, gyro_y_cal2, gyro_z_cal2;
boolean set_gyro_angles2;

long acc_x2, acc_y2, acc_z2, acc_total_vector2;
float angle_roll_acc2, angle_pitch_acc2;

float angle_pitch2, angle_roll2;
int angle_pitch_buffer2, angle_roll_buffer2;
float angle_pitch_output2, angle_roll_output2;

long loop_timer2;
int temp2;

void FootBand::setupSensor() {
  Wire.begin();                                                        //Start I2C as master
  setup_mpu_6050_registers();                                          //Setup the registers of the MPU-6050 
  for (int cal_int2 = 0; cal_int2 < 1000 ; cal_int2 ++){                  //Read the raw acc and gyro data from the MPU-6050 for 1000 times
    read_mpu_6050_data();                                             
    gyro_x_cal2 += gyro_x2;                                              //Add the gyro x offset to the gyro_x_cal variable
    gyro_y_cal2 += gyro_y2;                                              //Add the gyro y offset to the gyro_y_cal variable
    gyro_z_cal2 += gyro_z2;                                              //Add the gyro z offset to the gyro_z_cal variable
    delay(3);                                                          //Delay 3us to have 250Hz for-loop
  }

  // divide by 1000 to get avarage offset
  gyro_x_cal2 /= 1000;                                                 
  gyro_y_cal2 /= 1000;                                                 
  gyro_z_cal2 /= 1000;                                                 

  loop_timer2 = micros();                                               //Reset the loop timer
}

void FootBand::getData(){

  read_mpu_6050_data();   
 //Subtract the offset values from the raw gyro values
  gyro_x2 -= gyro_x_cal2;                                                
  gyro_y2 -= gyro_y_cal2;                                                
  gyro_z2 -= gyro_z_cal2;                                                
         
  //Gyro angle calculations . Note 0.0000611 = 1 / (250Hz x 65.5)
  angle_pitch2 += gyro_x2 * 0.0000611;                                   //Calculate the traveled pitch angle and add this to the angle_pitch variable
  angle_roll2 += gyro_y2 * 0.0000611;                                    //Calculate the traveled roll angle and add this to the angle_roll variable
  //0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
  angle_pitch2 += angle_roll2 * sin(gyro_z2 * 0.000001066);               //If the IMU has yawed transfer the roll angle to the pitch angel
  angle_roll2 -= angle_pitch2 * sin(gyro_z2 * 0.000001066);               //If the IMU has yawed transfer the pitch angle to the roll angel
  
  //Accelerometer angle calculations
  acc_total_vector2 = sqrt((acc_x2*acc_x2)+(acc_y2*acc_y2)+(acc_z2*acc_z2));  //Calculate the total accelerometer vector
  //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  angle_pitch_acc2 = asin((float)acc_y2/acc_total_vector2)* 57.296;       //Calculate the pitch angle
  angle_roll_acc2 = asin((float)acc_x2/acc_total_vector2)* -57.296;       //Calculate the roll angle
  
  angle_pitch_acc2 -= 0.0;                                              //Accelerometer calibration value for pitch
  angle_roll_acc2 -= 0.0;                                               //Accelerometer calibration value for roll

  if(set_gyro_angles2){                                                 //If the IMU is already started
    angle_pitch2 = angle_pitch2 * 0.9996 + angle_pitch_acc2 * 0.0004;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
    angle_roll2 = angle_roll2 * 0.9996 + angle_roll_acc2 * 0.0004;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
  }
  else{                                                                //At first start
    angle_pitch2 = angle_pitch_acc2;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle 
    angle_roll2 = angle_roll_acc2;                                       //Set the gyro roll angle equal to the accelerometer roll angle 
    set_gyro_angles2 = true;                                            //Set the IMU started flag
  }
  
  //To dampen the pitch and roll angles a complementary filter is used
  angle_pitch_output2 = angle_pitch_output2 * 0.9 + angle_pitch2 * 0.1;   //Take 90% of the output pitch value and add 10% of the raw pitch value
  angle_roll_output2 = angle_roll_output2 * 0.9 + angle_roll2 * 0.1;      //Take 90% of the output roll value and add 10% of the raw roll value
  Serial.print(" | Zwart  = "); Serial.println(angle_roll_output2);

 while(micros() - loop_timer2 < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
 loop_timer2 = micros();//Reset the loop timer
  
}

void FootBand::setup_mpu_6050_registers(){
  //Activate the MPU-6050
  Wire.beginTransmission(0x69);                                        //Start communicating with the MPU-6050
  Wire.write(0x6B);                                                    //Send the requested starting register
  Wire.write(0x00);                                                    //Set the requested starting register
  Wire.endTransmission();                                             
  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x69);                                        //Start communicating with the MPU-6050
  Wire.write(0x1C);                                                    //Send the requested starting register
  Wire.write(0x10);                                                    //Set the requested starting register
  Wire.endTransmission();                                             
  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(0x69);                                        //Start communicating with the MPU-6050
  Wire.write(0x1B);                                                    //Send the requested starting register
  Wire.write(0x08);                                                    //Set the requested starting register
  Wire.endTransmission();                                             
}

void FootBand::read_mpu_6050_data(){                                             //Subroutine for reading the raw gyro and accelerometer data
  Wire.beginTransmission(0x69);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x69,14);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 14);                                        //Wait until all the bytes are received
  acc_x2 = Wire.read()<<8|Wire.read();                                  
  acc_y2 = Wire.read()<<8|Wire.read();                                  
  acc_z2 = Wire.read()<<8|Wire.read();                                  
  temp2 = Wire.read()<<8|Wire.read();                                   
  gyro_x2 = Wire.read()<<8|Wire.read();                                 
  gyro_y2 = Wire.read()<<8|Wire.read();                                 
  gyro_z2 = Wire.read()<<8|Wire.read();                                 
}

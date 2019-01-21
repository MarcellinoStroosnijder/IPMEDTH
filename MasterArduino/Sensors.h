using namespace std;

#include <Arduino.h>

#ifndef Sensors_h
#define Sensors_h

//Base class ( abstract/interface)

class Sensors {
    public:
        virtual void setupSensor() = 0;
        virtual void getData() = 0;
        virtual void setup_mpu_6050_registers() = 0;
        virtual void read_mpu_6050_data() = 0;
};

#endif

//
// Created by Marcellino on 03/12/2018.
//


using namespace std;

#include <Arduino.h>

#ifndef Sensors_h
#define Sensors_h

//Base class ( abstract/interface)

class Sensors {
    public:
        virtual void registerSensor() = 0;
        virtual void calibration() = 0;
        virtual void getData() = 0;
        virtual void share() = 0;
        virtual void setXGyroOffset(int offset) = 0;
        virtual void setYGyroOffset(int offset) = 0;
        virtual void setZGyroOffset(int offset) = 0;
        virtual void setXAccelOffset(int offset) = 0;
        virtual void setYAccelOffset(int offset) = 0;
        virtual void setZAccelOffset(int offset) = 0;
};

#endif

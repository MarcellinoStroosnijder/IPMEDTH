//
// Created by Marcellino on 03/12/2018.
//


#include "Sensors.h"
#include <Arduino.h>


class FootBand: Sensors {
    public:       
        void registerSensor() override;
        void calibration() override;
        void getData() override;
        void share() override;        
        void setXGyroOffset(int offset) override;
        void setYGyroOffset(int offset) override;
        void setZGyroOffset(int offset) override;
        void setXAccelOffset(int offset) override;
        void setYAccelOffset(int offset) override;
        void setZAccelOffset(int offset) override;
};




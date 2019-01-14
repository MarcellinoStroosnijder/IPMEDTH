#include "Sensors.h"
#include <Arduino.h>


class FootBand: Sensors {
  public:
    void setupSensor() override;
    void getData() override;
    void read_mpu_6050_data() override;
    void setup_mpu_6050_registers() override;
};


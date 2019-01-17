//
// Created by Marcellino on 17/01/2019.
//


#include "Motors.h"

class MotorX:Motors {

public:
    void up() override;
    void down() override;
    float getPosition() override;
};




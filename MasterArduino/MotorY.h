//
// Created by Marcellino on 03/01/2019.
//


#ifndef IPMEDTH_FOOTBAND_H
#define IPMEDTH_FOOTBAND_H

#include "Motors.h"

class MotorY:Motors {

public:
    void up(int steps, int potPin) override;
    void down(int steps, int potPin) override;
    void getPosition() override;
    void setPosition() override;
};


#endif //IPMEDTH_FOOTBAND_H

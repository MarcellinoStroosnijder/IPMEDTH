#ifndef IPMEDTH_FOOTBAND_H
#define IPMEDTH_FOOTBAND_H

#include "Motors.h"

class MotorY:Motors {

public:
    void up() override;
    void down() override;
    float getPosition() override;
};


#endif //IPMEDTH_FOOTBAND_H

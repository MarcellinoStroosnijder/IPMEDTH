#include "Motors.h"

class MotorX:Motors {

public:
    void up() override;
    void down() override;
    float getPosition() override;
};

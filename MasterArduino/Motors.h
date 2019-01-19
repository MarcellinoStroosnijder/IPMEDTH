#ifndef IPMEDTH_MOTORS_H
#define IPMEDTH_MOTORS_H

using namespace std;

class Motors {
    public:
        virtual void up() = 0;
        virtual void down() = 0;
        virtual float getPosition() = 0;
};
#endif //IPMEDTH_MOTORS_H

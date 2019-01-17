//
// Created by Marcellino on 03/01/2019.
//

#ifndef IPMEDTH_MOTORS_H
#define IPMEDTH_MOTORS_H

using namespace std;

class Motors {
    public:

        virtual void up() = 0;
        virtual void down() = 0;
        virtual void getPosition() = 0;
        virtual void setPosition() = 0;
};
#endif //IPMEDTH_MOTORS_H

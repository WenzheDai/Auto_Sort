#ifndef AUTO_SORT_MOTOR_CONTROL_H
#define AUTO_SORT_MOTOR_CONTROL_H
#include <iostream>
using namespace std;

/*
 * This file contains the operations of our group with the motor.
 * We use the library of pigpio to program the pins.
 */

class motor_control
{
public:
    //set the GPIO level
    void setMode();

    //set the direction if rotation
    void setStep(int h1, int h2, int h3, int h4);

    //pull up the high-level GPIO's resistance
    void setPullUpDown(int h1, int h2, int h3, int h4);

    //compute the angle
    int angle(int angle);

    //control the motor forward rotation
    void motor_forward(int cir);

    //control the motor reverse rotation
    void motor_reverse(int cir);

    //motor turn
    int motor_turn(int x);
};

#endif

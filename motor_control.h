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
    int IN1, IN2, IN3, IN4;
    //set the GPIO level
    void setMode(int IN, int putNum);

    //set the direction if rotation
    void setStep(int h1, int h2, int h3, int h4);

    //pull up the high-level GPIO's resistance
    void setPullUpDown(int h1, int h2, int h3, int h4);

    //the number of loops is calculated by the angle
    int motor_angle(int angle);

};

#endif

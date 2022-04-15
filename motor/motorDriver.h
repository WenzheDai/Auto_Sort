#ifndef AUTO_SORT_MOTORDRIVER_H
#define AUTO_SORT_MOTORDRIVER_H
#include "motor_control.h"

// struct for callback function
typedef int(motor_control::*pClassFun)(int);

/*!
 * @file motorDriver.h
 * @brief This file enable the callback function for operation of motor
 */

class motorDriver {
public:

//callback function
void MyDriver(motor_control *motorControl, pClassFun motor_turn, int x);
};


#endif //AUTO_SORT_MOTORDRIVER_H

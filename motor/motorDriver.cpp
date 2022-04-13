//
// Created by jackno2d on 2022/4/12.
//

#include "motorDriver.h"
//#include "motor_control.h"

void motorDriver::MyDriver(motor_control *motorControl, pClassFun motor_turn, int x) {
    (motorControl->*motor_turn)(x);
}

#include "motorDriver.h"


void motorDriver::MyDriver(motor_control *motorControl, pClassFun motor_turn, int x) {
    (motorControl->*motor_turn)(x);
}

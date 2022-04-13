#include "pigpio.h"
#include "motor_control.h"
#include <iostream>
#include "motorDriver.h"
#include "motor.h"

using namespace std;
//the GPIO is 6 13 19 26

void motor::motor_l() {
    motorDriver driver;
    motor_control motorControl;
    driver.MyDriver(&motorControl, &motor_control::motor_turn, 0);
}

void motor::motor_r() {
    motorDriver driver;
    motor_control motorControl;
    driver.MyDriver(&motorControl, &motor_control::motor_turn, 1);
}

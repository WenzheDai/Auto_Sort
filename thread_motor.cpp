
#include "thread_motor.h"

thread_motor::thread_motor()
{
    lastMotorStateOPP = false;
    lastMotorStatePos = false;

}

void thread_motor::run()
{
    while(1)
    {
        if (get_run_motor() && !lastMotorStatePos)
        {
            qDebug("run motor");
            lastMotorStatePos=true;
            driver.MyDriver(&motorControl, &motor_control::motor_turn, 0);
            lastMotorStateOPP= false;
            msleep(1000);
        }
        else if (!get_run_motor() && !lastMotorStateOPP)
        {
            qDebug("stop motor");
            lastMotorStatePos = false;
            driver.MyDriver(&motorControl, &motor_control::motor_turn, 1);
            lastMotorStateOPP = true;
            msleep(1000);
        }

    }
}

void thread_motor::set_run_motor(bool motor_state) {
    mMotorState = motor_state;
}

bool thread_motor::get_run_motor() {
    return mMotorState;
}

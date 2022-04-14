
#include "thread_motor.h"

thread_motor::thread_motor()
{

}

void thread_motor::run()
{
    while(1)
    {
        qDebug("run thread_motor");
        if (getC() == 0)
        {
            driver.MyDriver(&motorControl, &motor_control::motor_turn, 0);
            break;
        }
        if (getC() == 1)
        {
            driver.MyDriver(&motorControl, &motor_control::motor_turn, 1);
            break;
        }

    }
}


int thread_motor::getC() const {
    return C;
}

void thread_motor::setC(int c) {
    C = c;
}

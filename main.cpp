#include "pigpio.h"
#include "motor_control.h"
#include <iostream>
using namespace std;
//the GPIO is 6 13 19 26

int angle(int angle)
{
    int j = (int)(angle/0.70312);
    return j;
}

int motor()
{
    if (gpioInitialise()<0) return -1;    //init the librarys of pigpio
    motor_control pi;
    pi.setMode();
    //pi.motor_forward(cir);
    pi.motor_reverse(angle(120));
    gpioTerminate();  //stop the pigpio
}

void callback(int (*p)())
{
    p();
}

int main()
{
    callback(motor);
    return 0;
}














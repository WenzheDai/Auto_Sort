#include "pigpio.h"
#include "motor_control.h"
#include <iostream>
using namespace std;
//the GPIO is 6 13 19 26

void set_mode(motor_control pi)
{
    pi.setMode(pi.IN1, 0);
    pi.setMode(pi.IN2,0);
    pi.setMode(pi.IN3,0);
    pi.setMode(pi.IN4,0);

}

void motor_spin(motor_control pi, int cir)
{
    for(int i = 0;i<cir;i++)
    {
        pi.setPullUpDown(1, 0, 0, 0);
        pi.setStep(1, 0, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);  //every impulse delay 2000ms
        pi.setPullUpDown(0, 1, 0, 0);
        pi.setStep(0, 1, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
        pi.setPullUpDown(0, 0, 1, 0);
        pi.setStep(0, 0, 1, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
        pi.setPullUpDown(0, 0, 0, 1);
        pi.setStep(0, 0, 0, 1);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
    }
}

void motor_reverse(motor_control pi, int cir)
{
    for(int i = 0;i<cir;i++)
    {
        pi.setPullUpDown(0, 0, 0, 1);
        pi.setStep(0, 0, 0, 1);
        gpioSleep(PI_TIME_RELATIVE,0,2000);  //every impulse delay 2000ms

        pi.setPullUpDown(0, 0, 1, 0);
        pi.setStep(0, 0, 1, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);

        pi.setPullUpDown(0, 1, 0, 0);
        pi.setStep(0, 1, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);

        pi.setPullUpDown(1, 0, 0, 0);
        pi.setStep(1, 0, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
    }

}


int main()
{
    motor_control pi;
    pi.IN1 = 6;
    pi.IN2 = 13;
    pi.IN3 = 19;
    pi.IN4 = 26;
    if (gpioInitialise()<0) return -1;    //init the librarys of pigpio
    set_mode(pi);
    int cir = pi.motor_angle(180);
    //motor_spin(pi, cir);
    motor_reverse(pi, cir);

    gpioTerminate();  //stop the pigpio
    return 0;
}














#include <iostream>
#include "pigpio.h"
#include "motor_control.h"
#include "motorDriver.h"

void motor_control::setMode()
{
    gpioSetMode(6,PI_OUTPUT);
    gpioSetMode(13, PI_OUTPUT);
    gpioSetMode(19, PI_OUTPUT);
    gpioSetMode(26, PI_OUTPUT);
}

void motor_control::setStep(int h1, int h2, int h3, int h4)
{
    gpioWrite(6, h1);
    gpioWrite(13, h2);
    gpioWrite(19, h3);
    gpioWrite(26, h4);
}

void motor_control::setPullUpDown(int h1, int h2, int h3, int h4)
{
    if(h1==1 && h2==0 && h3==0 && h4==0)
    {
        gpioSetPullUpDown(6, PI_PUD_UP);
        gpioSetPullUpDown(13, PI_PUD_DOWN);
        gpioSetPullUpDown(19, PI_PUD_DOWN);
        gpioSetPullUpDown(26, PI_PUD_DOWN);
    }

    if(h1==0 && h2==1 && h3==0 && h4==0)
    {
        gpioSetPullUpDown(6, PI_PUD_DOWN);
        gpioSetPullUpDown(6, PI_PUD_DOWN);
        gpioSetPullUpDown(13, PI_PUD_UP);
        gpioSetPullUpDown(19, PI_PUD_DOWN);
        gpioSetPullUpDown(26, PI_PUD_DOWN);
    }

    if(h1==0 && h2==0 && h3==1 && h4==0)
    {
        gpioSetPullUpDown(6, PI_PUD_DOWN);
        gpioSetPullUpDown(13, PI_PUD_DOWN);
        gpioSetPullUpDown(19, PI_PUD_UP);
        gpioSetPullUpDown(26, PI_PUD_DOWN);
    }

    if(h1==0 && h2==0 && h3==0 && h4==0)
    {
        gpioSetPullUpDown(6, PI_PUD_DOWN);
        gpioSetPullUpDown(13, PI_PUD_DOWN);
        gpioSetPullUpDown(19, PI_PUD_DOWN);
        gpioSetPullUpDown(26, PI_PUD_UP);
    }
}

void motor_control::motor_forward(int cir)
{
    for(int i = 0;i<cir;i++)
    {
        setPullUpDown(1, 0, 0, 0);
        setStep(1, 0, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);  //every impulse delay 2000ms
        setPullUpDown(0, 1, 0, 0);
        setStep(0, 1, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
        setPullUpDown(0, 0, 1, 0);
        setStep(0, 0, 1, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
        setPullUpDown(0, 0, 0, 1);
        setStep(0, 0, 0, 1);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
    }
}

void motor_control::motor_reverse(int cir)
{
    for(int i = 0;i<cir;i++)
    {
        setPullUpDown(0, 0, 0, 1);
        setStep(0, 0, 0, 1);
        gpioSleep(PI_TIME_RELATIVE,0,2000);  //every impulse delay 2000ms

        setPullUpDown(0, 0, 1, 0);
        setStep(0, 0, 1, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);

        setPullUpDown(0, 1, 0, 0);
        setStep(0, 1, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);

        setPullUpDown(1, 0, 0, 0);
        setStep(1, 0, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
    }

}

int motor_control::angle(int angle)
{
    int j = (int)(angle/0.70312);
    return j;
}

int motor_control::motor_turn(int x)
{
    if (gpioInitialise()<0) return -1;    //init the librarys of pigpio
    setMode();
    if(x==0)
    {
        motor_forward(angle(120));
    }
    if(x==1)
    {
        motor_reverse(angle(120));
    }
    gpioTerminate();  //stop the pigpio
}






























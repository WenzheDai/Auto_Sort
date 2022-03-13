#include <iostream>
#include "pigpio.h"
#include "motor_control.h"

void motor_control::setMode(int IN, int putNum)
{
    if(putNum == 0)
    {
        gpioSetMode(IN, PI_OUTPUT);
    }
    else if(putNum == 1)
    {
        gpioSetMode(IN,PI_INPUT);
    }
    else
    {
        printf("putNum only is 0 or 1");
    }
}

void motor_control::setStep(int h1, int h2, int h3, int h4)
{
    gpioWrite(IN1, h1);
    gpioWrite(IN2, h2);
    gpioWrite(IN3, h3);
    gpioWrite(IN4, h4);
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

int motor_control::motor_angle(int angle)
{
    int j = (int)(angle/0.70312);
    return j;
}


























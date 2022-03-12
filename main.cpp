#include "pigpio.h"
using namespace std;
//the GPIO is 6 13 19 26

//set the every GPIO level
void setStep(int h1, int h2, int h3, int h4)
{
    gpioWrite(6, h1);
    gpioWrite(13, h2);
    gpioWrite(19, h3);
    gpioWrite(26, h4);
}

//pull up the high-level GPIO's resistance
void pulldown(int h1, int h2, int h3, int h4)
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

//the number of loops is calculated by the angle
int montor_angle(int angle)
{
    int j = (int)(angle/0.70312);
    return j;
}


int main()
{
    if (gpioInitialise() < 0) return 1;  //init the librarys of pigpio

    //set the type of GPIO(input or output)
    gpioSetMode(6, PI_OUTPUT);
    gpioSetMode(13, PI_OUTPUT);
    gpioSetMode(19, PI_OUTPUT);
    gpioSetMode(26, PI_OUTPUT);


    int cir = montor_angle(3600); //turn it at 3600 degress
    int i = 0;

    //main loops
    while (i<cir)
    {
        pulldown(1, 0, 0, 0);
        setStep(1, 0, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);  //every impulse delay 2000ms
        pulldown(0, 1, 0, 0);
        setStep(0, 1, 0, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
        pulldown(0, 0, 1, 0);
        setStep(0, 0, 1, 0);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
        pulldown(0, 0, 0, 1);
        setStep(0, 0, 0, 1);
        gpioSleep(PI_TIME_RELATIVE,0,2000);
        i++;
    }

    gpioTerminate();  //stop the pigpio
    return 0;
}


































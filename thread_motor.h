
#ifndef AUTO_SORT_THREAD_MOTOR_H
#define AUTO_SORT_THREAD_MOTOR_H
#include <QThread>
#include "motor/motorDriver.h"
#include "motor/motor_control.h"


class thread_motor : public QThread{
    Q_OBJECT
public:
    thread_motor();
    motorDriver driver;
    motor_control motorControl;

private:
    int C;
public:
    int getC() const;

    void setC(int c);

private:
    void run();

};


#endif //AUTO_SORT_THREAD_MOTOR_H


#ifndef AUTO_SORT_THREAD_MOTOR_H
#define AUTO_SORT_THREAD_MOTOR_H
#include <QThread>
#include "motor/motorDriver.h"
#include "motor/motor_control.h"


class thread_motor : public QThread{
    Q_OBJECT
public:
    thread_motor();
    void set_run_motor(bool motor_state);
    bool get_run_motor();
    motorDriver driver;
    motor_control motorControl;

private:
    void run();
    bool mMotorState;
    bool lastMotorStatePos;
    bool lastMotorStateOPP;

};


#endif //AUTO_SORT_THREAD_MOTOR_H

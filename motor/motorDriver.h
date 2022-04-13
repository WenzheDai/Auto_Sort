//
// Created by jackno2d on 2022/4/12.
//

#ifndef AUTO_SORT_MOTORDRIVER_H
#define AUTO_SORT_MOTORDRIVER_H
#include "motor_control.h"
typedef int(motor_control::*pClassFun)(int);

class motorDriver {
public:

//callback function
void MyDriver(motor_control *motorControl, pClassFun motor_turn, int x);
};


#endif //AUTO_SORT_MOTORDRIVER_H

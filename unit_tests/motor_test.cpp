#include <gtest/gtest.h>
#include "motor/motor_control.h"



TEST(motor_test, MotorMove) {
    motor_control m;
    EXPECT_EQ(m.motor_turn(1),1);
}

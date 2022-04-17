#include <gtest/gtest.h>
#include "motor/motor_control.h"


// Demonstrate some basic assertions.
TEST(motor_test, BasicAssertions) {
    motor_control m;
    EXPECT_EQ(m.motor_turn(1),1);
}

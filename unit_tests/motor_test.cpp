#include <gtest/gtest.h>
#include "motor/motor_control.h"
#include "pigpio.h"

class motorTest : public ::testing::Test
{

protected:
    virtual void SetUp() {
        std::cout<<"check the motor";

    }

    virtual void TearDown() {
        std::cout<<"check the motor ok!";

    }
    motor_control m;
};

TEST_F(motorTest, SetMode)
{
    m.setMode();
    EXPECT_EQ(gpioGetMode(6), 1)<<"the GPIO 6 put PI_OUTPUT";
    EXPECT_EQ(gpioGetMode(13), 1)<<"the GPIO 13 put PI_OUTPUT";
    EXPECT_EQ(gpioGetMode(19), 1)<<"the GPIO 19 put PI_OUTPUT";
    EXPECT_EQ(gpioGetMode(26), 1)<<"the GPIO 26 put PI_OUTPUT";
}

TEST_F(motorTest, Writelevel)
{
    m.setStep(1, 1, 1, 1);
    EXPECT_EQ(gpioRead(6), 1)<<"Write the level of GPIO 6 OK!";
    EXPECT_EQ(gpioRead(13), 1)<<"Write the level of GPIO 6 OK!";
    EXPECT_EQ(gpioRead(19), 1)<<"Write the level of GPIO 6 OK!";
    EXPECT_EQ(gpioRead(26), 1)<<"Write the level of GPIO 6 OK!";
}

TEST_F(motorTest, Motormove) {
    EXPECT_EQ(m.motor_turn(1),1)<<"the motor forward OK!";
    EXPECT_EQ(m.motor_turn(0), 1)<<"the motor reverse OK!";
}

TEST_F(motorTest, angle)
{
    EXPECT_EQ(m.angle(60), (int)(60/0.70312))<<"the angle compute ok!";
}




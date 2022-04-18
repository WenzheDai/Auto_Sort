#include <gtest/gtest.h>
#include "motor/motor_control.h"
#include "detection/detecting.h"
#include "detection/object_detect.h"
#include "pigpio.h"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>

using std::cout; using std::cin;
using std::endl; using std::string;

using namespace cv;

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


class detectionTest : public ::testing::Test {
protected:
    void SetUp() {
    }
    Mat frame;
    Detecting detecting;
    Object_Detect mObject;
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

TEST_F(detectionTest, colorRGY)
{
    Mat frame = imread("../unit_tests/testImage/green.jpg");
//    char *cwd = get_current_dir_name();
//    cout << "Current working directory: " << cwd << endl;
//    free(cwd);
//    std::cout<<frame;
    cv::resize(frame, frame, Size(frame.cols /4, frame.rows /4));
    detecting.setCameraImage(frame);
    mObject = detecting.detectColor();
    string rColor = mObject.getColor();
    string eColor = "green";
    std::cout<<rColor;
    int ret = rColor.compare(eColor);
    EXPECT_EQ(ret, 0);
}




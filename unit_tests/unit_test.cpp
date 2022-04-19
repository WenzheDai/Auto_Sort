#include <gtest/gtest.h>
#include "motor/motor_control.h"
#include "detection/detecting.h"
#include "detection/object_detect.h"
#include "pigpio.h"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <string>

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


class detectionTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        std::cout<<"check the detecting";
    }
    virtual void TearDown(){

    }

    Detecting detecting;
    Object_Detect mObject;
};

TEST_F(detectionTest, colorG)
{
    Mat green = imread("../unit_tests/testImage/green.jpg");
    cv::resize(green, green, Size(green.cols / 4, green.rows / 4));
    detecting.setCameraImage(green);
    mObject = detecting.detectColor();
    string gColor = mObject.getColor();
    int g = gColor.compare("green");
    EXPECT_EQ(g, 0)<<"green check pass";
    EXPECT_EQ(mObject.getShape(), 4)<<"square check pass";
}

TEST_F(detectionTest, colorR)
{
    Mat red = imread("../unit_tests/testImage/red.jpg");

    cv::resize(red, red, Size(red.cols / 4, red.rows / 4));
    detecting.setCameraImage(red);
    mObject = detecting.detectColor();
    string rColor = mObject.getColor();
    int r = rColor.compare("red");
    EXPECT_EQ(r, 0)<<"red check pass"<<rColor;
}

TEST_F(detectionTest, colorY)
{
    Mat yellow = imread("../unit_tests/testImage/yellow.jpg");
    cv::resize(yellow, yellow, Size(yellow.cols / 4, yellow.rows / 4));
    detecting.setCameraImage(yellow);
    mObject = detecting.detectColor();
    string yColor = mObject.getColor();
    int r = yColor.compare("yellow");
    EXPECT_EQ(r, 0)<<"yellow check pass";
}

TEST_F(detectionTest, shapeC)
{
    Mat circle = imread("../unit_tests/testImage/circle.jpg");
    cv::resize(circle, circle, Size(circle.cols / 4, circle.rows / 4));
    detecting.setCameraImage(circle);
    mObject = detecting.detectColor();
    int cir = mObject.getShape();
    EXPECT_GE(cir, 5)<<"check circle pass";
}

TEST_F(detectionTest, shapeT)
{
    Mat triangle = imread("../unit_tests/testImage/triangle.jpg");
    cv::resize(triangle, triangle, Size(triangle.cols / 4, triangle.rows / 4));
    detecting.setCameraImage(triangle);
    mObject = detecting.detectColor();
    int tri = mObject.getShape();
    EXPECT_EQ(tri, 3);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}










































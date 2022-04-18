#include <gtest/gtest.h>
#include "detection/detecting.h"

class detectionTest : public ::testing::Test {
protected:
    void SetUp() {
    }
    Mat frame;
    Detecting detecting;
};

TEST_F(detectionTest, colorRGY)
{
    frame = cv::imread("./testImage/green.jpg");
    cv::resize(frame, frame, Size(frame.cols /4, frame.rows /4));
    detecting.setCameraImage(frame);
    //detecting.detectColor();
//    string rColor = detecting.detectColor().getColor();
    string eColor = "green";
//    int ret = eColor.compare(rColor);
//    std::cout<<rColor<<endl;
//    EXPECT_EQ(ret, 0);
}
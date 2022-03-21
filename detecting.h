#ifndef DETECTING_H
#define DETECTING_H
#include <opencv2/opencv.hpp>
#include "object_detect.h"
#include <QDebug>

using namespace cv;
class Detecting
{
public:
    Detecting();
    void setCameraImage(Mat src);
    Object_Detect detectColor();
    int detectShape();
private:
    Mat frame;
    Mat inputImageHSV;
    Mat mask;
    // HSV range to detect r, y, g color
    int minHue_R = 0, maxHue_R = 10;
    int minHue_Y = 25, maxHue_Y = 34;
    int minHue_G = 35, maxHue_G = 77;
    int minSat = 43, maxSat = 255;
    int minVal = 46, maxVal = 255;

    int reColor;
    int reShape;
    int mCount = 0;
    int mNum = 0;
    //默认capture 宽度和高度
    const int FRAME_WIDTH = 640/4;
    const int FRAME_HEIGHT = 480/4;
    //最小和最大物体面积
    const int MIN_OBJECT_AREA = 1000;
    const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;

    double shape_param = 0.05; //识别形状参数，调整范围（0.01-0.10）

private:
    void processMask(Mat& mMask, Object_Detect &mObject, string mColor);
    void morphOps(Mat &thresh);
};

#endif // DETECTING_H


#ifndef DETECTING_H
#define DETECTING_H

#include <opencv2/opencv.hpp>
#include "object_detect.h"
#include <QDebug>

using namespace cv;

/*!
 * @file detecting.h
 * @brief This file contains function for object detection
 *        HSV color space for color detection
 *        Polygon fitting for shape detection
 */
class Detecting {
public:
    Detecting();
    ~Detecting();

    void setCameraImage(Mat src);

    Object_Detect detectColor();

    int detectShape();

private:
    Mat frame;
    Mat inputImageHSV;
    Mat mask;
    // Range in HSV color space for detecting red, yellow, green color
    int minHue_R = 0, maxHue_R = 25;
    int minHue_Y = 25, maxHue_Y = 34;
    int minHue_G = 35, maxHue_G = 99;
    int minSat = 43, maxSat = 255;
    int minVal = 46, maxVal = 255;

    int reColor;
    int reShape;
    int mCount = 0;
    int mNum = 0;
    // Default width and height for capture frame
    const int FRAME_WIDTH = 640 / 4;
    const int FRAME_HEIGHT = 480 / 4;
    // Set the size range for object detected
    const int MIN_OBJECT_AREA = 1500;
    const int MAX_OBJECT_AREA = FRAME_HEIGHT * FRAME_WIDTH / 1;

    // Polygon Fitting Accuracy Parameters，range（0.01-0.10）
    double shape_param = 0.043;//0.045

private:
    void processMask(Mat &mMask, Object_Detect &mObject, string mColor);

    void morphOps(Mat &thresh);
};

#endif // DETECTING_H


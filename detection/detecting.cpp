#include "detecting.h"


Detecting::Detecting() {

}

void Detecting::setCameraImage(Mat src) {
    frame = src;
}

Object_Detect Detecting::detectColor() {
    Object_Detect mObject;
    cvtColor(frame, inputImageHSV, cv::COLOR_BGR2HSV);

    // Create mask and result (masked) image

    // params: input array, lower boundary array, upper boundary array, output array
    inRange(
            inputImageHSV,
            Scalar(minHue_R, minSat, minVal),
            Scalar(maxHue_R, maxSat, maxVal),
            mask
    );
    processMask(mask, mObject, "red");

    inRange(
            inputImageHSV,
            Scalar(minHue_Y, minSat, minVal),
            Scalar(maxHue_Y, maxSat, maxVal),
            mask
    );
    processMask(mask, mObject, "yellow");

    inRange(
            inputImageHSV,
            Scalar(minHue_G, minSat, minVal),
            Scalar(maxHue_G, maxSat, maxVal),
            mask
    );
    processMask(mask, mObject, "green");
    //printf("mColor = %s \n", mObject.getColor().c_str());



    Mat resultImage;
    // params: src1	array, src2 array, output array, mask
    bitwise_and(frame, frame, resultImage, mask);

    //// 4. Show images
    //cv::imshow("Input Image", frame);
    //cv::imshow("Result (Masked) Image", resultImage);
    return mObject;
}

void Detecting::processMask(Mat &mMask, Object_Detect &mObject, string mColor) {
    morphOps(mMask);
    Mat temp;
    mMask.copyTo(temp);
    //these two vectors needed for output of findContours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<Point> point;

    //find contours of filtered image using openCV findContours function
    findContours(temp, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point());
    //use moments method to find our filtered object
    int minVal = 46, maxVal = 255;
    bool objectFound = false;


    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        for (int index = 0; index >= 0; index = hierarchy[index][0]) {
            Moments moment = moments((cv::Mat) contours[index]);
            double area = moment.m00;
            // Might be noise if area less than 20px * 20px
            // Might be broken filter if area equals to 3/2 frame area
            // Only need the object with the largest area
            // Iterate and compare it to the area in the next iteration

            qDebug("area = %f", area);
            if (area > MIN_OBJECT_AREA) {
                int cx = int(moment.m10 / area);
                int cy = int(moment.m01 / area);
                if (cx > frame.cols * 0.25 && cx < frame.cols * 0.75) {
                    circle(frame, Point(cx, cy), 2, Scalar(255, 255, 255), 1, 8, 0);
                    objectFound = true;
                    mNum++;
                    if (mNum == 1) {
                        mCount++;
                    }
                } else {
                    mNum = 0;
                }


            } else {
                objectFound = false;
            }
            //let user know you found an object
            //qDebug("mCount = %d", mCount);
            mObject.setCount(mCount);
            if (objectFound == true) {
                int epsilon = shape_param * arcLength(contours[index], true);
                approxPolyDP(contours[index], point, epsilon, true);
                //printf("point = %d \n", point.size());
                qDebug("point.size() = %d", point.size());
                //draw object location on screen
                //drawObject(objects,cameraFeed);
                drawContours(frame, contours, index, (128), 1, 8, hierarchy);
                mObject.setColor(mColor);
                mObject.setShape(point.size());
                //mObject.setCount(mCount);
            } else {
                //mObject.setCount(-1);
            }

        }
    }
}


void Detecting::morphOps(Mat &thresh) {
    // Create structural elements for "expanding" and "eroding" images.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(2, 2));
    // Dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(3, 3));//8,8

    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);

    dilate(thresh, thresh, dilateElement);
    dilate(thresh, thresh, dilateElement);
    //imshow("th", thresh);
}


/****************************************************shape************************************************/
int Detecting::detectShape() {
    return 0;
}

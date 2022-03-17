#include "detecting.h"


Detecting::Detecting()
{

}
void Detecting::setCameraImage(Mat src)
{
    frame = src;
}
Object_Detect Detecting::detectColor()
{
   Object_Detect mObject;
   cvtColor(frame, inputImageHSV, cv::COLOR_BGR2HSV);

   //// 3. Create mask and result (masked) image

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

void Detecting::processMask(Mat& mMask, Object_Detect &mObject, string mColor)
{
    morphOps(mMask);
    Mat temp;
    mMask.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<Point> point;

    //find contours of filtered image using openCV findContours function
    findContours(temp, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point());
    //use moments method to find our filtered object
    //double refArea = 0;
    bool objectFound = false;
    //vector<vector<Point>> contours_poly(contours.size());//用于存放折线点集
    /*for (int i = 0; i<contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), contours_poly[i], 5, true);

        drawContours(frame, contours_poly, i, Scalar(0, 255, 255), 2, 8);  //绘制
    }*/
    //imshow("approx", frame);
    if (hierarchy.size() > 0)
    {
        int numObjects = hierarchy.size();
        for (int index = 0; index >= 0; index = hierarchy[index][0])
        {
             Moments moment = moments((cv::Mat)contours[index]);
             double area = moment.m00;
             //如果面积小于20px乘以20px，则可能只是噪声
             //如果面积与图像大小的3/2相同，可能只是一个坏的过滤器
             //只需要具有最大面积的对象，因此每个对象都有一个安全的参考区域
             //迭代并将其与下一次迭代中的区域进行比较。

             qDebug("area = %f", area);
             if(area > MIN_OBJECT_AREA)
             {
                 int cx = int(moment.m10 / area);
                 int cy = int(moment.m01 / area);
                 if(cx>frame.cols*0.25 && cx < frame.cols * 0.75) {
                     circle(frame, Point(cx, cy), 2, Scalar(255, 255, 255), 1, 8, 0);
                 }

                 objectFound = true;
             }
             else
             {
                 objectFound = false;
             }
             //let user know you found an object
             if(objectFound == true)
              {
                  int epsilon = 0.05*arcLength(contours[index], true);
                  approxPolyDP(contours[index], point, epsilon, true);
                  //printf("point = %d \n", point.size());
                  qDebug("point.size() = %d", point.size());
                  //draw object location on screen
                  //drawObject(objects,cameraFeed);
                  drawContours(frame, contours, index, (128), 3, 8,hierarchy);
                  mObject.setColor(mColor);
                  mObject.setShape(point.size());
              }
        }
    }
}


void Detecting::morphOps(Mat &thresh)
{
    //创建用于“扩张”和“侵蚀”形象的结构元素。
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(7,7));//8,8

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);
    //imshow("th", thresh);
}



/****************************************************shape************************************************/
int Detecting::detectShape()
{
    return 0;
}

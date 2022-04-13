#ifndef OBJECT_DETECT_H
#define OBJECT_DETECT_H
#include <iostream>

using namespace std;
class Object_Detect
{
public:
    Object_Detect();
    void setColor(string mC);
    string getColor();
    void setShape(int mS);
    int getShape();
    void setCount(int mC);
    int getCount();
private:
    string mColor;
    int mShape;
    int mCount;
};

#endif // OBJECT_DETECT_H

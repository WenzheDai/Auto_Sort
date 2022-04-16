#include "object_detect.h"

Object_Detect::Object_Detect()
{

}

void Object_Detect::setColor(string mC)
{
    mColor = mC;
}
string Object_Detect::getColor()
{
    return mColor;
}
void Object_Detect::setShape(int mS)
{
    mShape = mS;
}
int Object_Detect::getShape()
{
    return mShape;
}

void Object_Detect::setCount(int mC)
{
    mCount = mC;
}

int Object_Detect::getCount()
{
    return mCount;
}

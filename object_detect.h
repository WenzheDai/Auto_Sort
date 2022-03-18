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
private:
    string mColor;
    int mShape;
};

#endif // OBJECT_DETECT_H

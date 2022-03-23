#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H
#include <QLabel>
#include <QString>

class ImageUtils
{
public:
    ImageUtils();
    void setLED(QLabel* label, int color, int size);
};

#endif // IMAGEUTILS_H

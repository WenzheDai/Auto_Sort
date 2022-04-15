#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QLabel>
#include <QString>

/*!
 * @file ImageUtils.h
 * @brief Set the Parameters for user interface of realtime detector
 */
class ImageUtils {
public:
    ImageUtils();

    void setLED(QLabel *label, int color, int size);
};

#endif // IMAGEUTILS_H

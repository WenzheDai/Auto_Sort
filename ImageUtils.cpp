#include "ImageUtils.h"

ImageUtils::ImageUtils() {

}

void ImageUtils::setLED(QLabel *label, int color, int size) {
    // Clear the text in the label
    label->setText("");
    // Set the rectangle size
    // if label for ui was smaller than minimum width and height, rectangle size will be set by minimum width and height
    // otherwise, rectangle size will be set by maximum width and height
    QString min_width = QString("min-width: %1px;").arg(size);              // Minimum width：size
    QString min_height = QString("min-height: %1px;").arg(size);            // Minimum height：size
    QString max_width = QString("max-width: %1px;").arg(size);              // Maximum width：size
    QString max_height = QString("max-height: %1px;").arg(size);            // Maximum height：size
    // Set the border shape and border
    QString border_radius = QString("border-radius: %1px;").arg(
            size / 2);    // The border is rounded with a radius of size/2
    QString border = QString("border:1px solid black;");                    // set as 1px in black
    // Set the background color
    QString background = "background-color:";
    switch (color) {
        case 0:
            // grey
            background += "rgb(190,190,190)";
            break;
        case 1:
            // Red
            background += "rgb(255,0,0)";
            break;
        case 2:
            // Green
            background += "rgb(0,255,0)";
            break;
        case 3:
            // Yellow
            background += "rgb(255,255,0)";
            break;
        default:
            break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}

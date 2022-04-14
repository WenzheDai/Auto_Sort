#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTimeEdit>
#include <QGraphicsScene>
#include <opencv2/opencv.hpp>
#include "ImageUtils.h"
#include "detecting.h"
#include "thread_motor.h"

using namespace std;
using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ImageUtils *mUtils;
    //camera
    VideoCapture cap;
    Mat frame;
    QGraphicsScene *scene = new QGraphicsScene;
    QTimer *Time_camera ;//camera的更新时间
    QTimer *timer_run;
    QTime *time;
    int time_num;
    Detecting *mDetecting;
    Object_Detect mObject;
    thread_motor* mThread;


    //检测开关
    bool detect_w = false;
    enum {
        red, yellow, green, square, circle, triangle
    };
    int m_color;
    int m_shape;



private slots:
    //内联
    void on_Bt_start_clicked();
    void open_camera_time_click();

    void On_Changed_R();
    void On_Changed_Y();
    void On_Changed_G();

    void On_Changed_T();
    void On_Changed_S();
    void On_Changed_C();

    void updateTime();

    void on_Bt_stop_clicked();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

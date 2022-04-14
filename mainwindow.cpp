#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mThread = new thread_motor();

    mUtils = new ImageUtils();
    mUtils->setLED(ui->label_led_red, 0, 16);
    mUtils->setLED(ui->label_led_yellow, 0, 16);
    mUtils->setLED(ui->label_led_green, 0, 16);
    mUtils->setLED(ui->label_led_square, 0, 16);
    mUtils->setLED(ui->label_led_circle, 0, 16);
    mUtils->setLED(ui->label_led_Triangle, 0, 16);

    ui->label_team->setText("team_name");
    ui->groupBox->setStyleSheet("background-color: rgba(200,200,200,1)");


    time = new QTime();
    time->setHMS(0,0,0);
    time_num = 0;

    mDetecting = new Detecting();

    //选择按键
    connect(ui->checkBox_R, SIGNAL(stateChanged(int)), this, SLOT(On_Changed_R()));
    connect(ui->checkBox_Y, SIGNAL(stateChanged(int)), this, SLOT(On_Changed_Y()));
    connect(ui->checkBox_G, SIGNAL(stateChanged(int)), this, SLOT(On_Changed_G()));

    connect(ui->checkBox_T, SIGNAL(stateChanged(int)), this, SLOT(On_Changed_T()));
    connect(ui->checkBox_S, SIGNAL(stateChanged(int)), this, SLOT(On_Changed_S()));
    connect(ui->checkBox_C, SIGNAL(stateChanged(int)), this, SLOT(On_Changed_C()));
    m_color = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//打开摄像头预览
void MainWindow::on_Bt_start_clicked()
{
    Time_camera = new QTimer(this);
    connect(Time_camera, SIGNAL(timeout()), this, SLOT(open_camera_time_click()));
    Time_camera->start(30);//30ms刷新一次camera fps=30
    frame = cap.open(0);
//    cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 1);
//    cap.set(cv::CAP_PROP_EXPOSURE, 600);
    if(!cap.isOpened()){
        printf("open camera failed !");
    }

    timer_run = new QTimer(this);
    connect(timer_run, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer_run->start(1000);

}


void MainWindow::open_camera_time_click()
{

    //显示计数
    QString countShow;
    //weightshow.sprintf("%d (g)", ui->horizontalSlider->value());
    //ui->label_set_weight_show->setText(weightshow);

    //get image
    cap.read(frame);
    if(frame.empty()){
        qDebug("frame.empty()");
        return;
    }
    cv::resize(frame, frame,Size(frame.cols/4, frame.rows/4));
    mDetecting->setCameraImage(frame);
    mObject = mDetecting->detectColor();
    if(mObject.getColor() == "red")
    {
        mUtils->setLED(ui->label_led_red, 1, 16);
        mUtils->setLED(ui->label_led_yellow, 0, 16);
        mUtils->setLED(ui->label_led_green, 0, 16);
    }
    else if (mObject.getColor() == "yellow") {
        mUtils->setLED(ui->label_led_red, 0, 16);
        mUtils->setLED(ui->label_led_yellow, 3, 16);
        mUtils->setLED(ui->label_led_green, 0, 16);
    }
    else if (mObject.getColor() == "green") {
        mUtils->setLED(ui->label_led_red, 0, 16);
        mUtils->setLED(ui->label_led_yellow, 0, 16);
        mUtils->setLED(ui->label_led_green, 2, 16);
    } else {
        mUtils->setLED(ui->label_led_red, 0, 16);
        mUtils->setLED(ui->label_led_yellow, 0, 16);
        mUtils->setLED(ui->label_led_green, 0, 16);
    }

    //qDebug("state,R = %d", ui->checkBox_R->isChecked());
    //qDebug("state,Y = %d", ui->checkBox_Y->isChecked());
    //qDebug("state,G = %d", ui->checkBox_G->isChecked());
    //qDebug("m_color = %d", m_color);




    int mshape = mObject.getShape();
    //QString t_1 =  QString::number(m_color);
    //QString t_1 =  QString::number(mshape);
    //ui->textBrowser_count->setText(t_1);
    //red, yellow, green, square, circle, triangle
    if(mshape == 3)
    {
        mUtils->setLED(ui->label_led_Triangle, 1, 16);
        mUtils->setLED(ui->label_led_square, 0, 16);
        mUtils->setLED(ui->label_led_circle, 0, 16);
    }
    else if (mshape == 4) {
        mUtils->setLED(ui->label_led_Triangle, 0, 16);
        mUtils->setLED(ui->label_led_square, 1, 16);
        mUtils->setLED(ui->label_led_circle, 0, 16);
    }
    else if (mshape >= 5) {
        mUtils->setLED(ui->label_led_Triangle, 0, 16);
        mUtils->setLED(ui->label_led_square, 0, 16);
        mUtils->setLED(ui->label_led_circle, 1, 16);
    } else {
        mUtils->setLED(ui->label_led_Triangle, 0, 16);
        mUtils->setLED(ui->label_led_square, 0, 16);
        mUtils->setLED(ui->label_led_circle, 0, 16);
    }

    switch (m_color)
    {
    case red:
        if (m_shape == 0){
            if(mObject.getColor()=="red" && mObject.getShape()==3){
                qDebug("yes,R triangle!");
                if (mThread->getC() != 1)
                {
                    cout<<mThread->getC()<<"***************";
                    mThread -> setC(0);
                    mThread -> start();
                    mThread->terminate();
                }

            }

        }
        else if (m_shape == 1) {
            if(mObject.getColor()=="red" && mObject.getShape()==4){
                qDebug("yes,R square!");
            }

        }
        else if (m_shape == 2) {
            if(mObject.getColor()=="red" && mObject.getShape()>=5){
                qDebug("yes,R circle!");
            }
        }

        break;
    case yellow:
        if (m_shape == 0){
            if(mObject.getColor()=="yellow" && mObject.getShape()==3){
                qDebug("yes,Y triangle!");
            }

        }
        else if (m_shape == 1) {
            if(mObject.getColor()=="yellow" && mObject.getShape()==4){
                 qDebug("yes,Y square!");
            }

        }
        else if (m_shape == 2) {
            if(mObject.getColor()=="yellow" && mObject.getShape()>=5){
                qDebug("yes,Y circle!");
            }

        }
        break;
    case green:
        if (m_shape == 0){
            if(mObject.getColor()=="green" && mObject.getShape()==3){
                qDebug("yes,G triangle!");
            }

        }
        else if (m_shape == 1) {
            if(mObject.getColor()=="green" && mObject.getShape()==4){
                qDebug("yes,G square!");
            }

        }
        else if (m_shape == 2) {
            if(mObject.getColor()=="green" && mObject.getShape()>=5) {
                qDebug("yes,G circle!");
            }

        }
        break;
    default:
        if (mThread->getC() != 0)
        {
            mThread->start();
            mThread->setC(1);
        }
        break;
    }

    int shape_num = mObject.getCount();
    if (shape_num >= 0)
    {
        ui->textBrowser_count->setText(QString::number(shape_num));
    }

    //创建显示容器
    cvtColor(frame, frame, COLOR_BGR2RGB);
	cv::resize(frame, frame, Size(380, 280));
    QImage showImage = QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
    //向容器中添加文件路径为fileName（QString类型）的文件
    scene->addPixmap(QPixmap::fromImage(showImage));
    //借助graphicsView（QGraphicsView类）控件显示容器的内容
    ui->graphicsView_Camera->setScene(scene);
    //开始显示
    ui->graphicsView_Camera->show();
}

void MainWindow::On_Changed_R()
{

    if(ui->checkBox_R->isChecked())
    {
         ui->checkBox_Y->setChecked(false);
         ui->checkBox_G->setChecked(false);
         m_color = 0;
    }else {
         m_color = -1;
    }


}

void MainWindow::On_Changed_Y()
{
    if(ui->checkBox_Y->isChecked())
    {
         ui->checkBox_R->setChecked(false);
         ui->checkBox_G->setChecked(false);
         m_color = 1;
    }else {
         m_color = -1;
    }


}

void MainWindow::On_Changed_G()
{
    if(ui->checkBox_G->isChecked())
    {
         ui->checkBox_R->setChecked(false);
         ui->checkBox_Y->setChecked(false);
         m_color = 2;
    }else {
         m_color = -1;
    }

}


void MainWindow::On_Changed_T()
{

    if(ui->checkBox_T->isChecked())
    {
         ui->checkBox_S->setChecked(false);
         ui->checkBox_C->setChecked(false);
         m_shape = 0;
    }else {
         m_shape = -1;
    }

}

void MainWindow::On_Changed_S()
{
    if(ui->checkBox_S->isChecked())
    {
         ui->checkBox_T->setChecked(false);
         ui->checkBox_C->setChecked(false);
         m_shape = 1;
    }else {
         m_shape = -1;
    }

}

void MainWindow::On_Changed_C()
{
    if(ui->checkBox_C->isChecked())
    {
         ui->checkBox_T->setChecked(false);
         ui->checkBox_S->setChecked(false);
         m_shape = 2;
    }else {
         m_shape = -1;
    }

}

void MainWindow::updateTime()
{
    //qDebug("update");
    time_num++;
    QString strTime;
    strTime = time->addSecs(time_num).toString("hh:mm:ss");
    //strTime = time->currentTime().toString("hh:mm:ss");
    qDebug("update = %s", qPrintable(strTime));
    ui->textBrowser_timeShow->setText(strTime);
}

//退出
void MainWindow::on_Bt_stop_clicked()
{   printf("exit....");
    this->close();
}

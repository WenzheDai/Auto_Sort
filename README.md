# Auto Sort
An automatic real-time system for detection and sorting things.
## Demo
A shrot video shows how Auto Sort work on Youtube.

[![](https://res.cloudinary.com/marcomontalbano/image/upload/v1650308343/video_to_markdown/images/youtube--slp1gwdWYJk-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://youtu.be/slp1gwdWYJk "")
## Requirements
* [OpenCV 4.5.3](https://github.com/opencv/opencv) on Raspberry Pi
  [How](https://qengineering.eu/install-opencv-4.5-on-raspberry-64-os.html)
* [pigpio v79](https://github.com/joan2937/pigpio)
* [Qt 5.15.2](https://www.qt.io)
* [Google Tests](https://github.com/google/googletest)
## How to
### Deploy
1. Build a new directory named "cmake-build-debug".
2. Move in to the new directory, run the following commands in the terminal.
   ```
   cmake ..
   make
   ```
3. Run `sudo ./Auto_Sort`
### Test
1. Deploy first.
2. Move in to directory named "cmake-build-debug".
3. Run following command in the terminal.
    ```
   sudo ./unit_test
   ```

## Hardware Building
### Material Preparation

The workingflow of this device is to transport the target objects smoothly to the inspedtion area of the camera. When the camera captures the object, the Raspberry Pi determines the shape and color of the object through a computer vision algorithm, and outputs a corresponding signal to the pin connnected to the stepper motor to control its left and right rotation.

In order to make sure the device works properly, it can be divided into 3 parts, i.e. pipeline mechanism, sorting mechanism and camera. The pipeline mechanism includes wooden racks, conveyor tracks and DC drive motor; sorting mechanism includes a baffle and a stepper motor. The camera and steper motor are connected to the Raspberry Pi, and the DC motors are powered directly from AA batteries. Following is the sketch of the first version of design.

![image](https://raw.githubusercontent.com/WenzheDai/Auto_Sort/master/media/sketch.jpg)

### Installation Guide
#### pipeline mechanism
The pipeline mechanism is based on wood rack. The track is driven by a DC motor powered by four AA batteries. The motor is fixed on the side of the drive shaft, and the battery box is fixed under the conveyor belt to ensure the consistency of the whole set. A purple conveyor belt is recommended to improve detection accuracy.
#### sorting mechanism
Connect the baffle to the drive shaft of the stepping motor, and then fix the stepping motor under the end of the conveyer belt to ensure that the object can hit the baffle when it falls. The stepper motor is connected to the Raspberry Pi through the driver board, which needs to be powered by four AA batteries.
#### camera
This device uses a USB micro camera to connect directly to the Raspberry Pi. The camera is fixed directly above the end of the conveyor belt, and it is necessary to avoid objects other than the crawler in the detection range.
#### wiring
The connection method of the stepper motor and camera to the Raspberry Pi is shown in the following figure:

![image](https://raw.githubusercontent.com/WenzheDai/Auto_Sort/master/media/circuit.jpeg)
The pin diagram of Raspberry Pi is shown in the following figure :

![image](https://raw.githubusercontent.com/WenzheDai/Auto_Sort/master/media/RaspberryPi.jpeg)
### Cost Estimation
* Raspberry Pi: £43.5
* pipeline mechanism: £6.5
* Sorting mechanism: £5
* Camera: £15
* Total: £70
## Real-Time Responsiveness
The program adopts multi-threading and asynchronous callback mechanism. When OpenCV calls the camera and starts to video successfully, the program will take frame of the object on the conveyor belt at a speed of 30 FPS and sent it to Raspberry Pi.

When the software analyses the incoming frame of picture captured by camera and successfully recognizes it, it will immediately send a detection signal and send a request to wake up another thread. The code enters the next thread and calls back the motor driver, the stepper motor turns and controls the baffle to turn around. This motor thread is continuing running, but the motor is sleeping until the camera loses the target object capture signal, the motor will be called back again to return to the initial position.

### Delay Analysis
In this project, the event response is mainly achieved by waking up the motor drive thread. We believe that the real-time performance of this system is mainly reflected in the sum of the single-frame image processing time of image processing thread, and the time of thread switching, plus the time signal arrives GPIO port connected to the motor drive, which should be lower than the time difference that can be distinguished by the naked eye.

In our test, time taken up by detecting shape and color is less than 20ms, which means that the detection can be done early than next frame(can be done in 1/30 s).

![image](https://raw.githubusercontent.com/WenzheDai/Auto_Sort/master/media/detectionTime.png)
## Project Directory Tree

    |–– detection
    | |–– detecting.cpp
    | |–– detecting.h
    | |—— ImageUtils.cpp
    | |–– ImageUtils.h
    | |–– mainwindow.cpp
    | |–– mainwindow.h
    | |–– mainwindow.ui
    | |–– object_detect.cpp
    | |–– object_detect.h
    | |–– ui_mainwindow.h
    |–– motor
    | |–– motor_control.cpp
    | |–– motor_control.h
    | |—— motorDriver.cpp
    | |–– motorDriver.h
    | |–– thread_motor.cpp
    | |–– thread_motor.h
    |–– unit_tests
    | |–– testImage
    | | |–– circle.jpg
    | | |–– green.jpg
    | | |–– red.jpg
    | | |–– triangle.jpg
    | | |–– yellow.jpg
    | |–– unit_test.cpp
    |–– CMakeLists.txt
    |—— main.cpp
    |—— README.md
## License
The information about the license [MIT](https://choosealicense.com/licenses/mit/) is given here.
## Authors
* [Wenzhe Dai, 2628148D](https://github.com/WenzheDai)
* [Yuzhong Ding, 2710301D](https://github.com/YuzhongDing)
* [Yiqi Li, 2640204L](https://github.com/NANARua)
* [Xiaohang Yu, 2693647Y](https://github.com/XiaohangYu1234)
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
1. Build a new directory name "cmake-build".
2. Move in to the new directory, run the following commands in the terminal.
   ```
   cmake ..
   make
   ```
3. Run `sudo ./Auto_Sort`
### Test
1. Move to your project directory. (where CMakeLists.txt located)
2. Run the following commands for building.
   ```
   cmake -S . -B build
   cmake --build build
   cd build && ctest
   ```
3. Tests result will show in terminal window.

## Hardware Building
### Material Preparation

The workingflow of this device is to transport the target objects smoothly to the inspedtion area of the camera. When the camera captures the object, the Raspberry Pi determines the shape and color of the object through a computer vision algorithm, and outputs a corresponding signal to the pin connnected to the stepper motor to control its left and right rotation.

In order to make sure the device works properly, it can be divided into 3 parts, i.e. pipeline mechanism, sorting mechanism and camera. The pipeline mechanism includes wooden racks, conveyor tracks and DC drive motor; sorting mechanism includes a baffle and a stepper motor. The camera and steper motor are connected to the Raspberry Pi, and the DC motors are powered directly from AA batteries. Following is the sketch of the first version of design.


### Installation Guide
#### 

### Cost Estimation
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
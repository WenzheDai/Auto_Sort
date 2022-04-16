# Auto Sort
An automatic real-time system for detection and sorting things.
## How to deploy
1. Build a new dictionary name "cmake-build-debug".
2. Move in to the new dictionary, run the following command in the terminal.
   ```
   cmake ..
   make
   ```
3. Run `sudo ./Auto_Sort`

## Hardware Building
### Material Preparation

The workingflow of this device is to transport the target objects smoothly to the inspedtion area of the camera. When the camera captures the object, the Raspberry Pi determines the shape and color of the object through a computer vision algorithm, and outputs a corresponding signal to the pin connnected to the stepper motor to control its left and right rotation.

In order to make sure the device works properly, it can be divided into 3 parts, i.e. pipeline mechanism, sorting mechanism and camera. The pipeline mechanism includes wooden racks, conveyor tracks and DC drive motor; sorting mechanism includes a baffle and a stepper motor. The camera and steper motor are connected to the Raspberry Pi, and the DC motors are powered directly from AA batteries. Following is the sketch of the first version of design.


### Installation Guide
#### 

### Cost Estimation
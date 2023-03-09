# Line Tracking Car
- Designed for HITSZ 2022 自动化认识与实践课程项目。
- 所有者：MaxwellJay256，CHENY

---
#### 文件说明
1. [Line_Tracking_car.ino](Line_Tracking_Car.ino)：小车的主程序
2. [Motor.h](Motor.h)和[Motor.cpp](Motor.cpp)：电机对象的声明和实现，内置PID控制器。
3. [IRSensor.h](IRSensor.h)和[IRSensor.cpp](IRSensor.cpp)：光电传感器对象的声明和实现。
4. [RobotArm.h](RobotArm.h)和[RobotArm.cpp](RobotArm.cpp)：对机械臂的一些操纵函数。
5. [Device.h](Device.h)和[Device.cpp](Device.cpp)：此处集中定义了电机、光电传感器、机械臂对象，以及对它们的初始化函数。
6. [Drive.h](Drive.h)和[Drive.cpp](Drive.cpp)：调用电机和传感器对象，实现对底盘的操纵，包括巡线。
#### 本工程的特点
1. 采用多文件，将功能分散。
2. 利用了C++的类和面向对象，将硬件抽象化，有利于代码维护。
例如在[Motor.h](Motor.h)和[Motor.cpp](Motor.cpp)中，一个减速电机内包装了多种变量以及函数，在主程序中，只需定义MotorL，MotorR两个对象，即可非常方便地对它们进行控制。
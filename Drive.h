#ifndef DRIVE_H
#define DRIVE_H
#include "Device.h"
#include "RobotArm.h"

namespace Drive
{
    extern double Vc;
    /// @brief 让车体按照一定直线速度和和自转速度移动
    void Move(double v, double w);
    double GetCarDirection();
    void classic_move();
    void PatrolEnd();
    void Patrol();
    void classic_move();  //这个是测试用的函数
}

#endif
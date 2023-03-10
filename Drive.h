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
    /// @brief 到达巡线终点时执行的程序
    void PatrolEnd();
    /// @brief 自动巡线
    void Patrol();
    /// @brief 测试用的函数
    void classic_move();

    void Turn(double degree, double w);
}

#endif
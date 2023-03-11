#ifndef DRIVE_H
#define DRIVE_H
#include "Device.h"
#include "RobotArm.h"

namespace Drive
{
    extern double Vc, Wc, vL, vR;
    /// @brief 让车体按照一定直线速度和和自转速度移动
    void Move(double v, double w);
    
    /// @brief 到达巡线终点时执行的程序
    void PatrolEnd();
    /// @brief 自动巡线
    void Patrol();

    /// @brief 车体旋转一定角度
    /// @param degree 要旋转的角度(deg)
    /// @param w 角速度(rad/s)
    void Turn(double degree);

    void RunTaskFor(void (*task)(), long runTime);
}

#endif
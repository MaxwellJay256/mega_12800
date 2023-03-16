#ifndef DRIVE_H
#define DRIVE_H
#include "Device.h"
#include "RobotArm.h"

namespace Drive
{
    extern double Vc, Wc, wL, wR;
    /// @brief 让车体按照一定直线速度和和自转速度移动
    /// @param v 直行线速度（cm/s）
    /// @param w 自转角速度（rad/s）
    void Move(double v, double w);
    
    /// @brief 到达巡线终点时执行的程序
    void PatrolEnd();
    /// @brief 自动巡线
    void Patrol();

    /// @brief 让一个任务重复运行固定的时间
    /// @param task 要执行的任务
    /// @param runTime 运行时间（ms）
    void RunTaskFor(void (*task)(), long runTime);

    /// @brief 超声波避障
    void ObstacleAvoidace();
}

#endif
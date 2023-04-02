#ifndef DRIVE_H
#define DRIVE_H
#include "Device.h"
#include "RobotArm.h"

namespace Drive
{
    extern double Vc, Wc, wL, wR;
    extern bool ObstacleAvoidFlag; //是否执行超声波避障

    /// @brief 让车体按照一定直线速度和和自转速度移动
    /// @param v 直行线速度（cm/s）
    /// @param w 自转角速度（rad/s）
    /// @note 底层的移动函数，能套用在多个任务执行中。
    void Move(double v, double w);
    /// @brief 自动巡线
    void Patrol();
    /// @brief 超声波避障
    void ObstacleAvoidace();
    /// @brief 到达巡线终点时执行的程序
    void PatrolEnd();

    /// @brief 让一个任务重复运行固定的时间
    /// @param task 要执行的任务
    /// @param runTime 运行时间（ms）
    void RunTaskFor(void (*task)(), long runTime);
}

#endif // DRIVE_H
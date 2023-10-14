#ifndef ROBOTARM_H_
#define ROBOTARM_H_
#include "Device.h"

namespace RobotArm
{
    /// @brief 夹取物体，并抬起机械臂
    void claw_up();
    /// @brief 放下机械臂，然后松开物体
    void claw_down();
}

#endif // ROBOTARM_H_
#ifndef ROBOTARM_H
#define ROBOTARM_H
#include "Device.h"

/// @brief 夹取物体，并抬起机械臂
void ClawUp();
/// @brief 放下机械臂，然后松开物体
void ClawDown();

#endif // ROBOTARM_H
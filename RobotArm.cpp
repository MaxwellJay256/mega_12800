#include "RobotArm.h"
#define LIFT_DOWN_POSITION 74
#define LIFT_UP_POSITION 100
#define CLAW_FREE_POSITION 90
#define CLAW_HOLD_POSITION 125

namespace RobotArm
{
    void ClawUp() {
        Claw.write(CLAW_FREE_POSITION);
        delay(200);
        Claw.write(CLAW_HOLD_POSITION);
        delay(700);
        Lift.write(LIFT_UP_POSITION);
        delay(1000);
    }

    void ClawDown() {
        Lift.write(LIFT_DOWN_POSITION);
        delay(900);
        Claw.write(CLAW_FREE_POSITION);
    }
}
#include "RobotArm.h"
#define LIFT_DOWN_POSITION 74
#define LIFT_UP_POSITION 100
#define CLAW_FREE_POSITION 90
#define CLAW_HOLD_POSITION 125

namespace RobotArm
{
    void claw_up()
    {
        claw.write(CLAW_FREE_POSITION);
        delay(200);
        claw.write(CLAW_HOLD_POSITION);
        delay(700);
        lift.write(LIFT_UP_POSITION);
        delay(1000);
    }

    void claw_down()
    {
        lift.write(LIFT_DOWN_POSITION);
        delay(900);
        claw.write(CLAW_FREE_POSITION);
    }
}
#include "RobotArm.h"
#define LIFT_DOWN_POSITION 0
#define LIFT_UP_POSITION 35
#define CLAW_FREE_POSITION 45
#define CLAW_HOLD_POSITION 85

void ClawUp() {
    Claw.write(CLAW_FREE_POSITION);
    delay(500);
    Claw.write(CLAW_HOLD_POSITION);
    delay(500);
    Lift.write(LIFT_UP_POSITION);
    delay(1000);
}

void ClawDown() {
    Lift.write(LIFT_DOWN_POSITION);
    delay(500);
    Claw.write(CLAW_FREE_POSITION);
    delay(1000);
}
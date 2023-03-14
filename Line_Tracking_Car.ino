#include <MsTimer2.h>
#include "Motor.h"
#include "Sensor.h"
#include "Device.h"
#include "Drive.h"

void Control() {
    Drive::Patrol();
}

bool ObstacleAvoidFlag = true;

void setup()
{
    //PWM频率调节，设置9、10引脚的PWM输出频率为31372Hz，适合于我们使用的电机
    TCCR1B = TCCR1B & B11111000 | B00000001;
    DeviceInit();
    RobotArm::ClawDown();
    RobotArm::ClawUp();
    MsTimer2::set(period, Control);
    MsTimer2::start();
}

void loop()
{
    DisplayInfo();
    /*/ 只执行一次超声波避障
    if ( ObstacleAvoidFlag ) {
        Drive::ObstacleAvoidace();
        ObstacleAvoidFlag = false;
    }
    //*/
    //Drive::PatrolEnd();
    delay(period);
}

#include <MsTimer2.h>
#include "Motor.h"
#include "Sensor.h"
#include "Device.h"
#include "Drive.h"

void Control() {
    Drive::Patrol();
    // MotorR.Spin(-20);
    // MotorL.Spin(-10);
}

bool ObstacleAvoidFlag = true;

void setup()
{
    //PWM频率调节，设置9、10引脚的PWM输出频率为31372Hz，适合于我们使用的电机
    TCCR1B = TCCR1B & B11111000 | B00000001;
    pinMode(LED_BUILTIN, OUTPUT);
    DeviceInit();
    RobotArm::ClawDown();
    RobotArm::ClawUp();
    MsTimer2::set(period, Control);
    MsTimer2::start();
}

void loop()
{
    HeartBeat();
    // DisplayInfo();
    /*/ 只执行一次超声波避障
    if ( ObstacleAvoidFlag ) {
        Drive::ObstacleAvoidace();
        ObstacleAvoidFlag = false;
    } else {
        Drive::PatrolEnd();
    }
    //*/
    delay(period);
}

bool heartBeatFlag = false;
void HeartBeat() {
    if ( heartBeatFlag ) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
    heartBeatFlag = !heartBeatFlag;
}
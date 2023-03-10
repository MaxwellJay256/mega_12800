#include <MsTimer2.h>
#include "Motor.h"
#include "IRSensor.h"
#include "Device.h"
#include "Drive.h"

void Control() {
    Drive::classic_move();
}

void setup()
{
    TCCR1B = TCCR1B & B11111000 | B00000001;//PWM频率调节，设置9、10引脚的PWM输出频率为31372Hz，适合于我们使用的电机
    DeviceInit();
    MsTimer2::set(period, Control);
    MsTimer2::start();
    Serial.begin(9600);
    // ClawDown();
    // ClawUp();
}

void loop()
{
    DisplayInfo();
    Serial.print(MotorL.velocity);
    Serial.print(",");
    Serial.print(MotorR.velocity);
    Serial.print(",");
    Serial.print(TARGET);
    Serial.print("\r\n");
    delay(period);
    //Drive::PatrolEnd();
}

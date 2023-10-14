#include <MsTimer2.h>
#include "Motor.h"
#include "Sensor.h"
#include "Device.h"
#include "Drive.h"

void Control() {
    Drive::patrol();
    // motor_L.Spin(30);
    // motor_R.Spin(30);
}

void setup()
{
    TCCR1B = TCCR1B & B11111000 | B00000001;//PWM频率调节
    pinMode(LED_BUILTIN, OUTPUT);
    device_init();
    RobotArm::claw_down();
    RobotArm::claw_up();
    MsTimer2::set(motor_L.period, Control);
    MsTimer2::start();
    Drive::obstacle_avoid_flag = true;
    // Serial.begin(9600);
}

void loop()
{
    HeartBeat();
    // DisplayInfo();
    // OLED_display_info();
    //*/ 只执行一次超声波避障，避障后才激活终点检测
    if ( Drive::obstacle_avoid_flag ) {
        Drive::obstacle_avoidace();
    } else {
        Drive::patrol_end();
    }
    //*/
    delay(motor_L.period);
}

bool heartBeatFlag = false;
/// @brief 让开发板的自带LED灯闪烁，证明开发板还活着。
/// @note 如子果程序未能退出或者硬件出现故障，loop不能正常循环，则灯会停止闪烁。
void HeartBeat() {
    if ( heartBeatFlag ) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
    heartBeatFlag = !heartBeatFlag;
}

/// @brief 串口打印一些信息
void DisplayInfo() {
    //*/ 显示光电传感器的结果
    for ( int i=0; i<7; i++ ) {
        if ( IRGroup[i].get_IR_status() ) {
            Serial.print("+");
        } else {
            Serial.print("-");
        }
    }
    Serial.println();
    //*/ 显示超声波获取的距离
    // Serial.println(Ranger.get_distance());
}
#ifndef DEVICE_H_
#define DEVICE_H_
#include "Motor.h"
#include "Sensor.h"
#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

extern Motor motor_L;
extern Motor motor_R;
extern IR L3_IR;
extern IR L2_IR;
extern IR L1_IR;
extern IR Mid_IR;
extern IR R1_IR;
extern IR R2_IR;
extern IR R3_IR;
extern IR IRGroup[7];

extern UltraSonic ranger;

extern Servo lift;
extern Servo claw;

extern Adafruit_SSD1306 OLED;
/// @brief 初始化OLED屏幕
void set_OLED(Adafruit_SSD1306 *oled);
extern const int TARGET;
void OLED_display_info();

/// @brief 集中初始化设备
void device_init();

#endif // DEVICE_H_
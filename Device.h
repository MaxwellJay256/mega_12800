#ifndef DEVICE_H
#define DEVICE_H
#include "Motor.h"
#include "Sensor.h"
#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

extern Motor MotorL;
extern Motor MotorR;
extern IR L3_IR;
extern IR L2_IR;
extern IR L1_IR;
extern IR Mid_IR;
extern IR R1_IR;
extern IR R2_IR;
extern IR R3_IR;
extern IR IRGroup[7];

extern UltraSonic Ranger;

extern Servo Lift;
extern Servo Claw;

extern Adafruit_SSD1306 OLED;
/// @brief 初始化OLED屏幕
void SetOLED(Adafruit_SSD1306 *oled);
extern const int TARGET;
void OLEDDisplayInfo();

/// @brief 集中初始化设备
void DeviceInit();

#endif

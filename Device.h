#ifndef DEVICE_H
#define DEVICE_H
#include "Motor.h"
#include "IRSensor.h"
#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

extern Motor MotorL;
extern Motor MotorR;
extern IR L2_IR;
extern IR L1_IR;
extern IR Mid_IR;
extern IR R1_IR;
extern IR R2_IR;

extern Servo Lift;
extern Servo Claw;

extern Adafruit_SSD1306 OLED;
void SetOLED(Adafruit_SSD1306 *oled);
extern const int TARGET;
void DisplayInfo();

void DeviceInit();

#endif

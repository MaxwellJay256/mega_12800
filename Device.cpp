#include "Device.h"

Motor MotorL(9,12,13,3,4,true);
Motor MotorR(10,11,6,2,5,false);//这里引脚口改了一下
IR L3_IR(48);
IR L2_IR(46);
IR L1_IR(44);
IR Mid_IR(42);
IR R1_IR(40);
IR R2_IR(38);
IR R3_IR(36);
IR IRGroup[5] = {L2_IR, L1_IR, Mid_IR, R1_IR, R2_IR};

Adafruit_SSD1306 OLED(128,64);
void SetOLED(Adafruit_SSD1306 *oled) {
    oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled->setTextColor(WHITE);
    oled->setTextSize(1);
    oled->cp437(true);
    oled->clearDisplay();
    oled->display();
}

const int TARGET = 10;
void DisplayInfo() {
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    OLED.print("Target speed: ");
    OLED.println(TARGET);
    OLED.print("\nLeft speed:  ");
    OLED.println(MotorL.velocity);
    OLED.print("Left output: ");
    OLED.println(MotorL.output);
    OLED.print("\nRight speed: ");
    OLED.println(MotorR.velocity);
    OLED.print("Right output: ");
    OLED.println(MotorR.output);
    OLED.display();     
}

void GetEncoderL() { MotorL.GetEncoder(); }
void GetEncoderR() { MotorR.GetEncoder(); }

void DeviceInit() {
    attachInterrupt(1, GetEncoderL, CHANGE);
    attachInterrupt(0, GetEncoderR, CHANGE);
    // Lift.attach(3);
    // Claw.attach(4);
    SetOLED(&OLED);
} 

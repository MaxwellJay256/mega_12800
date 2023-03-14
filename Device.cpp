#include "Device.h"
#include "Drive.h"

Motor MotorL(9,12,13,3,4,true);
Motor MotorR(10,11,34,2,14,false);//这里引脚口改了一下
IR L3_IR(48);
IR L2_IR(46);
IR L1_IR(44);
IR Mid_IR(42);
IR R1_IR(40);
IR R2_IR(38);
IR R3_IR(36);
IR IRGroup[7] = {L3_IR, L2_IR, L1_IR, Mid_IR, R1_IR, R2_IR, R3_IR};

UltraSonic Ranger(26,28);

Servo Lift;
Servo Claw;

Adafruit_SSD1306 OLED(128,64);
void SetOLED(Adafruit_SSD1306 *oled) {
    oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled->setTextColor(WHITE);
    oled->setTextSize(1);
    oled->cp437(true);
    oled->clearDisplay();
    oled->display();
}

void DisplayInfo() {
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    /*/
    OLED.println();
    OLED.print("\nLeft speed:  ");
    OLED.println(MotorL.velocity);
    OLED.print("Left output: ");
    OLED.println(MotorL.output);
    OLED.print("\nRight speed: ");
    OLED.println(MotorR.velocity);
    OLED.print("Right output: ");
    OLED.println(MotorR.output);
    //*/
    for ( int i=0; i<7; i++ ) {
        if ( IRGroup[i].GetIRStatus() ) {
            OLED.print("+");
        } else {
            OLED.print("-");
        }
    }
    OLED.println();
    OLED.print("\nVc_ref: ");
    OLED.println(Drive::Vc);
    OLED.print("Wc: ");
    OLED.println(Drive::Wc);
    OLED.print("wL: ");
    OLED.println(Drive::vL/3.3);
    OLED.print("wR: ");
    OLED.println(Drive::vR/3.3);
    OLED.display();
    //*/
}

void GetEncoderL() { MotorL.GetEncoder(); }
void GetEncoderR() { MotorR.GetEncoder(); }

void DeviceInit() {
    MotorL.Initialize();
    MotorR.Initialize();
    Ranger.Initialize();
    attachInterrupt(digitalPinToInterrupt(MotorL.ENCODER_A), GetEncoderL, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MotorR.ENCODER_A), GetEncoderR, CHANGE);
    Lift.attach(8);
    Claw.attach(5);
    SetOLED(&OLED);
} 
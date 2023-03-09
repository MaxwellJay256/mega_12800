#include "Device.h"

Motor MotorL(6,8,7,2,4,true);
Motor MotorR(10,9,11,3,5,false);//这里引脚口改了一下

IR L2_IR(A1);
IR L1_IR(A2);
IR Mid_IR(A3);
IR R1_IR(A4);
IR R2_IR(A5);

//Adafruit_SSD1306 OLED(128,64);
/*void SetOLED(Adafruit_SSD1306 *oled) {
    oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled->setTextColor(WHITE);
    oled->setTextSize(1);
    oled->cp437(true);
    oled->clearDisplay();
    oled->display();
}
*/

/*/
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
//*/

void GetEncoderL() { MotorL.GetEncoder(); }
void GetEncoderR() { MotorR.GetEncoder(); }

void DeviceInit()
{
    attachInterrupt(0, GetEncoderL, CHANGE);
    attachInterrupt(1, GetEncoderR, CHANGE);
    // Lift.attach(3);
    // Claw.attach(4);
    //SetOLED(&OLED);
} 
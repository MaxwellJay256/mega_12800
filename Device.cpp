#include "Device.h"
#include "Drive.h"

#define MOTOR_L_PWM 9
#define MOTOR_L_INL1 12
#define MOTOR_L_INL2 15
#define MOTOR_L_ENCODER_A 3
#define MOTOR_L_ENCODER_B 4
#define MOTOR_R_PWM 10
#define MOTOR_R_INL1 11
#define MOTOR_R_INL2 34
#define MOTOR_R_ENCODER_A 2
#define MOTOR_R_ENCODER_B 14
Motor MotorL(MOTOR_L_PWM, MOTOR_L_INL1, MOTOR_L_INL2, MOTOR_L_ENCODER_A, MOTOR_L_ENCODER_B, true);
Motor MotorR(MOTOR_R_PWM, MOTOR_R_INL1, MOTOR_R_INL2, MOTOR_R_ENCODER_A, MOTOR_R_ENCODER_B, false);

IR L3_IR(48);
IR L2_IR(46);
IR L1_IR(44);
IR Mid_IR(42);
IR R1_IR(40);
IR R2_IR(38);
IR R3_IR(36);
IR IRGroup[7] = {L3_IR, L2_IR, L1_IR, Mid_IR, R1_IR, R2_IR, R3_IR};

#define RANGER_TRIG_PIN 25
#define RANGER_ECHO_PIN 24
UltraSonic Ranger(RANGER_TRIG_PIN, RANGER_ECHO_PIN);

#define SERVO_LIFT_PIN 8
#define SERVO_CLAW_PIN 5
Servo Lift;//机械臂
Servo Claw;//夹爪

// Adafruit_SSD1306 OLED(128,64);
void SetOLED(Adafruit_SSD1306 *oled) {
    oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled->setTextColor(WHITE);
    oled->setTextSize(1);
    oled->cp437(true);
    oled->clearDisplay();
    oled->display();
}
/// @brief OLED屏幕显示一些信息
void OLEDDisplayInfo() {
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    //*/ 显示电机的速度和PWM输出
    OLED.println();
    OLED.print("\nLeft speed:  ");
    OLED.println(MotorL.velocity);
    OLED.print("Left output: ");
    OLED.println(MotorL.output);
    OLED.print("\nRight speed: ");
    OLED.println(MotorR.velocity);
    OLED.print("Right output: ");
    OLED.println(MotorR.output);
    OLED.display();
    /*/ 显示光电传感器的结果以及底盘参考速度
    for ( int i=0; i<7; i++ ) {
        if ( IRGroup[i].GetIRStatus() ) {
            OLED.print("+");
        } else {
            OLED.print("-");
        }
    }
    OLED.println();
    OLED.print("\nVc: ");
    OLED.println(Drive::Vc);
    OLED.print("Wc: ");
    OLED.println(Drive::Wc);
    OLED.print("wL: ");
    OLED.println(Drive::wL);
    OLED.print("wR: ");
    OLED.println(Drive::wR);
    OLED.display();
    //*/
}

void GetEncoderL() { MotorL.GetEncoder(); }
void GetEncoderR() { MotorR.GetEncoder(); }

float Kp = 15, Ti = 30, Td = 10;
void DeviceInit() {
    // SetOLED(&OLED);
    // OLED.clearDisplay();
    // OLED.setCursor(0, 0);
    // OLED.println("Car initializing...");
    // OLED.display();
    MotorL.SetPID(Kp, Ti, Td);
    MotorR.SetPID(Kp, Ti, Td);
    MotorL.Initialize();
    MotorR.Initialize();
    Ranger.Initialize();
    attachInterrupt(digitalPinToInterrupt(MotorL.ENCODER_A), GetEncoderL, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MotorR.ENCODER_A), GetEncoderR, CHANGE);
    Lift.attach(SERVO_LIFT_PIN);
    Claw.attach(SERVO_CLAW_PIN);
    // OLED.println("Initialize success!");
    // OLED.display();
} 
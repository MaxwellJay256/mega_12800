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
Motor motor_L(MOTOR_L_PWM, MOTOR_L_INL1, MOTOR_L_INL2, MOTOR_L_ENCODER_A, MOTOR_L_ENCODER_B, true);
Motor motor_R(MOTOR_R_PWM, MOTOR_R_INL1, MOTOR_R_INL2, MOTOR_R_ENCODER_A, MOTOR_R_ENCODER_B, false);

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
UltraSonic ranger(RANGER_TRIG_PIN, RANGER_ECHO_PIN);

#define SERVO_LIFT_PIN 8
#define SERVO_CLAW_PIN 5
Servo lift; //机械臂
Servo claw; //夹爪

// Adafruit_SSD1306 OLED(128,64);
void set_OLED(Adafruit_SSD1306 *oled)
{
    oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled->setTextColor(WHITE);
    oled->setTextSize(1);
    oled->cp437(true);
    oled->clearDisplay();
    oled->display();
}
/// @brief OLED屏幕显示一些信息
void OLED_display_info()
{
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    //*/ 显示电机的速度和PWM输出
    OLED.println();
    OLED.print("\nLeft speed:  ");
    OLED.println(motor_L.velocity_);
    OLED.print("Left output: ");
    OLED.println(motor_L.output_);
    OLED.print("\nRight speed: ");
    OLED.println(motor_R.velocity_);
    OLED.print("Right output: ");
    OLED.println(motor_R.output_);
    OLED.display();
    /*/ 显示光电传感器的结果以及底盘参考速度
    for ( int i=0; i<7; i++ ) {
        if ( IRGroup[i].get_IR_status() ) {
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

void GetEncoderL() { motor_L.get_encoder(); }
void GetEncoderR() { motor_R.get_encoder(); }

float Kp = 15, Ti = 30, Td = 10;
void device_init()
{
    // set_OLED(&OLED);
    // OLED.clearDisplay();
    // OLED.setCursor(0, 0);
    // OLED.println("Car initializing...");
    // OLED.display();
    motor_L.set_PID(Kp, Ti, Td);
    motor_R.set_PID(Kp, Ti, Td);
    motor_L.initialize();
    motor_R.initialize();
    ranger.initialize();
    attachInterrupt(digitalPinToInterrupt(motor_L.encoder_A_), GetEncoderL, CHANGE);
    attachInterrupt(digitalPinToInterrupt(motor_R.encoder_A_), GetEncoderR, CHANGE);
    lift.attach(SERVO_LIFT_PIN);
    claw.attach(SERVO_CLAW_PIN);
    // OLED.println("Initialize success!");
    // OLED.display();
} 
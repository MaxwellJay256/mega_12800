#include "Motor.h"

const int period = 20;
const double Pi = acos(-1);

/// @brief 生成一个电机对象
/// @param _EN PWM输出端口
/// @param _INL1 正反转控制引脚
/// @param _INL2 正反转控制引脚
/// @param _ENCODER_A 编码器A端口（中断）
/// @param _ENCODER_B 编码器B端口
/// @param _isReverse 是否设置为反转
Motor::Motor(uint8_t _EN,uint8_t _INL1,uint8_t _INL2,uint8_t _ENCODER_A,uint8_t _ENCODER_B,bool _isReverse)
{
    EN0 = _EN;
    INL1 = _INL1;
    INL2 = _INL2;
    ENCODER_A = _ENCODER_A;
    ENCODER_B = _ENCODER_B;
    pinMode(EN0, OUTPUT);
    pinMode(INL2, OUTPUT);
    pinMode(INL1, OUTPUT);
    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);
    isReverse = _isReverse;
    encoderVal = 0;
    encoderLeapValue = isReverse ? -1 : 1;
}

void Motor::SetPin(uint8_t _EN,uint8_t _INL1,uint8_t _INL2,uint8_t _ENCODER_A,uint8_t _ENCODER_B)
{
    EN0 = _EN;
    INL1 = _INL1;
    INL2 = _INL2;
    ENCODER_A = _ENCODER_A;
    ENCODER_B = _ENCODER_B;
    pinMode(EN0, OUTPUT);
    pinMode(INL2, OUTPUT);
    pinMode(INL1, OUTPUT);
    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);
}

void Motor::Initialize() {
    digitalWrite(INL1, LOW);
    digitalWrite(INL2, LOW);
    analogWrite(EN0, 0);
}

void Motor::GetEncoder() {
    if ( digitalRead(ENCODER_A) == LOW ) {
        if ( digitalRead(ENCODER_B) == LOW ) {
            encoderVal -= encoderLeapValue;
        } else {
            encoderVal += encoderLeapValue;
        }
    } else {
        if ( digitalRead(ENCODER_B) == LOW ) {
            encoderVal += encoderLeapValue;
        } else {
            encoderVal -= encoderLeapValue;
        }
    }
}

const float Kp = 10, Ti = 5, Td = 5, T = period; //原先为5 140 80 
int Motor::PIDControl(double target)
{
    //离散增量式PID
    static float q0 = Kp * ( 1 + T/Ti + Td/T);
    static float q1 = -Kp * ( 1 + 2*Td/T );
    static float q2 = Kp * Td/T;
    static float u = 0;
    eI = target - velocity;
    u += q0*eI + q1*eII + q2*eIII; 
    eIII = eII; eII = eI;//更新上次和上上次误差
    if ( u >= 255 ) {   
        u = 255;
    }
    if ( u <= -255 ) {
        u = -255;
    }
    return (int)u; 
}

void Motor::Spin(double _targetVelocity) {
    velocity = (encoderVal / 780.0) * Pi * 2.0 * (1000 / period);
    encoderVal = 0;
    output = PIDControl(_targetVelocity);
    if ( output >= 0 ) {
        digitalWrite(INL1, LOW);
        digitalWrite(INL2, HIGH);
        analogWrite(EN0, output);
    } else {
        digitalWrite(INL1, HIGH);
        digitalWrite(INL2, LOW);
        analogWrite(EN0, -output);
    }
}

Motor::~Motor() {
    delete this;
}

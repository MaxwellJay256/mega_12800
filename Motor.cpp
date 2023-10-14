#include "Motor.h"

const double Pi = acos(-1);

/// @brief 实例化一个电机对象
/// @param EN PWM输出端口
/// @param INL1 正反转控制引脚
/// @param INL2 正反转控制引脚
/// @param encoder_A 编码器 A 端口（中断）
/// @param encoder_B 编码器 B 端口
/// @param is_reverse 是否设置为反转
Motor::Motor(
    uint8_t EN0, 
    uint8_t INL1, uint8_t INL2, 
    uint8_t encoder_A, uint8_t encoder_B, 
    bool is_reverse=false)
    : EN0_(EN0), 
    INL1_(INL1), INL2_(INL2), 
    encoder_A_(encoder_A), encoder_B_(encoder_B), 
    is_reverse_(is_reverse), 
    encoder_val_(0), 
    encoder_leap_value_(is_reverse_ ? -1 : 1)
{
    pinMode(EN0_, OUTPUT);
    pinMode(INL2_, OUTPUT);
    pinMode(INL1_, OUTPUT);
    pinMode(encoder_A_, INPUT);
    pinMode(encoder_B_, INPUT);
}

void Motor::initialize()
{
    digitalWrite(INL1_, LOW);
    digitalWrite(INL2_, LOW);
    digitalWrite(EN0_, LOW);
}

void Motor::set_PID(float Kp, float Ti, float Td)
{
    Kp_ = Kp; Ti_ = Ti; Td_ = Td;
}

void Motor::get_encoder()
{
    if (digitalRead(encoder_A_) == LOW)
    {
        if (digitalRead(encoder_B_) == LOW) {
            encoder_val_ -= encoder_leap_value_;
        } else {
            encoder_val_ += encoder_leap_value_;
        }
    } else {
        if (digitalRead(encoder_B_) == LOW) {
            encoder_val_ += encoder_leap_value_;
        } else {
            encoder_val_ -= encoder_leap_value_;
        }
    }
}

int Motor::PID_control(double target)
{
    //离散增量式PID
    static float q0 = Kp_ * ( 1 + period/Ti_ + Td_/period);
    static float q1 = -Kp_ * ( 1 + 2*Td_/period );
    static float q2 = Kp_ * Td_/period;
    static float u = 0;
    eI_ = target - velocity_;
    u += q0*eI_ + q1*eII_ + q2*eIII_; 
    eIII_ = eII_; eII_ = eI_; //更新上次和上上次误差
    if (u >= 255) {   
        u = 255;
    }
    if (u <= -255) {
        u = -255;
    }
    return (int)u; 
}

void Motor::spin(double target_velocity)
{
    velocity_ = (encoder_val_ / 780.0) * Pi * 2.0 * (1000 / period);
    encoder_val_ = 0;
    output_ = PID_control(target_velocity);
    if (output_ >= 0) {
        digitalWrite(INL1_, LOW);
        digitalWrite(INL2_, HIGH);
        analogWrite(EN0_, output_);
    } else {
        digitalWrite(INL1_, HIGH);
        digitalWrite(INL2_, LOW);
        analogWrite(EN0_, -output_);
    }
}

Motor::~Motor()
{
    detachInterrupt(digitalPinToInterrupt(encoder_A_));
}

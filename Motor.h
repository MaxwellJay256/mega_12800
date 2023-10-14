#ifndef MOTOR_H_
#define MOTOR_H_
#include <Arduino.h>

/// @brief 底盘电机
class Motor
{
private:
    volatile long encoder_val_; //编码器值
    float eI_, eII_, eIII_;
    uint8_t EN0_, INL1_, INL2_, encoder_B_;
    bool is_reverse_; //是否反转
    int encoder_leap_value_;
    /// @brief 使用 PID 计算电机需要的模拟值
    /// @return 电机需要的模拟值
    int PID_control(double target);
    float Kp_, Ti_, Td_;
public:
    const int period = 20;
    uint8_t encoder_A_;
    float velocity_;//速度
    int output_;//输出模拟值
    //float targetVelocity;//目标速度
    
    Motor(
        uint8_t EN, 
        uint8_t INL1, uint8_t INL2, 
        uint8_t encoder_A, uint8_t encoder_B, 
        bool is_reverse=false);
    ~Motor();

    /// @brief 初始化电机，不让其转动
    void initialize();
    /// @brief 修改电机的PID参数
    void set_PID(float Kp, float Ti, float Td);
    /// @brief 获取电机的编码器值
    void get_encoder();
    /// @brief 对电机进行PWM控制
    void spin(double _targetVelocity);
};

#endif // MOTOR_H
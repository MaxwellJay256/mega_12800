#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

extern const int period;
/// @brief 底盘电机
class Motor
{
    private:
        volatile long encoderVal;//编码器值
        float eI, eII, eIII;
        uint8_t EN0, INL1, INL2, ENCODER_B;
        bool isReverse;//是否反转
        int encoderLeapValue;
        /// @brief 使用PID计算电机需要的模拟值
        /// @return 电机需要的模拟值
        int PIDControl(double target);
        float Kp, Ti, Td;
    public:
        uint8_t ENCODER_A;
        float velocity;//速度
        int output;//输出模拟值
        //float targetVelocity;//目标速度
        
        Motor(uint8_t _EN,uint8_t _INL1,uint8_t _INL2,uint8_t _ENCODER_A,uint8_t _ENCODER_B,bool _isReverse);
        /// @brief 初始化电机，不让其转动
        void Initialize();
        /// @brief 修改电机的PID参数
        void SetPID(float _Kp, float _Ti, float _Td);
        /// @brief 获取电机的编码器值
        void GetEncoder();
        /// @brief 对电机进行PWM控制
        void Spin(double _targetVelocity);
        ~Motor();
};

#endif // MOTOR_H
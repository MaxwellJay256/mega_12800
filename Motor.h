#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

extern const int period;
class Motor
{
    private:
        volatile long encoderVal;//编码器值
        float eI, eII, eIII;
        uint8_t EN0, INL1, INL2, ENCODER_A, ENCODER_B; //!这里重名了
        bool isReverse;//是否反转
        int encoderLeapValue;
    public:
        float velocity;//速度
        int output;//输出模拟值
        //float targetVelocity;//目标速度
        Motor(bool _isReverse);
        Motor(uint8_t _EN,uint8_t _INL1,uint8_t _INL2,uint8_t _ENCODER_A,uint8_t _ENCODER_B,bool _isReverse);
        
        /// @brief 修改电机的针脚参数（虽然可能没什么用）
        /// @param _EN PWM输出端口
        /// @param _INL1 正反转控制引脚
        /// @param _INL2 正反转控制引脚
        /// @param _ENCODER_A 编码器A端口（中断）
        /// @param _ENCODER_B 编码器B端口
        void SetPin(uint8_t _EN,uint8_t _INL1,uint8_t _INL2,uint8_t _ENCODER_A,uint8_t _ENCODER_B);
        /// @brief 使用PID计算电机需要的模拟值
        /// @return 电机需要的模拟值
        int PIDControl(double target);
        /// @brief 获取电机的编码器值
        void GetEncoder();
        /// @brief 对电机进行PWM控制
        void Spin(double _targetVelocity);
        ~Motor();
};

#endif
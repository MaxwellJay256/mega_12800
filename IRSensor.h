#ifndef IRSENSOR_H
#define IRSENSOR_H
#include <Arduino.h>

class IR {
    private:
        uint8_t pin;//数据端口
        bool status;//传感器状态
    public:
        /// @brief 生成一个红外线传感器对象
        IR(uint8_t _pin);
        /// @brief 获取传感器状态
        /// @return 传感器是否压线
        bool GetIRStatus();
};

#endif
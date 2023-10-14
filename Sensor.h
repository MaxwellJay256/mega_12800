#ifndef SENSOR_H_
#define SENSOR_H_
#include <Arduino.h>

/// @brief 光电传感器
class IR
{
private:
    uint8_t pin_; //数据端口
public:
    /// @brief 红外线传感器构造函数
    IR(uint8_t pin);
    ~IR(){};
    /// @brief 获取传感器状态
    /// @return 传感器是否压线
    bool get_IR_status();
};

/// @brief 超声波传感器
class UltraSonic
{
private:
    uint8_t trig_pin_, echo_pin_;
    int distance_;
public:
    /// @brief 超声波传感器构造函数
    /// @param trigPin 
    /// @param echoPin 
    UltraSonic(uint8_t trig_pin, uint8_t echo_pin);
    ~UltraSonic(){};
    /// @brief 初始化超声波传感器
    void initialize();
    /// @brief 超声波测距
    /// @return 距离 (cm)
    float get_distance();
};

#endif // SENSOR_H_
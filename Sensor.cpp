#include "Sensor.h"

IR::IR(uint8_t pin) : pin_(pin)
{
    pin_ = pin;
    pinMode(pin_, INPUT);
}

bool IR::get_IR_status()
{
    return (digitalRead(pin_) == HIGH);
}

UltraSonic::UltraSonic(uint8_t trig_pin, uint8_t echo_pin) 
    : trig_pin_(trig_pin), echo_pin_(echo_pin)
{
    pinMode(trig_pin_, OUTPUT);
    pinMode(echo_pin_, INPUT);
}

void UltraSonic::initialize()
{
    digitalWrite(trig_pin_, LOW);
}

float UltraSonic::get_distance()
{
    digitalWrite(trig_pin_, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin_, LOW);
    distance_ = pulseIn(echo_pin_, HIGH) / 58.0;
    return distance_;
}
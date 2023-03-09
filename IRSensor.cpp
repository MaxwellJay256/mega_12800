#include "IRSensor.h"

IR::IR(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, INPUT);
    status = false;
}

bool IR::GetIRStatus()
{
    if ( digitalRead(pin) == HIGH )
        status = false; //红外线传感器在白色区域时，输出高电平
    else 
        status = true; //红外线传感器压住黑线时，输出低电平
    return status;
}
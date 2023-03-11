#include "IRSensor.h"

IR::IR(uint8_t _pin) {
    pin = _pin;
    pinMode(pin, INPUT);
}

bool IR::GetIRStatus() {
    return (digitalRead(pin)==HIGH);
}
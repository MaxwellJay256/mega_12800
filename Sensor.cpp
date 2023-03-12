#include "Sensor.h"

IR::IR(uint8_t _pin) {
    pin = _pin;
    pinMode(pin, INPUT);
}

bool IR::GetIRStatus() {
    return (digitalRead(pin)==HIGH);
}

UltraSonic::UltraSonic(uint8_t _trigPin, uint8_t _echoPin) {
    Trig_Pin = _trigPin;
    Echo_Pin = _echoPin;
    pinMode(Trig_Pin, OUTPUT);
    pinMode(Echo_Pin, INPUT);
    digitalWrite(Trig_Pin, LOW);
}

float UltraSonic::GetDistance() {
    digitalWrite(Trig_Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Pin, LOW);
    distance = pulseIn(Echo_Pin, HIGH) / 58.0;
    return distance;
}
#pragma once
#include <Arduino.h>

bool _ball_found;
float _ball_angle;
bool IRinit(HardwareSerial *serial, uint32_t baudrate);
void valReceive();
float ballAngle() { return _ball_angle; }
bool ballFound() { return _ball_found; }
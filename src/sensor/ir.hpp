#pragma once
#include <Arduino.h>

#include "angleHelper.hpp"
#include "attacker.hpp"

extern bool _ball_found;
extern float _ball_angle;

bool IRinit(HardwareSerial *serial, uint32_t baudrate);
void valReceive();
float ballAngle();
bool ballNear();
bool ballFound();

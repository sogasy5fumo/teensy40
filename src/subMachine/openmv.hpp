#pragma once
#include <Arduino.h>

bool cameraInit(HardwareSerial *serial, uint32_t baudrate);
void cameraReceive();

int yellowDeg();
int blueDeg();
// int ballDistance();
int centerDeg();

int bDistance();
int yDistance();

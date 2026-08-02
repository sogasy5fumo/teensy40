#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "angleHelper.hpp"

class GYRO
{
private:
    Adafruit_BNO055 *_bno;
    float yaw = 0.0f;
public:
    bool init();
    void update();
    float getYaw() { return yaw; }
};
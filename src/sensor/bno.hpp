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
    Adafruit_BNO055 *_bno = nullptr;
    float yaw;
public:
    bool init(TwoWire *wire,uint8_t address);
    void update();
    float getYaw() { return yaw; }
};
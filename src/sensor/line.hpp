#pragma once
#include <Arduino.h>

class SideLine
{
private:
    bool _left, _right, _back;
public:
    bool Lineinit(HardwareSerial *serial, uint32_t baudrate);
    void valDetect();

    bool getLeft() const { return _left; }
    bool getRight() const { return _right; }
    bool getBack() const { return _back; }
};
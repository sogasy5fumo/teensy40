#include "line.hpp"

static HardwareSerial *_serial = nullptr;
static uint32_t _baudrate = 115200;

bool SideLine::Lineinit(HardwareSerial *serial, uint32_t baudrate){
    _serial = serial;
    _baudrate = baudrate;
    _serial->begin(_baudrate);

    _left = false;
    _right = false;
    _back = false;

    return true;
}

static uint8_t readByteBlocking(uint32_t timeout_ms = 100) {
    uint32_t start = millis();
    while (!_serial->available()) {
        if (millis() - start > timeout_ms) return 0; // タイムアウト時の値
    }
    return _serial->read();
}

void SideLine::valDetect()
{
    if (readByteBlocking() != 0xFF) return;
    _left = readByteBlocking();
    _right = readByteBlocking();
    _back = readByteBlocking();
    if (readByteBlocking() != 0xFE) return;
}


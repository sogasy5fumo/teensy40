#include "ir.hpp"
static HardwareSerial *_serial =nullptr;
static uint32_t _baudrate = 115200;

bool IRinit(HardwareSerial *serial, uint32_t baudrate)
{
    _serial = serial;
    _baudrate = baudrate;
    _serial->begin(_baudrate);

    _ball_found = false;
    _ball_angle = 0.0f;

    return true;
}

static uint8_t readByteBlocking(uint32_t timeout_ms = 100) {
    uint32_t start = millis();
    while (!_serial->available()) {
        if (millis() - start > timeout_ms) return 0; // タイムアウト時の値
    }
    return _serial->read();
}

void valReceive()
{
    if (readByteBlocking() != 0xFF) return;
    _ball_found = readByteBlocking();
    uint8_t high = readByteBlocking();
    uint8_t low = readByteBlocking();
    _ball_angle = ((high << 8) | low) / 10.0f;
    if (readByteBlocking() != 0xFE) return;
}
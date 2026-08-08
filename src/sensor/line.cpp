// #include "line.hpp"

// static HardwareSerial *_serial = nullptr;
// static uint32_t _baudrate = 115200;

// bool SideLine::Lineinit(HardwareSerial *serial, uint32_t baudrate){
//     _serial = serial;
//     _baudrate = baudrate;
//     _serial->begin(_baudrate);

//     _left = false;
//     _right = false;
//     _back = false;

//     return true;
// }

// static uint8_t readByteBlocking(uint32_t timeout_ms = 100) {
//     uint32_t start = millis();
//     while (!_serial->available()) {
//         if (millis() - start > timeout_ms) return 0; // タイムアウト時の値
//     }
//     return _serial->read();
// }

// void SideLine::valDetect()
// {
//     if (readByteBlocking() != 0xFF) return;
//     _left = readByteBlocking();
//     _right = readByteBlocking();
//     _back = readByteBlocking();
//     if (readByteBlocking() != 0xFE) return;
// }



#include "line.hpp"

#define START 0xFF
#define FINISH 0xFE

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

void SideLine::valDetect()
{
    if (_serial == nullptr) return;

    // 1パケット(5バイト)以上溜まっている間ループ
    while (_serial->available() >= 5)
    {
        // 先頭が0xFFでない場合は1バイト捨てて同期を合わせる
        if (_serial->peek() != START)
        {
            _serial->read();
            continue;
        }

        // パケット読み出し
        uint8_t header = _serial->read(); // 0xFF
        uint8_t left   = _serial->read();
        uint8_t right  = _serial->read();
        uint8_t back   = _serial->read();
        uint8_t footer = _serial->read();

        // 終端チェック
        if (footer == FINISH)
        {
            _left  = (left != 0);
            _right = (right != 0);
            _back  = (back != 0);
        }
    }
}
// #include "ir.hpp"

// #define START 0xFF
// #define CHECK 0xAA
// #define FINISH 0xFE

// static HardwareSerial *_serial =nullptr;
// static uint32_t _baudrate = 115200;

// bool _ball_found;
// float _ball_angle;
// bool _ball_near;

// bool IRinit(HardwareSerial *serial, uint32_t baudrate)
// {
//     _serial = serial;
//     _baudrate = baudrate;
//     _serial->begin(_baudrate);

//     _ball_found = false;
//     _ball_angle = 0.0f;

//     return true;
// }

// static uint8_t readByteBlocking(uint32_t timeout_ms = 100) {
//     uint32_t start = millis();
//     while (!_serial->available()) {
//         if (millis() - start > timeout_ms) return 0; // タイムアウト時の値
//     }
//     return _serial->read();
// }

// void valReceive()
// {
//     // 0xFFが見つかるまで読み飛ばす（同期を取り直す）
//     uint8_t b;
//     int guard = 0;
//     do {
//         b = readByteBlocking();
//         guard++;
//     } while (b != 0xFF && guard < 50); // 50回試しても見つからなければ諦める

//     if (b != 0xFF) return;

//     _ball_found = readByteBlocking();
//     uint8_t high = readByteBlocking();
//     uint8_t low = readByteBlocking();
//     _ball_near = readByteBlocking();

//     if (readByteBlocking() != 0xFE) {
//         return; // 終端が合わなければこの回は捨てる（次回また0xFFを探しにいく）
//     }


//     _ball_angle = ((high << 8) | low) / 10.0f;
// }

// float ballAngle()
// {
//     _ball_angle = normalizeDeg(_ball_angle);
//     return _ball_angle;

// }

// bool ballNear(){ return _ball_near; }

// bool ballFound() { return _ball_found; }



#include "ir.hpp"

#define START 0xFF
#define FINISH 0xFE

static HardwareSerial *_serial = nullptr;
static uint32_t _baudrate = 115200;

bool _ball_found;
float _ball_angle;
bool _ball_near;

bool IRinit(HardwareSerial *serial, uint32_t baudrate)
{
    _serial = serial;
    _baudrate = baudrate;
    _serial->begin(_baudrate);

    _ball_found = false;
    _ball_angle = 0.0f;
    _ball_near = false;

    return true;
}

void valReceive()
{
    if (_serial == nullptr) return;

    // 1パケット(6バイト)以上溜まっている間ループ
    while (_serial->available() >= 6)
    {
        // 先頭が0xFFでない場合は1バイト捨てて同期を合わせる
        if (_serial->peek() != START)
        {
            _serial->read();
            continue;
        }

        // パケット読み出し
        uint8_t header = _serial->read(); // 0xFF
        uint8_t found  = _serial->read();
        uint8_t high   = _serial->read();
        uint8_t low    = _serial->read();
        uint8_t near   = _serial->read();
        uint8_t footer = _serial->read();

        // 終端チェック
        if (footer == FINISH)
        {
            _ball_found = (found != 0);
            _ball_near  = (near != 0);
            _ball_angle = ((high << 8) | low) / 10.0f;
        }
    }
}

float ballAngle()
{
    return -(normalizeDeg(_ball_angle - 180.0f));
}

bool ballNear()  { return _ball_near; }
bool ballFound() { return _ball_found; }
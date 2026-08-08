// #include "openmv.hpp"

// static HardwareSerial *_serial = nullptr;
// static uint32_t _baudrate = 115200;

// uint8_t blue_visible;
// uint16_t blue_angle;
// uint16_t blue_dist;
// uint8_t yellow_visible;
// uint16_t yellow_angle;
// uint16_t yellow_dist;
// uint8_t green_visible;
// uint16_t green_angle;
// uint16_t green_dist;
// uint8_t orange_visible;
// uint16_t orange_angle;
// uint16_t orange_dist;

// bool cameraInit(HardwareSerial *serial, uint32_t baudrate)
// {
//     _serial = serial;
//     _baudrate = baudrate;
//     _serial->begin(_baudrate);


//     return true;
// }


// static uint8_t readByteBlocking(uint32_t timeout_ms = 10) {
//     uint32_t start = millis();
//     while (!_serial->available()) {
//         if (millis() - start > timeout_ms) return 0; // タイムアウト時の値
//     }
//     return _serial->read();
// }

// uint16_t readUint16() {
//     uint8_t low  = readByteBlocking(); // 1バイト目（下位）
//     uint8_t high = readByteBlocking(); // 2バイト目（上位）
//     return (uint16_t)low | ((uint16_t)high << 8);
// }

// void cameraReceive()
// {
//     // バッファに複数パケット分溜まっていたら、最新のものだけ残す
//     while (_serial->available() > 22) {
//         _serial->read();
//     }

//     // 0xFFが見つかるまで、このループ内で読み捨てる(loop()を跨がない)
//     uint8_t b;
//     bool synced = false;
//     uint32_t sync_start = millis();
//     while (millis() - sync_start < 25) {  // 全体で25msだけ探す
//         if (_serial->available()) {
//             b = _serial->read();
//             if (b == 0xFF) {
//                 synced = true;
//                 break;
//             }
//         }
//     }
//     if (!synced) return;   // 見つからなければ諦めて次のloop()で再挑戦

//     uint8_t b_vis = readByteBlocking();
//     uint16_t b_ang = readUint16();
//     uint16_t b_dist = readUint16();
//     uint8_t y_vis = readByteBlocking();
//     uint16_t y_ang = readUint16();
//     uint16_t y_dist = readUint16();
//     uint8_t g_vis = readByteBlocking();
//     uint16_t g_ang = readUint16();
//     uint16_t g_dist = readUint16();
//     uint8_t o_vis = readByteBlocking();
//     uint16_t o_ang = readUint16();
//     uint16_t o_dist = readUint16();

//     uint8_t finish_byte = readByteBlocking();
//     if (finish_byte != 0xFE) {
//         // Serial.print("FINISH NG: got 0x");
//         // Serial.println(finish_byte, HEX);
//         return;
//     }

//     blue_visible = b_vis; blue_angle = b_ang; blue_dist = b_dist;
//     yellow_visible = y_vis; yellow_angle = y_ang; yellow_dist = y_dist;
//     green_visible = g_vis; green_angle = g_ang; green_dist = g_dist;
//     orange_visible = o_vis; orange_angle = o_ang; orange_dist = o_dist;

//     // Serial.println("OK!");
// }

// int yellowDeg() { return yellow_angle / 10; }
// int blueDeg() { return blue_angle / 10; }
// // int ballDistance() { return orange_dist; }
// int centerDeg() { return green_angle / 10; }

#include "openmv.hpp"

#define START 0xFF
#define FINISH 0xFE

static HardwareSerial *_serial = nullptr;
static uint32_t _baudrate = 115200;

uint8_t blue_visible;
uint16_t blue_angle;
uint16_t blue_dist;
uint8_t yellow_visible;
uint16_t yellow_angle;
uint16_t yellow_dist;
uint8_t green_visible;
uint16_t green_angle;
uint16_t green_dist;
uint8_t orange_visible;
uint16_t orange_angle;
uint16_t orange_dist;

bool cameraInit(HardwareSerial *serial, uint32_t baudrate)
{
    _serial = serial;
    _baudrate = baudrate;
    _serial->begin(_baudrate);
    return true;
}

void cameraReceive()
{
    if (_serial == nullptr) return;

    // 1パケット(22バイト)以上溜まっている間ループ
    while (_serial->available() >= 22)
    {
        // 先頭が0xFFでない場合は1バイト捨てて同期を合わせる
        if (_serial->peek() != START)
        {
            _serial->read();
            continue;
        }

        // ヘッダー読み飛ばし
        _serial->read(); // 0xFF

        // 青ゴール
        uint8_t  b_vis  = _serial->read();
        uint16_t b_ang  = _serial->read() | (_serial->read() << 8);
        uint16_t b_dist = _serial->read() | (_serial->read() << 8);

        // 黄ゴール
        uint8_t  y_vis  = _serial->read();
        uint16_t y_ang  = _serial->read() | (_serial->read() << 8);
        uint16_t y_dist = _serial->read() | (_serial->read() << 8);

        // グリーン(コート中心)
        uint8_t  g_vis  = _serial->read();
        uint16_t g_ang  = _serial->read() | (_serial->read() << 8);
        uint16_t g_dist = _serial->read() | (_serial->read() << 8);

        // オレンジ(ボール等)
        uint8_t  o_vis  = _serial->read();
        uint16_t o_ang  = _serial->read() | (_serial->read() << 8);
        uint16_t o_dist = _serial->read() | (_serial->read() << 8);

        // 終端チェック
        uint8_t footer = _serial->read();
        if (footer == FINISH)
        {
            blue_visible   = b_vis;   blue_angle   = b_ang;   blue_dist   = b_dist;
            yellow_visible = y_vis;   yellow_angle = y_ang;   yellow_dist = y_dist;
            green_visible  = g_vis;   green_angle  = g_ang;   green_dist  = g_dist;
            orange_visible = o_vis;   orange_angle = o_ang;   orange_dist = o_dist;
        }
    }
}

int bDistance() { return blue_dist; }
int yDistance() { return yellow_dist; }
int yellowDeg() { return yellow_angle / 10; }
int blueDeg()   { return blue_angle / 10; }
int centerDeg() { return green_angle / 10; }
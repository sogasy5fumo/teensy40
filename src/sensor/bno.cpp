#include "bno.hpp"

static float now_val = 0;
// const int DAC_PIN = A0;

const int RESET_PIN = 2;
bool BNO_start = false;

bool GYRO::init(TwoWire *wire, uint8_t address)
{
    pinMode(RESET_PIN, INPUT_PULLDOWN);

    wire->begin();

    _bno = new Adafruit_BNO055(BNO055_ID, address, wire);

    Serial.print("BNO055 start   ");

    if (!_bno->begin())
    {
    Serial.println("BNO not detected");
    BNO_start = false;
    while (1)
        ;
    }

    delay(1000);

    BNO_start = true;
    _bno->setExtCrystalUse(true);
    Serial.print("bno ready");

    analogWriteResolution(10); // 2^10=1024
    return true;
}

void GYRO::update()
{
    // // Serial.println("update start");

    // imu::Vector<3> euler = _bno->getVector(Adafruit_BNO055::VECTOR_EULER);
    // // Serial.println("getVector done");

    // yaw = euler.x();
    // // Serial.println("yaw set");

    // bool now_button = digitalRead(RESET_PIN);
    // // Serial.println("button read done");

    // static bool prevButton = LOW;

    // if(prevButton == LOW && now_button == HIGH)
    // {
    //     Serial.println(" Reset ");
    //     now_val = yaw;
    // }
    // Serial.print(" ");
    // // Serial.println("before prevButton");
    // prevButton = now_button;

    // yaw = fmod((yaw - now_val + 360.0),360.0);

    // static float smoothed_yaw = 0.0f;
    // const float ALPHA = 0.2f;
    // smoothed_yaw = yaw * ALPHA + smoothed_yaw * (1.0f - ALPHA);
    // yaw = smoothed_yaw; // これ以降 getYaw() が返す値を平滑化されたものにする
    // // Serial.println("fmod done"); // ← 追加

    // yaw = normalizeDeg(yaw);
    // // Serial.println("normalizeDeg done");

    // delay(1);
    imu::Vector<3> euler = _bno->getVector(Adafruit_BNO055::VECTOR_EULER);

    float new_yaw = euler.x();
    bool now_button = digitalRead(RESET_PIN);
    static bool prevButton = LOW;

    if(prevButton == LOW && now_button == HIGH)
    {
        Serial.println(" Reset ");
        now_val = new_yaw;
    }
    prevButton = now_button;

    new_yaw = fmod((new_yaw - now_val + 360.0), 360.0);
    new_yaw = normalizeDeg(new_yaw);

    // 異常なジャンプを検出して無視する
    static float last_valid_yaw = 0.0f;
    static bool first_run = true;
    float diff = fabs(new_yaw - last_valid_yaw);
    if (diff > 180.0f) diff = 360.0f - diff; // 円環の最短距離に補正

    if (first_run || diff < 150.0f) // 1回のupdateで30度以上の急変は無視
    {
        yaw = new_yaw;
        last_valid_yaw = new_yaw;
        first_run = false;
    }
    // 異常値なら yaw を更新しない(前回の値を維持)
}
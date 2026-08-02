#include "bno.hpp"
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

static float now_val = 0;
const int DAC_PIN = A0;

const int RESET_PIN = 1;
bool BNO_start = false;

bool GYRO::init()
{
    Serial.begin(115200);
    pinMode(RESET_PIN, INPUT_PULLDOWN);


    Serial.print("BNO055 start   ");

    if (!bno.begin())
    {
    Serial.println("BNO not detected");
    BNO_start = false;
    while (1)
        ;
    }

    delay(1000);

    BNO_start = true;
    bno.setExtCrystalUse(true);
    Serial.print("bno ready");

    analogWriteResolution(10); // 2^10=1024
}

void GYRO::update()
{
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    float yaw   = euler.x();
    bool now_button = digitalRead(RESET_PIN);
    static bool prevButton = LOW;

    if(prevButton == LOW && now_button == HIGH)
    {
        Serial.println(" Reset ");
        now_val = yaw; // 現在の角度(Yaw)を保存
    }
    Serial.print(" ");
    prevButton = now_button;

    /* リセット時の角度を基準としたbnoの角度=(bno本体の角度-リセット時の角度+360)を360で割った余り */
    yaw = fmod((yaw - now_val + 360.0),360.0);

    // int robot_angle = yaw * 1023 / 360; // 角度：0 ~ 360 -> 0 ~ 1023 -> 0v ~ 3.3v


    // float pitch = euler.y();
    // float roll  = euler.z();

    Serial.print(" reset val : ");
    Serial.print(now_val);

    Serial.print(" Yaw : ");
    Serial.print(normalizeDeg(yaw));

    yaw = normalizeDeg(yaw);

    // Serial.print(" Pitch : ");
    // Serial.print((pitch));

    // Serial.print(" Roll : ");
    // Serial.print((roll));

    // Serial.print(" manman ");
    // Serial.println(robot_angle);

//  analogWrite(DAC_PIN, robot_angle); // DAC_pinに値を送る。

    delay(1);
}
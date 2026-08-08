#include <Arduino.h>
#include "action/attacker.hpp"

#include "common/angleHelper.hpp"
#include "common/pd.hpp"
#include "timer.hpp"
#include "vector.hpp"

#include "driver/motors.hpp"
#include "driver/motorsDSR1202.hpp"
#include "driver/uiNamespace.hpp"

#include "Function/Display.h"
#include "Function/option.h"
#include "sensor/ir.hpp"
#include "sensor/line.hpp"
#include "sensor/bno.hpp"

#include "subMachine/OLED.hpp"
#include "subMachine/openmv.hpp"

SideLine sideLine;

void setup()
{
    Serial.begin(115200);

    // while(!Serial);

    if (CrashReport)
    {
        Serial.print(CrashReport);
    }

    // initDisplay();
    // dsr1202.begin();

    IRinit(&Serial2, 115200);
    gyro.init(&Wire, 0x28);
    sideLine.Lineinit(&Serial1, 115200);
    cameraInit(&Serial3, 115200);

    motorsInit(&Serial4, 115200);
    motorsSetMoveSign(1, 1, -1, -1);
    motorsSetPdSign(-1, 1, -1, 1);
    motorsSetDegPosition(45, 135, 315, 225);

    // attackerInit();

    for (int i = 0; i < 10; i++)
    {
        motorsStop();
        delay(100);
    }
}

void loop()
{
    // menuChoosen();
    valReceive();
    sideLine.valDetect();
    gyro.update();
    // cameraReceive();

    // camera check
    // while (Serial1.available())
    // { // 実際に使っているポートに置き換え
    //     Serial.print(Serial1.read(), HEX);
    //     Serial.print(" ");
    // Serial.print(" yellow : ");
    // Serial.print(yellowDeg());
    // Serial.print(" blue : ");
    // Serial.print(blueDeg());
    // Serial.print(" ballDis : ");
    // Serial.print(ballDistance());
    Serial.print(" green : ");
    Serial.println(centerDeg());

    // BNO & IRチェック
    // Serial.print("irDetect : ");
    // Serial.print(ballFound());
    // Serial.print(" irDeg : ");
    // Serial.print(ballAngle());
    // Serial.print(" irNear : ");
    // Serial.print(ballNear());
    // Serial.print(" robotAngle :");
    // Serial.println(gyro.getYaw());

    // // lineチェック
    // Serial.print("Right");
    // Serial.print(sideLine.getRight());
    // Serial.print("Left");
    // Serial.print(sideLine.getLeft());
    // Serial.print("Back");
    // Serial.println(sideLine.getBack());

    playAttacker(0);
    // motorsDirectMove(10, 0, 10, 0);

    // motorTest();

    delay(1);
}
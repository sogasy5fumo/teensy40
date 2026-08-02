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

DSR1202 dsr1202(&Serial4,115200);
GYRO BNO;
SideLine sideLine;

void setup() {
    Serial.begin(115200);

    // initDisplay();
    // serialStart();
    dsr1202.begin();

    IRinit(&Serial2, 115200);
    BNO.init();
    sideLine.Lineinit(&Serial1, 115200);

    motorsInit(&Serial4, 115200);
    motorsSetMoveSign(1, 1, -1, -1);
    motorsSetDegPosition(45, 135, 225, 315);

}

void loop() {
    // menuChoosen();
    valReceive();
    sideLine.valDetect();
    BNO.update();

    Serial.print("irDetect : ");
    Serial.print(ballFound());
    Serial.print(" irDeg : ");
    Serial.print(ballAngle());
    Serial.print(" robotAngle :");
    Serial.print(BNO.getYaw());
}


#include "attacker.hpp"


const float line_escape_power = 55.0f; // ライン反応時のモーターの強さ
const float line_trace_power = 75.0f;  // ライントレース時モーターの強さ
const float ir_max_power = 95.0f;      // モーターの強さ

Vector mawarikomi(float max_power, float ir_deg, float ir_distance)
{
    float ir_X = cosf(radians(ir_deg)) * ir_distance;
    float ir_y = sinf(radians(ir_deg)) * ir_distance;

    Vector vec;
    // キャッチセンサーが反応している && -20<irDeg<20なら
        // vec = Vector(0.0f, max_power);

    if (!ballFound())
    {
        return vec = Vector(0.0f, 0);
    }

    int sigh = (ir_deg < 0) ? -1 : 1;
    if (ir_distance/*藤城からもらう*/ < 300 && fabsf(ir_deg) < 20)
    {
        return vec = Vector(0.0f, ir_max_power);
    }else{
        return vec = Vector(ir_deg + (sigh * 50), ir_max_power / 2);
    }
}

PD myPD(1.0f, 0.1f);
SideLine sideLine;
GYRO gyro;

void playAttacker(ATTACKER::Mode mode)
{
    motorsPdProcess(&myPD, gyro.getYaw(), 0);

    Vector line_arrow;
    if (sideLine.getLeft() == 1 || sideLine.getRight() == 1 || sideLine.getBack() == 1)// ifラインに反応したら
    {
        line_arrow = Vector(180 /*コートの中心への角度*/, line_escape_power); // コートの中心へと向かう(角度は藤城が出すだろう)
    }
    // ifキャッチセンサーが反応したら
        // キッカーを蹴る。

    Vector IR_arrow = mawarikomi(ir_max_power, ballAngle(), ballDistance());

    Vector overall_arrow = IR_arrow + line_arrow;
    if(overall_arrow.length() > 100){
        overall_arrow = overall_arrow * (100.0 / overall_arrow.length());
    }

    motorsVectorMove(&overall_arrow);
}
// #include "attacker.hpp"

// const float line_escape_power = 40.0f; // ライン反応時のモーターの強さ
// const float line_trace_power = 75.0f;  // ライントレース時モーターの強さ
// const float mawarikomi_power = 25.0f;  // 回り込み時のモーターの強さ
// const float ir_max_power = 30.0f;      // モーターの強さ

// Vector mawarikomi(float max_power, float ir_deg , bool ir_distance)
// {
//     // float ir_X = cosf(radians(ir_deg)) * ir_distance;
//     // float ir_y = sinf(radians(ir_deg)) * ir_distance;

//     Vector vec;

//     if (!ballFound())
//     {
//         return vec = Vector(0.0f, 0);
//     }

//     // int goal_dis = goal_color ? bDistance() : yDistance();
//     // float goal_deg = goal_color ? blueDeg() : yellowDeg();
//     // float motor_deg = 0.0f;

//     // if (goal_dis < 20){
//     //     // if (goal_color)
//     //     //     motor_deg = goal_deg;
//     //     motor_deg = yellowDeg();
//     // }

//     if (ir_distance == true && fabsf(ir_deg) < 13)
//     {
//         return vec = Vector(0.0f, max_power);
//     }
//     else if(ir_distance == false && fabsf(ir_deg) < 20)
//     {
//         return vec = Vector(0.0f, max_power * 0.6);
//     }else
//     {
//         return vec = Vector(normalizeDeg(-ir_deg) + 1.5f, mawarikomi_power);
//     }
// }

// PD myPD(1.0f, 0.1f);
// PD gyroPD(1.0f, 0.1f);
// extern SideLine sideLine;
// GYRO gyro;

// void attackerInit()
// {
//     // myPD.useD(false);
// }

// void playAttacker(bool goal_toward) // 0:yellow 1:blue
// {
//     // if (goal_toward == 0 && yDistance() < 110){
//     //     motorsPdProcess(&gyroPD, gyro.getYaw(), yellowDeg());
//     // }
//     // else if (goal_toward == 1 && bDistance() < 110)
//     // {
//     //     motorsPdProcess(&gyroPD, gyro.getYaw(), blueDeg());
//     // }

//     motorsPdProcess(&myPD, gyro.getYaw(), 0.0f);

//     Vector line_arrow(0.0f, 0.0f);
//     if (sideLine.getLeft() == 1 || sideLine.getRight() == 1 || sideLine.getBack() == 1) // ifラインに反応したら
//     {
//         line_arrow = Vector(centerDeg(), line_escape_power); // コートの中心へと向かう(角度は藤城が出すだろう)
//     }
//     else
//     {
//     }
//     // ifキャッチセンサーが反応したら
//     // キッカーを蹴る。

//     Vector IR_arrow = mawarikomi(ir_max_power, ballAngle() , ballNear());

//     Vector overall_arrow = IR_arrow + line_arrow;
//     if (overall_arrow.length() > 100)
//     {
//         overall_arrow = overall_arrow * (100.0 / overall_arrow.length());
//     }

//     motorsVectorMove(&overall_arrow);
// }
#include "attacker.hpp"

uint32_t last_time = millis();

const float line_escape_power = 40.0f; // ライン反応時のモーターの強さ

const float line_trace_power = 75.0f; // ライントレース時モーターの強さ

const float mawarikomi_power = 38.0f; // 回り込み時のモーターの強さ

const float ir_max_power = 45.0f; // モーターの強さ

Vector mawarikomi(float max_power, float ir_deg, bool ir_distance)

{

    // float ir_X = cosf(radians(ir_deg)) * ir_distance;

    // float ir_y = sinf(radians(ir_deg)) * ir_distance;

    Vector vec;

    if (!ballFound())

    {
        return vec = Vector(0.0f, 0);
    }

    if (ir_distance == true && fabsf(ir_deg) < 15)
    {
        return vec = Vector(0.0f, max_power * 0.9);
    }
    else if (ir_distance == false && fabsf(ir_deg) < 24)
    {
        return vec = Vector(0.0f, max_power * 0.6);
    }
    else if (ir_deg < -90)
    {
        return vec = Vector(-170.0f, mawarikomi_power);
    }
    else if (ir_deg > 90)
    {
        return vec = Vector(170.0f, mawarikomi_power);
    }
    else
    {
        return vec = Vector(normalizeDeg(-ir_deg) * 1.5f, mawarikomi_power);
    }
}

PD myPD(0.8f, 0.02f);

PD gyroPD(1.0f, 0.1f);

extern SideLine sideLine;

GYRO gyro;

void attackerInit()

{

    // myPD.useD(false);
}

void playAttacker(bool goal_toward) // 0:yellow 1:blue

{

    motorsPdProcess(&myPD, gyro.getYaw(), 0.0f);

    // if (goal_toward == 0 && yDistance() < 110)

    //     motorsPdProcess(&gyroPD, gyro.getYaw(), yellowDeg());

    // if (goal_toward == 1 && bDistance() < 110)

    //     motorsPdProcess(&gyroPD, gyro.getYaw(), blueDeg());

    static Vector line_arrow(0.0f, 0.0f);

    if (sideLine.getLeft() == 1 || sideLine.getRight() == 1 || sideLine.getBack() == 1) // ifラインに反応したら

    {
        // line_arrow = Vector(normalizeDeg(centerDeg()), line_escape_power); // コートの中心へと向かう(角度は藤城が出すだろう)
    }

    else

    {
    }

    // ifキャッチセンサーが反応したら

    // キッカーを蹴る。

    Vector IR_arrow = mawarikomi(ir_max_power, ballAngle(), ballNear());

    Vector overall_arrow = IR_arrow;

    if (overall_arrow.length() > 100)

    {

        // overall_arrow = overall_arrow * (100.0 / overall_arrow.length());
    }

    static uint8_t a = 0;

    if (millis() - last_time < 25 && a != 0){

    }
    else if (sideLine.getRight() && sideLine.getLeft())
    {
        if(!sideLine.getBack())
        {
            line_arrow = Vector(180, 20);
            a = 1;
            last_time = millis();
        }
    }
    else if (sideLine.getRight())
    {
        line_arrow = Vector(-90, 20);
        a = 2;
        last_time = millis();
    }
    else if (sideLine.getLeft())
    {
        line_arrow = Vector(90, 20);
        a = 3;
        last_time = millis();
    }
    else if (sideLine.getBack())
    {
        line_arrow = Vector(0, 20);
        a = 4;
        last_time = millis();
    }else {
        a = 0;
        line_arrow = Vector(0, 0);
    }
    if (line_arrow.is_empty())
    {

        motorsVectorMove(&overall_arrow);
    }
    else
    {
        motorsVectorMove(&line_arrow);
    }
}

// void motorTest()
// {

//     motorsPdProcess(&myPD, gyro.getYaw(), 0.0f);

//     if (ballFound() && fabsf(ballAngle()) < 20){

//         motorsMove(0, 20);

//     }else

//     {

//         motorsMove(0, 0.0f);

//     }

// }

void motorTest()
{
    motorsPdProcess(&myPD, gyro.getYaw(), 0.0f);
    // motorsPdMove()
    motorsMove(0, 20);
}

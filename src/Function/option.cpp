#include "Function/option.h"

float normalizeAngle(float angle)
{
    while (angle > 180.0)
        angle -= 360.0;
    while (angle < -180.0)
        angle += 360.0;
    return angle;
}

void serialStart()
{
    while (!Serial)
        ;

    Serial.println("Serial start    ");
}

float MovingAverage::update(float now_val)
{
    // 1. 新しい値をバッファに書き込む (循環バッファ)
    _storage[_current_target] = now_val;
    _current_target = (_current_target + 1) % _num_elements;

    // 2. データ点数のカウント（上限はウィンドウサイズ）
    if (_count < _num_elements)
        _count++;

    // 3. 移動平均の計算
    float sum = 0;
    // 蓄積されたデータ点数分だけ合計する
    for (int i = 0; i < _count; i++)
    {
        sum += _storage[i];
    }

    // 整数除算で平均を出す
    return sum / _count;
}
#pragma once
#include <Arduino.h>

class Vector
{
private:
    float _vector_x;
    float _vector_y;

public:
    // コンストラクタ
    Vector();
    Vector(float x0, float y0, float x1, float y1);
    Vector(int deg, float length);

    // 演算
    Vector operator+(const Vector &other) const;
    Vector operator-(const Vector &other) const;
    Vector operator*(const float &scale) const;
    Vector operator/(const float &scale) const;

    // データの取得
    bool is_empty() const { return (_vector_x == 0.0f && _vector_y == 0.0f); }

    float x() const { return _vector_x; }                                                 // x
    float y() const { return _vector_y; }                                                 // y
    float length() const { return sqrtf(_vector_x * _vector_x + _vector_y * _vector_y); } // 大きさ

    float deg() const // 度数法
    {
        float deg = degrees(atan2f(_vector_y, _vector_x));
        return deg;
    }

    float rad() const // ラジアン
    {
        float rad = atan2f(_vector_y, _vector_x);
        if (rad < 0.0f)
            rad += 2.0f * PI;
        return rad;
    }
};

// ベクター自動生成用
Vector getVec(int deg, float length);

// ベクターマッピング
Vector mapVec(Vector vec, float in_scale, float out_scale);
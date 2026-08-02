#pragma once

#include <Arduino.h>

// 関数
float normalizeDeg(float deg); // 0~360 -> -180~180

float diffDeg(float deg1, float deg2); // -180~180 の範囲で計算

float nearSessenDeg(float target_deg, float enter_deg);

float areaIndexFromDeg(int n, float deg); // 角度からエリアインデックスを計算
float degFromAreaIndex(int n, int index); // エリアインデックスから角度を計算
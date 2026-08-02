#include "angleHelper.hpp"

//// パブリック関数 ////

// 角度を -180度から180度の範囲に正規化する関数
float normalizeDeg(float deg)
{
    float norm = fmodf(deg + 360.0f, 360);
    if (norm > 180)
        norm -= 360;
    return norm;
}

// 角度の差分を -180度から180度の範囲で計算する
float diffDeg(float deg1, float deg2)
{
    deg1 = normalizeDeg(deg1);
    deg2 = normalizeDeg(deg2);
    float diff = (deg1 - deg2); // 差分

    // 差分が360度を超えないように調整
    float mod = fmodf(diff + 360.0f, 360);
    if (mod > 180)
        mod -= 360;
    return mod;
}

// target_degに対する接戦方向のうち、enter_Degに近い方を返す
float nearSessenDeg(float target_deg, float enter_deg)
{
    // targetDegに±90°を加算した角度を正規化する
    float sessen1_deg = normalizeDeg(target_deg + 90);
    float sessen2_deg = normalizeDeg(target_deg - 90);

    // 差分を -180 ~ 180 の範囲で計算
    bool is_sessen1_deg_near = abs(diffDeg(sessen1_deg, enter_deg)) < abs(diffDeg(sessen2_deg, enter_deg));

    return is_sessen1_deg_near ? sessen1_deg : sessen2_deg;
}
/*
"hensuu1 ? choice1 : choice2;""

hensuu1がtrueならchoosen1 falseならchoosen2を返す
ライントレースに使う
*/

// 角度からエリアインデックスを計算
float areaIndexFromDeg(int n, float deg)
{
    float area_size = 360.f / n;

    // degを0~359に変換 (-180は180, 180は180として扱う)
    float positiveDeg = fmodf(deg + 360, 360);

    int index = (int)fmodf((positiveDeg + area_size / 2.0f) / area_size, n);
    return index;
}

// エリアインデックスからエリアの中心角度を計算
float degFromAreaIndex(int n, int index)
{
    float area_size = 360.0f /n;

    //0 ~ 359度の中心核を計算
    float positiveDeg = fmodf(index * area_size + area_size / 2.0f, 360);

    // 0 ~ 359 の角度を -180 ~ 179に正規化して返す
    return normalizeDeg(positiveDeg);
}
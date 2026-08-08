#pragma once
#include <Arduino.h>

class PD
{
public:
    PD(float kp, float kd);

    void setGains(float kp, float kd);
    void setDeadline(float line);

    void useP(bool use);
    void useD(bool use);

    void process(float val, float target, bool angle = false);

    float output() const;
    void reset(float current_val);

private:
    float _kp, _kd;
    float _deadline = 0.0f;

    float _value = 0.0f;
    // float _old_value = 0.0f;
    float _old_error = 0.0f;
    float _p_power = 0.0f;
    float _d_power = 0.0f;
    float _d_filtered = 0.0f;
    float _output = 0.0f;

    bool _useP = true;
    bool _useD = true;

    uint32_t _last_time = 0;

    float getDiffDeg(float a, float b);
};
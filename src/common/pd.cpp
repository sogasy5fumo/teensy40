#include "pd.hpp"

PD::PD(float kp, float kd)
    : _kp(kp), _kd(kd)
{
    _last_time = micros();
}

void PD::setGains(float kp, float kd)
{
    _kp = kp;
    _kd = kd;
}

void PD::setDeadline(float line)
{
    _deadline = fabsf(line);
}

void PD::useP(bool use) { _useP = use; }
void PD::useD(bool use) { _useD = use; }

void PD::process(float val, float target, bool angle)
{
    uint32_t now = micros();
    float dt = (float)(now - _last_time) / 1000000.0f; // 瞬間の速さ
    if (dt <= 0)
        dt = 0.0001f;
    _last_time = now;

    _value = val;

    // P(比例)
    float error = angle ? getDiffDeg(target, _value) : (target - _value);

    if (fabsf(error) < _deadline)
        error = 0.0f;
    _p_power = error * _kp;

    // D(微分)
    float diff = angle ? getDiffDeg(_value, _old_value) : (_value - _old_value); //

    float raw_d_speed = diff / dt;
    float raw_d_power = raw_d_speed * _kd;

    _d_filtered = raw_d_power + _d_filtered;
    _d_power = _d_filtered;

    _old_value = _value;

    float total_power = 0.0f;
    if (_useP)
        total_power += _p_power;
    if (_useD)
        total_power += _d_power;

    _output = constrain(total_power, -100.0f, 100.0f);
}

float PD::output() const
{
    return _output;
}

void PD::reset(float current_val)
{
    _old_value = current_val;
    _d_filtered = 0.0f;
    _output = 0.0f;
    _last_time = micros();
}

float PD::getDiffDeg(float target, float current)
{
    float diff = target - current;
    while (diff > 180.0f)
        diff -= 360.0f;
    while (diff < -180.0f)
        diff += 360.0f;
    return diff;
}
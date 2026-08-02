#pragma once
#include <Arduino.h>

class Timer
{
private:
    unsigned long _reset_time = 0UL;
    unsigned long _now_time = 0UL;
    unsigned long _stop_time = 0UL;

    bool _is_stopped = false;
public:
    void reset();
    void stop();
    void start();

    unsigned long msTime();
};
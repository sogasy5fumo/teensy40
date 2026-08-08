#pragma once
#include <Arduino.h>

#include "angleHelper.hpp"
#include "pd.hpp"
#include "timer.hpp"
#include "vector.hpp"

#include "motors.hpp"
#include "motorsDSR1202.hpp"
#include "uiNamespace.hpp"

#include "ir.hpp"
#include "line.hpp"
#include "bno.hpp"

#include "openmv.hpp"

void attackerInit();

void playAttacker(bool goal_toward);

extern GYRO gyro;

void motorTest();
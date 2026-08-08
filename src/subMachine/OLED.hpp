#pragma once
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <Fonts/FreeSerifItalic12pt7b.h>
#include "Fonts/FreeMono9pt7b.h"
#include "Fonts/FreeSerif9pt7b.h"

static const unsigned char PROGMEM image_paint_3_bits[] = {0x80};

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#include "Function/Display.h"
#include "sensor/ir.hpp"
#include "sensor/bno.hpp"
// class btn
// {
// public:
//     int button_btn[3];
//     bool push_btn = 0;
// };

extern void menuChoosen();

bool modeChange();
bool goalToward();
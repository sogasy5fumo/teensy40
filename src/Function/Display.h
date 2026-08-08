#pragma once
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

extern const int TOP_BUTTON;
extern const int ENTER_BUTTON;
extern const int DOWN_BUTTON;
extern const int BACK_BUTTON;
extern const int choosen_pins[3];

void initDisplay(); // begin()をここに集約
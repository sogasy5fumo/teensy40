#include <Wire.h>
#include "Display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

const int TOP_BUTTON = 10;
const int ENTER_BUTTON = 12;
const int DOWN_BUTTON = 11;
const int BACK_BUTTON = 13;
const int choosen_pins[3] = {TOP_BUTTON, ENTER_BUTTON, DOWN_BUTTON};

void initDisplay()
{
    for (int i = 0;i < 3;i ++){
        pinMode(choosen_pins[i],INPUT_PULLDOWN);
    }

    pinMode(BACK_BUTTON, INPUT_PULLDOWN);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 disconnection"));
        for (;;);
    }
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.clearDisplay();
}
#include "OLED.hpp"

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

static int count = 1;
static int click = 0;



int menuNumberReset(int num)
{
    while (num < 1)
    {
        num += 4;
    }
    while (num >= 5)
    {
        num -= 4;
    }
    return num;
}

int clickNumberReset(int num)
{
    while (num < 1)
    {
        num += 2;
    }
    while (num >= 2)
    {
        num -= 2;
    }
    return num;
}

void drawItem(int x, int y, int w, int h, const char *label, bool selected)
{
    if (selected)
    {
        display.fillRect(x, y, w, h, WHITE);
        display.setTextColor(BLACK);
    }
    else
    {
        display.drawRect(x, y, w, h, WHITE);
        display.setTextColor(WHITE);
    }
    display.setTextSize(1);
    display.setCursor(x + 8, y + (h - 8) / 2); // 縦方向おおよそ中央
    display.print(label);
}

// 1つ目 IR
void mode_1st()
{
    if (click == 0)
    {
        drawItem(4, 4, 56, 28, "IR", true);
        drawItem(68, 4, 56, 28, "Gyro", false);
        drawItem(4, 36, 56, 24, "tetsu", false);
        drawItem(68, 36, 56, 24, "ema", false);
    }
    else
    {
        display.clearDisplay();
        // string 1
        display.setTextColor(1);
        display.setTextWrap(false);
        display.setFont(&FreeSerifItalic12pt7b);
        display.setCursor(3, 19);
        display.print("IRval");
        // circle 2
        display.drawCircle(96, 31, 28, 1);
        // paint 3
        display.drawBitmap(96, 32, image_paint_3_bits, 1, 1, 1);
        // string 4
        display.setFont(&FreeSansOblique18pt7b);
        display.setCursor(-4, 58);
        display.print(ballAngle());
    }
}

// 2つ目 gyro
void mode_2nd()
{
    if (click == 0)
    {
        drawItem(4, 4, 56, 28, "IR", false);
        drawItem(68, 4, 56, 28, "Gyro", true);
        drawItem(4, 36, 56, 24, "tetsu", false);
        drawItem(68, 36, 56, 24, "ema", false);
    }
    else
    {
    display.clearDisplay();
    // string 1
    display.setTextColor(1);
    display.setTextWrap(false);
    display.setFont(&FreeSerifItalic12pt7b);
    display.setCursor(3, 19);
    display.print("IRval");
    // circle 2
    display.drawCircle(96, 31, 28, 1);
    // paint 3
    display.drawBitmap(96, 32, image_paint_3_bits, 1, 1, 1);
    // string 4
    display.setFont(&FreeSansOblique18pt7b);
    display.setCursor(-4, 58);
    display.print("Text");

    }
}

// 3つ目
void mode_3th()
{
    if (click == 0)
    {
        drawItem(4, 4, 56, 28, "IR", false);
        drawItem(68, 4, 56, 28, "Gyro", false);
        drawItem(4, 36, 56, 24, "tetsu", true);
        drawItem(68, 36, 56, 24, "ema", false);
    }
    else
    {
        // circle 1
        display.drawCircle(34, 26, 18, 1);
        // string 2
        display.setTextColor(1);
        display.setTextWrap(false);
        display.setCursor(23, 24);
        display.print("Test");
        // string 3
        display.setCursor(69, 25);
        display.print("tetsu");
    }
}

// 4つ目
void mode_4th()
{
    if (click == 0)
    {
        drawItem(4, 4, 56, 28, "IR", false);
        drawItem(68, 4, 56, 28, "Gyro", false);
        drawItem(4, 36, 56, 24, "tetsu", false);
        drawItem(68, 36, 56, 24, "ema", true);
    }
    else
    {
        // circle 1
        display.drawCircle(34, 26, 18, 1);
        // string 2
        display.setTextColor(1);
        display.setTextWrap(false);
        display.setCursor(23, 24);
        display.print("Test");
        // string 3
        display.setCursor(69, 25);
        display.print("ema");
    }
}

void menuChoosen()
{
    static bool last_button_state[3] = {1, 1, 1}; // プルアップなのでデフォルトHIGH
    static bool now_button_state[3];

    display.clearDisplay();

    for (int i = 0; i < 3; i++)
    {
        now_button_state[i] = digitalRead(choose_pins[i]);
    }

    if (now_button_state[1] != last_button_state[1] && now_button_state[1] == LOW)
    {
        click += 1;
        delay(50);
        last_button_state[1] = now_button_state[1];
    }
    if (click == 0)
    {
        if (now_button_state[0] != last_button_state[0] && now_button_state[0] == LOW)
        {
            count += 1;
            delay(50);
            last_button_state[0] = now_button_state[0];
        }
        else if (now_button_state[2] != last_button_state[2] && now_button_state[2] == LOW)
        {
            count -= 1;
            delay(50);

            last_button_state[2] = now_button_state[2];
        }
    }

    count = menuNumberReset(count);
    click = clickNumberReset(click);

    if (count == 1)
    {
        mode_1st();
    }
    else if (count == 2)
    {
        mode_2nd();
    }
    else if (count == 3)
    {
        mode_3th();
    }
    else if (count == 4)
    {
        mode_4th();
    }

    display.display();

    last_button_state[0] = now_button_state[0];
    last_button_state[1] = now_button_state[1];
    last_button_state[2] = now_button_state[2];
}
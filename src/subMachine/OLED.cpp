#include "OLED.hpp"

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

static int count = 1;
static int click = 0;

GYRO Gyro;

static bool _is_running;
bool _goal_toward;

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
        drawItem(4, 4, 56, 28, "Deg", true);
        drawItem(68, 4, 56, 28, "Goal", false);
        drawItem(4, 36, 56, 24, "Mode", false);
        drawItem(68, 36, 56, 24, "ema", false);
    }
    else
    {
        display.clearDisplay();
        // string 1
        display.setTextColor(1);
        display.setTextWrap(false);
        display.setCursor(115, 55);
        display.print("IR");
        // circle 2
        display.drawCircle(96, 31, 28, 1);
        // paint 3
        // display.drawBitmap(96, 32, image_paint_3_bits, 1, 1, 1);
        // string 4
        display.setFont(&FreeMono9pt7b);
        display.setCursor(75, 46);
        display.print(ballAngle());
        // line 5
        display.drawLine(0, 0, 0, 0, 1);
        // line 6
        float rad = radians(ballAngle());
        display.drawLine(96, 32, 96 + cos(rad) * 28, 32 + sin(rad) * 28, 1);
        // string 1 copy 1
        display.setFont();
        display.setCursor(1, 56);
        display.print("BNO");
        // circle 2 copy 1
        display.drawCircle(32, 31, 28, 1);
        // string 4 copy 1
        display.setFont(&FreeMono9pt7b);
        display.setCursor(11, 46);
        display.print(Gyro.getYaw());
        // line 6 copy 1
        float rad2 = radians(Gyro.getYaw());
        display.drawLine(32, 32, 32 + cos(rad2) * 28, 32 + sin(rad2) * 28, 1);
        display.display();
    }
}

void mode_2nd()
{
    if (click == 0)
    {
        drawItem(4, 4, 56, 28, "Deg", false);
        drawItem(68, 4, 56, 28, "Goal", true);
        drawItem(4, 36, 56, 24, "Mode", false);
        drawItem(68, 36, 56, 24, "ema", false);
    }
    else
    {
        static bool last_button_state[3] = {1, 1, 1}; // プルアップなのでデフォルトHIGH
        static bool now_button_state[3];

        for (int i = 0; i < 3; i++)
        {
            now_button_state[i] = digitalRead(choosen_pins[i]);
        }

        static int goal_change = 0;
        if (now_button_state[0] != last_button_state[0] && now_button_state[0] == LOW)
        {
            goal_change += 1;
            delay(50);
            last_button_state[0] = now_button_state[0];
        }
        else if (now_button_state[2] != last_button_state[2] && now_button_state[2] == LOW)
        {
            goal_change -= 1;
            delay(50);
            last_button_state[2] = now_button_state[2];
        }

        last_button_state[0] = now_button_state[0];
        last_button_state[1] = now_button_state[1];
        last_button_state[2] = now_button_state[2];

        goal_change = clickNumberReset(goal_change);
        if (goal_change == 0)
        {
            display.clearDisplay();
            // string 1
            display.setTextColor(1);
            display.setTextWrap(false);
            display.setFont(&FreeMono12pt7b);
            display.setCursor(11, 30);
            display.print("YELLOW");
            // string 2
            display.setCursor(12, 52);
            display.print("BLUE");
            // triangle 3
            display.fillTriangle(2, 19, 2, 27, 9, 23, 1);
            // string 4
            display.setFont(&FreeSerif9pt7b);
            display.setCursor(80, 62);
            display.print("toward");
            display.display();
            _goal_toward = 0;
        }
        else if (goal_change == 1)
        {
            display.clearDisplay();
            // string 1
            display.setTextColor(1);
            display.setTextWrap(false);
            display.setFont(&FreeMono12pt7b);
            display.setCursor(11, 30);
            display.print("YELLOW");
            // string 2
            display.setCursor(12, 52);
            display.print("BLUE");
            // triangle 3
            display.fillTriangle(3, 41, 3, 49, 10, 45, 1);
            // string 4
            display.setFont(&FreeSerif9pt7b);
            display.setCursor(80, 62);
            display.print("toward");
            display.display();
            _goal_toward = 1;
        }
    }
}

void mode_3th()
{
    if (click == 0)
    {
        drawItem(4, 4, 56, 28, "Deg", false);
        drawItem(68, 4, 56, 28, "Goal", false);
        drawItem(4, 36, 56, 24, "Mode", true);
        drawItem(68, 36, 56, 24, "ema", false);
    }
    else
    {
        // static int triangle_pos = 0;
        // static bool is_running = false;
        // static bool last_button_state[3] = {1, 1, 1};
        // bool now_button_state[3];

        // for (int i = 0; i < 3; i++)
        // {
        //     now_button_state[i] = digitalRead(choose_pins[i]);
        // }

        // if (now_button_state[0] != last_button_state[0] && now_button_state[0] == LOW)
        // {
        //     triangle_pos = 0;
        //     delay(50);
        // }
        // else if (now_button_state[2] != last_button_state[2] && now_button_state[2] == LOW)
        // {
        //     triangle_pos = 1;
        //     delay(50);
        // }
        // if (now_button_state[1] != last_button_state[1] && now_button_state[1] == LOW)
        // {
        //     if (triangle_pos == 0)
        //     {
        //         is_running = !is_running;
        //     }
        //     delay(50);
        // }

        // last_button_state[0] = now_button_state[0];
        // last_button_state[1] = now_button_state[1];
        // last_button_state[2] = now_button_state[2];

        // display.clearDisplay();
        // display.setTextColor(1);
        // display.setTextWrap(false);
        // display.setFont(&FreeMono12pt7b);
        // display.setCursor(11, 30);
        // display.print(is_running ? "STOP " : "START");
        // display.setCursor(12, 52);
        // display.print("BACK");

        // if (triangle_pos == 0)
        // {
        //     display.fillTriangle(2, 20, 2, 28, 9, 24, 1);
        // }
        // else
        // {
        //     display.fillTriangle(2, 42, 2, 50, 9, 46, 1);
        // }

        // _is_running = is_running;

        display.display();
    }
}

// 4つ目
void mode_4th()
{
    if (click == 0)
    {
        drawItem(4, 4, 56, 28, "Deg", false);
        drawItem(68, 4, 56, 28, "Goal", false);
        drawItem(4, 36, 56, 24, "Mode", false);
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
        now_button_state[i] = digitalRead(choosen_pins[i]);
    }

    bool now_start_button = digitalRead(BACK_BUTTON);
    static bool last_start_button = 1;

    if (now_button_state[1] != last_button_state[1] && now_button_state[1] == LOW)
    {
        click += 1;
        delay(50);
        last_button_state[1] = now_button_state[1];
    }

    last_button_state[1] = now_button_state[1];

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
    last_start_button = now_start_button;


    if ( last_start_button != now_start_button ){
        _is_running += 1;
        delay(50);
        _is_running = clickNumberReset(_is_running);
    }
}

bool modeChange() { return _is_running; } // 0:stop 1:running
bool goalToward() { return _goal_toward; } // 0:yellow 1:blue
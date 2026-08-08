#include "motorsDSR1202.hpp"
DSR1202::DSR1202(HardwareSerial *Serial, uint32_t baudrate)
{
    _serial = Serial;
    _baudrate = baudrate;
}

void DSR1202::begin()
{
    _serial->begin(_baudrate);
}

void DSR1202::stop()
{
    _serial->println("1R0002R0003R0004R000");
}

void DSR1202::move(int value_1ch, int value_2ch, int value_3ch, int value_4ch)
{
    // 1chについて
    value_1ch = constrain(value_1ch, -100, 100);
    String str_abs_value_1ch = String(abs(value_1ch));
    if (abs(value_1ch) < 10)
        str_abs_value_1ch = "00" + str_abs_value_1ch;
    else if (abs(value_1ch) < 100)
        str_abs_value_1ch = "0" + str_abs_value_1ch;

    String data_value_1ch;
    if (value_1ch >= 0)
        data_value_1ch = "1F" + str_abs_value_1ch;
    else
        data_value_1ch = "1R" + str_abs_value_1ch;

    // 2chについて
    value_2ch = constrain(value_2ch, -100, 100);
    String str_abs_value_2ch = String(abs(value_2ch));
    if (abs(value_2ch) < 10)
        str_abs_value_2ch = "00" + str_abs_value_2ch;
    else if (abs(value_2ch) < 100)
        str_abs_value_2ch = "0" + str_abs_value_2ch;

    String data_value_2ch;
    if (value_2ch >= 0)
        data_value_2ch = "2F" + str_abs_value_2ch;
    else
        data_value_2ch = "2R" + str_abs_value_2ch;

    // 3chについて
    value_3ch = constrain(value_3ch, -100, 100);
    String str_abs_value_3ch = String(abs(value_3ch));
    if (abs(value_3ch) < 10)
        str_abs_value_3ch = "00" + str_abs_value_3ch;
    else if (abs(value_3ch) < 100)
        str_abs_value_3ch = "0" + str_abs_value_3ch;

    String data_value_3ch;
    if (value_3ch >= 0)
        data_value_3ch = "3F" + str_abs_value_3ch;
    else
        data_value_3ch = "3R" + str_abs_value_3ch;

    // 4chについて
    value_4ch = constrain(value_4ch, -100, 100);
    String str_abs_value_4ch = String(abs(value_4ch));
    if (abs(value_4ch) < 10)
        str_abs_value_4ch = "00" + str_abs_value_4ch;
    else if (abs(value_4ch) < 100)
        str_abs_value_4ch = "0" + str_abs_value_4ch;

    String data_value_4ch;
    if (value_4ch >= 0)
        data_value_4ch = "4F" + str_abs_value_4ch;
    else
        data_value_4ch = "4R" + str_abs_value_4ch;

    _serial->println(data_value_1ch + data_value_2ch + data_value_3ch + data_value_4ch);
}
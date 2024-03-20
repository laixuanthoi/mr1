#include <stdio.h>
#include <math.h>
#include "stm32f4xx.h"

#define PI 3.14159265359

//----- delay nano seconds -----
void delay_us(vu32 num)
{
    __IO uint32_t index = 0;
    /* default system clock is 180MHz */
    for (index = (18 * num); index != 0; index--)
        ;
}
//----- delay mili seconds -----
void delay_ms(vu32 num)
{
    __IO uint32_t index = 0;
    /* default system clock is 180MHz */
    for (index = (18000 * num); index != 0; index--)
        ;
}

void DATA_SPEED_RUN_LOOP() /// TOC DO <254
{
    int _k, _i;
    DMA_Cmd(DMA1_Stream6, ENABLE);
}

int Chong_Nhieu_ADC(vs32 value)
{
    int en, enOld = value;
    u16 i = 2;
    while (i < 2)
    {
        en = value;
        if (abs(en - enOld) < 50)
            i++;
        enOld = en;
    }
    return abs(en);
}

int mapRange_int(int value, int inMin, int inMax, int outMin, int outMax)
{
    return outMin + (((value - inMin) / (inMax - inMin)) * (outMax - outMin));
}

float mapRange_float(float value, float inMin, float inMax, float outMin, float outMax)
{
    return (outMin + (((value - inMin) / (inMax - inMin)) * (outMax - outMin))) * 1.0;
}
//
float radians_to_degrees(float rad)
{
    return rad * (180.0 / PI);
}

float degrees_to_radians(float degree)
{
    return degree * (PI / 180.0);
}

// convert encoder counts to radians
float encoders_to_radians(int encoder_count, int encoder_resolution)
{
    return (encoder_count / encoder_resolution) * 2 * PI * 1.0;
}

float encoders_to_degrees(int encoder_count, int encoder_resolution)
{
    return radians_to_degrees(encoders_to_radians(encoder_count, encoder_resolution));
}

// void polar_to_cartersian(float &rho, float &phi, int &x, int &y)
// {
//     x = rho * cos(phi);
//     y = rho * sin(phi);
// }

// void cartersian_to_polar(int &x, int &y, float &rho, float &phi)
// {
//     x = float(x);
//     rho = sqrt(pow(x, 2) + pow(y, 2));
//     phi = atan2(y, x);
// }

int map_Min_Max(int value, int min, int max)
{
    int new_value = value;
    if (value < min)
    {
        new_value = min;
    }
    if (value > max)
    {
        new_value = max;
    }
    return new_value;
}

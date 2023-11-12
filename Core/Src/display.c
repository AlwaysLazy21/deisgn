/*
 * display.c
 *
 *  Created on: Nov 5, 2023
 *      Author: 91838
 */

#include "oled.h"
#include "font.h"
#include <stdio.h>
#include "aht20.h"
#include "main.h"
#include "usart.h"
#include "display.h"
uint8_t mesu_x = 48, mesu_y = 16;
// 显示温湿度信息
void oled_display_mainPage()
{
    OLED_NewFrame();
    OLED_DrawImage(mesu_x, mesu_y, &main_pageImg, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
}
// 显示作者信息
void oled_display_authorInfo()
{
    OLED_NewFrame();
    OLED_DrawImage(mesu_x, mesu_y, &authorImg, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
}
// 显示计时器
void oled_display_timer()
{
    OLED_NewFrame();
    OLED_DrawImage(mesu_x, mesu_y, &timerImg, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
}
// 显示当前时间
void oled_display_curTime()
{
    OLED_NewFrame();
    OLED_DrawImage(mesu_x, mesu_y, &cur_timeImg, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
}

// 功能函数
void oled_disfunc_time(uint8_t flag, uint8_t *x, uint8_t *y, uint8_t *z)
{
    char title[10];
    if (flag == CUR_TIME)
    {
        strcpy(title, "CUR TIME");
    }
    else if (flag == TIMER)
    {
        strcpy(title, " *TIMER");
    }
    uint8_t font_x1 = 16;
    uint8_t font_x2 = 16;
    uint8_t font_y1 = 0;
    uint8_t font_y2 = 32;
    OLED_NewFrame();
    char message[15];
    sprintf(message, "%02d:%02d:%02d", *x, *y, *z);
    OLED_PrintASCIIString(font_x1, font_y1, title, &afont24x12, OLED_COLOR_NORMAL);
    OLED_PrintASCIIString(font_x2, font_y2, message, &afont24x12, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
}
void oled_disfunc_authorInfo()
{
    OLED_NewFrame();
    OLED_DrawImage(0, 0, &author_infoImg, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
}

void oled_disfunc_temperatureANDhumidity()
{
    aht20_measure();
    HAL_Delay(75);
    aht20_get();
    float temperature, humidity;
    temperature = aht20_getTemperature();
    humidity = aht20_getHumidity();
    if (A_isopen)
    {
        A_count++;
        if (A_count == 5)
        {
            A_count = 0;
            char info[50];
            sprintf(info, "{\"temperature\": %.1f,\"humidity\": %.2f}", temperature, humidity/100.0);
            HAL_UART_Transmit_DMA(&huart1, (uint8_t *)info, strlen(info));
        }
    }
    OLED_NewFrame();
    char message[20];
    OLED_DrawImage(16, 0, &temperatureImg, OLED_COLOR_NORMAL);
    OLED_DrawImage(21, 40, &humidityImg, OLED_COLOR_NORMAL);
    sprintf(message, "%4.1f °", temperature);
    OLED_PrintString(52, 11, message, &ZH_ATH, OLED_COLOR_NORMAL);
    sprintf(message, "%4.1f %%", humidity);
    OLED_PrintString(52, 42, message, &ZH_ATH, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
}

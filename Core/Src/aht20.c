/*
 * ath20.c
 *
 *  Created on: Oct 27, 2023
 *      Author: 91838
 */

#include <aht20.h>
#define AHT20_ADDRESS 0x70

uint8_t readbuffer[6] = {0};
float temperature, humidity;
void aht20_init()
{
    uint8_t read_buffer;
    HAL_Delay(40);
    HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS, &read_buffer, 1, HAL_MAX_DELAY);
    if ((read_buffer & 0x08) == 0)
    {
        uint8_t sendbuffer[3] = {0xbe, 0x08, 0x00};
        HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS, sendbuffer, 3, HAL_MAX_DELAY);
    }
}

void aht20_measure()
{
    static uint8_t sendbuffer[3] = {0xac, 0x33, 0x00};
    HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS, sendbuffer, 3, HAL_MAX_DELAY);
}

void aht20_get()
{
    HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS, readbuffer, 6, HAL_MAX_DELAY);
    if ((readbuffer[0] & 0x80) == 0x00)
    {
        uint32_t data = ((uint32_t)readbuffer[3] >> 4) + ((uint32_t)readbuffer[2] << 4) + ((uint32_t)readbuffer[1] << 12);
        humidity = data * 100.0 / (1 << 20);
        data = ((uint32_t)(readbuffer[3] & 0x07) << 16) + ((uint32_t)readbuffer[4] << 8) + readbuffer[5];
        temperature = data * 200.0 / (1 << 20) - 50;
    }
}

float aht20_getTemperature()
{
    return temperature;
}

float aht20_getHumidity()
{
    return humidity;
}

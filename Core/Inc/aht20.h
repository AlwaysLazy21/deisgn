/*
 * ath20.h
 *
 *  Created on: Oct 27, 2023
 *      Author: 91838
 */

#ifndef INC_AHT20_H_
#define INC_AHT20_H_

#include"i2c.h"
void aht20_init();
void aht20_measure();
void aht20_get();
float aht20_getTemperature();
float aht20_getHumidity();
#endif /* INC_AHT20_H_ */
  

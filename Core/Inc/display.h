/*
 * display.h
 *
 *  Created on: Nov 5, 2023
 *      Author: 91838
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_
void oled_display_mainPage();
void oled_display_authorInfo();
void oled_display_timer();
void oled_display_curTime();
void oled_disfunc_time(uint8_t flag, uint8_t *hour, uint8_t *minute, uint8_t *second);
void oled_disfunc_authorInfo();
void oled_disfunc_temperatureANDhumidity();
#endif /* INC_DISPLAY_H_ */

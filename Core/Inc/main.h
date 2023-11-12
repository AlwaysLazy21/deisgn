/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_STATUS_Pin GPIO_PIN_4
#define BUTTON_STATUS_GPIO_Port GPIOA
#define BUTTON_STATUS_EXTI_IRQn EXTI4_IRQn
#define BUTTON_ENSURE_Pin GPIO_PIN_7
#define BUTTON_ENSURE_GPIO_Port GPIOA
#define BUTTON_ENSURE_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */
#define TRUE 1
#define FALSE 0
#define MESU_MAIN_PAGE 1
#define MESU_CURRENT_TIME 2
#define MESU_TIMER 3
#define MESU_AUTHOR_INFO 4
#define CUR_TIME 1
#define TIMER 2
    extern uint8_t cur_status;
    extern uint8_t status_inside;
    extern uint8_t hour;
    extern uint8_t minute;
    extern uint8_t second;
    extern uint8_t millisecond;
    extern uint8_t T_minute;
    extern uint8_t T_second;
    extern uint8_t T_millisecond;
    extern uint8_t T_isopen;
    extern uint8_t A_isopen;
    extern uint8_t C_hour;
    extern uint8_t C_minute;
    extern uint8_t C_second;
    extern char message[30];

    extern uint8_t A_count;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

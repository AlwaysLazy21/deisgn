/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "aht20.h"
#include "oled.h"
#include "display.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t cur_status = 1;
uint8_t status_inside = FALSE;

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;
uint8_t millisecond = 0;
uint8_t T_minute = 0;
uint8_t T_second = 0;
uint8_t T_millisecond = 0;
uint8_t T_isopen = FALSE;
uint8_t A_isopen = FALSE;
uint8_t A_count = 0;
uint8_t C_hour = 0;
uint8_t C_minute = 0;
uint8_t C_second = 0;
char message[30];
char time[20];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim2)
  {
    millisecond++;
    if (T_isopen)
    {
      T_millisecond++;
      if (T_millisecond == 100)
      {
        T_second++;
        T_millisecond = 0;
        if (T_second == 60)
        {
          T_minute++;
          T_second = 0;
          if (T_minute == 100)
          {
            T_minute = 0;
          }
        }
      }
    }
    if (millisecond == 100)
    {
      second++;
      millisecond = 0;
      if (second == 60)
      {
        minute++;
        second = 0;
        if (minute == 60)
        {
          hour++;
          minute = 0;
          if (hour == 24)
          {
            hour = 0;
          }
        }
      }
    }
  }
  else if (htim == &htim3)
  {
    static uint8_t x = 50;
    static uint8_t cc = 50;
    uint16_t y = pow(1.1, fabs(x - cc)) * (2000.0 / pow(1.1, cc - 1));
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, y);
    if (++x == 2 * cc)
    {
      x = 0;
    }
  }
}
char fail[] = "notice: hh:mm:ss";
char success[] = "success!";
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart == &huart1)
  {
    if (Size == 8)
    {
      C_hour = (time[0] - '0') * 10 + (time[1] - '0');
      C_minute = (time[3] - '0') * 10 + (time[4] - '0');
      C_second = (time[6] - '0') * 10 + (time[7] - '0');
      HAL_UART_Transmit_DMA(&huart1, (uint8_t *)success, strlen(success));
    }
    else
    {
      HAL_UART_Transmit_DMA(&huart1, (uint8_t *)fail, strlen(fail));
    }
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *)&time, sizeof(time) / sizeof(char));
  }
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  // 初始化
  {
    aht20_init();
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_Delay(20);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    OLED_Init();
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *)&time, sizeof(time) / sizeof(char));
  }
  // 开机动画
  {
    OLED_NewFrame();
    OLED_DrawImage(0, 0, &xcuImg, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
    HAL_Delay(1000);
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // OLED_Init();
    if (status_inside)
    {
      switch (cur_status)
      {
      case MESU_MAIN_PAGE:
        oled_disfunc_temperatureANDhumidity();
        break;
      case MESU_CURRENT_TIME:
        oled_disfunc_time(CUR_TIME, &hour, &minute, &second);
        break;
      case MESU_TIMER:
        oled_disfunc_time(TIMER, &T_minute, &T_second, &T_millisecond);
        break;
      case MESU_AUTHOR_INFO:
        oled_disfunc_authorInfo();
        break;
      default:
        break;
      }
    }
    else
    {
      switch (cur_status)
      {
      case MESU_MAIN_PAGE:
        oled_display_mainPage();
        break;
      case MESU_CURRENT_TIME:
        oled_display_curTime();
        break;
      case MESU_TIMER:
        oled_display_timer();
        break;
      case MESU_AUTHOR_INFO:
        oled_display_authorInfo();
        break;
      default:
        break;
      }
    }
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

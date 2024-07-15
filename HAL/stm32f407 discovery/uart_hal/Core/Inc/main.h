/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "stm32f4xx_hal.h"


/*Function declarations*/
/*
 * Function declaration for high level
 */
void SystemClock_Config(void);
void UART2_Init();
void Error_handler();
uint8_t convert_low_to_upper_case(uint8_t data);

/*
 * Function declaration for low level
 */
void GPIO_UART_Init(GPIO_InitTypeDef *gpio_uart, uint8_t PinNumber);

#endif /* __MAIN_H */

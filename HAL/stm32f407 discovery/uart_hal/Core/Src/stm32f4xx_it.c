/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"

extern UART_HandleTypeDef huart2;

void SysTick_Handler()
{
	//Initialize the systick timer
	HAL_IncTick();

	//implement systick timer handler
	HAL_SYSTICK_IRQHandler();
}

void USART2_IRQHandler()
{
	HAL_UART_IRQHandler(&huart2);
}



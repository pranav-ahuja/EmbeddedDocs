/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32f4xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
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

#include "main.h"

void HAL_MspInit()
{
	//1) Configure the priority group
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2) Enable the exceptions
	SCB->SHCSR |= (7 << 16);

	//3) Set the priority of exceptions
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	//Function to do the low level initializations
	//Variable for GPIO Initializations
	GPIO_InitTypeDef gpio_uart;

	//1) Enable the clock peripheral
	__HAL_RCC_USART2_CLK_ENABLE();

	//2) Do the pin muxing for the peripheral using GPIO
	__HAL_RCC_GPIOA_CLK_ENABLE();	//GPIOA Clock enable
	GPIO_UART_Init(&gpio_uart, GPIO_PIN_2);		//TX
	GPIO_UART_Init(&gpio_uart, GPIO_PIN_3);		//RX

	//3) Configure and set the priority of the interrupt
	HAL_NVIC_EnableIRQ(USART2_IRQn);	//Enabling UART2 IRQ
	HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);	//Set the priority of the usart2 IRQ
}

void GPIO_UART_Init(GPIO_InitTypeDef *gpio_uart, uint8_t PinNumber)
{
	gpio_uart->Pin = PinNumber;
	gpio_uart->Mode = GPIO_MODE_AF_PP;
	gpio_uart->Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart->Pull = GPIO_PULLUP;
	gpio_uart->Alternate = GPIO_AF7_USART2;

	HAL_GPIO_Init(GPIOA, gpio_uart);
}

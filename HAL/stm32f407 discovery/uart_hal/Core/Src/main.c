/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/*
 * Currently the receiving will work in Polling Mode.
 * To make it work in INTERRUPT Mode, un-comment the INTERRUPT_RECV macro and comment the POLLING_RECV macro
 */
#define POLLING_RECV	1
//#define INTERRUPT_RECV	2

UART_HandleTypeDef huart2;

char *userData = "Hi, yYou can test the code here";
uint8_t recvData;
uint8_t inputData[100];
uint16_t count = 0;
bool receptionComplete = FALSE;

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  UART2_Init();

  //Start window for the UART
  if(HAL_UART_Transmit(&huart2, (uint8_t*)userData, strlen(userData), HAL_MAX_DELAY) != HAL_OK)
	{
	  Error_handler();
	}

  #if POLLING_RECV

  //UART_Receive polling
  while(1)
  {
	  if(HAL_UART_Receive(&huart2, &recvData, 1, HAL_MAX_DELAY) == HAL_OK)
	  {
		  if(recvData == '\r')
		  {
			  inputData[count++] = '\r';
			  break;
		  }
		  else{
			  inputData[count++] = convert_low_to_upper_case(recvData);	//convert to the lower case and add to the array
			  count++;
		  }
	  }
	  else{
		  Error_handler();
	  }
  }

  //After receiving, send the result back to PC
  if(HAL_UART_Transmit(&huart2, inputData, count, HAL_MAX_DELAY) != HAL_OK)
  {
	  Error_handler();
  }

  #elif INTERRUPT_RECV

  while(receptionComplete != true)
  {
	  if(HAL_UART_Receive_IT(&huart2, &recvData, 1) != HAL_OK)
	  {
		  Error_handler();
	  }
  }

  #endif


  while(1);

}

void SystemClock_Config(void)
{

}

void UART2_Init()
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;

	if(HAL_UART_Init(&huart2)!= HAL_OK)
	{
		//There is some error
		Error_handler();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//If the control comes here, that means the UART reception is completed
	//Collect the data bytes received
	if (recvData != '\r')
	{
		inputData[count++] = convert_low_to_upper_case(recvData);
	}
	else{
		receptionComplete = true;
		inputData[count++] = '\r';

		//transmit the data back to the system
		HAL_UART_Transmit_IT(&huart2, inputData, count);
	}
}

uint8_t convert_low_to_upper_case(uint8_t data)
{
	//The offset is calculated by subtracting upper case letter from the smaller case letter only for the lower case data
	if(data >= 'a' && data <='z')
	{
		data -= ('a' - 'A');
	}
	return data;
}

void Error_handler()
{

}


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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

//#define HSE_CLK				0
//#define HSI_CLK				1
//#define HSE_TO_GEN_PLL		2
#define HSI_TO_GEN_PLL		3

RCC_OscInitTypeDef clk_osc;
RCC_ClkInitTypeDef clk_cfg;
char msg[100];

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_USB_HOST_Init();

  HAL_RCC_Init();

#ifdef HSE_CLK

  //Shutting down the HSI clock to save some current
  __HAL_RCC_HSI_DISABLE();

  //Printing the clock values
  memset(msg, 0, sizeof(msg));
  sprintf(msg, "SYSCLK Configs: %ld\n\r", HAL_RCC_GetSysClockFreq());

  memset(msg, 0, sizeof(msg));
  sprintf(msg, "HCLK Configs: %ld\n\r", HAL_RCC_GetHCLKFreq());

  memset(msg, 0, sizeof(msg));
  sprintf(msg, "PCLK1 Configs: %ld\n\r", HAL_RCC_GetPCLK1Freq());

  memset(msg, 0, sizeof(msg));
  sprintf(msg, "PCLK2 Configs: %ld\n\r", HAL_RCC_GetPCLK2Freq());

  HAL_RCC_config(SYSCLK_FREQ_50);

#elif HSI_CLK

#elif HSE_TO_GEN_PLL

#elif HSI_TO_GEN_PLL

  HAL_RCC_config(SYSCLK_FREQ_50);

#endif

  //Initialization of SYSTICK Timer using HSE because the HCLK clock value has been changed from 8MHz to 1MHz

  HAL_SYSTICK_Config(TIME_DELAY_1MS);	//Adding a delay of 1 second in the SYSTICK Timer

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);	//Clock source for the SYSTICK Timer



  while (1)
  {
    MX_USB_HOST_Process();
  }
}

void HAL_RCC_Init()
{
	memset(&clk_osc, 0, sizeof(clk_osc));	//Resetting the values

#ifdef HSE_CLK
	//HSE External clock
	clk_osc.HSEState = RCC_HSE_ON;
	clk_osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;

#elif HSI_CLK

#elif HSE_TO_GEN_PLL

#elif HSI_TO_GEN_PLL
	clk_osc.HSIState = RCC_HSI_ON;
	clk_osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	clk_osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

#endif

	if(HAL_RCC_OscConfig(&clk_osc) != HAL_OK)
	{
		Error_Handler();
	}

}

void HAL_RCC_config(uint32_t clk_freq)
{
#ifdef HSE_CLK
	clk_cfg.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clk_cfg.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_cfg.AHBCLKDivider = RCC_SYSCLK_DIV2;
	clk_cfg.APB1CLKDivider = RCC_HCLK_DIV2;
	clk_cfg.APB2CLKDivider = RCC_HCLK_DIV2;

	if(HAL_RCC_ClockConfig(&clk_cfg, FLASH_ACR_LATENCY_0WS) != HAL_OK)	//Flash Latency is 0 depending on the reference manual
		{
			Error_Handler();
		}
#elif HSI_CLK

	if(HAL_RCC_ClockConfig(&clk_cfg, FLASH_ACR_LATENCY_0WS) != HAL_OK)	//Flash Latency is 0 depending on the reference manual
		{
			Error_Handler();
		}

#elif HSE_TO_GEN_PLL

#elif HSI_TO_GEN_PLL
	clk_osc.PLL.PLLState = RCC_PLL_ON;
	clk_osc.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	clk_osc.PLL.PLLM = PLLM_VAL;

	switch(clk_freq)
	{
	case SYSCLK_FREQ_50:
		clk_osc.PLL.PLLN = 100;
		clk_osc.PLL.PLLP = RCC_PLLP_DIV2;
		clk_osc.PLL.PLLQ = 2;
		break;
	case SYSCLK_FREQ_80:
		clk_osc.PLL.PLLN = 160;
		clk_osc.PLL.PLLP = RCC_PLLP_DIV2;
		clk_osc.PLL.PLLQ = 2;
		break;
	case SYSCLK_FREQ_120:
		clk_osc.PLL.PLLN = 240;
		clk_osc.PLL.PLLP = RCC_PLLP_DIV2;
		clk_osc.PLL.PLLQ = 2;
		break;
	}

	if(HAL_RCC_OscConfig(&clk_osc) != HAL_OK)
	{
		Error_Handler();
	}

#endif


}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

}

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


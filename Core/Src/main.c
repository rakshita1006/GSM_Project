/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
//#include "stm32f4_discovery.h"
#include "Peripheral_Init.h"
#include "main.h"
#include "gpioconfig.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal.h"
#include "gsm.h"


//TIM_HandleTypeDef htim6;
UART_HandleTypeDef huart2;
//uint8_t Uart_Rx_Buffer[1024];



//static void MX_GPIO_Init(void);
//static void MX_USART2_UART_Init(void);
//
//void SystemClock_Config(void);


GPIO_InitTypeDef GPIOD_Confg = {
		 GPIO_PIN_NO_12,MODE_OUTPUT_PP
 };

 GPIO_InitTypeDef GPIOD15_Confg = {
		 GPIO_PIN_NO_15,MODE_OUTPUT_PP
 };

 GPIO_InitTypeDef GPIOA_Confg = {
		 GPIO_PIN_NO_0,MODE_IT_RISING,NOPULL
 };

 //ATCommadsConfig AT_ECHO ={"ATE0",{"\r\nOK\r\n"," ","\r\nERROR\r\n"},{0,0,0},'\r','\n',300};
 //char data[] = "HELLO DS GROUP \r\n";

int main(void)
{

	//  HAL_Init();
	  PeripheralInit();
	  gsmtask();
	//  SystemClock_Config();

	//  MX_GPIO_Init();
	//  MX_USART2_UART_Init();
	 // USART2_UART_Init();

//	 uint32_t Hclk =0;
//	 Hclk = HAL_RCC_GetHCLKFreq();


//	  GPIO_Init(GPIOD,&GPIOD_Confg);
//	  GPIO_Init(GPIOD,&GPIOD15_Confg);
//	  GPIO_Init(GPIOA,&GPIOA_Confg);
//	  GPIO_Interrupt_Init(EXTI0_IRQn, 0,0);

//	   TIM6_Init(1000);
//	    // HAL_TIM_Base_Start(&htim6);
//       HAL_TIM_Base_Start_IT(&htim6);

	 // GPIO_Interrupt_Init(GPIOA,&GPIOA_Confg);
	  /* USER CODE BEGIN 2 */

	  /* USER CODE END 2 */

	  /* Infinite loop */
	  /* USER CODE BEGIN WHILE */
//	  HAL_UART_Receive_IT(&huart2,&Uart_Rx_Buffer, sizeof(Uart_Rx_Buffer));

	 // Send_AT_Command(&AT_ECHO,1);

	  while (1)
	  {
	    /* USER CODE END WHILE */

		//  HAL_UART_Transmit(&huart2, &data, sizeof(data), 1000);

//	      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
//	     // HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
//	      HAL_Delay(500);
	    /* USER CODE BEGIN 3 */
	  }
	  /* USER CODE END 3 */
}




//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	{
//		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
//	}
//}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */


  //UNUSED(GPIO_Pin);
   HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
   // HAL_EXTI_ClearPending(hexti, Edge);


}

//static void MX_GPIO_Init(void)
//  {
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//    /* GPIO Ports Clock Enable */
//    __HAL_RCC_GPIOE_CLK_ENABLE();
//    __HAL_RCC_GPIOC_CLK_ENABLE();
//    __HAL_RCC_GPIOH_CLK_ENABLE();
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    __HAL_RCC_GPIOD_CLK_ENABLE();
//
//    /*Configure GPIO pin Output Level */
//    HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);
//
//    /*Configure GPIO pin Output Level */
//    HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);
//
//    /*Configure GPIO pin Output Level */
//    HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
//                            |Audio_RST_Pin, GPIO_PIN_RESET);
//
//    /*Configure GPIO pin : CS_I2C_SPI_Pin */
//    GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);
//
//    /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
//    GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);
//
//    /*Configure GPIO pin : PDM_OUT_Pin */
//    GPIO_InitStruct.Pin = PDM_OUT_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
//    HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);
//
//    /*Configure GPIO pin : B1_Pin */
//    GPIO_InitStruct.Pin = B1_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
//
//    /*Configure GPIO pin : BOOT1_Pin */
//    GPIO_InitStruct.Pin = BOOT1_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);
//
//    /*Configure GPIO pin : CLK_IN_Pin */
//    GPIO_InitStruct.Pin = CLK_IN_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
//    HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);
//
//    /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
//                             Audio_RST_Pin */
//    GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
//                            |Audio_RST_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
//
//    /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
//    GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);
//
//    /*Configure GPIO pin : MEMS_INT2_Pin */
//    GPIO_InitStruct.Pin = MEMS_INT2_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);
//
//  }
//
//static void MX_USART2_UART_Init(void)
//{
//
//  /* USER CODE BEGIN USART2_Init 0 */
//
//  /* USER CODE END USART2_Init 0 */
//
//  /* USER CODE BEGIN USART2_Init 1 */
//
//  /* USER CODE END USART2_Init 1 */
//  huart2.Instance = USART2;
//  huart2.Init.BaudRate = 9600;
//  huart2.Init.WordLength = UART_WORDLENGTH_8B;
//  huart2.Init.StopBits = UART_STOPBITS_1;
//  huart2.Init.Parity = UART_PARITY_NONE;
//  huart2.Init.Mode = UART_MODE_TX_RX;
//  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart2) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//
//
//  /* USER CODE BEGIN USART2_Init 2 */
//
//  /* USER CODE END USART2_Init 2 */
//
//}
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}



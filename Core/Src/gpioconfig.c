/*
 * gpioconfig.c
 *
 *  Created on: 05-Oct-2020
 *      Author: rakshita.parihar
 */


#include "main.h"
#include "gpioconfig.h"



void GPIO_Init(GPIO_Reg_Config* GPIOx, GPIO_User_Config* GPIO_INITx)
{

//	GPIO_EXTI_TypeDef *GPIOAx=0;

	uint32_t tempVar = 0x00U;
	int32_t temp = 0x00U;
	uint32_t ioposition = 0x00U;
	uint32_t iocurrent = 0x00U;

	//Clock enable for specific port

	if(GPIOx==GPIOA)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if(GPIOx==GPIOB)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}
	else if(GPIOx==GPIOC)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}
	else if(GPIOx==GPIOD)
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();
	}
	else if(GPIOx==GPIOE)
	{
		__HAL_RCC_GPIOE_CLK_ENABLE();
	}


	// for MODER register configuration
	if (GPIO_INITx->Mode == MODE_INPUT)
	{
		tempVar=GPIOx->MODER;
		tempVar &= ~(0x3UL<<(GPIO_INITx->Pin *2U));
		tempVar |= ((GPIO_INITx->Mode & GPIO_MODE_Ref) << (GPIO_INITx->Pin *2));
		GPIOx->MODER = tempVar;
	}
	else if (GPIO_INITx->Mode == MODE_OUTPUT_PP)
	{
		tempVar=GPIOx->MODER;
		tempVar &= ~(0x3UL<<(GPIO_INITx->Pin  *2U));
		tempVar |= ((GPIO_INITx->Mode  & GPIO_MODE_Ref) << (GPIO_INITx->Pin *2));
		GPIOx->MODER = tempVar;
	}
	else if (GPIO_INITx->Mode == MODE_AF_PP)
	{
		tempVar=GPIOx->MODER;
		tempVar &= ~(0x3UL<<(GPIO_INITx->Pin  *2U));
		tempVar |= ((GPIO_INITx->Mode  & GPIO_MODE_Ref) << (GPIO_INITx->Pin *2));
		GPIOx->MODER = tempVar;
	}
	else if (GPIO_INITx->Mode == MODE_ANALOG)
	{
		tempVar=GPIOx->MODER;
		tempVar &= ~(0x3UL<<(GPIO_INITx->Mode  *2U));
		tempVar |= ((GPIO_INITx->Mode  & GPIO_MODE_Ref) << (GPIO_INITx->Pin *2));
		GPIOx->MODER = tempVar;
	}

	// for speed register configuration
	tempVar = 0x00U;
	if(GPIO_INITx->Mode == MODE_OUTPUT_PP)
	{
		if ( GPIO_INITx->Speed==SPEED_FREQ_LOW)
		{
			tempVar = GPIOx->OSPEEDR;
			tempVar &= ~(GPIO_OSPEEDER_OSPEEDR0 << (GPIO_INITx->Pin * 2U));
			tempVar |= (GPIO_INITx->Speed << (GPIO_PIN_NO_12 * 2U));
			GPIOx->OSPEEDR = tempVar;
		}
		else if ( GPIO_INITx->Speed==SPEED_FREQ_MEDIUM)
		{
			tempVar = GPIOx->OSPEEDR;
			tempVar &= ~(GPIO_OSPEEDER_OSPEEDR0 << (GPIO_INITx->Pin * 2U));
			tempVar |= (GPIO_INITx->Speed << (GPIO_PIN_NO_12 * 2U));
			GPIOx->OSPEEDR = tempVar;
		}
		else if ( GPIO_INITx->Speed==SPEED_FREQ_HIGH)
		{
			tempVar = GPIOx->OSPEEDR;
			tempVar &= ~(GPIO_OSPEEDER_OSPEEDR0 << (GPIO_INITx->Pin * 2U));
			tempVar |= (GPIO_INITx->Speed << (GPIO_PIN_NO_12 * 2U));
			GPIOx->OSPEEDR = tempVar;
		}
		else if ( GPIO_INITx->Speed==SPEED_FREQ_VERY_HIGH)
		{
			tempVar = GPIOx->OSPEEDR;
			tempVar &= ~(GPIO_OSPEEDER_OSPEEDR0 << (GPIO_INITx->Pin * 2U));
			tempVar |= (GPIO_INITx->Speed << (GPIO_PIN_NO_12 * 2U));
			GPIOx->OSPEEDR = tempVar;
		}
	}
// for pull-up pull-down register configuration
	 tempVar = 0x00U;

 	 if (GPIO_INITx->Pull==NOPULL)
	 {
 		tempVar = GPIOx->PUPDR;
 		tempVar &= ~(GPIO_PUPDR_PUPDR0 << (GPIO_INITx->Pin * 2U));
 		tempVar |= ((GPIO_INITx->Pull) << (GPIO_INITx->Pin * 2U));
 		GPIOx->PUPDR = tempVar;
	 }
 	 else if (GPIO_INITx->Pull==PULLUP)
 	 {
 	 	tempVar = GPIOx->PUPDR;
 	 	tempVar &= ~(GPIO_PUPDR_PUPDR0 << (GPIO_INITx->Pin * 2U));
 	 	//tempVar |= ((GPIO_INITx->Pull) << (GPIO_INITx->Pin * 2U));
 	 	tempVar |= ((GPIO_INITx->Pull) << 0);
 	 	GPIOx->PUPDR = tempVar;
 	}
 	else if (GPIO_INITx->Pull==PULLDOWN)
 	{
 	 	tempVar = GPIOx->PUPDR;
 	 	tempVar &= ~(GPIO_PUPDR_PUPDR0 << (GPIO_INITx->Pin * 2U));
 	 	tempVar |= ((GPIO_INITx->Pull) << (GPIO_INITx->Pin * 2U));
 	 	GPIOx->PUPDR = tempVar;
 	}
	// output type register configuration
 	tempVar = 0x00U;
 	if(GPIO_INITx->Mode==MODE_OUTPUT_PP)
 	{
 		if(GPIO_INITx->Otype==MODE_OUTPUT_PP)
 		{
 			tempVar = GPIOx->OTYPER;
 			tempVar &= ~(GPIO_OTYPER_OT_0 << GPIO_INITx->Pin) ;
 			tempVar |= (((GPIO_INITx->Mode & OUTPUT_TYPE) >> 4U) << GPIO_INITx->Pin);
 			GPIOx->OTYPER = tempVar;
 		}
 		else if(GPIO_INITx->Otype==MODE_OUTPUT_OD)
 		{
 			tempVar = GPIOx->OTYPER;
 			tempVar &= ~(GPIO_OTYPER_OT_0 << GPIO_INITx->Pin) ;
 			tempVar |= (((GPIO_INITx->Mode & OUTPUT_TYPE) >> 4U) << GPIO_INITx->Pin);
 			GPIOx->OTYPER = tempVar;
 		}
 	}

 	if((GPIO_INITx->Mode & EXTI_MODE) == EXTI_MODE)
 		     {
 		        /* Enable SYSCFG Clock */
 		       __HAL_RCC_SYSCFG_CLK_ENABLE();

 		       temp = SYSCFG->EXTICR[GPIO_INITx->Pin >> 2U ];
 		       temp &= ~(0x0FU << (4U * (GPIO_INITx->Pin & 0x03U)));
 		       temp |= ((uint32_t)(GPIO_GET_INDEX(GPIOx)) << (4U * ((GPIO_INITx->Pin) & 0x03U)));
 		       SYSCFG->EXTICR[GPIO_INITx->Pin >> 2U] = temp;

 		        /* Clear EXTI line configuration */
 		       iocurrent = 1 << GPIO_INITx->Pin;
 		       // iocurrent = 1 << 0;
 		       temp = EXTI->IMR;
 		       temp &= ~((uint32_t)iocurrent);
 		       if((GPIO_INITx->Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
 		        {
 		          temp |= iocurrent;
 		        }

 		       EXTI->IMR = temp;
 		    //    EXTI->IMR = 0x01;
 		       temp = EXTI->EMR;
 		       temp &= ~((uint32_t)iocurrent);
 		       if((GPIO_INITx->Mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
 		        {
 		          temp |= iocurrent;
 		        }
 		       EXTI->EMR = temp;

 		        /* Clear Rising Falling edge configuration */
 		       temp = EXTI->RTSR;
 		       temp &= ~((uint32_t)iocurrent);
 		       if((GPIO_INITx->Mode & RISING_EDGE) == RISING_EDGE)
 		       {
 		          temp |= iocurrent;
 		       }
 		       EXTI->RTSR = temp;

 		       temp = EXTI->FTSR;
 		       temp &= ~((uint32_t)iocurrent);
 		       if((GPIO_INITx->Mode & FALLING_EDGE) == FALLING_EDGE)
 		       {
 		          temp |= iocurrent;
 		       }
 		        EXTI->FTSR = temp;
 		      }
}

void GPIO_Interrupt_Init(IRQn_Type IRQn, uint32_t Priority,uint32_t SubPriority)
{
	HAL_NVIC_SetPriority(IRQn, Priority, SubPriority);
    HAL_NVIC_EnableIRQ(IRQn);
}



void ON_OFF(GPIO_Reg_Config* GPIOx,uint16_t GPIO_Pin,int ON_OFF)
{

	if (ON_OFF  ==  PIN_RESET)
	{
		GPIOx->BSRR = GPIO_PIN_12 << 16U;

	}
	else if(ON_OFF  ==  PIN_SET)
	{
		GPIOx->BSRR |= 1 <<  GPIO_Pin;

	}

}

void MS_Delay()
{
	static int var;
	for(int i; i<=50000; i++)
	{
		var++;
	}
}


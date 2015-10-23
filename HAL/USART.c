
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "USART.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeUSART(USART_TypeDef* USARTx)
{
	USART_InitTypeDef usart_conf;
	USART_StructInit(&usart_conf);

	if(USARTx == USART_BT)
	{
		usart_conf.USART_BaudRate = 115200u;
		USART_Init(USART_BT, &usart_conf);
		USART_BT->CR1 |= USART_CR1_UE;
		USART_BT->CR1 |= USART_CR1_TE;
		USART_ITConfig(USART_BT, USART_IT_RXNE, ENABLE);
	}
	else if(USARTx == USART_WIFI)
	{
		USART_Cmd(USART_WIFI, ENABLE);
		USART_Init(USART_WIFI, &usart_conf);
		USART_ITConfig(USART_WIFI, USART_IT_RXNE, ENABLE);
	}
	else if(USARTx == USART_PI)
	{
		USART_Cmd(USART_PI, ENABLE);
		USART_Init(USART_PI, &usart_conf);
		USART_ITConfig(USART_PI, USART_IT_RXNE, ENABLE);
	}
}

void USARTInterrupt(USART_TypeDef *USARTx)
{
	if(USARTx == USART_BT)
	{

	}

	/* RXNE handler */
	/*if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
	{
		globalData.communication_safety = 1;
		//LED4_GPIO->ODR ^= LED4_PIN;
		//Disable interrupt until all data is received
		USARTx->CR1 &= ~USART_CR1_RXNEIE;


		uint8_t data = USARTx->DR;

		if (data == 0xFF) // start command
		{
			while((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until next data
			data = USARTx->DR;

			uint8_t address = (data&0b11110000)>>4;
			uint8_t dir = (data&0b00001100)>>2;
			uint8_t data_h = data&0b00000011;

			while((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until next data
			data = USARTx->DR;


			if(address==1||address==2||address==3){
				setDCMotor(address, (data_h<<8)+data, dir);
			}

			else if(address==4){
				uint16_t steps = (data_h<<8)+data;

				while((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until next data
				data = USARTx->DR;

				setStepperPosition(data, steps, dir);
			}

			//Enable receive interrupt
			USARTx->CR1 |= USART_CR1_RXNEIE;
		}
		else
		{
			// error occurred start interrupt
			USARTx->CR1 |= USART_CR1_RXNEIE;
			return;
		}
	}

	else if(USART_GetITStatus(USARTx, USART_IT_TXE) != RESET)
	{
		//Disable transmit interrupt
		USARTx->CR1 &= ~(USART_CR1_TXEIE);

		USARTx->DR = globalData.battery_level;
		while((USARTx->SR & USART_SR_TXE) == RESET);
		USARTx->DR = 'b';
		while((USARTx->SR & USART_SR_TXE) == RESET);
		USARTx->DR = 'c';

		//Enable receive interrupt
		USARTx->CR1 |= USART_CR1_RXNEIE;
	}*/
}

void USART1_IRQHandler(void)
{
	USARTInterrupt(USART1);
}

void USART2_IRQHandler(void)
{
	USARTInterrupt(USART2);
}

void USART3_IRQHandler(void)
{
	USARTInterrupt(USART3);
}

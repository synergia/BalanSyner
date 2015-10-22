
//-----------------------Includes-------------------------------------//
#include "NVIC.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeNVIC()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitTypeDef nvic_encoder1;
	nvic_encoder1.NVIC_IRQChannel = TIM4_IRQn;
	nvic_encoder1.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_encoder1.NVIC_IRQChannelSubPriority = 0;
	nvic_encoder1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_encoder1);

	NVIC_InitTypeDef nvic_encoder2;
	nvic_encoder2.NVIC_IRQChannel = TIM2_IRQn;
	nvic_encoder2.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_encoder2.NVIC_IRQChannelSubPriority = 1;
	nvic_encoder2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_encoder2);

	NVIC_InitTypeDef nvic_I2C;
	nvic_I2C.NVIC_IRQChannel = I2C3_EV_IRQn;
	nvic_I2C.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_I2C.NVIC_IRQChannelSubPriority = 2;
	nvic_I2C.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_I2C);

#ifndef USART_BT
	NVIC_InitTypeDef nvic_usartBT;
	nvic_usartBT.NVIC_IRQChannel = USART_BT_IRQn;
	nvic_usartBT.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_usartBT.NVIC_IRQChannelSubPriority = 3;
	nvic_usartBT.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usartBT);
	NVIC_EnableIRQ(USART_BT_IRQn);
#endif

#ifdef USART_WIFI
	NVIC_InitTypeDef nvic_usartWIFI;
	nvic_usartWIFI.NVIC_IRQChannel = USART_WIFI_IRQn;
	nvic_usartWIFI.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_usartWIFI.NVIC_IRQChannelSubPriority = 4;
	nvic_usartWIFI.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usartWIFI);
	NVIC_EnableIRQ(USART_WIFI_IRQn);
#endif

#ifdef USART_PI
	NVIC_InitTypeDef nvic_usartPI;
	nvic_usartPI.NVIC_IRQChannel = USART_PI_IRQn;
	nvic_usartPI.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_usartPI.NVIC_IRQChannelSubPriority = 5;
	nvic_usartPI.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usartPI);
	NVIC_EnableIRQ(USART_PI_IRQn);
#endif

	NVIC_InitTypeDef nvic_adc;
	nvic_adc.NVIC_IRQChannel = ADC_IRQn;
	nvic_adc.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_adc.NVIC_IRQChannelSubPriority = 6;
	nvic_adc.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_adc);
}

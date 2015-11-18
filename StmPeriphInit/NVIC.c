
//-----------------------Includes-------------------------------------//
#include "NVIC.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//
typedef enum
{
	NVIC_EncoderLeft = 0U,
	NVIC_EncoderRight,
	NVIC_BT,
	NVIC_Wifi,
	NVIC_Pi,
} NVIC_Priority_T;

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static void priv_InitializeBt( NVIC_Priority_T NVIC_Priority );
static void priv_InitializeWifi( NVIC_Priority_T NVIC_Priority );
static void priv_InitializePi( NVIC_Priority_T NVIC_Priority );
static void priv_InitializeEncoderLeft( NVIC_Priority_T NVIC_Priority );
static void priv_InitializeEncoderRight( NVIC_Priority_T NVIC_Priority );

//-----------------------Private functions-----------------------------//
static void priv_InitializeBt( NVIC_Priority_T NVIC_Priority )
{
	NVIC_InitTypeDef nvic_usartBT;
	nvic_usartBT.NVIC_IRQChannel = USART_BT_IRQn;
	nvic_usartBT.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_usartBT.NVIC_IRQChannelSubPriority = NVIC_Priority;
	nvic_usartBT.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usartBT);
	NVIC_EnableIRQ(USART_BT_IRQn);
}

static void priv_InitializeWifi( NVIC_Priority_T NVIC_Priority )
{
	NVIC_InitTypeDef nvic_usartWIFI;
	nvic_usartWIFI.NVIC_IRQChannel = USART_WIFI_IRQn;
	nvic_usartWIFI.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_usartWIFI.NVIC_IRQChannelSubPriority = NVIC_Priority;
	nvic_usartWIFI.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usartWIFI);
	NVIC_EnableIRQ(USART_WIFI_IRQn);
}

static void priv_InitializePi( NVIC_Priority_T NVIC_Priority )
{
	NVIC_InitTypeDef nvic_usartPI;
	nvic_usartPI.NVIC_IRQChannel = USART_PI_IRQn;
	nvic_usartPI.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_usartPI.NVIC_IRQChannelSubPriority = NVIC_Priority;
	nvic_usartPI.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usartPI);
	NVIC_EnableIRQ(USART_PI_IRQn);
}

static void priv_InitializeEncoderLeft( NVIC_Priority_T NVIC_Priority )
{
	NVIC_InitTypeDef nvic_encoder1;
	nvic_encoder1.NVIC_IRQChannel = TIM_ENC1_IRQn;
	nvic_encoder1.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_encoder1.NVIC_IRQChannelSubPriority = NVIC_Priority;
	nvic_encoder1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_encoder1);
}

static void priv_InitializeEncoderRight( NVIC_Priority_T NVIC_Priority )
{
	NVIC_InitTypeDef nvic_encoder2;
	nvic_encoder2.NVIC_IRQChannel = TIM_ENC2_IRQn;
	nvic_encoder2.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_encoder2.NVIC_IRQChannelSubPriority = NVIC_Priority;
	nvic_encoder2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_encoder2);
}

//-----------------------Public functions------------------------------//
void InitializeNVIC( DriverSelector_T NVIC_Selector )
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	switch ( NVIC_Selector )
	{
	case DriverSelectBt:
		priv_InitializeBt(NVIC_BT);
		break;
	case DriverSelectWifi:
		priv_InitializeWifi(NVIC_Wifi);
		break;
	case DriverSelectPi:
		priv_InitializePi(NVIC_Pi);
		break;
	case DriverSelectEncoders:
		priv_InitializeEncoderLeft( NVIC_EncoderLeft );
		priv_InitializeEncoderRight( NVIC_EncoderRight );
		break;
	default:
		break;
	}

#if 0
	NVIC_InitTypeDef nvic_adc;
	nvic_adc.NVIC_IRQChannel = ADC_IRQn;
	nvic_adc.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_adc.NVIC_IRQChannelSubPriority = 6;
	nvic_adc.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_adc);
#endif
}

//TODO:handle it. OR not.
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}

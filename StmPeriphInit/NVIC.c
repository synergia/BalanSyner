
//-----------------------Includes-------------------------------------//
#include "NVIC.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//
typedef enum
{
   NVIC_BT = 1u,
} NVIC_Priority_T;

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static void priv_InitializeBt( NVIC_Priority_T NVIC_Priority );

//-----------------------Private functions-----------------------------//
static void priv_InitializeBt( NVIC_Priority_T NVIC_Priority )
{
   NVIC_InitTypeDef nvic_usartBT;
   nvic_usartBT.NVIC_IRQChannel = USART_BT_IRQn;
   nvic_usartBT.NVIC_IRQChannelPreemptionPriority = 0u;
   nvic_usartBT.NVIC_IRQChannelSubPriority = NVIC_Priority;
   nvic_usartBT.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init( &nvic_usartBT );
   NVIC_EnableIRQ( USART_BT_IRQn );
}

//-----------------------Public functions------------------------------//
void InitializeNVIC( DriverSelector_T NVIC_Selector )
{
   NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );

   switch ( NVIC_Selector )
   {
   case DriverSelectBt:
      priv_InitializeBt( NVIC_BT );
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


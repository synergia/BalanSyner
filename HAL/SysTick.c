
//-----------------------Includes-------------------------------------//
#include "SysTick.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//

void InitializeSysTick()
{
	SysTick_Config(SYSTICK_FREQUENCY_KHZ>>3);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

void SysTick_Handler(void)
{
	//------------------1ms tasks-------------------------------------//
	//LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;
}

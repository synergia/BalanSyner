
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
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
	SysTick_Config(SYSTICK_FREQUENCY_KHZ>>0);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

void SysTick_Handler(void)
{
	static uint16_t Counter = 124;

	//-------------------------8ms tasks-------------------------------------//
	--Counter;

	//-------------------------32ms tasks-------------------------------------//
	if( 0 == (Counter % 4) )
	{
		MainTask32ms();
	}
	//-------------------------1000ms(1Hz)	tasks-------------------------------------//
	if( 0 == Counter)
	{
		Counter = 124;
	}

}

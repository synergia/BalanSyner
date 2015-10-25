
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "SysTick.h"
#include "../Drivers/MPU/MPU.h" 	//struct with angle and gyro
#include "../Drivers/LEDs/LED.h" 	//led blinking functions
#include "../Drivers/BT/BT.h"		//usart sending

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
	static uint16_t Counter = 125;

	//-------------------------8ms tasks-------------------------------------//
	--Counter;

	//-------------------------32ms tasks-------------------------------------//
	if( 0 == (Counter % 4) )
	{
		/* whole process needs about 2ms */
		LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;

		MPU_Perform(); //save data to struct in MPU.h/c
 	    BT_SendMeasuredData( );

		LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;
	}
	//-------------------------1000ms(1Hz)	tasks-------------------------------------//
	if( 0 == Counter)
	{
		Counter = 125;
	}

}

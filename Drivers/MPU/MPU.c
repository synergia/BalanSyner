
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "MPU.h"
#include "GPIO.h"
#include "I2C.h"
#include "RCC.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeMPU()
{
	InitializeRCC(SelectMpu);
	InitializeI2C();
	InitializeGPIO(SelectMpu);
}

void MPU_Send(uint16_t Char)
{
	//while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	//USART_SendData(USART_BT, Char);

	//while ((USART_BT->ISR & USART_FLAG_TXE) == RESET) {}
	//USART_BT->TDR = Char;
}

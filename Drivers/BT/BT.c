
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "BT.h"
#include "GPIO.h"
#include "RCC.h"
#include "USART.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeBT()
{
	InitializeRCC(SelectBt);
	InitializeUSART(USART_BT);
	InitializeGPIO(SelectBt);
}

void BT_Send(uint16_t Char)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART_BT, Char);
}

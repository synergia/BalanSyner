
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "BT.h"
#include "GPIO.h"
#include "RCC.h"
#include "USART.h"
#include "../Drivers/MPU/MPU.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//
extern MpuKalmanDataStruct MpuKalmanData;

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeBT()
{
	InitializeRCC(SelectBt);
	InitializeUSART(USART_BT);
	InitializeGPIO(SelectBt);
}

void BT_Send8(int8_t Char)
{
	while (USART_GetFlagStatus(USART_BT, USART_FLAG_TXE) == RESET);
	USART_SendData(USART_BT, Char);
}

void BT_Send16(int16_t Word)
{
	while (USART_GetFlagStatus(USART_BT, USART_FLAG_TXE) == RESET);
	USART_SendData(USART_BT, (Word>>8 & 0xFF) );
	while (USART_GetFlagStatus(USART_BT, USART_FLAG_TXE) == RESET);
	USART_SendData(USART_BT, (Word & 0xFF) );
}

void BT_Send32(int32_t Word)
{
	while (USART_GetFlagStatus(USART_BT, USART_FLAG_TXE) == RESET);
	USART_SendData(USART_BT, (Word>>24 & 0xFF) );
	while (USART_GetFlagStatus(USART_BT, USART_FLAG_TXE) == RESET);
	USART_SendData(USART_BT, (Word>>16 & 0xFF) );
	while (USART_GetFlagStatus(USART_BT, USART_FLAG_TXE) == RESET);
	USART_SendData(USART_BT, (Word>>8 & 0xFF) );
	while (USART_GetFlagStatus(USART_BT, USART_FLAG_TXE) == RESET);
	USART_SendData(USART_BT, (Word & 0xFF) );

}

void BT_SendF32(float f)
{
	int8_t *p, i;
	p=(int8_t *) & f;
	for(i=0; i<sizeof(float);i++)
	{
		while (USART_GetFlagStatus(USART_BT, USART_FLAG_TXE) == RESET);
		USART_SendData(USART_BT, (*p++) );
	}
}

void BT_SendMeasuredData( void )
{
	BT_Send16( 0xFFFF );										//start bits
	BT_Send32( (int32_t)(MpuKalmanData.Angle*1000) );
	BT_Send32( (int32_t)(MpuKalmanData.AngleFiltered*1000) );
}

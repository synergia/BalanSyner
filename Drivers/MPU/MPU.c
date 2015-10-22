
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "MPU.h"
#include "_LibMPU6050.h"
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
uint8_t InitializeMPU()
{
	MPU6050_errorstatus errorstatus;
	InitializeRCC(SelectMpu);
	InitializeI2C();
	InitializeGPIO(SelectMpu);
	errorstatus = MPU6050_Initialization();
	return errorstatus;
}

void MPU_Send(uint16_t Char)
{

}

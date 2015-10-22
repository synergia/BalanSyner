
//-----------------------Includes-------------------------------------//
#include "I2C.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static uint8_t checkI2CErrors(I2C_TypeDef *I2Cx);

//-----------------------Private functions-----------------------------//
static uint8_t checkI2CErrors(I2C_TypeDef *I2Cx)
{
	return 0;
}

//-----------------------Public functions------------------------------//
void InitializeI2C()
{
	I2C_InitTypeDef  I2C_InitStructure;

	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
	I2C_InitStructure.I2C_DigitalFilter = 0x00;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_Timing = 0xC062121F;

	I2C_Init(MPU_I2C, &I2C_InitStructure);
	I2C_Cmd(MPU_I2C, ENABLE);
}

void I2C_read(I2C_TypeDef *I2Cx, uint8_t address, uint8_t first_reg, uint8_t length, int8_t *buffor)
{
	checkI2CErrors(MPU_I2C);
	I2C_SendData(MPU_I2C, 'd');
}

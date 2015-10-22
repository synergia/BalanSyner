#ifndef I2C_H_
#define I2C_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void InitializeI2C();
void I2C_read(I2C_TypeDef *I2Cx, uint8_t address, uint8_t first_reg, uint8_t length, int8_t *buffor);

#endif

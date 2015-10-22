#ifndef SYSTICK_H_
#define SYSTICK_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "main.h"
#include "../Drivers/PinDefines.h"
#include "../Drivers/LEDs/LED.h"

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void InitializeSysTick();
void SysTick_Handler(void);

#endif

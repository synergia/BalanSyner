#ifndef LED_H_
#define LED_H_

//-----------------------Includes-------------------------------------//
#include "../Drivers/PinDefines.h"

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//
#define LED_Nucleo_SetOff 	GPIO_SetBits(LED_NUCLEO_GPIO, LED_NUCLEO_PIN)
#define LED_Nucleo_SetOn 	GPIO_ResetBits(LED_NUCLEO_GPIO, LED_NUCLEO_PIN)
#define LED_NUCLEO_IsOn		GPIO_ReadOutputDataBit(LED_NUCLEO_GPIO, LED_NUCLEO_PIN)
//TODO: Add macros for every each LED, operate on registers, not functions

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void InitializeLedNucleo();
void InitializeLed14();
void InitializeLedEye();

#endif

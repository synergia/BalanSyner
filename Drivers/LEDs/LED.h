#ifndef LED_H_
#define LED_H_

//-----------------------Includes-------------------------------------//
#include "../Drivers/PinDefines.h"

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//
#define LED_Nucleo_SetOff  GPIO_SetBits(LED_NUCLEO_GPIO, LED_NUCLEO_PIN)
#define LED_Nucleo_SetOn   GPIO_ResetBits(LED_NUCLEO_GPIO, LED_NUCLEO_PIN)
#define LED_NUCLEO_IsOn    GPIO_ReadOutputDataBit(LED_NUCLEO_GPIO, LED_NUCLEO_PIN)

#define LED1_SetOff  GPIO_SetBits(LED1_GPIO, LED1_PIN)
#define LED1_SetOn   GPIO_ResetBits(LED1_GPIO, LED1_PIN)
#define LED1_IsOn    GPIO_ReadOutputDataBit(LED1_GPIO, LED1_PIN)
#define LED1_Toggle  (LED1_IsOn ? LED1_SetOn : LED1_SetOff )

#define LED2_SetOff  GPIO_SetBits(LED2_GPIO, LED2_PIN)
#define LED2_SetOn   GPIO_ResetBits(LED2_GPIO, LED2_PIN)
#define LED2_IsOn    GPIO_ReadOutputDataBit(LED2_GPIO, LED2_PIN)
#define LED2_Toggle  ( LED2_IsOn ? LED2_SetOn : LED2_SetOff )

#define LED3_SetOff  GPIO_SetBits(LED3_GPIO, LED3_PIN)
#define LED3_SetOn   GPIO_ResetBits(LED3_GPIO, LED3_PIN)
#define LED3_IsOn    GPIO_ReadOutputDataBit(LED3_GPIO, LED3_PIN)
#define LED3_Toggle  (LED3_IsOn ? LED3_SetOn : LED3_SetOff )

#define LED4_SetOff  GPIO_SetBits(LED4_GPIO, LED4_PIN)
#define LED4_SetOn   GPIO_ResetBits(LED4_GPIO, LED4_PIN)
#define LED4_IsOn    GPIO_ReadOutputDataBit(LED4_GPIO, LED4_PIN)
#define LED4_Toggle  (LED4_IsOn ? LED4_SetOn : LED4_SetOff )
//TODO: Add macros for every each LED, operate on registers, not functions

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void InitializeLedNucleo();
void InitializeLed14();
void InitializeLedEye();

#endif

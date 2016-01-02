#ifndef SYSTICK_H_
#define SYSTICK_H_

//-----------------------Includes-------------------------------------//
#include <stdbool.h>

//-----------------------Public defines-------------------------------//
#define SYSTICK_FREQUENCY_HZ  72000000
#define SYSTICK_FREQUENCY_KHZ 72000
#define SYSTICK_FREQUENCY_MHZ 72

//-----------------------Public macros--------------------------------//

//-----------------------Public typedefs------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void InitializeSysTick();
void SysTick_Handler( void );

#endif

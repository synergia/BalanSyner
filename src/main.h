#ifndef MAIN_H_
#define MAIN_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"

//-----------------------Public typedefs------------------------------//
typedef struct
{
	int16_t X_AccRaw;
	int16_t Y_AccRaw;
	int16_t Z_AccRaw;
	int16_t X_GyroRaw;
	int16_t Y_GyroRaw;
	int16_t Z_GyroRaw;
}MeasuredDataStruct;

//-----------------------Public defines-------------------------------//
#define CPU_FREQUENCY_HZ 		24000000
#define CPU_FREQUENCY_KHZ 		24000
#define CPU_FREQUENCY_MHZ 		24
#define SYSTICK_FREQUENCY_HZ	72000000
#define SYSTICK_FREQUENCY_KHZ	72000
#define SYSTICK_FREQUENCY_MHZ	72

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//

#endif

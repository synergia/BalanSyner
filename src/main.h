#ifndef MAIN_H_
#define MAIN_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"

#include "../HAL/SysTick.h"
#include "../HAL/NVIC.h"
#include "../HAL/Timers.h"
#include "../HAL/RCC.h"
#include "../HAL/USART.h"

#include "../Drivers/Clock/clock.h"
#include "../Drivers/LEDs/LED.h"
#include "../Drivers/BT/BT.h"
#include "../Drivers/Wifi/Wifi.h"
#include "../Drivers/MPU/MPU.h"
#include "../Drivers/MPU/_LibMPU6050.h"

//-----------------------Public typedefs------------------------------//
typedef struct
{
	int16_t Z_AccRaw;
	int16_t Y_AccRaw;
	int16_t X_GyroRaw;
	float AngleYZ_AccRaw;
	int32_t AngleYZ_AccPrsc1000;
	float AngleX_GyroRaw;
	int32_t AngleX_GyroPrsc1000;
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
MPU6050_errorstatus err;
MeasuredDataStruct MpuMeasuredData;

//-----------------------Public prototypes----------------------------//

#endif

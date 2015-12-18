#ifndef ADC_H_
#define ADC_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//
#define NumberOfAdcs       2

#define BatteryNumber      1
#define BatteryIndex       ( BatteryNumber - 1 )
#define SharpNumber        2
#define SharpIndex         ( SharpNumber - 1 )

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//
uint16_t AdcBufferTable[NumberOfAdcs];

//-----------------------Public prototypes----------------------------//
void InitializeADC( uint8_t GPIO_Selector );

#endif

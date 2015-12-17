#ifndef BATTERY_H_
#define BATTERY_H_

//-----------------------Includes-------------------------------------//
#include "../Drivers/PinDefines.h"

//-----------------------Public typedefs------------------------------//
typedef struct
{
   float Voltage;
   float ChargedPercent;
}BatteryParameters_T;

typedef struct
{
   BatteryParameters_T Parameters;

   void ( *AdjustPwm ) ( float *Pwm );
   float ( *GetVoltage ) ( BatteryParameters_T *pkThis );
   void ( *Perform ) ( BatteryParameters_T *pkThis );
}Battery_C;

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//
Battery_C oBattery;

//-----------------------Public prototypes----------------------------//
void InitializeBattery();

#endif

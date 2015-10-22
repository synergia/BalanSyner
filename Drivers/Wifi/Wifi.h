#ifndef WIFI_H_
#define WIFI_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void InitializeWifi();
void Wifi_Send(uint8_t Char);

#endif

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

//-----------------------Includes-------------------------------------//
#include "USART.h"
#include "../Drivers/BT/BT.h"

//-----------------------Public defines-------------------------------//
//#define USART1InterruptCallback()
#define USART2InterruptCallback()   BtRxInterruptCallback()
//#define USART3InterruptCallback()

//-----------------------Public macros--------------------------------//

//-----------------------Public typedefs------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//


#endif

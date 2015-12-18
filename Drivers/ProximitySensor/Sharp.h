#ifndef SHARP_H_
#define SHARP_H_

//-----------------------Includes-------------------------------------//
#include "../Drivers/PinDefines.h"

//-----------------------Public typedefs------------------------------//
typedef struct
{
   float Distance;
   float Omega;
   void ( *Perform )( void );
}Sharp_C;

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//
Sharp_C oSharp;

//-----------------------Public prototypes----------------------------//
void InitializeSharp();

#endif

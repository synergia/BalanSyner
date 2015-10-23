/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO(R)
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. This file may only be built (assembled or compiled and linked)
**  using the Atollic TrueSTUDIO(R) product. The use of this file together
**  with other tools than Atollic TrueSTUDIO(R) is not permitted.
**
*****************************************************************************
*/

//-----------------------Includes-------------------------------------//
#include "main.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
int main(void);

//-----------------------Private functions-----------------------------//
int main(void)
{
	InitializeClock();
	InitializeSysTick();
	InitializeTimers();//todo wypieprzyæ: ma by initMOTORS, SERVOSARM, SERVOSCAM

#ifdef _USE_LED_NUCLEO
	InitializeLedNucleo();
#endif

#ifdef _USE_LED_14
	InitializeLed14();
#endif

#ifdef _USE_LED_EYE
	InitializeLedEye();
#endif

#ifdef _USE_BT
	InitializeBT();
#endif

#ifdef _USE_WIFI
	InitializeWifi();
#endif

#ifdef _USE_MPU
	err = InitializeMPU();
#endif

  //InitializeNVIC(); todo: ma byæ w initach komponentów, powyej
  while (1)
  {
	  ;
  }
  return 0;
}

//-----------------------Public functions------------------------------//


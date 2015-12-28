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
#include "stm32f30x.h"
#include "main.h"

#include "../StmPeriphInit/SysTick.h"

#include "../Drivers/Battery/Battery.h"
#include "../Drivers/BT/BT.h"
#include "../Drivers/Clock/clock.h"
#include "../Drivers/LEDs/LED.h"
#include "../Drivers/Motors/Motors.h"
#include "../Drivers/MPU/MPU.h"
#include "../Drivers/ProximitySensor/Sharp.h"
#include "../Drivers/Wifi/Wifi.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
int main(void);

//-----------------------Private functions-----------------------------//
int main(void)
{
   uint16_t i;
   for( i = 0; i < 64000; i++) asm("nop");

   InitializeClock();
   InitializeSysTick();

#ifdef _USE_DISPLAY
   InitializeDisplay();
#endif

#ifdef _USE_MOTORS
   InitializeMotors();
#endif

#ifdef _USE_ADC_BATTERY
   InitializeBattery();
#endif

#ifdef _USE_ADC_SHARP
   InitializeSharp();
#endif

#ifdef _USE_ENCODERS
   InitializeEncoders();
#endif

#ifdef _USE_SERVOS
   InitializeServos();
#endif

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
   InitializeMPU();
#endif

#if 0
   if(//MPU error))
   {
      //sth bad had happened...
   }
#endif


   oMotors.SetSpeedLeft( 0.0f );
   oMotors.SetSpeedRight( 0.0f );
   oServos.SetAngle( SelectServoArmLeft, 0.0f );
   oServos.SetAngle( SelectServoArmRight, 0.0f );
   oServos.SetAngle( SelectServoCamVer, 0.0f );
   oServos.SetAngle( SelectServoCamHor, -15.0f );
   while (1)
   {

   }
   return 0;
}

//-----------------------Public functions------------------------------//


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



//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
int main(void);

//-----------------------Private functions-----------------------------//
int main(void)
{
  uint32_t ii = 1;
  MPU6050_errorstatus err;
  err = MPU6050_I2C_ERROR;

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

  int16_t x,y,z;
  int8_t s8x, s8y, s8z;
  while (1)
  {
       if(--ii==0){
    	   err = MPU6050_Get_Accel_Data_Raw(&x,&y,&z);
    	   if(MPU6050_NO_ERROR == err){
    		   BT_Send( 1 );
    		   s8x = (x>>8) & 0xFF;
    		   s8y = (y>>8) & 0xFF;
    		   s8z = (z>>8) & 0xFF;
    		   ( s8x==1 ) ? BT_Send( 0 ) : BT_Send( s8x );
    		   ( s8y==1 ) ? BT_Send( 0 ) : BT_Send( s8y );
    		   ( s8z==1 ) ? BT_Send( 0 ) : BT_Send( s8z );

    		   LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;
    	   }
    	   ii=50000;
       }
  }
  return 0;
}

//-----------------------Public functions------------------------------//


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

#include "../Drivers/Clock/clock.h"
#include "../Drivers/LEDs/LED.h"
#include "../Drivers/BT/BT.h"
#include "../Drivers/Wifi/Wifi.h"
#include "../Drivers/MPU/MPU.h"
#include "../Drivers/Motors/Motors.h"

#include "Logic.h"

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

#ifdef _USE_MOTORS
   InitializeMotors();
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
   if(//no MPU error))
   {
      //sth bad had happened...
   }
#endif

   /*todo: only for labview sending purposes
   *AnglePrsc1000 = (int32_t)(*Angle*1000);*/


   while (1)
   {
//      oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, 'A');
//      oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, 'T');
   //   oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, '+');
   //   oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, 'N');
   //   oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, 'A');
   //   oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, 'M');
   //   oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, 'E');
   //   oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, '=');
   //   oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, 'A');
//      oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, 0x0d);
//      oBluetooth.PushFifo(&oBluetooth.oBtTxFifo, 0x0a);

//      oBluetooth.SendFifo();

   }
   return 0;
}

//-----------------------Public functions------------------------------//
inline void MainTask16ms()
{
   /* whole process needs about 2ms */
//   LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;

   //oMpuKalman.GetFiltedAngle();
   //int8_t speed = oEncoderLeft.GetOmega( &oEncoderLeft.Parameters );
   //oBluetooth.PushFifo( &oBluetooth.oBtTxFifo, speed );
   //oBluetooth.SendFifo();

   static float f=0.0f;
   static uint8_t up = 1;
   if(up)
   {
      f += 1;
      if(f>=180) up=0;
   }
   else{
      f -= 1;
      if(f<=-180) up=1;
   }
   oServosArm.SetAngle(SelectServoArmLeft, f);

   //oBluetooth.SendKalmanToLabView();

//   LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;
}

inline void MainTask128ms()
{
#if 0
   uint8_t Command[] = { 0xFF, 0xFF, 101, 0, 0, 0, 0, 1 };

   float Value = oMpuKalman.GetKalmanQAngle();

   uint32_t transport_bits = *( ( uint32_t* ) &Value );
   *(uint32_t *) &Command[3] = transport_bits;

   priv_SendCommandBT( Command );

#endif

   static uint16_t i=300;
   oMotor.SetSpeed(SelectMotorLeft, i, DirectionCW);
   oMotor.SetSpeed(SelectMotorRight, i, DirectionCW);
   i += 5;
   if(900 < i) i=300;

   Logic_CheckInputs(); //check if any command from USART or buttons came and save buffer to struct. ADCx2.
   LED1_IsOn ? LED1_SetOn : LED1_SetOff;
}

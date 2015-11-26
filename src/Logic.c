/*
 * Logic.c
 *
 *  Created on: Nov 22, 2015
 *      Author: Kuba
 */

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "Logic.h"

#include "../Drivers/BT/BT.h"
#include "../Drivers/MPU/MPU.h"

//-----------------------Private defines-------------------------------//
#define START_BYTE_DEF           0xFF
#define COMMAND_LENGTH           4

//-----------------------Private macros--------------------------------//

//-----------------------Private typedefs------------------------------//
typedef enum
{
   ReadKalmanQAngle = 0u,
   ReadKalmanRMeasure = 1u,

   WriteKalmanQAngleDef    = 100u,
   WriteKalmanQAngle       = 101u,
   WriteKalmanRMeasureDef  = 102u,
   WriteKalmanRMeasure     = 103u,

}Addresses_T;
//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
uint8_t priv_CheckParityBits();
//static void priv_ReadKalmanQAngle();
static void priv_ReadKalmanRMeasure();

//static void priv_WriteKalmanQAngle( uint8_t *Command );
static void priv_WriteKalmanQAngleDef();
static void priv_WriteKalmanRMeasure( uint8_t *Command );
static void priv_WriteKalmanRMeasureDef();

//-----------------------Private functions-----------------------------//
uint8_t priv_CheckParityBits()
{
   return 1;
}

void priv_ReadKalmanQAngle()
{
   float Value = oMpuKalman.GetKalmanQAngle();
   //TODO: send Usart
}

static void priv_ReadKalmanRMeasure()
{
   float Value = oMpuKalman.GetKalmanRMeasure();
   //TODO: send Usart
}

 void priv_WriteKalmanQAngle( uint8_t *Command )
{
   //TODO:check it
   uint32_t transport_bits = *( ( uint32_t* ) Command );
   float destination_float = *( ( float* ) & transport_bits );

   oMpuKalman.SetKalmanQAngle( destination_float );
}

static void priv_WriteKalmanQAngleDef()
{
   oMpuKalman.SetKalmanQAngleDef();
}

static void priv_WriteKalmanRMeasure( uint8_t *Command )
{
   //TODO:check it
   uint32_t transport_bits = *( ( uint32_t* ) Command );
   float destination_float = *( ( float* ) & transport_bits );

   oMpuKalman.SetKalmanRMeasure( destination_float );
}

static void priv_WriteKalmanRMeasureDef()
{
   oMpuKalman.SetKalmanRMeasureDef();
}

//-----------------------Public functions------------------------------//
/*!
 * fn:            Logic_CheckInputs
 * Description:   This function checks whether external command came. The protocol is as follows:
 *    --------------------------------------------------
 *    | SB | SB | Adr | Val1 | Val2 | Val3 | Val4 | PB |
 *    --------------------------------------------------
 *
 *    SB - start byte = 255
 *
 *    Adr: TODO:Update list. Temporarly look at enum Addresses.
 *       000 - Read&Send Kalman Q_Angle (gyro variance)
 *       001 - Read&Send Kalman R_measure (accelerometer variance)
 *
 *       100 - Write new Kalman Q_Angle (gyro variance)
 *       101 - Write new Kalman R_measure (accelerometer variance)
 *
 *    Valx: uint32_t value or float value
 *       Val1:MSB - - - Val4:LSB
 *
 *       float source_float = 1234.5678f ;
 *       uint32_t transport_bits = *((uint32_t*)&source_float);
 *       float destination_float = *((float*)&transport_bits);
 *
 *    PB - parity check TODO: implement some
 */
#include "../Drivers/LEDs/LED.h"
void Logic_CheckInputs()
{
   while( 0u != oBluetooth.IsFifoEmpty( &oBluetooth.oBtRxFifo ) )
   {

      /*!
       * Check for first start byte
       */
      uint8_t BufferSize = 0u;
      uint8_t StartByte = 0u;
      do
      {
         BufferSize = oBluetooth.PopFifo( &oBluetooth.oBtRxFifo, &StartByte );
      } while ( ( START_BYTE_DEF != StartByte ) && ( 6u < BufferSize ) );

      /*!
       *  Check for second start byte.
       */
      if( START_BYTE_DEF == StartByte )
      {
         StartByte = 0u;
         BufferSize = oBluetooth.PopFifo( &oBluetooth.oBtRxFifo, &StartByte );

         if( ( START_BYTE_DEF == StartByte ) && ( 5u < BufferSize ) )
         {
            uint8_t Command[6];
            uint8_t Counter;
            /*! Copy buffer to Command array */
            for( Counter = 0u ;  Counter < 6u; Counter++ )
            {
               oBluetooth.PopFifo( &oBluetooth.oBtRxFifo, &Command[ Counter ] );
            }

            if( priv_CheckParityBits() == Command[5] )
            {
               /*! Everything is ok. */
               LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;

               switch( Command[0] )
               {
                  case ReadKalmanQAngle:
                     priv_ReadKalmanQAngle();
                     break;
                  case ReadKalmanRMeasure:
                     priv_ReadKalmanRMeasure();
                     break;
                  case WriteKalmanQAngleDef:
                     priv_WriteKalmanQAngleDef();
                     break;
                  case WriteKalmanQAngle:
                     priv_WriteKalmanQAngle( &Command[1] ); //send addres of first value byte
                     break;
                  case WriteKalmanRMeasureDef:
                     priv_WriteKalmanRMeasureDef();
                     break;
                  case WriteKalmanRMeasure:
                     priv_WriteKalmanRMeasure( &Command[1] );
                     break;
                  default:
                     break;
               }
            }
         }
      }
   }
}

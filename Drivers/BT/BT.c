
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "../Drivers/MPU/MPU.h"
#include "../Framework/Fifo/Fifo.h"
#include "BT.h"
#include "GPIO.h"
#include "RCC.h"
#include "USART.h"
#include "NVIC.h"

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private typedefs------------------------------//

//-----------------------Private variables-----------------------------//
extern MpuKalmanClass_T oMpuKalman;

//-----------------------Private prototypes----------------------------//
static void priv_BtSend8( int8_t Char );
static void priv_BtSendMeasuredData( void );
static void priv_BtPushFifo( Fifo_C *oFifo, int8_t Value );
static uint16_t priv_BtFifoPop( Fifo_C *oFifo, void *pDst );
static void priv_BtSendFifo(); /*! Sends TxBuffer via USARTc */
static uint8_t priv_BtFifoIsEmpty( Fifo_C *oFifo );

//-----------------------Private functions-----------------------------//
static void priv_BtPushFifo( Fifo_C *oFifo, int8_t Value )
{
   int8_t Src = Value;
   Fifo_Push( oFifo, &Src );
}

static uint16_t priv_BtFifoPop( Fifo_C *oFifo, void *pDst )
{
   return ( Fifo_Pop( oFifo, pDst ) );
}

static void priv_BtSendFifo()
{
   uint8_t Data;
   while( !Fifo_IsEmpty( &oBluetooth.oBtTxFifo ) )
   {
      Fifo_Pop( &oBluetooth.oBtTxFifo, &Data );
      priv_BtSend8( Data );
   }
}

static uint8_t priv_BtFifoIsEmpty( Fifo_C *oFifo )
{
   return ( 0u == Fifo_IsEmpty( oFifo ) );
}

static void priv_BtSend8( int8_t Char )
{
   while (USART_GetFlagStatus(USART_BT, USART_FLAG_TXE) == RESET);
   USART_SendData(USART_BT, Char);
}

static void priv_BtSendMeasuredData( void )
{
   priv_BtPushFifo( &oBluetooth.oBtTxFifo, 0xFF );
   priv_BtPushFifo( &oBluetooth.oBtTxFifo, 0xFF );

   priv_BtPushFifo( &oBluetooth.oBtTxFifo, (int32_t)(oMpuKalman.AngleRaw*1000)>>24 & 0xFF );
   priv_BtPushFifo( &oBluetooth.oBtTxFifo, (int32_t)(oMpuKalman.AngleRaw*1000)>>16 & 0xFF );
   priv_BtPushFifo( &oBluetooth.oBtTxFifo, (int32_t)(oMpuKalman.AngleRaw*1000)>>8  & 0xFF );
   priv_BtPushFifo( &oBluetooth.oBtTxFifo, (int32_t)(oMpuKalman.AngleRaw*1000)     & 0xFF );

   priv_BtPushFifo( &oBluetooth.oBtTxFifo, (int32_t)(oMpuKalman.AngleFiltered*1000)>>24 & 0xFF );
   priv_BtPushFifo( &oBluetooth.oBtTxFifo, (int32_t)(oMpuKalman.AngleFiltered*1000)>>16 & 0xFF );
   priv_BtPushFifo( &oBluetooth.oBtTxFifo, (int32_t)(oMpuKalman.AngleFiltered*1000)>>8  & 0xFF );
   priv_BtPushFifo( &oBluetooth.oBtTxFifo, (int32_t)(oMpuKalman.AngleFiltered*1000)     & 0xFF );

   priv_BtSendFifo();
}

//-----------------------Public functions------------------------------//
void InitializeBT()
{
   /*! Physical initialization */
   InitializeRCC( DriverSelectBt );
   InitializeGPIO( DriverSelectBt );
   InitializeNVIC( DriverSelectBt );
   InitializeUSART( USART_BT );

   /*! Software */
   oBluetooth.PushFifo = priv_BtPushFifo;
   oBluetooth.PopFifo = priv_BtFifoPop;
   oBluetooth.SendFifo = priv_BtSendFifo;
   oBluetooth.IsFifoEmpty = priv_BtFifoIsEmpty;
   oBluetooth.SendKalmanToLabView = priv_BtSendMeasuredData;

   Fifo_Initialize( &oBluetooth.oBtTxFifo, oBluetooth.kBtTxBuffer, BtTxElementSize, BtTxBufferSize );
   Fifo_Initialize( &oBluetooth.oBtRxFifo, oBluetooth.kBtRxBuffer, BtRxElementSize, BtRxBufferSize );
}
#include "../Drivers/LEDs/LED.h"
void BtRxInterruptCallback()
{
   LED3_Toggle;
   oBluetooth.PushFifo( &oBluetooth.oBtRxFifo, USART_BT->RDR );
}


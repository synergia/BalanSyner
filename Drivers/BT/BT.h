#ifndef BT_H_
#define BT_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/Fifo/Fifo.h"

//-----------------------Public defines-------------------------------//
#define BtTxBufferNumberOfElements  64
#define BtTxElementSize             1

#define BtRxBufferNumberOfElements  64
#define BtRxElementSize             1

//-----------------------Public macros--------------------------------//
#define BtTxBufferSize              ( BtTxBufferNumberOfElements * BtTxElementSize )

#define BtRxBufferSize              ( BtTxBufferNumberOfElements * BtTxElementSize )

//-----------------------Public typedefs------------------------------//
typedef struct
{
   FifoBuffer_T kBtTxBuffer[ BtTxBufferSize ];
   Fifo_C oBtTxFifo;

   FifoBuffer_T kBtRxBuffer[ BtRxBufferSize ];
   Fifo_C oBtRxFifo;

   void ( *PushFifo )( Fifo_C *oFifo, int8_t Value );
   uint16_t ( *PopFifo )( Fifo_C *oFifo, void *pDst);
   void ( *SendFifo )( void );
   uint8_t ( *IsFifoEmpty)( Fifo_C *oFifo );
   void ( *SendKalmanToLabView )( void );
}Bluetoth_C;

//-----------------------Public variables-----------------------------//
Bluetoth_C oBluetooth;

//-----------------------Public prototypes----------------------------//
void InitializeBT( void );
void BtRxInterruptCallback();

#endif

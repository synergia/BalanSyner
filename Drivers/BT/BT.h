#ifndef BT_H_
#define BT_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/Fifo/Fifo.h"

//-----------------------Public defines-------------------------------//
#define BtTxBufferNumberOfElements  64
#define BtTxElementSize             1

//-----------------------Public macros--------------------------------//
#define BtTxBufferSize              ( BtTxBufferNumberOfElements * BtTxElementSize )

//-----------------------Public typedefs------------------------------//
typedef struct
{
   FifoBuffer_T kBtTxBuffer[ BtTxBufferSize ];
   Fifo_C oBtFifo;

   void ( *PushFifo )( int8_t Value );
   void ( *SendFifo )( void );
   void ( *SendKalmanToLabView )( void );
}Bluetoth_C;

//-----------------------Public variables-----------------------------//
Bluetoth_C oBluetooth;

//-----------------------Public prototypes----------------------------//
void InitializeBT( void );

#endif

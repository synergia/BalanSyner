
//-----------------------Includes-------------------------------------//
#include "Fifo.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void Fifo_Initialize( Fifo_C *pThis, uint8_t *pAddress, uint8_t uDataSize, uint16_t uBufferSize )
{
   pThis->pFifoBuffer = pAddress;
   pThis->uElementSize = uDataSize;
   pThis->uFifoPointer = 0U;
   pThis->uFifoCounter = 0U;
   pThis->uFifoBufferSize = uBufferSize;
}

void Fifo_Push( Fifo_C *pThis, void *pSrc )
{
   uint32_t uFifoIndex;
   uint16_t i;

   for ( i = 0U ; i < pThis->uElementSize ; i++ )
   {
      uFifoIndex = ( uint32_t ) pThis->uFifoPointer + ( uint32_t ) pThis->uFifoCounter;

      if ( uFifoIndex < ( uint32_t )( pThis->uFifoBufferSize ) )
      {
         pThis->pFifoBuffer[ uFifoIndex ] = *( ( uint8_t* )pSrc + i );
      }
      else
      {
         pThis->pFifoBuffer[ uFifoIndex % ( pThis->uFifoBufferSize ) ] = *( ( uint8_t* )pSrc + i );
      }

      if( !Fifo_IsFull( pThis ) )
      {
         pThis->uFifoCounter++;
      }
      else
      {
         pThis->uFifoPointer++;
         if ( pThis->uFifoPointer >= ( pThis->uFifoBufferSize ) )
         {
            pThis->uFifoPointer = 0u;
         }
      }
   }
}

uint16_t Fifo_Pop( Fifo_C *pThis, void *pDst )
{
   uint16_t i;

   if ( !Fifo_IsEmpty( pThis ) )
   {
      for ( i = 0U ; i < pThis->uElementSize ; i++ )
      {
         *( ( uint8_t* )pDst + i ) = pThis->pFifoBuffer[ pThis->uFifoPointer ];
         pThis->uFifoCounter--;
         pThis->uFifoPointer++;

         if ( pThis->uFifoPointer >= ( pThis->uFifoBufferSize ) )
         {
            pThis->uFifoPointer = 0U;
         }
      }
   }

   return ( pThis->uFifoCounter );
}

uint8_t Fifo_IsEmpty( Fifo_C *pThis )
{
   return ( 0U == pThis->uFifoCounter );
}

uint8_t Fifo_IsFull( Fifo_C *pThis )
{
   return ( pThis->uFifoCounter >= pThis->uFifoBufferSize );
}

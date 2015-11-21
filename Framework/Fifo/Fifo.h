/*
 * Fifo.h
 *
 *  Created on: Nov 20, 2015
 *      Author: Kuba
 */

#ifndef FIFO_H_
#define FIFO_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"

//-----------------------Public typedefs------------------------------//
typedef uint8_t FifoBuffer_T;

typedef struct Fifo
{
   FifoBuffer_T *pFifoBuffer;
   uint8_t  uElementSize;
   uint16_t uFifoPointer;
   uint16_t uFifoCounter;
   uint16_t uFifoBufferSize;
} Fifo_C;

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void Fifo_Initialize( Fifo_C *pThis, uint8_t *pAddress, uint8_t uDataSize, uint16_t uBufferSize );

void Fifo_Push( Fifo_C *pThis, void *pSrc );
uint16_t Fifo_Pop( Fifo_C *pThis, void *pDst );

uint8_t Fifo_IsEmpty( Fifo_C *pThis );
uint8_t Fifo_IsFull( Fifo_C *pThis );

#endif /* FIFO_H_ */

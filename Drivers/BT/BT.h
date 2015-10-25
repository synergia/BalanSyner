#ifndef BT_H_
#define BT_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void InitializeBT( void );
void BT_Send8(int8_t Char);
void BT_Send16(int16_t Word);
void BT_SendF32(float f);
void BT_SendMeasuredData( void );

#endif

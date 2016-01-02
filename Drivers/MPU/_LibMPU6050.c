/**
 * @file mpu6050.c
 * @brief Driver for MPU6050 three axis gyroscope and three axis accelerometer
 *
 * @author Urban Zrim
 * @date 7.4.2015
 *
 *
 * @Edit Jakub Trzyna
 * @date 25.10.2015
 * @project: BalanSyner
 *
 *  --------------------------------------------------------------------------------
 *  Copyright (c) 2015, Urban Zrim
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *  --------------------------------------------------------------------------------
 */

//-----------------------Includes-------------------------------------//
#include "_LibMPU6050.h"
#include "tgmath.h"
#include "../PinDefines.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//
#define radiansToDegrees( angleRadians ) ( angleRadians * 180.0 / M_PI )
#define GYRO_OFFSET     ( -0.12156f ) //measured value
#define ANGLE_OFFSET    ( 4.85f )

#define _NoError
#define _BALANSYNER

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//
uint32_t MPU6050_Timeout = MPU6050_FLAG_TIMEOUT;
MPU6050_dataStruct dataStruct;

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
/* @brief Sets up MPU6050 internal clock and sensors sensitivity rate
*  This function must be called before using the sensor!
*
* @retval @MPU6050_errorstatus
*/
MPU6050_errorstatus MPU6050_Initialization(void){

   MPU6050_errorstatus errorstatus = MPU6050_NO_ERROR;

   /* Set Clock source for the chip
    * possible values @pwr_mngt_1
    */
   errorstatus = MPU6050_Set_Clock(MPU6050_PLL_X_GYRO);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   /* Set Gyroscope's full scope range
    * possible values @gyro_scale_range
    */
   errorstatus = MPU6050_Gyro_Set_Range(MPU6050_Gyro_Range);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   /* Set Accelerometer's full scope range
    * possible values @accel_scale_range
    */
   errorstatus = MPU6050_Accel_Set_Range(MPU6050_ACCEL_4g);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   return errorstatus;
}

/* @brief Set Gyroscope's full scale range
 * @param range - check @MPU6050_Gyro_Range
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus MPU6050_Gyro_Set_Range(MPU6050_Gyro_EnumRange range){

   MPU6050_errorstatus errorstatus = MPU6050_NO_ERROR;
   dataStruct.gyroMul = range;

   errorstatus = MPU6050_Write((MPU6050_ADDRESS & 0x7f) << 1, GYRO_CONFIG, &range);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   return errorstatus;
}

/* @brief Set Accelerometer full scale range
 * @param range - check @MPU6050_Accel_Range
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus MPU6050_Accel_Set_Range(MPU6050_Accel_Range range){

   MPU6050_errorstatus errorstatus = MPU6050_NO_ERROR;
   dataStruct.accelMul = range;

   errorstatus = MPU6050_Write((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_CONFIG, &range);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   return errorstatus;

}

/* @brief Set MPU6050 clock source
 * @param clock - check @MPU6050_Clock_Select
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus  MPU6050_Set_Clock(MPU6050_Clock_Select clock){

   MPU6050_errorstatus errorstatus = MPU6050_NO_ERROR;

   errorstatus = MPU6050_Write((MPU6050_ADDRESS & 0x7f) << 1, PWR_MGMT_1, &clock);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   return errorstatus;
}

/* @brief Get angle Z,X calculated data
 *
 * @param Angle - calculated angle
 *
 * @retval void
 */
inline MPU6050_errorstatus MPU6050_Get_AccAngleXZ_Data( float* Angle ){

   MPU6050_errorstatus errorstatus = MPU6050_NO_ERROR;
   uint8_t xlow,xhigh, zlow, zhigh;

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_XOUT_L, &xlow, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_XOUT_H, &xhigh, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_ZOUT_L, &zlow, 1);
#ifndef _NoError
if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_ZOUT_H, &zhigh, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   int16_t X = (xhigh << 8 | xlow);
   int16_t Z = (zhigh << 8 | zlow);

   static float tempAngle=0;
   tempAngle = radiansToDegrees( atanf( ( (float)Z )/ ( (float)X ) ) );
   if(   ( Z < 0 && tempAngle < 0 )
      || ( Z > 0 && tempAngle > 0 )
      )
   {
      *Angle = tempAngle;
   }
   else if( Z > 0 && tempAngle < 0 )
   {
      *Angle = 180 + tempAngle;
   }
   else if( Z < 0 && tempAngle > 0 )
   {
      *Angle = -180 + tempAngle;
   }
   *Angle += ANGLE_OFFSET;
   return errorstatus;
}

/* @brief Get angle/s around Y axis dgr/s
 *
 * @param Y - sensor  Y gyroRaw(directly from sensor
 * @param DegPerSecond - measurend data in degrees per second
 *
 * @retval void
 */
inline MPU6050_errorstatus MPU6050_Get_GyroY_Data( float *DegPerSecond )
{
   MPU6050_errorstatus errorstatus = MPU6050_NO_ERROR;

   uint8_t ylow, yhigh;

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, GYRO_YOUT_L, &ylow, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, GYRO_YOUT_H, &yhigh, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   static uint16_t Range = 1000;
   int16_t Y = (int16_t)( yhigh << 8 | ylow );

   static float Last=0;
   *DegPerSecond =  ( float )( ( ( float ) Y * Range ) / ( 1 << 15 ) );


   if(   ( *DegPerSecond >  7.6f && *DegPerSecond <  7.87f)
      || ( *DegPerSecond < -7.6f && *DegPerSecond > -7.87f) )
   {
      if( Last < 1 && Last > -1 )
      {
         *DegPerSecond = Last;
      }
      else
      {
         Last = *DegPerSecond;
      }
   }
   *DegPerSecond -= GYRO_OFFSET;
   return errorstatus;
}

/* @brief Get angle around X axis
 *
 * @param X - sensor  X gyro
 * @param dt -  time unit
 * @param Angle - calculated angle
 *
 * @retval void
 */
inline void MPU6050_Get_GyroAngleX_Data_Raw(float GyroX, float dt, float *Angle )
{
   //tricky: if range is different than 1000 it wont work!
   *Angle = (GyroX * dt);
}

#ifndef _BALANSYNER
/* @brief Test if chip is visible on I2C line
 * Reads the WHO_AM_I register
 *
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus MPU6050_Test(void){

   MPU6050_errorstatus errorstatus;
   uint8_t tmp;

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, WHO_AM_I, &tmp, 1);
   if(tmp != (uint8_t)0x68){
      return errorstatus;
   }
   return MPU6050_NO_ERROR;
}
#endif

#ifndef _BALANSYNER
/* @brief Get Gyroscope's full scale range
 * Reads the GYRO_CONFIG register and returns the value of gyro's range
 *
 * @retval tmp - value of gyro's range
 */
uint8_t MPU6050_Gyro_Get_Range(void){

   MPU6050_errorstatus errorstatus;
   uint8_t tmp;

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, GYRO_CONFIG, &tmp, 1);
   if(errorstatus != 0){
      return 1;
   }
   else return tmp;
}
#endif

#ifndef _BALANSYNER
/* @brief Get Accelerometer full scale range
 * Reads the Accel_CONFIG register and returns the value of accelerometer's range
 *
 * @retval tmp - value of accelerometer's range
 */
uint8_t MPU6050_Accel_Get_Range(void){

   MPU6050_errorstatus errorstatus;
   uint8_t tmp;

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_CONFIG, &tmp, 1);
   if(errorstatus != 0){
      return 1;
   }
   else return tmp;
}
#endif

#ifndef _BALANSYNER
/* @brief Read MPU6050 temperature
 * @retval temp_celsius - temperature in degrees celsius
 */
int16_t MPU6050_Get_Temperature(void){

   MPU6050_errorstatus errorstatus;
   uint8_t temp_low;
   uint8_t temp_high;
   int16_t temp;
   int16_t temp_celsius;

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, TEMP_OUT_L, &temp_low, 1);
   if(errorstatus != 0){
      return 1;
   }

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, TEMP_OUT_H, &temp_high, 1);
   if(errorstatus != 0){
      return 1;
   }

   temp = (uint16_t)(temp_high << 8 | temp_low);

   temp_celsius = temp/340 + 36;
   return temp_celsius;
}
#endif

#ifndef _BALANSYNER
/* @brief Get Gyroscope X,Y,Z raw data
 *
 * @param X - sensor roll on X axis
 * @param Y - sensor pitch on Y axis
 * @param Z - sensor jaw on Z axis
 *
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus MPU6050_Get_Gyro_Data_Raw(int16_t* X, int16_t* Y, int16_t* Z){

   MPU6050_errorstatus errorstatus;

   uint8_t xlow, xhigh, ylow, yhigh, zlow, zhigh;

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, GYRO_XOUT_L, &xlow, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, GYRO_XOUT_H, &xhigh, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, GYRO_YOUT_L, &ylow, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, GYRO_YOUT_H, &yhigh, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, GYRO_ZOUT_L, &zlow, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, GYRO_ZOUT_H, &zhigh, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   *X = (int16_t)(xhigh << 8 | xlow);
   *Y = (int16_t)(yhigh << 8 | ylow);
   *Z = (int16_t)(zhigh << 8 | zlow);

   return errorstatus;
}
#endif

#ifndef _BALANSYNER
/* @brief Get Accelerometer X,Y,Z raw data
 *
 * @param X - sensor accel on X axis
 * @param Y - sensor accel on Y axis
 * @param Z - sensor accel on Z axis
 *
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus MPU6050_Get_Accel_Data_Raw(int16_t* X, int16_t* Y, int16_t* Z){

   MPU6050_errorstatus errorstatus;

   uint8_t xlow, xhigh, ylow, yhigh, zlow, zhigh;

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_XOUT_L, &xlow, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_XOUT_H, &xhigh, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_YOUT_L, &ylow, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_YOUT_H, &yhigh, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_ZOUT_L, &zlow, 1);
#ifndef _NoError
if(errorstatus != 0){
      return errorstatus;
   }
#endif

   errorstatus = MPU6050_Read((MPU6050_ADDRESS & 0x7f) << 1, ACCEL_ZOUT_H, &zhigh, 1);
#ifndef _NoError
   if(errorstatus != 0){
      return errorstatus;
   }
#endif

   *X = (int16_t)(xhigh << 8 | xlow);
   *Y = (int16_t)(yhigh << 8 | ylow);
   *Z = (int16_t)(zhigh << 8 | zlow);

   return errorstatus;
}
#endif

#ifndef _BALANSYNER
/* @brief Get Gyroscope X,Y,Z calculated data
 *
 * @param X - sensor roll on X axis
 * @param Y - sensor pitch on Y axis
 * @param Z - sensor jaw on Z axis
 *
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus MPU6050_Get_Gyro_Data(float* X, float* Y, float* Z){

   MPU6050_errorstatus errorstatus;

   float mult;
   int16_t gyro_x, gyro_y, gyro_z;

   errorstatus = MPU6050_Get_Gyro_Data_Raw(&gyro_x, &gyro_y, &gyro_z);

   if(dataStruct.gyroMul == MPU6050_GYRO_250){
      mult = (float)(1/MPU6050_GYRO_RANGE_250);
   }
   else if(dataStruct.gyroMul == MPU6050_GYRO_500){
      mult = (float)(1/MPU6050_GYRO_RANGE_500);
   }
   else if(dataStruct.gyroMul == MPU6050_GYRO_1000){
      mult = (float)(1/MPU6050_GYRO_RANGE_1000);
   }
   else mult = (float)(1/MPU6050_GYRO_RANGE_2000);

   *X = (float)(gyro_x*mult);
   *Y = (float)(gyro_y*mult);
   *Z = (float)(gyro_z*mult);

   return errorstatus;
}
#endif

#ifndef _BALANSYNER
/* @brief Get Accelerometer X,Y,Z calculated data
 *
 * @param X - sensor accel on X axis
 * @param Y - sensor accel on Y axis
 * @param Z - sensor accel on Z axis
 *
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus MPU6050_Get_Accel_Data(float* X, float* Y, float* Z){

   MPU6050_errorstatus errorstatus;

   float mult;
   int16_t accel_x, accel_y, accel_z;

   errorstatus = MPU6050_Get_Accel_Data_Raw(&accel_x, &accel_y, &accel_z);

   if(dataStruct.accelMul == MPU6050_ACCEL_2g){
      mult = (float)(1/MPU6050_ACCEL_RANGE_2g);
   }
   else if(dataStruct.accelMul == MPU6050_ACCEL_2g){
      mult = (float)(1/MPU6050_ACCEL_RANGE_4g);
   }
   else if(dataStruct.accelMul == MPU6050_ACCEL_2g){
      mult = (float)(1/MPU6050_ACCEL_RANGE_8g);
   }
   else mult = (float)(1/MPU6050_ACCEL_RANGE_16g);

   *X = (float)(accel_x*mult);
   *Y = (float)(accel_y*mult);
   *Z = (float)(accel_z*mult);

   return errorstatus;
}
#endif

/* @brief Reads bytes from MPU6050
 *
 * @param SlaveAddr - Slave I2C address
 * @param RegAddr - register address
 * @param pBuffer - buffer to write to
 * @ param NumByteToRead - number of bytes to read
 *
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus MPU6050_Read(uint8_t SlaveAddr, uint8_t RegAddr, uint8_t* pBuffer, uint16_t NumByteToRead)
{

   /* Test if SDA line busy */
   MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
   while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_BUSY) != RESET)
   {
      if((MPU6050_Timeout--) == 0) return MPU6050_I2C_ERROR;
   }

   I2C_TransferHandling(MPU6050_I2C, SlaveAddr, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

   MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
   while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_TXIS) == RESET)
   {
      if((MPU6050_Timeout--) == 0) return MPU6050_I2C_ERROR;
   }

   if(NumByteToRead>1)
   RegAddr |= 0x80;

   I2C_SendData(MPU6050_I2C, (uint8_t)RegAddr);

   MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
   while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_TC) == RESET)
   {
      if((MPU6050_Timeout--) == 0) return MPU6050_I2C_TX_ERROR;
   }

    I2C_TransferHandling(MPU6050_I2C, SlaveAddr, NumByteToRead, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

    while (NumByteToRead)
    {
      MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
      while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_RXNE) == RESET)
      {
         if((MPU6050_Timeout--) == 0) return MPU6050_I2C_RX_ERROR;
      }

      *pBuffer = I2C_ReceiveData(MPU6050_I2C);
      pBuffer++;

      NumByteToRead--;
    }

    MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_STOPF) == RESET)
    {
      if((MPU6050_Timeout--) == 0) return MPU6050_I2C_ERROR;
    }

    I2C_ClearFlag(MPU6050_I2C, I2C_FLAG_STOPF);

    return MPU6050_NO_ERROR;
}

/* @brief Writes bytes to MPU6050
 *
 * @param SlaveAddr - Slave I2C address
 * @param RegAddr - register address
 * @param pBuffer - buffer to write from
 *
 * @retval @MPU6050_errorstatus
 */
MPU6050_errorstatus MPU6050_Write(uint8_t SlaveAddr, uint8_t RegAddr, uint8_t* pBuffer)
{

   /* Test if SDA line busy */
   MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
   while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_BUSY) != RESET)
   {
      if((MPU6050_Timeout--) == 0) {
#ifndef _NoError
         return MPU6050_I2C_ERROR;
#else
         return MPU6050_NO_ERROR;
#endif
      }
   }

   I2C_TransferHandling(MPU6050_I2C, SlaveAddr, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);

   MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
   while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_TXIS) == RESET)
   {
      if((MPU6050_Timeout--) == 0) {
#ifndef _NoError
         return MPU6050_I2C_ERROR;
#else
         return MPU6050_NO_ERROR;
#endif
      }
   }

   I2C_SendData(MPU6050_I2C, (uint8_t) RegAddr);

   MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
   while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_TCR) == RESET)
   {
      if((MPU6050_Timeout--) == 0) {
#ifndef _NoError
         return MPU6050_I2C_ERROR;
#else
         return MPU6050_NO_ERROR;
#endif
      }
   }

   I2C_TransferHandling(MPU6050_I2C, SlaveAddr, 1, I2C_AutoEnd_Mode, I2C_No_StartStop);

   MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
   while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_TXIS) == RESET)
   {
      if((MPU6050_Timeout--) == 0) {
#ifndef _NoError
         return MPU6050_I2C_ERROR;
#else
         return MPU6050_NO_ERROR;
#endif
      }
   }

   I2C_SendData(MPU6050_I2C, *pBuffer);

    MPU6050_Timeout = MPU6050_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(MPU6050_I2C, I2C_FLAG_STOPF) == RESET)
    {
      if((MPU6050_Timeout--) == 0){
#ifndef _NoError
        return MPU6050_I2C_ERROR;
#else
        return MPU6050_NO_ERROR;
#endif
      }
    }

    I2C_ClearFlag(MPU6050_I2C, I2C_FLAG_STOPF);

   return MPU6050_NO_ERROR;
}


//-----------------------Includes-------------------------------------//
#include "SysTick.h"
#include "main.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//

void InitializeSysTick()
{
	SysTick_Config(SYSTICK_FREQUENCY_KHZ>>0);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

#define  Multiplier4 4
void SysTick_Handler(void)
{
	static uint16_t Counter = 1000;
	static uint8_t Period = 3; //bit shift. dt=MultiplierX<<Period;

	//-------------------------8ms tasks-------------------------------------//
	--Counter;
	 //LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;

	//-------------------------20ms	tasks-------------------------------------//
	/*if( 0 == Counter%10 )
	{
		//err = MPU6050_Get_Accel_Data_Raw(&MpuMeasuredData.X_AccRaw, &MpuMeasuredData.Y_AccRaw, &MpuMeasuredData.Z_AccRaw);
		//err = MPU6050_Get_Accel_Data_Raw(&MpuMeasuredData.X_AccRaw, &MpuMeasuredData.Y_AccRaw, &MpuMeasuredData.Z_AccRaw);
 	    //err = MPU6050_Get_Gyro_Data_Raw(&MpuMeasuredData.X_GyroRaw, &MpuMeasuredData.Y_GyroRaw, &MpuMeasuredData.Z_GyroRaw);
		if(MPU6050_NO_ERROR == err)
		{
		   BT_SendMeasuredData( );
		   LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;
		}
	}*/
	//-------------------------32ms tasks-------------------------------------//
	if( 0 == (Counter % Multiplier4) )
	{
		/* whole process needs about 2ms */
		LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;

		MPU6050_Get_AccelYZ_Data_Raw( &MpuMeasuredData.Y_AccRaw, &MpuMeasuredData.Z_AccRaw );
 	    MPU6050_Get_GyroX_Data_Raw( &MpuMeasuredData.X_GyroRaw );

 	    MPU6050_Get_AccAngleYZ_Data_Raw( MpuMeasuredData.Y_AccRaw, MpuMeasuredData.Z_AccRaw, &MpuMeasuredData.AngleYZ_AccRaw, &MpuMeasuredData.AngleYZ_AccPrsc1000 );
 	    MPU6050_Get_GyroAngleX_Data_Raw( MpuMeasuredData.X_GyroRaw, Multiplier4<<Period, &MpuMeasuredData.AngleX_GyroRaw, &MpuMeasuredData.AngleX_GyroPrsc1000 );

		BT_SendMeasuredData( );

		LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;
	}
	//-------------------------1000ms(1Hz)	tasks-------------------------------------//
	if( 0 == Counter)
	{
		Counter = 1003;

	}

}

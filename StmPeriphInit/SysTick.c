
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "SysTick.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
extern void MainTask8ms();
extern void MainTask16ms();
extern void MainTask32ms();
extern void MainTask128ms();

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//

void InitializeSysTick()
{
   SysTick_Config(SYSTICK_FREQUENCY_KHZ>>0);
   SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
   NVIC_SetPriority(SysTick_IRQn, 0x0);
}

void SysTick_Handler(void)
{
   static uint16_t Counter = 384;

   //-------------------------8ms tasks-------------------------------------//
   --Counter;

   MainTask8ms();

   //-------------------------16ms tasks------------------------------------//

   if( 0 == ( Counter % 2 ) )
   {
      MainTask16ms();
   }

   //-------------------------40ms tasks-------------------------------------//

   if( 0 == ( Counter % 4 ) )
   {
      MainTask32ms();
   }

   //-------------------------128ms tasks-------------------------------------//
   if( 0 == ( Counter % 16 ) )
   {
      MainTask128ms();
   }

   //-------------------------1000ms(1Hz) tasks-------------------------------------//
   if( 0 == Counter )
   {
      Counter = 384;
   }

}

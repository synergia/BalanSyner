//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "SysTick.h"

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private typedefs------------------------------//

//-----------------------Private variables-----------------------------//
extern volatile uint8_t time3072msPassed;
extern volatile uint8_t time128msPassed;
extern volatile uint8_t time32msPassed;
extern volatile uint8_t time16msPassed;

//-----------------------Private prototypes----------------------------//
extern void MainTask8ms();
extern void MainTask16ms();
extern void MainTask32ms();
extern void MainTask128ms();


//-----------------------Private functions-----------------------------//
void SysTick_Handler( void )
{
   static uint16_t Counter = 384;

   /*!-------------------------1000ms(1Hz) tasks------------------------------*/
   if( 0 == Counter )
   {
      Counter = 384;
      time3072msPassed = 1;
   }

   /*!-------------------------128ms tasks------------------------------------*/
   if( 0 == ( Counter % 16 ) )
   {
      time128msPassed = 1;
      MainTask128ms();
   }

   /*!-------------------------32ms tasks-------------------------------------*/
   if( 0 == ( Counter % 4 ) )
   {
      time32msPassed = 1;
      MainTask32ms();
   }

   /*!-------------------------16ms tasks-------------------------------------*/
   if( 0 == ( Counter % 2 ) )
   {
      time16msPassed = 1;
      MainTask16ms();
   }

   /*!-------------------------8ms tasks--------------------------------------*/
   --Counter;
   MainTask8ms();

   time16msPassed = 0;
   time32msPassed = 0;
   time128msPassed = 0;
   time3072msPassed = 0;
}

//-----------------------Public functions------------------------------//

void InitializeSysTick()
{
   SysTick_Config( SYSTICK_FREQUENCY_KHZ >> 0 );
   SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK_Div8 );
   NVIC_SetPriority( SysTick_IRQn, 0x0 );
}


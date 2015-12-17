
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/stm32f30x/inc/stm32f30x_rcc.h"
#include "RCC.h"
#include "../Drivers/PinDefines.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static void priv_InitializeMPU();
static void priv_InitializeLedNucleo();
static void priv_InitializeLed14();
static void priv_InitializeLedEye();
static void priv_InitializeBt();
static void priv_InitializePi();
static void priv_InitializeWifi();
static void priv_InitializeMotors();
static void priv_InitializeServosArm();
static void priv_InitializeServosCam();
static void priv_InitializeEncoders();
static void priv_InitializeBattery();
static void priv_InitializeSharp();

//-----------------------Private functions-----------------------------//
static void priv_InitializeMPU()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE);
}

static void priv_InitializeLedNucleo()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
}

static void priv_InitializeLed14()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
}

static void priv_InitializeLedEye()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
}

static void priv_InitializeBt()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //todo make it define
}

static void priv_InitializeWifi()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //todo make it define
}

static void priv_InitializePi()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //todo make it define
}

static void priv_InitializeMotors()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
}

static void priv_InitializeServosArm()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}

static void priv_InitializeServosCam()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}

static void priv_InitializeEncoders()
{
   /*!< ENCODER 1 */
   RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE );
   RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );

   /*!< ENCODER 2 */
   RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE );
   RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );
}

static void priv_InitializeBattery()
{
   RCC_ADCCLKConfig( RCC_ADC34PLLCLK_Div10 );
   RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE );
   RCC_AHBPeriphClockCmd( RCC_AHBPeriph_ADC34, ENABLE );
}

static void priv_InitializeSharp()
{
   RCC_ADCCLKConfig( RCC_ADC34PLLCLK_Div10 );
   RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE );
   RCC_AHBPeriphClockCmd( RCC_AHBPeriph_ADC34, ENABLE );
}

//-----------------------Public functions------------------------------//
void InitializeRCC( uint8_t RCC_Selector )
{
   switch ( RCC_Selector )
   {
   case DriverSelectLedNucleo:
      priv_InitializeLedNucleo();
      break;
   case DriverSelectLed14:
      priv_InitializeLed14();
      break;
   case DriverSelectLedEye:
      priv_InitializeLedEye();
      break;
   case DriverSelectMpu:
      priv_InitializeMPU();
      break;
   case DriverSelectBt:
      priv_InitializeBt();
      break;
   case DriverSelectPi:
      priv_InitializePi();
      break;
   case DriverSelectWifi:
      priv_InitializeWifi();
      break;
   case DriverSelectMotors:
      priv_InitializeMotors();
      break;
   case DriverSelectServosArm:
      priv_InitializeServosArm();
      break;
   case DriverSelectServosCam:
      priv_InitializeServosCam();
      break;
   case DriverSelectEncoders:
      priv_InitializeEncoders();
      break;
   case DriverSelectBattery:
      priv_InitializeBattery();
      break;
   case DriverSelectSharp:
      priv_InitializeSharp();
      break;
   default:
      break;
   }
}

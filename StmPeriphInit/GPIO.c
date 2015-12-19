
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "GPIO.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static void priv_InitializeLed14();
static void priv_InitializeLedEye();
static void priv_InitializeLedNucleo();
static void priv_InitializeBt();
static void priv_InitializeWifi();
static void priv_InitializePi();
static void priv_InitializeMpu();
static void priv_InitializeMotors();
static void priv_InitializeServosArm();
static void priv_InitializeServosCam();
static void priv_InitializeBattery();
static void priv_InitializeSharp();

//-----------------------Private functions-----------------------------//
static void priv_InitializeLed14()
{
   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   // to save power

   GPIO_InitStruct.GPIO_Pin = LED1_PIN;
   GPIO_Init(LED1_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = LED2_PIN;
   GPIO_Init(LED2_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = LED3_PIN;
   GPIO_Init(LED3_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = LED4_PIN;
   GPIO_Init(LED4_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeLedEye()
{
   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   // to save power

   GPIO_InitStruct.GPIO_Pin = LEDEYE_PIN;
   GPIO_Init(LEDEYE_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeLedNucleo()
{
   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   // to save power

   GPIO_InitStruct.GPIO_Pin = LEDNUCLEO_PIN;
   GPIO_Init(LEDNUCLEO_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeBt()
{
   GPIO_PinAFConfig(USART_BT_RX_GPIO, USART_BT_RX_SOURCE, USART_AF_BT);
   GPIO_PinAFConfig(USART_BT_TX_GPIO, USART_BT_TX_SOURCE, USART_AF_BT);

   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStruct.GPIO_Pin = USART_BT_TX_PIN;
   GPIO_Init(USART_BT_TX_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = USART_BT_RX_PIN;
   GPIO_Init(USART_BT_RX_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeWifi()
{
   //todo write it
}

static void priv_InitializePi()
{
   //todo write it
}
static void priv_InitializeMpu()
{
   GPIO_PinAFConfig(MPU_SDA_GPIO, MPU_SDA_SOURCE, MPU_AF_I2C3);
   GPIO_PinAFConfig(MPU_SCL_GPIO, MPU_SCL_SOURCE, MPU_AF_I2C3);

   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
   GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

   GPIO_InitStruct.GPIO_Pin = MPU_SDA_PIN;
   GPIO_Init(MPU_SDA_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = MPU_SCL_PIN;
   GPIO_Init(MPU_SCL_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeMotors()
{
   /*! PWM output pins */
   GPIO_PinAFConfig(MOT1_PWM_GPIO, MOT1_PWM_SOURCE, TIM_AF_MOTOR);
   GPIO_PinAFConfig(MOT2_PWM_GPIO, MOT2_PWM_SOURCE, TIM_AF_MOTOR);

   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP ;

   GPIO_InitStruct.GPIO_Pin = MOT1_PWM_PIN;
   GPIO_Init(MOT1_PWM_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = MOT2_PWM_PIN;
   GPIO_Init(MOT2_PWM_GPIO, &GPIO_InitStruct);


   /*! DIR output pins */
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;

   GPIO_InitStruct.GPIO_Pin = MOT1_DIRA_PIN;
   GPIO_Init(MOT1_DIRA_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = MOT1_DIRB_PIN;
   GPIO_Init(MOT1_DIRB_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = MOT2_DIRA_PIN;
   GPIO_Init(MOT2_DIRA_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = MOT2_DIRB_PIN;
   GPIO_Init(MOT2_DIRB_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeServosArm()
{
   GPIO_PinAFConfig(SERVO_ARM_L_PWM_GPIO, SERVO_ARM_L_PWM_SOURCE, TIMER_AF_SERVOS);
   GPIO_PinAFConfig(SERVO_ARM_P_PWM_GPIO, SERVO_ARM_P_PWM_SOURCE, TIMER_AF_SERVOS);

   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP ;

   GPIO_InitStruct.GPIO_Pin = SERVO_ARM_L_PWM_PIN;
   GPIO_Init(SERVO_ARM_L_PWM_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = SERVO_ARM_P_PWM_PIN;
   GPIO_Init(SERVO_ARM_P_PWM_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeServosCam()
{
   GPIO_PinAFConfig(SERVO_HOR_PWM_GPIO, SERVO_HOR_PWM_SOURCE, TIMER_AF_SERVOS);
   GPIO_PinAFConfig(SERVO_VER_PWM_GPIO, SERVO_VER_PWM_SOURCE, TIMER_AF_SERVOS);

   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP ;

   GPIO_InitStruct.GPIO_Pin = SERVO_VER_PWM_PIN;
   GPIO_Init(SERVO_VER_PWM_GPIO, &GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = SERVO_HOR_PWM_PIN;
   GPIO_Init(SERVO_HOR_PWM_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeEncoders()
{
   GPIO_InitTypeDef GPIO_InitStruct;

   /*! ENCODER 1 */
   GPIO_PinAFConfig( ENC1_GPIO, ENC1A_SOURCE, TIM_AF_ENC1 );
   GPIO_PinAFConfig( ENC1_GPIO, ENC1B_SOURCE, TIM_AF_ENC1 );

   GPIO_InitStruct.GPIO_Pin =  ENC1A_PIN | ENC1B_PIN;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init( ENC1_GPIO, &GPIO_InitStruct );

   /*! ENCODER 2 */
   GPIO_PinAFConfig( ENC2_GPIO, ENC2A_SOURCE, TIM_AF_ENC2 );
   GPIO_PinAFConfig( ENC2_GPIO, ENC2B_SOURCE, TIM_AF_ENC2 );

   GPIO_InitStruct.GPIO_Pin =  ENC2A_PIN | ENC2B_PIN;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init( ENC2_GPIO, &GPIO_InitStruct );
}

static void priv_InitializeBattery()
{
   GPIO_InitTypeDef GPIO_InitStructure;

   GPIO_InitStructure.GPIO_Pin = ADC_BATTERY_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
   GPIO_Init(ADC_BATTERY_GPIO, &GPIO_InitStructure);
}

static void priv_InitializeSharp()
{
   GPIO_InitTypeDef GPIO_InitStructure;

   GPIO_InitStructure.GPIO_Pin = ADC_SHARP_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
   GPIO_Init(ADC_SHARP_GPIO, &GPIO_InitStructure);
}

//-----------------------Public functions------------------------------//
void InitializeGPIO(uint8_t GPIO_Selector)
{
   switch (GPIO_Selector)
   {
   case DriverSelectLed14:
      priv_InitializeLed14();
      break;
   case DriverSelectLedEye:
      priv_InitializeLedEye();
      break;
   case DriverSelectLedNucleo:
      priv_InitializeLedNucleo();
      break;
   case DriverSelectBt:
      priv_InitializeBt();
      break;
   case DriverSelectWifi:
      priv_InitializeWifi();
      break;
   case DriverSelectPi:
      priv_InitializePi();
      break;
   case DriverSelectMpu:
      priv_InitializeMpu();
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


//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "Timers.h"
#include "SysTick.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//
#define _SYSTICK_FREQ            SYSTICK_FREQUENCY_HZ

#define _PWM_SERVO_RESOLUTION    7200  //Hz ->servo angle range 180st, 1 => 0,5st
#define _PWM_SERVO_FREQUENCY     50    //Hz

#define  _PWM_MOTOR_RESOLUTION   1000
#define  _PWM_MOTOR_FREQUENCY    3600  //Hz

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static void priv_InitializeMotors();
static void priv_InitializeServos();
static void priv_InitializeEncoderLeft();
static void priv_InitializeEncoderRight();

//-----------------------Private functions-----------------------------//

static void priv_InitializeMotors()
{
   TIM_TimeBaseInitTypeDef timerInitStructure;

    timerInitStructure.TIM_Prescaler = ( _SYSTICK_FREQ / ( _PWM_MOTOR_FREQUENCY * _PWM_MOTOR_RESOLUTION ) )-1;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = _PWM_MOTOR_RESOLUTION-1;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM_MOTORS, &timerInitStructure);

    TIM_OCInitTypeDef outputChannelInit = {0,};
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse = _PWM_MOTOR_FREQUENCY;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM_MOTORS, &outputChannelInit);
    TIM_OC1PreloadConfig(TIM_MOTORS, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM_MOTORS, &outputChannelInit);
    TIM_OC2PreloadConfig(TIM_MOTORS, TIM_OCPreload_Enable);

    TIM_Cmd(TIM_MOTORS, ENABLE);
    TIM_CtrlPWMOutputs(TIM_MOTORS, ENABLE);
}

static void priv_InitializeServos()
{
   TIM_TimeBaseInitTypeDef timerInitStructure;

    timerInitStructure.TIM_Prescaler = (_SYSTICK_FREQ/(_PWM_SERVO_FREQUENCY*_PWM_SERVO_RESOLUTION) )-1;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = _PWM_SERVO_RESOLUTION-1;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM_SERVOS, &timerInitStructure);

    TIM_OCInitTypeDef outputChannelInit = {0,};
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse = 0;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM_SERVOS, &outputChannelInit);
    TIM_OC1PreloadConfig(TIM_SERVOS, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM_SERVOS, &outputChannelInit);
    TIM_OC2PreloadConfig(TIM_SERVOS, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM_SERVOS, &outputChannelInit);
    TIM_OC3PreloadConfig(TIM_SERVOS, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM_SERVOS, &outputChannelInit);
    TIM_OC4PreloadConfig(TIM_SERVOS, TIM_OCPreload_Enable);

    TIM_Cmd(TIM_SERVOS, ENABLE);
    TIM_CtrlPWMOutputs(TIM_SERVOS, ENABLE);
}

static void priv_InitializeEncoderLeft()
{
   TIM_TimeBaseInitTypeDef timerInitStructure;

   /* Compute the prescaler value */
   uint16_t PrescalerValue = 0;
   PrescalerValue = (uint16_t) 0;

   /* Time base configuration */
   timerInitStructure.TIM_Period = 3000;
   timerInitStructure.TIM_Prescaler = 0;
   timerInitStructure.TIM_ClockDivision = 0;
   timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

   TIM_TimeBaseInit(TIM_ENC1, &timerInitStructure);

   /* Prescaler configuration */
   TIM_PrescalerConfig(TIM_ENC1, PrescalerValue, TIM_PSCReloadMode_Immediate);

   TIM_EncoderInterfaceConfig(TIM_ENC1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

   /* TIM Interrupts enable */
   //TIM_ITConfig(TIM_ENC1, TIM_IT_Update, ENABLE);

   /* TIM3 enable counter */
   TIM_Cmd(TIM_ENC1, ENABLE);
}

static void priv_InitializeEncoderRight()
{
   TIM_TimeBaseInitTypeDef timerInitStructure;

   /* Compute the prescaler value */
   uint16_t PrescalerValue = 0;
   PrescalerValue = (uint16_t) 0;

   /* Time base configuration */
   timerInitStructure.TIM_Period = 3000;
   timerInitStructure.TIM_Prescaler = 0;
   timerInitStructure.TIM_ClockDivision = 0;
   timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

   TIM_TimeBaseInit(TIM_ENC2, &timerInitStructure);

   /* Prescaler configuration */
   TIM_PrescalerConfig(TIM_ENC2, PrescalerValue, TIM_PSCReloadMode_Immediate);

   TIM_EncoderInterfaceConfig(TIM_ENC2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

   /* TIM Interrupts enable */
   TIM_ITConfig(TIM_ENC2, TIM_IT_Update, ENABLE);

   /* TIM3 enable counter */
   TIM_Cmd(TIM_ENC2, ENABLE);
}

//-----------------------Public functions------------------------------//
void InitializeTimers(TIM_TypeDef* TIMx)
{
   if ( TIM_MOTORS == TIMx )
   {
      priv_InitializeMotors();
   }
   else if ( TIM_SERVOS == TIMx )
   {
      priv_InitializeServos();
   }
   else if ( TIM_ENC1 == TIMx )
   {
      priv_InitializeEncoderLeft();
   }
   else if ( TIM_ENC2 == TIMx )
   {
      priv_InitializeEncoderRight();
   }
}

uint32_t GetCounter( TIM_TypeDef *TIMx )
{
   return TIMx->CNT;
}

void SetCounter( TIM_TypeDef *TIMx, uint32_t NewValue )
{
   TIMx->CNT = NewValue;
}

#include "../Drivers/LEDs/LED.h"
//TODO:delete it
void TIM4_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
  {
     //LED_NUCLEO_IsOn ? LED_Nucleo_SetOn : LED_Nucleo_SetOff;
     TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
  }
}

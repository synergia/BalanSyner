
//-----------------------Includes-------------------------------------//
#include "main.h"
#include "Timers.h"
//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//
#define _PWM_SERVO_FREQ 	50		//Hz
#define _PWM_MOTOR_FREQ 	3600 	//Hz
#define _CPU_FREQ 			SYSTICK_FREQUENCY_MHZ
#define _FREQ_AFTER_PRC		3.6		//MHz
#define _TIM_PERIOD			1000
//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeTimers()
{
	/*!
	 * TIM1, TIM2, TIM3, TIM4
	 */
    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = (_CPU_FREQ/_FREQ_AFTER_PRC)-1;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = _TIM_PERIOD-1;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM1, &timerInitStructure);

    TIM_Cmd(TIM1, ENABLE);

    TIM_OCInitTypeDef outputChannelInit = {0,};
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse = 100;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

    /*!
     * Channel output customization,TIM1-4
     */
    //TODO : initialize all timers and channels
    TIM_OC2Init(MOT1_TIMER, &outputChannelInit);
    TIM_OC2PreloadConfig(MOT1_TIMER, TIM_OCPreload_Enable);

	GPIO_PinAFConfig(MOT1_PWM_GPIO, MOT1_PWM_SOURCE, MOT1_AF);

    //gpio
	GPIO_InitTypeDef pwmgpio;
	pwmgpio.GPIO_Mode = GPIO_Mode_AF;
	pwmgpio.GPIO_Speed = GPIO_Speed_50MHz;
	pwmgpio.GPIO_Pin = MOT1_PWM_PIN;
	GPIO_Init(MOT1_PWM_GPIO, &pwmgpio);

}



//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "Timers.h"
#include "SysTick.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//
#define _SYSTICK_FREQ 			SYSTICK_FREQUENCY_HZ

#define _PWM_SERVO_RESOLUTION	7200	//Hz ->servo angle range 180st, 1 => 0,5st
#define _PWM_SERVO_FREQUENCY	50		//Hz

#define	_PWM_MOTOR_RESOLUTION	1000
#define _PWM_MOTOR_FREQUENCY	3600	//Hz

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeTimers(TIM_TypeDef* TIMx)
{
	TIM_TimeBaseInitTypeDef timerInitStructure;

	if(TIMx == TIM_MOTORS)
	{
	    timerInitStructure.TIM_Prescaler = (_SYSTICK_FREQ/(_PWM_MOTOR_FREQUENCY*_PWM_MOTOR_RESOLUTION) )-1;
	    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	    timerInitStructure.TIM_Period = _PWM_MOTOR_RESOLUTION-1;
	    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	    timerInitStructure.TIM_RepetitionCounter = 0;

	    TIM_TimeBaseInit(TIM_MOTORS, &timerInitStructure);

	    TIM_OCInitTypeDef outputChannelInit = {0,};
	    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	    outputChannelInit.TIM_Pulse = 3600;
	    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

	    TIM_OC1Init(TIM_MOTORS, &outputChannelInit);
	    TIM_OC1PreloadConfig(TIM_MOTORS, TIM_OCPreload_Enable);

	    TIM_OC2Init(TIM_MOTORS, &outputChannelInit);
	    TIM_OC2PreloadConfig(TIM_MOTORS, TIM_OCPreload_Enable);

	    TIM_Cmd(TIM_MOTORS, ENABLE);
	    TIM_CtrlPWMOutputs(TIM_MOTORS, ENABLE);
	}
	else if(TIMx == TIM_SERVOS)
	{
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

	    //todo: configure it. and gpio
	    TIM_OC1Init(TIM_SERVOS, &outputChannelInit);
	    TIM_OC1PreloadConfig(TIM_SERVOS, TIM_OCPreload_Enable);

	    TIM_OC2Init(TIM_SERVOS, &outputChannelInit);
	    TIM_OC2PreloadConfig(TIM_SERVOS, TIM_OCPreload_Enable);

	    TIM_Cmd(TIM_SERVOS, ENABLE);

	    TIM_CtrlPWMOutputs(TIM_SERVOS, ENABLE);
	}
}


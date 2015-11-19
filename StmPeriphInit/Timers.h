#ifndef TIMERS_H_
#define TIMERS_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void InitializeTimers(TIM_TypeDef* TIMx);

uint32_t GetCounter( TIM_TypeDef * TIMx );
void SetCounter( TIM_TypeDef * TIMx, uint32_t Value);

#endif

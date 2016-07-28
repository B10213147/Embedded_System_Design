#ifndef TIMER_H_
#define TIMER_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "stm32f0xx.h"

extern void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter);
extern uint32_t TIM_GetCounter(TIM_TypeDef* TIMx);
extern void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_H_ */

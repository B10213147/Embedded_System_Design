#ifndef TIMER_H_
#define TIMER_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "stm32f0xx.h"
	 
#define TIM_IT_Update                      ((uint16_t)0x0001)
#define TIM_IT_CC1                         ((uint16_t)0x0002)
#define TIM_IT_CC2                         ((uint16_t)0x0004)
#define TIM_IT_CC3                         ((uint16_t)0x0008)
#define TIM_IT_CC4                         ((uint16_t)0x0010)
#define TIM_IT_COM                         ((uint16_t)0x0020)
#define TIM_IT_Trigger                     ((uint16_t)0x0040)
#define TIM_IT_Break                       ((uint16_t)0x0080)

extern void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter);
extern uint32_t TIM_GetCounter(TIM_TypeDef* TIMx);
extern void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
extern void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1);
extern void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2);
extern void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3);
extern void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4);
extern void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
extern ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);
extern void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_H_ */

#include "timer.h"

void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter){
	TIMx->CNT = Counter;
}

uint32_t TIM_GetCounter(TIM_TypeDef* TIMx){
	return TIMx->CNT;
}

void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState){
	if(NewState == ENABLE){
		TIMx->CR1 |= 0x1;
	}
	else{
		TIMx->CR1 &= ~0x1;
	}	
}

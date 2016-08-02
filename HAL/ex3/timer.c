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

void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1){
	TIMx->CCR1 = Compare1;
}

void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2){
	TIMx->CCR2 = Compare2;
}

void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3){
	TIMx->CCR3 = Compare3;
}

void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4){
	TIMx->CCR4 = Compare4;
}

void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState){
	if(NewState != DISABLE){
		TIMx->DIER |= TIM_IT;
	}
	else{
		TIMx->DIER &= ~TIM_IT;
	}
}

ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT){
	uint32_t bitstatus = TIMx->SR & TIM_IT;
	if(bitstatus != 0) return SET;
	else return RESET;
}

void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT){
	TIMx->SR = ~TIM_IT;
}

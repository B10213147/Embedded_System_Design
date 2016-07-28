#include "rcc.h"

void RCC_AHBPeriphClockCmd(uint32_t RCC_Periph, FunctionalState NewState){
	if(NewState == DISABLE){
		RCC->AHBENR &= ~RCC_Periph;
	}
	else{
		RCC->AHBENR |= RCC_Periph;
	}	
}

void RCC_APB1PeriphClockCmd(uint32_t RCC_Periph, FunctionalState NewState){
	if(NewState == DISABLE){
		RCC->APB1ENR &= ~RCC_Periph;
	}
	else{
		RCC->APB1ENR |= RCC_Periph;
	}	
}

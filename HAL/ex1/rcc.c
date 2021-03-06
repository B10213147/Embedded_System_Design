#include "rcc.h"

void RCC_AHBPeriphClockCmd(uint32_t RCC_Periph, uint8_t NewState){
	if(NewState == DISABLE){
		RCC->AHBENR &= ~RCC_Periph;
	}
	else{
		RCC->AHBENR |= RCC_Periph;
	}	
}

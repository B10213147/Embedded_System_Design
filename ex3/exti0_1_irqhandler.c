#include "stm32f0xx.h"
extern int led_f;

void EXTI0_1_IRQHandler(void){
	if((EXTI->PR & EXTI_PR_PR0) != 0){
		led_f++;
		if(led_f > 10) led_f = 1;
	}
	// Clear IT Pending Bit
	EXTI->PR = EXTI_PR_PR0;
}

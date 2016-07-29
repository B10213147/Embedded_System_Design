#include "stm32f0xx.h"
#include "timer.h"
#include "gpio.h"

int led_f = 1;	//LED frequency
float duty = 0.5;
uint8_t pin_state = 0;

void TIM2_IRQHandler(void){
	TIM_SetCounter(TIM2, 0);
	
	int period = 12000000 / led_f;
	int nH = duty * period;
	int nL = (1 - duty) * period;
	
	if(pin_state != 0){
		pin_state = 0;
		TIM2->CCR1 = nL;
	}
	else{
		pin_state = 1;
		TIM2->CCR1 = nH;
	}
	GPIO_WriteBit(GPIOC, 8, pin_state);
	TIM2->SR &= ~TIM_DIER_CC1IE;
}

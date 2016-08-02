#include "stm32f0xx.h"                  // Device header

int period = 8000000;	// ticks/s
int led_f = 5;	// frequency
float duty = 0.5;
int main(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN;	// GPIOA, GPIOA clock enable
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	// Timer 2 clock enable

	GPIOA->MODER &= ~(0x0 << 0);	// Set GPIOA Pin0 as input
	GPIOC->MODER |= (0x1 << 2*8) | (0x1 << 2*9);	// Set GPIOC Pin8, Pin9 as output

	while(1){
		if(GPIOA->IDR & 0x0001){    // if GPIOA Pin0 pressed
			TIM2->CR1 |= TIM_CR1_CEN;	// Counter enable
			int nH = duty * period / led_f;
			int nL = (1 - duty) * period / led_f;
			unsigned int next = TIM2->CNT + nL;
			uint8_t pin_state = 0;

			while(GPIOA->IDR & 0x0001){ // while GPIOA Pin0 pressed
				if(TIM2->CNT > next){
					if(pin_state == 0){
						next += nH;
						pin_state = 1;
						GPIOC->BSRR = 0x1 << 8;	// Set LED
					}
					else{	//pin_state == 1
						next += nL;
						pin_state = 0;
						GPIOC->BSRR = 0x1 << (8+16);	// Reset LED
					}
				}
			}
			// Button released
			TIM2->CR1 &= ~TIM_CR1_CEN;	// Counter disable
			TIM2->CNT = 0;	// Reset counter
			GPIOC->BSRR = 0x1 << (8+16);	// Reset LED
		}
	}
}

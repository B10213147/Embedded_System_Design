#include "stm32f0xx.h"                  // Device header

int main(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN;	// GPIOA, GPIOA clock enable

	GPIOA->MODER &= ~(0x0 << 0);	// Set GPIOA Pin0 as input
	GPIOC->MODER |= (0x1 << 2*8) | (0x1 << 2*9);	// Set GPIOC Pin8, Pin9 as output
	
	while(1){
		if(GPIOA->IDR & 0x0001){	// Button pressed
			GPIOC->BSRR = 0x1 << 8;	// Set LED
		}
		else{	// Button released
			GPIOC->BSRR = 0x1 << (8+16);	// Reset LED
		}
	}
}

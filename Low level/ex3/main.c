#include "stm32f0xx.h"                  // Device header

void EXTI0_1_IRQHandler(void);
void TIM2_IRQHandler(void);

int led_f = 1;	//LED frequency
int main(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN;	// GPIOA, GPIOA clock enable
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	// Timer 2 clock enable
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;	// SYSCFG clock enable

	GPIOA->MODER &= ~(0x0 << 0);	// Set GPIOA Pin0 as input
	GPIOC->MODER |= (0x1 << 2*8) | (0x1 << 2*9);	// Set GPIOC Pin8, Pin9 as output

	// Set PA0 as EXTI0 input source
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0 & SYSCFG_EXTICR1_EXTI0_PA;

	EXTI->IMR |= EXTI_IMR_IM0;	// mask bit
	EXTI->RTSR |= EXTI_RTSR_RT0;	// active when rising edge occur

	TIM2->DIER |= TIM_DIER_CC1IE;	// Capture/Compare 1 interrupt enable
	TIM2->CCR1 = 100;	// Give a match value to compare
	TIM2->CR1 |= TIM_CR1_CEN;	// Counter enable

	NVIC_EnableIRQ(EXTI0_1_IRQn);	// Enable NVIC EXTI0_1_IRQn channel
	NVIC_EnableIRQ(TIM2_IRQn);	// Enable NVIC TIM2_IRQn channel

	while(1);
}

void EXTI0_1_IRQHandler(void){
	if((EXTI->PR & EXTI_PR_PR0) != 0){
		led_f = 1 + (led_f % 10);
        // Clear IT Pending Bit
        EXTI->PR = EXTI_PR_PR0;
	}
}

uint8_t pin_state = 0;
float duty = 0.5;
int period = 8000000;
void TIM2_IRQHandler(void){
	if(TIM2->SR & TIM_SR_CC1IF){
		TIM2->CNT = 0;	// Reset counter

		int nH = duty * period / led_f;
		int nL = (1 - duty) * period / led_f;

		if(pin_state != 0){
			pin_state = 0;
			TIM2->CCR1 = nL;	// Set new match value
			GPIOC->BSRR = 0x1 << (8+16);	// Reset LED
		}
		else{
			pin_state = 1;
			TIM2->CCR1 = nH;	// Set new match value
			GPIOC->BSRR = 0x1 << 8;	// Set LED
		}
		// Clear IT Status Bit
		TIM2->SR = ~TIM_SR_CC1IF;
	}
}

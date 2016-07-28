#include "stm32f0xx.h"                  // Device header
#include "rcc.h"
#include "gpio.h"
#include "timer.h"

int main(void){
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);
	
	GPIO_Set_Direction(GPIOA, 0x0001, 0x0000);
	GPIO_Set_Direction(GPIOC, 0x0000, 0x0300);
	
	EXTI->IMR |= EXTI_IMR_IM0;	// mask bit
	EXTI->RTSR |= EXTI_RTSR_RT0;	// active when rising edge occur
	
	TIM2->DIER |= TIM_DIER_CC1IE;	// Capture/Compare 1 interrupt enable
	TIM2->CCR1 = 100;
	TIM_Cmd(TIM2, ENABLE);	
	
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	NVIC_EnableIRQ(TIM2_IRQn);
	
	while(1);
	
}

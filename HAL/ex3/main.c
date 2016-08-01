#include "stm32f0xx.h"                  // Device header
#include "rcc.h"
#include "gpio.h"
#include "timer.h"
#include "exti.h"

void EXTI0_1_IRQHandler(void);
void TIM2_IRQHandler(void);

int led_f = 1;	//LED frequency
int main(void){
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);
	
	GPIO_Set_Direction(GPIOA, 0x0001, 0x0000);
	GPIO_Set_Direction(GPIOC, 0x0000, 0x0300);	
	
	// Set PA0 as EXTI0 input source
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0 & SYSCFG_EXTICR1_EXTI0_PA;

	EXTI_Init(0, EXTI_Trigger_Rising, ENABLE);
	
	TIM2->DIER |= TIM_DIER_CC1IE;	// Capture/Compare 1 interrupt enable
	TIM2->CCR1 = 100;
	TIM_Cmd(TIM2, ENABLE);	
	
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	NVIC_EnableIRQ(TIM2_IRQn);
	
	while(1);
	
}

void EXTI0_1_IRQHandler(void){
	if(EXTI_GetITStatus(0) != RESET){
		led_f = 1 + (led_f % 10);
		// Clear IT Pending Bit
		EXTI_ClearITPendingBit(0);
	}
}

int period = 8000000;
float duty = 0.5;
uint8_t pin_state = 0;
void TIM2_IRQHandler(void){
	TIM_SetCounter(TIM2, 0);
	
	int nH = duty * period / led_f;
	int nL = (1 - duty) * period / led_f;
	
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

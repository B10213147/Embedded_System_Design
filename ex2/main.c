#include "stm32f0xx.h"                  // Device header
#include "rcc.h"
#include "gpio.h"

int period = 12000000;	// ticks/s
int f = 10;	// frequency 
float duty = 0.5;
int main(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN;	// GPIOA, GPIOC clock enable
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	// Timer 2 clock enable
	GPIO_Set_Direction(GPIOA, 0x0001, 0x0000);
	GPIO_Set_Direction(GPIOC, 0x0000, 0x0300);
	
	while(1){
		if(GPIO_ReadInputDataBit(GPIOA, 0)){
			TIM2->CR1 |= TIM_CR1_CEN;	// Counter enable
			int nH = duty * period / f;
			int nL = (1 - duty) * period / f;
			uint8_t pin_state = 0;	
			unsigned int next = TIM2->CNT + nL;
			
			while(GPIO_ReadInputDataBit(GPIOA, 0)){
				if(TIM2->CNT > next){
					if(pin_state == 0){
						next += nH;
						pin_state = 1;
					}
					else{	//pin_state == 1
						next += nL;
						pin_state = 0;
					}
					GPIO_WriteBit(GPIOC, 8, pin_state);
				}
			}
			// Button released
			TIM2->CR1 &= ~TIM_CR1_CEN; // Counter disable
			TIM2->CNT = 0;
			GPIO_WriteBit(GPIOC, 8, 0);	//Turn off LED
		}
	}
}

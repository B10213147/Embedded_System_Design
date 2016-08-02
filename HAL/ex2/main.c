#include "stm32f0xx.h"                  // Device header
#include "rcc.h"
#include "gpio.h"
#include "timer.h"

int period = 8000000;	// ticks/s
int led_f = 5;	// frequency 
float duty = 0.5;
int main(void){
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);
	GPIO_Set_Direction(GPIOA, 0x0001, 0x0000);
	GPIO_Set_Direction(GPIOC, 0x0000, 0x0300);
	
	while(1){
		if(GPIO_ReadInputDataBit(GPIOA, 0)){
			TIM_Cmd(TIM2, ENABLE);
			int nH = duty * period / led_f;
			int nL = (1 - duty) * period / led_f;	
			unsigned int next = TIM_GetCounter(TIM2) + nL;
			uint8_t pin_state = 0;
			
			while(GPIO_ReadInputDataBit(GPIOA, 0)){
				if(TIM_GetCounter(TIM2) > next){
					if(pin_state == 0){
						next += nH;
						pin_state = 1;
					}
					else{	// pin_state == 1
						next += nL;
						pin_state = 0;
					}
					GPIO_WriteBit(GPIOC, 8, pin_state);
				}
			}
			// Button released
			TIM_Cmd(TIM2, DISABLE);
			TIM_SetCounter(TIM2, 0);	// Reset counter
			GPIO_WriteBit(GPIOC, 8, 0);	// Turn off LED
		}
	}
}

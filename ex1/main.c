#include "stm32f0xx.h"                  // Device header
#include "rcc.h"
#include "gpio.h"

int main(void){
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN, ENABLE);
	
	GPIO_Set_Direction(GPIOA, 0x0001, 0x0000);
	GPIO_Set_Direction(GPIOC, 0x0000, 0x0100 | 0x0200);
	
	while(1){
		GPIO_WriteBit(GPIOC, 8, GPIO_ReadInputDataBit(GPIOA, 0));
	}
	
	return 0;
}




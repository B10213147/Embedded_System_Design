#include "stm32f0xx.h"                  // Device header
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_rcc.h"

int main(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_Init;
	GPIO_Init.Pin = GPIO_PIN_8 | GPIO_PIN_9; 
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_Init);
	
	GPIO_Init.Pin = GPIO_PIN_0;
	GPIO_Init.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA, &GPIO_Init);
	
	while(1){
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != 0){
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != 0){			
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
			for(int i=0; i<80000; i++);
		}
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		}
	}
}

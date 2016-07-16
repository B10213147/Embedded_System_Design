#include "stm32f0xx.h"                  // Device header

void GPIO_Set_Direction(GPIO_TypeDef* GPIOx, uint16_t inputMask, uint16_t outputMask);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, int Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, int Pin, uint8_t BitVal);

int main(void){
	RCC->AHBENR |= 0x00020000 | 0x00080000;	// Enable GPIOA, GPIOC
	
	GPIO_Set_Direction(GPIOA, 0x0001, 0x0000);
	GPIO_Set_Direction(GPIOC, 0x0000, 0x0300);
	while(1){
		GPIO_WriteBit(GPIOC, 8, GPIO_ReadInputDataBit(GPIOA, 0));
	}
	//return 0;
}

void GPIO_Set_Direction(GPIO_TypeDef* GPIOx, uint16_t inputMask, uint16_t outputMask){
	int i;
	for(i=0; i<16; i++){
		if((inputMask & (0x1 << i)) != 0){
			GPIOx->MODER |= (0x0 << 2*i);
		}
		if((outputMask & (0x1 << i)) != 0){
			GPIOx->MODER |= (0x1 << 2*i);
		}
	}
}

uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, int Pin){
	if((GPIOx->IDR & (0x1 << Pin)) != 0){		
		return 1;
	}
	else return 0;
}

void GPIO_WriteBit(GPIO_TypeDef* GPIOx, int Pin, uint8_t BitVal){
	if(BitVal == 0){
		GPIOx->BSRR = (0x1 << (16 + Pin));	//Reset
	}
	else{
		GPIOx->BSRR = (0x1 << Pin);	//Set
	}
}


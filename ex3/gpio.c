#include "gpio.h"

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

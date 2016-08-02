#include "exti.h"

void EXTI_Init(int EXTI_Line, EXTITrigger_TypeDef EXTI_Trigger, FunctionalState EXTI_LineCmd){
	if(EXTI_LineCmd != DISABLE){
		EXTI->IMR |= 0x1 << EXTI_Line;
		switch(EXTI_Trigger){
			case EXTI_Trigger_Rising_Falling:
				EXTI->RTSR |= 0x1 << EXTI_Line;
				EXTI->FTSR |= 0x1 << EXTI_Line;
				break;
			case EXTI_Trigger_Falling:
				EXTI->FTSR |= 0x1 << EXTI_Line;
				break;
			default:
				EXTI->RTSR |= 0x1 << EXTI_Line;
		}
	}
	else{
		EXTI->IMR &= ~(0x1 << EXTI_Line);
	}
}

ITStatus EXTI_GetITStatus(int EXTI_Line){
	uint32_t bitstatus =  EXTI->PR & (0x1 << EXTI_Line);
	if(bitstatus != 0) return SET; 
	else return RESET;
}

void EXTI_ClearITPendingBit(int EXTI_Line){
	EXTI->PR = (0x1 << EXTI_Line);
}

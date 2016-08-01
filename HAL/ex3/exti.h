#ifndef EXTI_H_
#define EXTI_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "stm32f0xx.h"

typedef enum
{
	EXTI_Trigger_Rising,
	EXTI_Trigger_Falling,
	EXTI_Trigger_Rising_Falling
}EXTITrigger_TypeDef;
	 
extern void EXTI_Init(int EXTI_Line, EXTITrigger_TypeDef EXTI_Trigger, FunctionalState EXTI_LineCmd);
extern ITStatus EXTI_GetITStatus(int EXTI_Line);
extern void EXTI_ClearITPendingBit(int EXTI_Line);
	 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EXTI_H_ */

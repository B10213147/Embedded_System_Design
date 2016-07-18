#ifndef RCC_H_
#define RCC_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "stm32f0xx.h"
	 
extern void RCC_AHBPeriphClockCmd(uint32_t RCC_Periph, FunctionalState NewState);
extern void RCC_APB1PeriphClockCmd(uint32_t RCC_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_H_ */

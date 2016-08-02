#ifndef RCC_H_
#define RCC_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "stm32f0xx.h"

#define DISABLE 0x00
#define ENABLE	0x01
	 
extern void RCC_AHBPeriphClockCmd(uint32_t RCC_Periph, uint8_t NewState);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_H_ */

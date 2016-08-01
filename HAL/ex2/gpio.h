#ifndef GPIO_H_
#define GPIO_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "stm32f0xx.h"

extern void GPIO_Set_Direction(GPIO_TypeDef* GPIOx, uint16_t inputMask, uint16_t outputMask);
extern uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, int Pin);
extern void GPIO_WriteBit(GPIO_TypeDef* GPIOx, int Pin, uint8_t BitVal);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_H_ */

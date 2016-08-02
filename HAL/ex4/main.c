#include "stm32f0xx.h"                  // Device header

void GPIOC_Config(void);
void EXTI0_1_IRQHandler_Config(void);
void TIM2_IRQHandler_Config(void);

int led_f = 1;	// LED frequency
int main(void){
	/* Condigure GPIOC*/
	GPIOC_Config();
	
	/* Configure EXTI_Line0 (connected to PA.00 pin) in interrupt mode */
	EXTI0_1_IRQHandler_Config();
	
	while(1);
}

void GPIOC_Config(void){
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_Init;
	GPIO_Init.Pin = GPIO_PIN_8 | GPIO_PIN_9; 
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_Init);
}

void EXTI0_1_IRQHandler_Config(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_Init;
	GPIO_Init.Pin = GPIO_PIN_0;
	GPIO_Init.Mode = GPIO_MODE_IT_RISING;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_Init);
	
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void TIM2_IRQHandler_Config(void){
	__HAL_RCC_TIM2_CLK_ENABLE();
	
	TIM_Base_InitTypeDef Structure;
	Structure.ClockDivision = 0;
	Structure.CounterMode = TIM_COUNTERMODE_UP;
	Structure.Period = 0xffffffff;
	Structure.Prescaler = TIM_CLOCKDIVISION_DIV1;	
	TIM_Base_SetConfig(TIM2, &Structure);
	
	TIM_HandleTypeDef htim;
	htim.Instance = TIM2;

	
	HAL_TIM_OC_Start_IT(&htim, TIM_CHANNEL_1);
	
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_0){
		led_f = 1 + (led_f % 10);
	}
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){
	
}

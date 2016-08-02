#include "stm32f0xx.h"                  // Device header

void GPIOC_Config(void);
void EXTI0_1_IRQHandler_Config(void);
void TIM2_IRQHandler_Config(void);

TIM_HandleTypeDef TimHandle;

int main(void){
	/* Condigure GPIOC*/
	GPIOC_Config();
	
	/* Configure EXTI_Line0 (connected to PA.00 pin) in interrupt mode */
	EXTI0_1_IRQHandler_Config();
	
	/* Configure Timer2 in interrupt mode */
	TIM2_IRQHandler_Config();
	
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
	
	TimHandle.Instance = TIM2;
	
	TimHandle.Init.Period            = 0xffffffff;
	TimHandle.Init.Prescaler         = 0;
	TimHandle.Init.ClockDivision     = 0;
	TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&TimHandle);

	__HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_1, 100);	
	HAL_TIM_OC_Start_IT(&TimHandle, TIM_CHANNEL_1);
	
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

int led_f = 1;	// LED frequency
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin & GPIO_PIN_0){
		led_f = 1 + (led_f % 10);
	}
}

int period = 8000000;
float duty = 0.5;
GPIO_PinState pin_state = GPIO_PIN_RESET;
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
		__HAL_TIM_SET_COUNTER(&TimHandle, 0);
		
		int nH = duty * period / led_f;
		int nL = (1 - duty) *period / led_f;
		
		if(pin_state == GPIO_PIN_RESET){
			pin_state = GPIO_PIN_SET;
			__HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_1, nH);	
		}
		else{	// pin_state == 1
			pin_state = GPIO_PIN_RESET;
			__HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_1, nL);
		}
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, pin_state);
	}
}

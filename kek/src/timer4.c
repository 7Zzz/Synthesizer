#include "timer4.h"

TIM_TimeBaseInitTypeDef timer4;

void Timer4_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseStructInit(&timer4);
	timer4.TIM_Prescaler = TIMER4_PRESCALER - 1;
	timer4.TIM_Period = TIMER4_PERIOD - 1;
	TIM_TimeBaseInit(TIM4, &timer4);

	NVIC_EnableIRQ(TIM4_IRQn);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}



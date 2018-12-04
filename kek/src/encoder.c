#include "encoder.h"

void Enc_Init(void) {
	GPIO_InitTypeDef Enc_GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(enc_RCC_Port, ENABLE);
	Enc_GPIO_InitStruct.GPIO_Pin = encPinA | encPinB;
	Enc_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	Enc_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	Enc_GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(encPort, &Enc_GPIO_InitStruct);
	prev_millis = 0;
	encoder_A_prev = 0;
}

void Enc_Read() {
	uint8_t encoder_A = GPIO_ReadInputDataBit(encPort, encPinA); // считываем состо€ние выхода ј энкодера
	uint8_t encoder_B = GPIO_ReadInputDataBit(encPort, encPinB); // считываем состо€ние выхода B энкодера
	if ((encoder_A == 0) && (encoder_A_prev == 1)
			&& (millis - prev_millis > 40)) { // если состо€ние изменилось с положительного к нулю
		prev_millis = millis;
		if (encoder_B == 1) {
			LEDs_redSet();
			LEDs_blueReset();
		} else {
			LEDs_redReset();
			LEDs_blueSet();
		}
	}else if(prev_millis>millis) {
		prev_millis=0;
	}
	encoder_A_prev = encoder_A;
}

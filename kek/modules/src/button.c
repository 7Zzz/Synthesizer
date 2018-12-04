/*
 * button.c
 *
 *  Created on: 13 июл. 2018 г.
 *      Author: Дом
 */
#include "button.h"

GPIO_InitTypeDef buttonInitStruct;

uint8_t ButtonRead(void) {
	u8 btn = GPIO_ReadInputDataBit(USER_BUTTON_PORT, USER_BUTTON_PIN);
	if (btn != btn_prev && millis - prevTime > BTN_INTERVAL) {
		prevTime = millis;
		if (millis < prevTime)
			prevTime = 0;
		btn_prev = btn;
		return btn;
	} else
		return btn_prev;

}

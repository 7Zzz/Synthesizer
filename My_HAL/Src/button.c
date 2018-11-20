///*
// * button.c
// *
// *  Created on: Jul 6, 2018
// *      Author: Roman
// */
//#include "button.h"
//
//void Button_Init(BTN_TypeDef* b, GPIO_TypeDef* port, u16 pin) {
//	b->port = port;
//	b->pin = pin;
//	b->state = UNPRESSED;
//	b->prevTime = 0;
//	//b->readFlag = NOREAD;
//}
//
//uint8_t BTN_ReadChange(BTN_TypeDef* b) {
//	uint8_t read = (!HAL_GPIO_ReadPin(b->port, b->pin));
//	if (millis - b->prevTime > INTERVAL) {
//		if (read && b->state == UNPRESSED) {
//			b->state = PRESSED;
//			return b->state;
//		}
//		else if (!read && b->state == PRESSED) {
//			b->state = UNPRESSED;
//			return b->state;
//		}
//		b->prevTime = millis;
//		return 50;
//	}
//	return 50;
//}
//
//// TODO:
////u8 BTN_ReadPush(BTN_TypeDef b) {
////
////	return 0;
////}


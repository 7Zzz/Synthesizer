/*
 * button.h
 *
 *  Created on: 13 июл. 2018 г.
 *      Author: Дом
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "global.h"

#define USER_BUTTON_PIN        GPIO_Pin_0
#define USER_BUTTON_PORT       GPIOA
#define USER_BUTTON_PORT_RCC   RCC_AHB1Periph_GPIOA
#define BTN_INTERVAL           50

volatile unsigned long prevTime;
volatile u8 btn_prev;
extern volatile long millis;

void Button_Init(void);
uint8_t ButtonRead(void);

#endif /* INC_BUTTON_H_ */

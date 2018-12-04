#ifndef ENCODER_H_
#define ENCODER_H_

#include "stm32f4xx.h"
#include "leds.h"
#include "global.h"

#define encPort GPIOE
#define enc_RCC_Port RCC_AHB1Periph_GPIOE
#define encPinA GPIO_Pin_9
#define encPinB GPIO_Pin_10

long prev_millis;
uint8_t encoder_A_prev;

void Enc_Init(void);
void Enc_Read(void);

#endif /* ENCODER_H_ */

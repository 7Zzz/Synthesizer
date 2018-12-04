
#include "stm32f4xx.h"

#ifndef LEDS_H
#define LEDS_H

#define GREEN_LED    GPIO_Pin_12
#define ORANGE_LED   GPIO_Pin_13
#define RED_LED      GPIO_Pin_14
#define BLUE_LED     GPIO_Pin_15

#define _LED_BLUE_ON   GPIOD->BSRRL = GPIO_Pin_15;
#define _LED_BLUE_OFF  GPIOD->BSRRH = GPIO_Pin_15;

void LEDs_Init(void);
void LEDs_Toggle(void);
void LEDs_Set(void);
void LEDs_Reset(void);
void LEDs_redToggle(void);
void LEDs_redSet(void);
void LEDs_redReset(void);
void LEDs_greenToggle(void);
void LEDs_greenSet(void);
void LEDs_greenReset(void);

void LEDs_orangeToggle(void);
void LEDs_orangeSet(void);
void LEDs_orangeReset(void);
void LEDs_blueToggle(void);
void LEDs_blueSet(void);
void LEDs_blueReset(void);
#endif /* LEDS_H */

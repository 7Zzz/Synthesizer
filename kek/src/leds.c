
/* Some functions for giving some feedback through the LEDs */
#include "leds.h"

GPIO_InitTypeDef LEDs_GPIO_InitStruct;


void LEDs_Init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    LEDs_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    LEDs_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    LEDs_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    LEDs_GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    LEDs_GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(GPIOD, &LEDs_GPIO_InitStruct);
}

void LEDs_Toggle(void)
{
    GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void LEDs_Set(void)
{
    GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void LEDs_Reset(void)
{
    GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void LEDs_redToggle(void)
{
    GPIO_ToggleBits(GPIOD, RED_LED);
}

void LEDs_redSet(void)
{
    GPIO_SetBits(GPIOD, RED_LED);
}

void LEDs_redReset(void)
{
    GPIO_ResetBits(GPIOD, RED_LED);
}

void LEDs_greenToggle(void)
{
    GPIO_ToggleBits(GPIOD, GREEN_LED);
}

void LEDs_greenSet(void)
{
    GPIO_SetBits(GPIOD, GREEN_LED);
}

void LEDs_greenReset(void)
{
    GPIO_ResetBits(GPIOD, GREEN_LED);
}

void LEDs_orangeToggle(void)
{
    GPIO_ToggleBits(GPIOD, ORANGE_LED);
}

void LEDs_orangeSet(void)
{
    GPIO_SetBits(GPIOD, ORANGE_LED);
}

void LEDs_orangeReset(void)
{
    GPIO_ResetBits(GPIOD, ORANGE_LED);
}

void LEDs_blueToggle(void)
{
    GPIO_ToggleBits(GPIOD, BLUE_LED);
}

void LEDs_blueSet(void)
{
    GPIO_SetBits(GPIOD, BLUE_LED);
}

void LEDs_blueReset(void)
{
    GPIO_ResetBits(GPIOD, BLUE_LED);
}

/*
 * spi.h
 *
 *  Created on: 18 ���. 2018 �.
 *      Author: ���
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"

GPIO_InitTypeDef port;
SPI_InitTypeDef spi;

void mySPI_Init(void);

#endif /* SPI_H_ */

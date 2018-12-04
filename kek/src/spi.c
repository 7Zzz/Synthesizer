/*
 * spi.c
 *
 *  Created on: 18 июл. 2018 г.
 *      Author: Дом
 */

#include "spi.h"

void mySPI_Init() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);

	port.GPIO_Mode = GPIO_Mode_AF;
	port.GPIO_OType = GPIO_OType_PP;
	port.GPIO_PuPd = GPIO_PuPd_NOPULL;
	port.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_13;
	port.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &port);
	SPI_StructInit(&spi);
	spi.SPI_Direction = SPI_Direction_2Lines_RxOnly;
	spi.SPI_Mode = SPI_Mode_Slave;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_NSS = SPI_NSS_Soft;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_CRCPolynomial = 10;
	SPI_Init(SPI2, &spi);
	SPI_Cmd(SPI2, ENABLE);
	NVIC_EnableIRQ(SPI2_IRQn);
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
}

/*
 * reg.c
 *
 *  Created on: Jul 13, 2018
 *      Author: Roman
 */
//#include "reg.h"
//
//void Reg_Send(u8* data) {
//	HAL_GPIO_WritePin(STROBE_PORT, STROBE_PIN, GPIO_PIN_RESET);
//	HAL_SPI_Transmit(&hspi1, data, SIZE_8_BIT, SPI_TIMEOUT);
//
//	HAL_GPIO_WritePin(STROBE_PORT, STROBE_PIN, GPIO_PIN_SET);
//}
//
//void Reg_Init(void) {
//	Reg_state = 0x00;
//	HAL_GPIO_WritePin(STROBE_PORT, STROBE_PIN, GPIO_PIN_RESET);
//	HAL_SPI_Transmit(&hspi1, &Reg_state, SIZE_8_BIT, SPI_TIMEOUT);
//
//	HAL_GPIO_WritePin(STROBE_PORT, STROBE_PIN, GPIO_PIN_SET);
//}
//
//void Reg_Animation(u16 delay) {
//	HAL_Delay(delay);
//	switch (Reg_state) {
//	case 0xFF:
//		Reg_state = 0x00;
//		break;
//	case 0x00:
//		Reg_state = 0x01;
//		break;
//	default:
//		Reg_state = Reg_state | (Reg_state << 1);
//		break;
//	}
//	Reg_Send(&Reg_state);
//}





/*
 * MCP23017.c
 *
 *  Created on: Jul 8, 2018
 *      Author: Roman
 */
#include "MCP23017.h"

void MCP23017_Init(void) {
#ifdef MCP23017_DEFAULT_OUT_CONFIG
#define PACKET_SIZE 5
	u8 regsa[PACKET_SIZE] = {MCP23017_IOCONA, MCP23017_IODIRA, MCP23017_IPOLA, MCP23017_GPPUA, MCP23017_GPIOA}; // reg addresses here
	u8 dataa[PACKET_SIZE] = {0x31, 0x00, 0x00, 0x00, 0xFF}; // init reg values here
	MCP_Astate = 0x00;

	u8 regsb[PACKET_SIZE] = {MCP23017_IOCONB, MCP23017_IODIRB, MCP23017_IPOLB, MCP23017_GPPUB, MCP23017_GPIOB}; // reg addresses here
	u8 datab[PACKET_SIZE] = {0x31, 0x00, 0x00, 0x00, 0x00}; // init reg values here
	MCP_Bstate = 0x00;
#endif

#ifdef MCP23017_DEFAULT_IN_CONFIG
#define PACKET_SIZE 5
	u8 regsa[PACKET_SIZE] = { MCP23017_IOCONA, MCP23017_IODIRA, MCP23017_IPOLA,
			MCP23017_GPPUA, MCP23017_GPIOA };  // reg addresses here
	u8 dataa[PACKET_SIZE] = { 0x31, 0xFF, 0xFF, 0xFF, 0x00 }; // init reg values here
	MCP_Astate = 0x00;

	u8 regsb[PACKET_SIZE] = { MCP23017_IOCONB, MCP23017_IODIRB, MCP23017_IPOLB,
			MCP23017_GPPUB, MCP23017_GPIOB };  // reg addresses here
	u8 datab[PACKET_SIZE] = { 0x31, 0xFF, 0xFF, 0xFF, 0x00 }; // init reg values here
	MCP_Bstate = 0x00;
#endif

/////////////////////////  send to all MCPs  //////////////////////
	u8 mcp_addresses[1] = { MCP23017_ADDR(3) }; // TODO:
	for (u8 j = 0; j < 1; j++) {

		for (int i = 0; i < PACKET_SIZE; i++) {
			HAL_I2C_Mem_Write(&(MCP_I2C_HANDLER), (mcp_addresses[j] << 1),
					regsa[i],
					I2C_MEMADD_SIZE_8BIT, &(dataa[i]), 1, 10);
		}
		for (int i = 0; i < PACKET_SIZE; i++) {
			HAL_I2C_Mem_Write(&(MCP_I2C_HANDLER), (mcp_addresses[j] << 1),
					regsb[i],
					I2C_MEMADD_SIZE_8BIT, &(datab[i]), 1, 10);
		}
	}

}

u8 MCP23017_ReadPort(u8 mcp_addr, IO_PortTD port) {
	u8 buf = 0;
	if (port == PORTA)
		HAL_I2C_Mem_Read(&(MCP_I2C_HANDLER), (mcp_addr << 1), MCP23017_GPIOA,
		MCP23017_MEM_ADDR_SIZE, &buf, 1, MCP_TIMEOUT);
	if (port == PORTB)
		HAL_I2C_Mem_Read(&(MCP_I2C_HANDLER), (mcp_addr << 1), MCP23017_GPIOB,
		MCP23017_MEM_ADDR_SIZE, &buf, 1, MCP_TIMEOUT);

	return buf;
}
//
// TODO:
//mcp adresses - to massive (mcp's in structs)

//void MCP_SpinA(u8* state, IO_PinTD pin) {
//	*state = (*state) | (1 << (pin));
//	HAL_I2C_Mem_Write(&hi2c2, (MCP23017_ADDR << 1), MCP23017_GPIOA,
//			MCP23017_MEM_ADDR_SIZE, state, 1, MCP_TIMEOUT);
//}
//
//void MCP_RpinA(u8* state, IO_PinTD pin) {
//	*state = (*state) & (~(1 << (pin)));
//	HAL_I2C_Mem_Write(&hi2c2, (MCP23017_ADDR << 1), MCP23017_GPIOA,
//			MCP23017_MEM_ADDR_SIZE, state, 1, MCP_TIMEOUT);
//}
//
//void MCP_TpinA(u8* state, IO_PinTD pin) {
//	*state = (*state) ^ (1 << (pin));
//	HAL_I2C_Mem_Write(&hi2c2, (MCP23017_ADDR << 1), MCP23017_GPIOA,
//			MCP23017_MEM_ADDR_SIZE, state, 1, MCP_TIMEOUT);
//}
//
//void MCP_SpinB(u8* state, IO_PinTD pin) {
//	*state = (*state) | (1 << (pin));
//	HAL_I2C_Mem_Write(&hi2c2, (MCP23017_ADDR << 1), MCP23017_GPIOB,
//			MCP23017_MEM_ADDR_SIZE, state, 1, MCP_TIMEOUT);
//}
//
//void MCP_RpinB(u8* state, IO_PinTD pin) {
//	*state = (*state) & (~(1 << (pin)));
//	HAL_I2C_Mem_Write(&hi2c2, (MCP23017_ADDR << 1), MCP23017_GPIOB,
//			MCP23017_MEM_ADDR_SIZE, state, 1, MCP_TIMEOUT);
//}
//
//void MCP_TpinB(u8* state, IO_PinTD pin) {
//	*state = (*state) ^ (1 << (pin));
//	HAL_I2C_Mem_Write(&hi2c2, (MCP23017_ADDR << 1), MCP23017_GPIOB,
//			MCP23017_MEM_ADDR_SIZE, state, 1, MCP_TIMEOUT);
//}
//
//void MCP_LED_Animation(u16 delay) {
//	HAL_Delay(delay);
//	switch (MCP_Astate) {
//	case 0xFF:
//		MCP_Astate = 0x00;
//		break;
//	case 0x00:
//		MCP_Astate = 0x01;
//		break;
//	default:
//		MCP_Astate = MCP_Astate | (MCP_Astate << 1);
//		break;
//	}
//	HAL_I2C_Mem_Write(&hi2c2, (MCP23017_ADDR << 1), MCP23017_GPIOA,
//			MCP23017_MEM_ADDR_SIZE, &MCP_Astate, 1, MCP_TIMEOUT);
//}

// TODO:
//void MCP23017_PinInit(IO_PinTD pin, u8 dir, u8 pullup, u8 pol ) {
//
//}


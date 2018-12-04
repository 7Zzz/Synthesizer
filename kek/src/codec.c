//*************************************
//
//  codec related functions
//
//*************************************

#include "codec.h"

void Codec_Init() {

	GPIO_InitTypeDef PinInitStruct;
	GPIO_StructInit(&PinInitStruct);

	I2S_InitTypeDef I2S_InitType;

	I2C_InitTypeDef I2C_InitType;

	//Reset pin as GPIO
	PinInitStruct.GPIO_Pin = CODEC_RESET_PIN;
	PinInitStruct.GPIO_Mode = GPIO_Mode_OUT;
	PinInitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	PinInitStruct.GPIO_OType = GPIO_OType_PP;
	PinInitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	RCC_AHB1PeriphClockCmd(
			RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOB
					| RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_Init(GPIOD, &PinInitStruct);

	// I2C pins
	PinInitStruct.GPIO_Mode = GPIO_Mode_AF;
	PinInitStruct.GPIO_OType = GPIO_OType_OD;
	PinInitStruct.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	PinInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	PinInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &PinInitStruct);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);

	//enable I2S and I2C clocks
	//RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 | RCC_APB1Periph_SPI3, ENABLE);
	RCC_PLLI2SCmd(ENABLE);

	// I2S pins
	PinInitStruct.GPIO_OType = GPIO_OType_PP;
	PinInitStruct.GPIO_Pin = I2S3_SCLK_PIN | I2S3_SD_PIN | I2S3_MCLK_PIN;
	GPIO_Init(GPIOC, &PinInitStruct);

	PinInitStruct.GPIO_Pin = I2S3_WS_PIN;
	GPIO_Init(GPIOA, &PinInitStruct);

	// MIDI pins
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	PinInitStruct.GPIO_Pin = UART_TX;
	PinInitStruct.GPIO_Mode = GPIO_Mode_AF;
	PinInitStruct.GPIO_OType = GPIO_OType_PP;
	PinInitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	PinInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &PinInitStruct);

	PinInitStruct.GPIO_Pin = UART_RX;
	GPIO_Init(GPIOA, &PinInitStruct);

	//prepare output ports for alternate function
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_SPI3);

	//keep Codec off for now
	GPIO_ResetBits(GPIOD, CODEC_RESET_PIN);

	// configure I2S port
	SPI_I2S_DeInit(CODEC_I2S);
	I2S_InitType.I2S_AudioFreq = I2S_AudioFreq_48k;
	I2S_InitType.I2S_MCLKOutput = I2S_MCLKOutput_Enable;
	I2S_InitType.I2S_DataFormat = I2S_DataFormat_16b;
	I2S_InitType.I2S_Mode = I2S_Mode_MasterTx;
	I2S_InitType.I2S_Standard = I2S_Standard_Phillips;
	I2S_InitType.I2S_CPOL = I2S_CPOL_Low;

	I2S_Init(CODEC_I2S, &I2S_InitType);
	I2S_Cmd(CODEC_I2S, ENABLE); // codec enable

	// configure I2C port
	I2C_DeInit(CODEC_I2C);
	I2C_InitType.I2C_ClockSpeed = 100000;
	I2C_InitType.I2C_Mode = I2C_Mode_I2C;
	I2C_InitType.I2C_OwnAddress1 = CORE_I2C_ADDRESS;
	I2C_InitType.I2C_Ack = I2C_Ack_Enable;
	I2C_InitType.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitType.I2C_DutyCycle = I2C_DutyCycle_2;

	I2C_Cmd(CODEC_I2C, ENABLE);
	I2C_Init(CODEC_I2C, &I2C_InitType);

	USART_InitTypeDef usartis;
	USART_StructInit(&usartis);
	usartis.USART_BaudRate = 115200;
	usartis.USART_WordLength = USART_WordLength_8b;
	usartis.USART_StopBits = USART_StopBits_1;
	usartis.USART_Parity = USART_Parity_No;
	usartis.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartis.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &usartis);

	NVIC_EnableIRQ(USART2_IRQn);
	USART_Cmd(USART2, ENABLE);

//		NVIC_InitTypeDef NVIC_InitStructure;
//		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);

}

void Codec_Ctrl_Init() {
	uint32_t delaycount;
	uint8_t CodecCommandBuffer[5];

	uint8_t regValue = 0xFF;

	GPIO_SetBits(GPIOD, CODEC_RESET_PIN);
	delaycount = 1000000;
	while (delaycount > 0) {
		delaycount--;
	}
	//keep codec OFF
	CodecCommandBuffer[0] = CODEC_MAP_PLAYBACK_CTRL1;
	CodecCommandBuffer[1] = 0x01;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	//begin initialization sequence (p. 32)
	CodecCommandBuffer[0] = 0x00;
	CodecCommandBuffer[1] = 0x99;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x47;
	CodecCommandBuffer[1] = 0x80;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	regValue = Codec_Register_Read(0x32);

	CodecCommandBuffer[0] = 0x32;
	CodecCommandBuffer[1] = regValue | 0x80;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	regValue = Codec_Register_Read(0x32);

	CodecCommandBuffer[0] = 0x32;
	CodecCommandBuffer[1] = regValue & (~0x80);
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x00;
	CodecCommandBuffer[1] = 0x00;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);
	//end of initialization sequence

	CodecCommandBuffer[0] = CODEC_MAP_PWR_CTRL2;
	CodecCommandBuffer[1] = 0xAF;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = CODEC_MAP_PLAYBACK_CTRL1;
	CodecCommandBuffer[1] = 0x70;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = CODEC_MAP_CLK_CTRL;
	CodecCommandBuffer[1] = 0x81; //auto detect clock
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = CODEC_MAP_IF_CTRL1;
	CodecCommandBuffer[1] = 0x07;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x0A;
	CodecCommandBuffer[1] = 0x00;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x27;
	CodecCommandBuffer[1] = 0x00;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x1A | CODEC_MAPBYTE_INC;
	CodecCommandBuffer[1] = 0x0A;
	CodecCommandBuffer[2] = 0x0A;
	Codec_Ctrl_Send(CodecCommandBuffer, 3);

	CodecCommandBuffer[0] = 0x1F;
	CodecCommandBuffer[1] = 0x0F;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = CODEC_MAP_PWR_CTRL1;
	CodecCommandBuffer[1] = 0x9E;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = CODEC_MAP_MISC_CTRL;
	CodecCommandBuffer[1] = 0x07;
	Codec_Ctrl_Send(CodecCommandBuffer, 2);

}

void Codec_Ctrl_Send(uint8_t controlBytes[], uint8_t numBytes) {
	uint8_t bytesSent = 0;

	while (I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_BUSY)) {
		//just wait until no longer busy
	}

	I2C_GenerateSTART(CODEC_I2C, ENABLE);
	while (!I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_SB)) {
		//wait for generation of start condition
	}
	I2C_Send7bitAddress(CODEC_I2C, CODEC_I2C_ADDRESS,
	I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(CODEC_I2C,
	I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
		//wait for end of address transmission
	}
	while (bytesSent < numBytes) {
		I2C_SendData(CODEC_I2C, controlBytes[bytesSent]);
		bytesSent++;
		while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING)) {
			//wait for transmission of byte
		}
	}
	while (!I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_BTF)) {
		//wait until it's finished sending before creating STOP
	}
	I2C_GenerateSTOP(CODEC_I2C, ENABLE);

}

uint8_t Codec_Register_Read(uint8_t mapbyte) {
	uint8_t receivedByte = 0;

	while (I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_BUSY)) {
		//just wait until no longer busy
	}

	I2C_GenerateSTART(CODEC_I2C, ENABLE);
	while (!I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_SB)) {
		//wait for generation of start condition
	}

	I2C_Send7bitAddress(CODEC_I2C, CODEC_I2C_ADDRESS,
	I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(CODEC_I2C,
	I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
		//wait for end of address transmission
	}

	I2C_SendData(CODEC_I2C, mapbyte); //sets the transmitter address
	while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING)) {
		//wait for transmission of byte
	}

	I2C_GenerateSTOP(CODEC_I2C, ENABLE);

	while (I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_BUSY)) {
		//just wait until no longer busy
	}

	I2C_AcknowledgeConfig(CODEC_I2C, DISABLE);

	I2C_GenerateSTART(CODEC_I2C, ENABLE);
	while (!I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_SB)) {
		//wait for generation of start condition
	}

	I2C_Send7bitAddress(CODEC_I2C, CODEC_I2C_ADDRESS, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
		//wait for end of address transmission
	}

	while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
		//wait until byte arrived
	}
	receivedByte = I2C_ReceiveData(CODEC_I2C);

	I2C_GenerateSTOP(CODEC_I2C, ENABLE);

	return receivedByte;
}

//****************************************************
//
//   EXAMPLE OF USING CS42L22 on STM32F4-Discovery
//
//   author: A.Finkelmeyer
//   http://www.mind-dump.net/configuring-the-stm32f4-discovery-for-audio
//
//****************************************************
#include <math.h>
#include "main.h"
#include "arm_math.h"

volatile long millis = 0;  // global time counter
volatile long micros = 0;  // global time counter

// Create:
M_OscTypeDef oscillators[MAX_NOTES];
uint8_t isOscOn[MAX_NOTES];
M_ADSR_TypeDef adsr[MAX_NOTES];
float adsrStash[MAX_GENERATORS][4];
M_ADSRwave_TypeDef adsrWave[MAX_NOTES];
float adsrWaveStash[MAX_GENERATORS][5];
M_LFO_TypeDef lfo[MAX_NOTES];
float lfoStash[MAX_GENERATORS][2];
M_LFOfld_TypeDef lfofld[MAX_NOTES];
float lfofldStash[MAX_GENERATORS][2];
M_WireTypeDef wires[MAX_NOTES];
M_DACTypeDef dacs;
u16 smpInPer[MAX_NOTES];
uint16_t smpOffset[MAX_GENERATORS];
u16 amp[MAX_GENERATORS];
float fldPow[MAX_GENERATORS];
float wavFrm[MAX_GENERATORS];
int8_t playingNote[MAX_NOTES];

uint8_t SPIreceivedData[3];
uint8_t receivedData[3];
uint8_t bytesToReceive = 3;
uint8_t receive_flag = 0;
uint8_t receivedDataCounter = 0;
uint8_t flagToNoteOn = 0;
uint8_t numPlayingNotes = 0;
uint8_t currentGen = 0;

int main(void) {
	// Initialize:
	Dac_Init_(&dacs);
	for (int i = 0; i < MAX_NOTES; i++) {
		Osc_Init(&oscillators[i]);
		isOscOn[i] = 0;
		Wire_Init(&wires[i]);
		playingNote[i] = -1;
		smpInPer[i] = 109;
		wires[i].addrSrc = oscillators[i].oBptr;
		wires[i].addrDst = dacs.iBptr;
		ADSR_Init(&adsr[i]);
		ADSRwave_Init(&adsrWave[i]);
		LFO_Init(&lfo[i]);
		LFOfld_Init(&lfofld[i]);
	}
	for (int i = 0; i < MAX_GENERATORS; i++) {
		amp[i] = 500;
		smpOffset[i] = 0;
		adsrStash[i][0] = 0.3;
		adsrStash[i][1] = 0.3;
		adsrStash[i][2] = 0.7;
		adsrStash[i][3] = 0.3;

		adsrWaveStash[i][0] = 0.3;
		adsrWaveStash[i][1] = 0.3;
		adsrWaveStash[i][2] = 0.7;
		adsrWaveStash[i][3] = 0.3;
		adsrWaveStash[i][4] = -1;

		lfoStash[i][0] = 0;
		lfoStash[i][1] = 0;
		lfofldStash[i][0] = 0;
		lfofldStash[i][1] = 0;

	}

// а можно поменять функцию обновления осциллятора:
	SystemInit();
	SysTick_Init();
	Timer4_Init();
	LEDs_Init();
	Enc_Init();
	Codec_Init();
	Codec_Ctrl_Init();
	mySPI_Init();
	SPI_I2S_ITConfig(SPI3, SPI_I2S_IT_TXE, ENABLE); //  configure I2S TX interrupt
	NVIC_EnableIRQ(SPI3_IRQn);                //  audio request interrupt enable
	__enable_irq();

	u16 amp1;
	u16 smp1;
	float wavFrm1;
	float fldPow1;
	while (1) {
		if (updateFlag == 1) {
			// Update:
			while (dacs.snt_smp / AUDIO_BLOCKSIZE != 0) {
				for (int i = 0; i < MAX_NOTES; i++) {
					amp1 = ADSR_Func(adsr + i, amp[currentGen], isOscOn + i);
					wavFrm1 = ADSRwave_Func(adsrWave + i, wavFrm[currentGen],
							isOscOn + i);
					if (adsr[i].isADSRon) {
						smp1 = LFO_Func(lfo + i, smpInPer[i], adsr[i].isADSRon);
						fldPow1 = LFOfld_Func(lfofld + i, fldPow[i],
								adsr[i].isADSRon);
						OscFunc(oscillators + i, amp1, smp1, wavFrm1, fldPow1);
					}
					WireFunc(&wires[i]);
				}
				dacs.snt_smp -= AUDIO_BLOCKSIZE;
				dacs.ld_blk++;
				if (dacs.ld_blk == IB_SIZE)
					dacs.ld_blk = 0;
				for (int i = 0; i < AUDIO_BLOCKSIZE; i++)
					dacs.iB[dacs.ld_blk][i] = 0;
				for (int i = 0; i < MAX_NOTES; i++) {
					wires[i].addrSrc = (oscillators + i)->oB_samples;
					wires[i].addrDst = &(*(dacs.iB[dacs.ld_blk]));
				}
			}
			if (flagToNoteOn && adsr[MAX_NOTES - 1].current == 3) {
				isOscOn[MAX_NOTES - 1] = 1;
				flagToNoteOn = 0;
			}
			updateFlag = 0;
		}
	}
}
/*********IRQ**********************************************************/
void SysTick_Handler(void) {
	micros++;
	if (micros == 5) {
		millis++;       // ?
		micros = 0;
	}
}

void TIM4_IRQHandler(void) {
//millis++;
	if (millis > MILLIS_IN_HOUR) {
		millis = 0;
	}
//Очищаем бит прерывания
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

void SPI3_IRQHandler(void) {
	uint16_t smpNum = dacs.unld_smp;
	uint16_t blkNum = smpNum / AUDIO_BLOCKSIZE;
	float sample = dacs.iB[blkNum][smpNum % AUDIO_BLOCKSIZE];
	SPI_I2S_SendData(CODEC_I2S, (u16) (sample));
	//only update on every second sample to insure that L & R ch. have the same sample value
	if (toggleDacLR == 1) {
		dacs.snt_smp++;                         // we sent another sample
		dacs.unld_smp++;                         // next sample to unload
		if (dacs.snt_smp >= HALF) { // if sent > half - "load new", request update
			updateFlag = 1;                                   // update req
		}
		if (dacs.unld_smp == IB_SIZE * AUDIO_BLOCKSIZE) // обнуление номера выгр. семпла
			dacs.unld_smp = 0;
		toggleDacLR = 0;                            // toggle L & R channels
	} else
		toggleDacLR = 1;                            // toggle L & R channels
//Очищаем бит прерывания
	SPI_ClearITPendingBit(SPI3, SPI_I2S_FLAG_TXE);
}

void SPI2_IRQHandler() {
	if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == SET) {
		SPIreceivedData[receivedDataCounter] = SPI_I2S_ReceiveData(SPI2);
		if (SPIreceivedData[0] == 'b' || SPIreceivedData[0] == 'e')
			receivedDataCounter++;
		else
			receivedDataCounter = 0;
		if (receivedDataCounter == bytesToReceive) {
			for (int i = 0; i < receivedDataCounter; i++)
				receivedData[i] = SPIreceivedData[i];
			receivedDataCounter = 0;
			float* changingParam;
			float changingAmount;
			float changingMax;
			float changingMin;
			uint8_t whichUpdate;
			switch (receivedData[0]) {
			case 'b':
				if (receivedData[2]) {
					if (numPlayingNotes != MAX_NOTES)
						numPlayingNotes++;
					else {
						flagToNoteOn = 1;
						isOscOn[MAX_NOTES - 1] = 0;
						playingNote[MAX_NOTES - 1] = receivedData[1];
						smpInPer[MAX_NOTES - 1] = NoteToSmp(
								playingNote[MAX_NOTES - 1])
								+ smpOffset[currentGen];
						break;
					}
					for (int i = 0; i < MAX_NOTES; i++)
						if (!adsr[i].isADSRon) {
							isOscOn[i] = 1;
							playingNote[i] = receivedData[1];
							smpInPer[i] = NoteToSmp(playingNote[i])
									+ smpOffset[currentGen];
							break;
						}
				} else {
					for (int i = 0; i < MAX_NOTES; i++)
						if (receivedData[1] == playingNote[i]) {
							isOscOn[i] = 0;
							playingNote[i] = -1;
							break;
						}
				}
				break;
			case 'e':
				switch (receivedData[1]) {
				case 0:
					changingParam = &wavFrm[currentGen];
					changingAmount = 0.1;
					changingMax = 4;
					changingMin = 0;
					whichUpdate = -1;
					break;
				case 1:
					changingParam = &adsrWaveStash[currentGen][4];
					changingAmount = 0.1;
					changingMax = 1;
					changingMin = -1;
					whichUpdate = 1;
					break;
				case 2:
					changingParam = &adsrWaveStash[currentGen][0];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 1;
					break;
				case 3:
					changingParam = &adsrStash[currentGen][0];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 0;
					break;
				case 4:
					changingParam = &lfoStash[currentGen][0];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 2;
					break;
				case 5:
					changingParam = &lfofldStash[currentGen][0];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 3;
					break;
				case 6:
					changingParam = &adsrWaveStash[currentGen][1];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 1;
					break;
				case 7:
					changingParam = &adsrStash[currentGen][1];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 0;
					break;
				case 8:
					changingParam = &lfoStash[currentGen][1];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 2;
					break;
				case 9:
					changingParam = &lfofldStash[currentGen][1];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 3;
					break;
				case 10:
					changingParam = &adsrWaveStash[currentGen][2];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 1;
					break;
				case 11:
					changingParam = &adsrStash[currentGen][2];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 0;
					break;
				case 12:
					changingParam = &smpOffset[currentGen];
					changingAmount = 45;
					changingMax = 450;
					changingMin = -450;
					break;
				case 13:
					changingParam = &fldPow[currentGen];
					changingAmount = 0.5;
					changingMax = 10;
					changingMin = 0;
					break;
				case 14:
					changingParam = &adsrWaveStash[currentGen][3];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 1;
					break;
				case 15:
					changingParam = &adsrStash[currentGen][3];
					changingAmount = 0.05;
					changingMax = 1;
					changingMin = 0;
					whichUpdate = 0;
					break;
				case 16:
					changingParam = &amp[currentGen];
					changingAmount = 25;
					changingMax = 500;
					changingMin = 0;
					break;
				}
				if (receivedData[2] && *changingParam < changingMax)
					*changingParam += changingAmount;
				else if (!receivedData[2] && *changingParam > changingMin)
					*changingParam -= changingAmount;
				switch (whichUpdate) {
				case 0:
					for (int i = 0; i < numPlayingNotes; i++)
						ADSR_Update(adsr + i, adsrStash[currentGen][0],
								adsrStash[currentGen][1],
								adsrStash[currentGen][2],
								adsrStash[currentGen][3]);
					break;
				case 1:
					for (int i = 0; i < numPlayingNotes; i++)
						ADSRwave_Update(adsrWave + i,
								adsrWaveStash[currentGen][0],
								adsrWaveStash[currentGen][1],
								adsrWaveStash[currentGen][2],
								adsrWaveStash[currentGen][3],
								adsrWaveStash[currentGen][4]);
					break;
				case 2:
					for (int i = 0; i < numPlayingNotes; i++)
						LFO_Update(lfo + i, lfoStash[currentGen][0],
								lfoStash[currentGen][1]);
					break;
				case 3:
					for (int i = 0; i < numPlayingNotes; i++)
						LFOfld_Update(lfofld + i, lfofldStash[currentGen][0],
								lfofldStash[currentGen][1]);
					break;
				}
				break;
			}

		}
	}
}

//  my funcs:---------------------------------------------------------------
// System clock 1us
void SysTick_Init(void) {
	SysTick->LOAD = SYSTIMERTICK;
	SysTick->VAL = SYSTIMERTICK;

	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
	SysTick_CTRL_TICKINT_Msk |
	SysTick_CTRL_ENABLE_Msk;
}

uint16_t NoteToSmp(uint8_t note) {
	float freq = NoteNum_ToFreq(note);
	return SAMPLERATE / freq;
}

float NoteNum_ToFreq(u8 noteNumber) {
	s8 offset = noteNumber - 7;  //difference from A4 (440Hz, MIDI-note 69)
	float freq = 440.0f;

	if (offset > 0) {
		while (offset > 11) {
			offset -= 12;
			freq *= 2.0f;
		}
		while (offset > 0) {
			offset--;
			freq *= 1.059463f;  // 2^(1/12)
		}
	} else if (offset < 0) {
		while (offset < -11) {
			offset += 12;
			freq *= 0.5f;
		}
		while (offset < 0) {
			offset++;
			freq *= 0.9438743f; // 2^(-1/12)
		}
	}
	return freq;
}

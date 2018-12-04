#include "Osc.h"

void Osc_Init(M_OscTypeDef* M) {
	M->smpInPeriod = 40;
	M->genCnt = M->smpInPeriod;
	M->oBptr = M->oB_samples; // connection block pointer
	M->regenerate = 1;
	M->wavFrm = 0;
	M->amp = 0;
	M->fldPow = 0;
}

void OscFunc(M_OscTypeDef *M, u16 amp, u16 smpInPer, float wavFrm, float fldPow) {
	for (int smpCnt = 0; smpCnt < AUDIO_BLOCKSIZE; smpCnt++) {
		if (M->genCnt == M->smpInPeriod) {
			//if (M->regenerate) {
			M->smpInPeriod = smpInPer;
			M->wavFrm = wavFrm;
			M->fldPow = fldPow;
			M->amp = amp;
			waveForm(M);
			folder(M);
			//}
			M->genCnt = 0;
			M->regenerate = 0;
		}
		M->oB_samples[smpCnt] = M->amp * (M->per[M->genCnt] + 1) / 2;
		M->genCnt++;
	}
}

void waveForm(M_OscTypeDef *M) {
	int mo;
	if (M->wavFrm > 0)
		mo = (int) myCeil(M->wavFrm);
	else
		mo = 1;
	float g = mo - M->wavFrm;
	float ab = 4.0 / (float) M->smpInPeriod;
	float quarter = (float) M->smpInPeriod / 4.0;

	float xtri;
	float xsin;

	float a;
	float b;
	float aa1;

	float bb;

	float pwpw;

	switch (mo) {
	case 1:
		for (int i = 0; i < M->smpInPeriod; i++) {
			xsin = arm_sin_f32(i * ab * 3.1416 / 2.0);
			if (i < quarter)
				xtri = ab * i;
			else if (i < 3.0 * quarter)
				xtri = 1.0 - ab * (i - quarter);
			else
				xtri = ab * (i - 3 * quarter) - 1;
			M->per[i] = xsin * (1 - M->wavFrm) + xtri * M->wavFrm;
		}
		break;
	case 2:
		for (int i = 0; i < M->smpInPeriod; i++) {
			a = ab / g;
			b = ab / M->wavFrm;
			aa1 = quarter * g;
			if ((float) i < aa1)
				M->per[i] = a * (float) i;
			else if ((float) i < (float) M->smpInPeriod - aa1)
				M->per[i] = 1 - b * ((float) i - aa1);
			else
				M->per[i] = a * ((float) i - ((float) M->smpInPeriod - aa1))
						- 1;
		}
		break;
	case 3:
		for (int i = 0; i < M->smpInPeriod; i++) {
			bb = g * ab / (float) 2;
			if ((float) i < (float) M->smpInPeriod/(float)2)
				M->per[i] = 1 - bb * (float) i;
			else
				M->per[i] = -1 + 2 * g - bb * (float) i;
		}
		break;
	case 4:
		for (int i = 0; i < M->smpInPeriod; i++) {
			pwpw = (float) 2 * quarter * g;
			if ((float) i >= pwpw)
				M->per[i] = -1;
			else
				M->per[i] = 1;
		}
		break;
	}
}

float myAbsMax(float*a, int size) {
	float max = 0;
	for (int i = 1; i < size; i++)
		if (a[i] > max)
			max = a[i];
		else if (a[i] < -max)
			max = -a[i];
	return max;
}

void folder(M_OscTypeDef *M) {
	for (int i = 0; i < M->smpInPeriod; i++)
		M->per[i] = arm_sin_f32((M->fldPow + 1) * M->per[i]);
	float max = myAbsMax(M->per, M->smpInPeriod);
	for (int i = 0; i < M->smpInPeriod; i++)
		M->per[i] /= max;
}

/*void skewer(M_OscTypeDef *M) {
 float n = M->skwPow;
 float *k = tt(M);
 float *out = (float*) malloc(sizeof(float) * M->smpInPeriod);
 uint8_t *bools = (uint8_t*) malloc(sizeof(uint8_t) * M->smpInPeriod);
 for (int i = 0; i < M->smpInPeriod; i++) {
 bools[i] = 0;
 }
 for (int i = 0; i < M->smpInPeriod; i++) {
 int rq = myRound((k[i] + 1) / 2 * (M->smpInPeriod - 1));
 out[rq] = M->per[i];
 bools[rq] = 1;
 }
 free(k);
 for (int i = M->smpInPeriod / 2; i >= 0; i--) {
 if (bools[i] == 0)
 for (int j = i - 1; j >= 0; j--)
 if (bools[j] != 0) {
 out[i] = (out[j] * (i + 1) - j * out[i + 1]
 + i * (out[i + 1] - out[j])) / (i + 1 - j);
 bools[i] = 1;
 break;
 }
 }

 for (int i = M->smpInPeriod / 2 + 1; i < M->smpInPeriod; i++) {
 if (bools[i] == 0)
 for (int j = i + 1; j < M->smpInPeriod; j++)
 if (bools[j] != 0) {
 out[i] = (out[j] * (i - 1) - j * out[i - 1]
 + i * (out[i - 1] - out[j])) / (i - 1 - j);
 bools[i] = 1;
 break;
 }
 }
 free(bools);
 M->per = out;
 free(out);
 }

 }
 */
int myCeil(float in) {
	int out = (int) in;
	if (out < in)
		out++;
	return out;
}

int myRound(float in) {
	int out = (int) in;
	if (in - out >= (float) 0.5)
		out++;
	return out;
}
//
//u16 tt(M_OscTypeDef *M, u16 i) {
//	u16 n = M->tenPow;
//	u16 out;
//	if (i < M->smpInPeriod / 2)
//		out = i
//				+ (n * M->smpInPeriod / 2 - n * M->smpInPeriod / (2 * (i + 1))
//						- i * n + i * n * 2 / M->smpInPeriod) / 1000;
//	else
//		out = i
//				+ (n * M->smpInPeriod / 2
//						- n * M->smpInPeriod / (2 * (M->smpInPeriod - i))
//						- (M->smpInPeriod - i - 1) * n
//						+ (M->smpInPeriod - i - 1) * n * 2 / M->smpInPeriod)
//						/ 1000;
//
//	return out;
//}
//float* tt(M_OscTypeDef *M, float n) {
//	float* out = (float*) malloc(sizeof(float) * M->smpInPeriod);
//	for (int i = 0; i < M->smpInPeriod; i++) {
//		if (M->smpInPeriod % 2 == 0)
//			if (i <= M->smpInPeriod / 2)
//				out[i] = -my_exp(n * (M->smpInPeriod / 2 - i)) + 1;
//			else
//				out[i] = my_exp(n * (i + 1 - M->smpInPeriod / 2)) - 1;
//		else if (i < M->smpInPeriod / 2)
//			out[i] = -my_exp(n * (M->smpInPeriod / 2 - i)) + 1;
//		else if (i == M->smpInPeriod / 2)
//			out[i] = 0;
//		else
//			out[i] = my_exp(n * (i - M->smpInPeriod / 2)) - 1;
//	}
//	for (int i = 0; i < M->smpInPeriod; i++)
//		out[i] /= out[M->smpInPeriod - 1];
//	return out;
//}
//
//void tension(M_OscTypeDef *M) {
//	//float kek[1000];
//	for (int j = 0; j < M->smpInPeriod; j++) {
//		u16 i = M->smpInPeriod * (M->per[j] + 1) / 2;
//		M->per[j] = 2 * (float) tt(M, i) / (float) (M->smpInPeriod - 1) - 1;
//		//kek[j] = M->per[j];
//	}
//	//free(kek);
//}

//#include "Osc.h"
//
//void Osc_Init(M_OscTypeDef* M) {
//	M->smpInPeriod = 200;
//	M->per = (u16*) malloc(sizeof(u16) * M->smpInPeriod);
//	for (int i = 0; i < M->smpInPeriod; i++) {
//		M->per[i] = 0;
//	}
//	M->oB_samples = (u16*) malloc(sizeof(u16) * AUDIO_BLOCKSIZE);
//	for (int i = 0; i < AUDIO_BLOCKSIZE; i++) {
//		M->oB_samples[i] = 0;
//	}
//	M->oBptr = &(M->oB_samples); // connection block pointer
//	M->regenerate = 1;
//	M->amp = 500;
//	M->genCnt = 0;
//	M->wavFrm = 0;
//	M->fldPow = 0;
//	M->tenPow = 0;
//	M->skwPow = 0;
//}
//
//void OscFunc(M_OscTypeDef *M, u16 amp) {
//	M->amp = amp;
//	for (int smpCnt = 0; smpCnt < AUDIO_BLOCKSIZE; smpCnt++) {
//		if (M->genCnt == M->smpInPeriod) {
//			M->wavFrm++;
//			if (M->wavFrm == 4000)
//				M->wavFrm = 0;
//			//if (M->regenerate) {
//			waveForm(M);
//			//folder(M);
//			//tension(M);
//			//skewer(M);
//			//}
//			M->genCnt = 0;
//			M->regenerate = 0;
//		}
//		M->oB_samples[smpCnt] = M->per[M->genCnt];
//		M->genCnt++;
//	}
//}
//
//void waveForm(M_OscTypeDef *M) {
//	u16 thou = 1000;
//	u8 mo = M->wavFrm / thou + 1;
//	u16 g = mo * thou - M->wavFrm;
//
//	u16 xtri;
//	u16 xsin;
//
//	u16 aa1;
//	u16 bb;
//	u16 pwpw;
//
//	u16 gg[500];
//	switch (mo) {
//	case 1:
//		for (int i = 0; i < M->smpInPeriod; i++) {
//			xsin = M->amp * (arm_sin_f32(i * 2 * 3.1416 / M->smpInPeriod) + 1)
//					/ 2;
//			if (i < M->smpInPeriod / 4)
//				xtri = (M->amp * 4 * i + M->amp * M->smpInPeriod)
//						/ (2 * M->smpInPeriod);
//			else if (i < 3 * M->smpInPeriod / 4)
//				xtri = (3 * M->amp * M->smpInPeriod - M->amp * 4 * i)
//						/ (2 * M->smpInPeriod);
//			else
//				xtri = (M->amp * 4 * i - M->amp * 3 * M->smpInPeriod)
//						/ (2 * M->smpInPeriod);
//			M->per[i] = (xsin * g + xtri * (thou - g)) / thou;
//		}
//
//		break;
//	case 2:
//		aa1 = M->smpInPeriod * g / 4;
//		for (int i = 0; i < M->smpInPeriod; i++) {
//			if (i * thou < aa1)
//				M->per[i] = (i * thou * M->amp + M->amp * aa1) / (2 * aa1);
//			else if (i * thou < M->smpInPeriod * thou - aa1)
//				M->per[i] = (M->amp * (M->smpInPeriod * thou - 2 * aa1)
//						- M->amp * (i * thou - aa1))
//						/ (M->smpInPeriod * thou - 2 * aa1);
//			else
//				M->per[i] = M->amp * (thou * i - thou * M->smpInPeriod + aa1)
//						/ (2 * aa1);
//			gg[i] = M->per[i];
//		}
//		if (g == 500)
//			aa1 = 1;
//		break;
//	case 3:
//		for (int i = 0; i < M->smpInPeriod; i++) {
//			bb = g * 2 / (M->smpInPeriod);
//			if (i < M->smpInPeriod / 2)
//				M->per[i] = M->amp * (thou * M->smpInPeriod - g * 2 * i)
//						/ (thou * M->smpInPeriod);
//			else
//				M->per[i] = M->amp * (g * M->smpInPeriod - g * 2 * i)
//						/ (thou * M->smpInPeriod);
//		}
//		break;
//	case 4:
//		for (int i = 0; i < M->smpInPeriod; i++) {
//			pwpw = M->smpInPeriod * g / (2 * thou);
//			if (i < pwpw)
//				M->per[i] = M->amp;
//			else
//				M->per[i] = 0;
//		}
//		break;
//	}
//}
//u16 myAbsMinus(u16 task1, u16 task2) {
//	if (task1 > task2)
//		return task1 - task2;
//	else
//		return task2 - task1;
//}
///*
// float myAbsMax(float*a, int size) {
// float max = 0;
// for (int i = 1; i < size; i++)
// if (a[i] > max)
// max = a[i];
// else if (a[i] < -max)
// max = -a[i];
// return max;
// }
//
// void folder(M_OscTypeDef *M) {
// for (int i = 0; i < M->smpInPeriod; i++)
// M->per[i] = arm_sin_f32((M->fldPow + 1) * M->per[i]);
// float max = myAbsMax(M->per, M->smpInPeriod);
// for (int i = 0; i < M->smpInPeriod; i++)
// M->per[i] /= max;
// }
//
// void skewer(M_OscTypeDef *M) {
// float n = M->skwPow / 10;
// float *k = tt(M, n);
// float *out = (float*) malloc(sizeof(float) * M->smpInPeriod);
// uint8_t *bools = (uint8_t*) malloc(sizeof(uint8_t) * M->smpInPeriod);
// for (int i = 0; i < M->smpInPeriod; i++) {
// bools[i] = 0;
// }
// for (int i = 0; i < M->smpInPeriod; i++) {
// int rq = myRound((k[i] + 1) / 2 * (M->smpInPeriod - 1));
// out[rq] = M->per[i];
// bools[rq] = 1;
// }
// free(k);
// for (int i = M->smpInPeriod / 2; i >= 0; i--) {
// if (bools[i] == 0)
// for (int j = i - 1; j >= 0; j--)
// if (bools[j] != 0) {
// out[i] = (out[j] * (i + 1) - j * out[i + 1]
// + i * (out[i + 1] - out[j])) / (i + 1 - j);
// bools[i] = 1;
// break;
// }
// }
//
// for (int i = M->smpInPeriod / 2 + 1; i < M->smpInPeriod; i++) {
// if (bools[i] == 0)
// for (int j = i + 1; j < M->smpInPeriod; j++)
// if (bools[j] != 0) {
// out[i] = (out[j] * (i - 1) - j * out[i - 1]
// + i * (out[i - 1] - out[j])) / (i - 1 - j);
// bools[i] = 1;
// break;
// }
// }
// free(bools);
// M->per = out;
// free(out);
// }
//
// int myCeil(float in) {
// int out = (int) in;
// if (out < in)
// out++;
// return out;
// }
//
// int myRound(float in) {
// int out = (int) in;
// if (in - out >= (float) 0.5)
// out++;
// return out;
// }
//
// float* tt(M_OscTypeDef *M, float n) {
// float* out = (float*) malloc(sizeof(float) * M->smpInPeriod);
// float* help = (float*) malloc(sizeof(float) * M->smpInPeriod);
// for (int i = 0; i < M->smpInPeriod / 2; i++) {
// help[i] = n / (2 * ((float) M->smpInPeriod / (float) 2 - i));
// }
// float rr = (-help[M->smpInPeriod / 2 - 1] + help[0]);
// for (int i = 0; i < M->smpInPeriod; i++) {
// if (i < (float) M->smpInPeriod / (float) 2) {
// out[i] = myRound(
// ((-help[M->smpInPeriod / 2 - i - 1] + help[0])
// - (1 - 2 * (float) i / (float) M->smpInPeriod)
// * ((float) 0.5 + rr) + 0.5)
// * (M->smpInPeriod));
// } else {
// out[i] = -out[M->smpInPeriod - i - 1] + M->smpInPeriod - 1;
// }
// }
// return out;
// }
//
// void tension(M_OscTypeDef *M) {
// float n = M->tenPow / 10;
// float *k = tt(M, n);
// for (int j = 0; j < M->smpInPeriod; j++) {
// int i = myCeil(
// (float) M->smpInPeriod * (float) (M->per[j] + 1) / (float) 2)
// - 1;
// M->per[j] = k[i] * 2 / (float) M->smpInPeriod - 1;
// }
// free(k);
// }
// */

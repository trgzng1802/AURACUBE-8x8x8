#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"

void fft_ADC_Init(void);							//��fft�ɼ������ݽ���ADC�ĳ�ʼ��
uint16_t Get_ADC(uint8_t ch); 						//��ȡADC������  

#endif


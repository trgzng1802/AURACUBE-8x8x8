#ifndef _fft_H
#define _fft_H

#include "stm32f10x.h"
#include "fft_tab.h"
#include "math.h"
#include "adc.h"
#include "led.h"

typedef struct									//����Ҷ�任 ��������������
{
	float real;
	float imag;
}compx;

//#define fft_64 																		//64���fft 
#define fft_128 																		//128���fft
//#define fft_256 																		//256���fft
//#define fft_512 																		//512���fft 
//#define fft_1024 																		//1024���fft

#ifdef fft_64
#define fft_N 64
#endif
#ifdef fft_128
#define fft_N 128
#endif
#ifdef fft_256
#define fft_N 256
#endif
#ifdef fft_512
#define fft_N 512
#endif
#ifdef fft_1024
#define fft_N 1024
#endif	 

extern compx fftData[fft_N];    														//fft���ݶ� 
extern uint16_t fftIn[fft_N];    														//fft��������
extern uint8_t fftOut[fft_N / 2];    													//fft������� 
extern uint8_t sqrt_M(uint16_t temp);													//fft�����Mֵ

#define M sqrt_M(fft_N)																	//���M��ֵ 

void fft_Convert(compx *xin);															//N��fft���㺯��,fft����ת��������
void fft_powerMag(void);																//fft�������ֵ������fftOut�������
void fft_Data(void);																	//����fft��ADC�����ݲɼ�
void fft_Display(void);																	//fft���㴦��֮�����ʾ����


#endif





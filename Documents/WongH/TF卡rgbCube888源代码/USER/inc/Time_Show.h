#ifndef __Time_Show_H__
#define __Time_Show_H__

#include "stm32f10x.h"
#include "LED.h"
#include "timer.h"
#include "calculate.h"
#include "snake.h"
#include "adc.h"
#include "fft.h"

void Cartoon(void);																//������ʾ
void ReadW25Q64(void);															//��ȡ�ڴ����������
void Snake_scrolling(void);														//����ʾ�ƶ�
void BOX_move(uint8_t flashorder);

#endif








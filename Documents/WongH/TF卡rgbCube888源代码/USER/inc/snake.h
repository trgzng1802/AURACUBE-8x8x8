#ifndef _SNAKE_H
#define _SNAKE_H

#include "stdlib.h"
#include "led.h"
#include "calculate.h"

#define Snake_Long 	20  														//��󳤶�

typedef struct
{
	int8_t Sx;
	int8_t Sy;
	int8_t Sz;
}Coordinate;																	//������ά����Ľṹ��

extern Coordinate Snake[Snake_Long + 1];										//����̰���ߵ���ά�����
extern int8_t Add_X, Add_Y, Add_Z;            									//λ��ƫ����

uint8_t Collide(void);															//�ж�̰�����Ƿ�����ײ
void Snake_Start(void);															//�����ʼ������
void Snake_Above(void);															//��ʳ�ﲢ���ж�ʳ���Ƿ�����������
void Snake_Feed(void);															//�ж��Ƿ��ʳ��Ծͳ��ȼ�1�����򲻼ӣ������ж��Ƿ�ﵽ��󳤶�
void Snake_Move(void);															//̰���ߵ������ƶ�
void Snake_Show(uint8_t snake_red, uint8_t snake_green, uint8_t snake_blue,
	uint8_t feeed_red, uint8_t feeed_green, uint8_t feeed_blue);				//̰���ߵ���ʾ����

#endif




#ifndef __calculate_H__
#define __calculate_H__

#include "LED.h"
#include "stm32f10x.h"

extern int8_t Get_Point[3];																					//��ȡĳ���������
extern const uint8_t Dat_print[];																			//��ӡ����ʹ��
extern const uint8_t MathSum[];																				//����,������Ļʹ��,��������
extern void Frame(const uint8_t *Data, uint8_t red, uint8_t green, uint8_t blue, int8_t direction);
extern void Move(uint8_t *Data_Move, uint8_t d, uint8_t b, uint8_t c, uint8_t e);

uint8_t Word_Swap(uint8_t temp);																			//�ߵ�λת��
//void ColorPoint(int8_t x,int8_t y,int8_t z,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut);				//���ѡ������ɫ����
void Funnel_Shape(int8_t number, uint8_t red, uint8_t green, uint8_t blue);									//һ�����γ�©������״����
void line(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue);																//3ά�����л���
void Rotat(int16_t number, uint8_t red, uint8_t green, uint8_t blue);										//�򵥵���ת��
void Line_Change(int8_t number, uint8_t red, uint8_t green, uint8_t blue);									//���������仯
void Page(int8_t number, uint8_t red, uint8_t green, uint8_t blue, int8_t way);								//����һ����Ч����һ��һ�����ʾ
void GetPoint(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2, int8_t Number);				//��ȡ�����γɵ����е�ĳ��������꣬����Get_Point[3]����
void PlaneXY(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill);													//3ά�����л�����,��ֱ��xy��ƽ��
void Change_PlaneXY(int8_t number, uint8_t red, uint8_t green, uint8_t blue);								//��ֱxy�������Ч��
void PlaneYZ(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill);													//3ά�����л�����,��ֱ��yz��ƽ��
void PlaneZX(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill);													//3ά�����л�����,��ֱ��zx��ƽ��
void Box(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2,
	uint8_t red, uint8_t green, uint8_t blue, int8_t fill, int8_t Up_Down);									//3ά�����л�����
void Box_Change(int8_t number, uint8_t red, uint8_t green, uint8_t blue, int8_t Up_Down);					//4����������תЧ��
void DNA_Change(int16_t number, uint8_t red, uint8_t green, uint8_t blue);									//DNA��תЧ��
void Waveform(int16_t number, uint8_t red, uint8_t green, uint8_t blue);									//���˵ı仯Ч��
void print(int number, const uint8_t *Data, uint8_t red, uint8_t green, uint8_t blue, char m, int8_t direction);	//��ӡͼ��
void Mov_Show(int number, const uint8_t *Data, uint8_t red, uint8_t green, uint8_t blue, int8_t direction);			//������Ļ
void sphere(int x0, int y0, int z0, int r, uint8_t R, uint8_t G, uint8_t B);

#endif








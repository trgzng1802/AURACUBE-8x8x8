#include "SNAKE.h"

Coordinate Snake[Snake_Long+1];																				//����̰���ߵ���ά�����

/********************************************************
Add_X�� 1Ϊ����
Add_X��-1Ϊ����
Add_Y�� 1Ϊ���
Add_Y��-1Ϊ��ǰ
Add_Z�� 1Ϊ����
Add_Z��-1Ϊ����
Add_X��Add_Y��Ϊ0ʱ����
********************************************************/
int8_t Add_X = 0,Add_Y = 0,Add_Z = 0;            															//λ��ƫ����
#define Start_Long 	3																						//��ʼ����
uint8_t New_Long = 0;																						//��ǰ����

/*******************************************************************************
 * @name     :uint8_t Collide(void)
 * @return   :0��ײ��1ײ
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :�ж�̰�����Ƿ�����ײ
*******************************************************************************/
uint8_t Collide(void)
{
	int i;
	
	for(i = 2; i < New_Long; i++)																	
	{
		if(Snake[1].Sx == Snake[i].Sx && Snake[1].Sy == Snake[i].Sy && Snake[1].Sz == Snake[i].Sz)								//�ж��Ƿ�ײ�Լ�
			return 1;
	} 	
	if(Snake[1].Sx >= 0 && Snake[1].Sx <= 7 && Snake[1].Sy >= 0 && Snake[1].Sy <= 7 && Snake[1].Sz >= 0 && Snake[1].Sz <= 7)	//�ж��Ƿ�ײǽ
		return 0 ;
	else 
		return 1;	  											
}

/*******************************************************************************
 * @name     :void Snake_Start(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :�����ʼ������
*******************************************************************************/
void Snake_Start(void)
{
	int i = 0;
	New_Long = Start_Long;																					//��ʼ���ߵĳ���
	for(i = 0; i < Snake_Long; i++)
	{
		Snake[i].Sx = 0;
		Snake[i].Sy = 0;										
		Snake[i].Sz = 0;																					//����
	}	
	Snake[1].Sx = 1;
	Snake[1].Sy = 0;														
	Snake[1].Sz = 0;																						//��ͷ

	Snake[2].Sx = 0;
	Snake[2].Sy = 0;														
	Snake[2].Sz = 0;																						//��β
	
	Add_X = 0;
	Add_Y = 0;            												
	Add_Z = 0;            																					//λ��ƫ������0���߲���
}

/*******************************************************************************
 * @name     :void Snake_Above(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :��ʳ�ﲢ���ж�ʳ���Ƿ�����������
*******************************************************************************/
void Snake_Above(void)
{
	int i = 1;
Back:
	srand(TIM2->CNT);																						//�����һ������ȡ��ʱ����ֵ��α���
	Snake[0].Sx = (char)(rand()%8);																			//���Ÿ���ʳ��
	Snake[0].Sy = (char)(rand()%8);																			//���Ÿ���ʳ��		
	Snake[0].Sz = (char)(rand()%8);																			//���Ÿ���ʳ��		

	i = 1;
	while(i <= New_Long) 																					//�ж�ʳ���Ƿ�����������
	{
		if(Snake[i].Sx == Snake[0].Sx && Snake[i].Sy == Snake[0].Sy && Snake[i].Sz == Snake[0].Sz)			//ʳ��������ߵ����ϣ���ȥ�ٴ�ȡ�����
			goto Back;																						
		i++;
	}        											
}

/*******************************************************************************
 * @name     :void Snake_Feed(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :��ʳ�ﲢ���ж�ʳ���Ƿ�����������
*******************************************************************************/
void Snake_Feed(void)
{
	if(Snake[1].Sx == Snake[0].Sx && Snake[1].Sy == Snake[0].Sy && Snake[1].Sz == Snake[0].Sz)				//�ж��Ƿ�Զ���
	{
		New_Long++;																							//���ȼ�1--ʵ�ʾ��Ǵ��ߵĺ�������һ���㣬��ͷ����һ�㣬ʹ�˵Ĵ���ǳ���ʳ��
		if(New_Long != Snake_Long+1)																		//�ж��Ƿ���Ҫ���¸�ʳ��
			Snake_Above();																					//��ʳ�ﲢ���ж�ʳ���Ƿ�����������
		else if(New_Long == Snake_Long+1) 																	//�ж��Ƿ�ﵽ��󳤶�
		{
			New_Long = Start_Long;																			//���߳�ʼ������
			Snake_Start();																					//�����ʼ��
			Snake_Above();																					//��ʳ�ﲢ���ж�ʳ���Ƿ�����������
		}
	}
}

/*******************************************************************************
 * @name     :void Snake_Move(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :̰���ߵ������ƶ�
*******************************************************************************/
void Snake_Move(void)
{
	int i = 0;
	if(0 != Add_X || 0 != Add_Y || 0 != Add_Z)																//�ж��Ƿ���Ҫ�ƶ�
	{
		for(i = New_Long-1; i; i--)													
		{
			Snake[i].Sx = Snake[i-1].Sx;
			Snake[i].Sy = Snake[i-1].Sy;						
			Snake[i].Sz = Snake[i-1].Sz;																	//̰���ߵ������ƶ�(�Ӻ�����ǰ�ƶ�һλ)
		}   
		Snake[1].Sx = Snake[2].Sx+Add_X;
		Snake[1].Sy = Snake[2].Sy+Add_Y;                    				
		Snake[1].Sz = Snake[2].Sz+Add_Z;                    												//̰���ߵ�ͷ���ƶ�
	}
}

/*******************************************************************************
 * @name     :void Snake_Show(uint8_t snake_red,uint8_t snake_green,uint8_t snake_blue,uint8_t feeed_red,uint8_t feeed_green,uint8_t feeed_blue)
 * @param    :snake_red   ������ĺ�ɫ
 * @param    :snake_green ���������ɫ
 * @param    :snake_blue  ���������ɫ
 * @param    :feeed_red   ��ʳ��ĺ�ɫ
 * @param    :feeed_green ��ʳ�����ɫ
 * @param    :feeed_blue  ��ʳ�����ɫ
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :̰���ߵ���ʾ����
*******************************************************************************/
void Snake_Show(uint8_t snake_red,uint8_t snake_green,uint8_t snake_blue,uint8_t feeed_red,uint8_t feeed_green,uint8_t feeed_blue)
{
	int i;
	clearAll();																								//������л���
	for(i = 1; i < New_Long; i++)																			//��������ʾ����
		set(Snake[i].Sx,Snake[i].Sy,Snake[i].Sz,snake_red,snake_green,snake_blue);
	set(Snake[0].Sx,Snake[0].Sy,Snake[0].Sz,feeed_red,feeed_green,feeed_blue);						//��ʾʵ��
}




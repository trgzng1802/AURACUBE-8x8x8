#include "timer.h"

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void Timer4_Init(uint16_t psc,uint16_t arr)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);                //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr;                             //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);                       //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ   
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                        //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);                     //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(                                       				//ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM4,                                           				//TIM4
		TIM_IT_Update  |                                				//TIM �ж�Դ
		TIM_IT_Trigger,                                 				//TIM �����ж�Դ 
		ENABLE                                          				//ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                 	//TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 	//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);                                          	//ʹ��TIMx����
}

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void Timer3_Init(uint16_t psc,uint16_t arr)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr;                             //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);                       //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ   
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                        //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                     //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(                                       				//ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3,                                           				//TIM3
		TIM_IT_Update  |                                				//TIM �ж�Դ
		TIM_IT_Trigger,                                 				//TIM �����ж�Դ 
		ENABLE                                          				//ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                 	//TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;       	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 	//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);                                          	//ʹ��TIMx����
}

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void Timer2_Init(uint16_t psc,uint16_t arr)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr;                             //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);                       //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ   
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                        //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                     //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(                                       				//ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2,                                           				//TIM2
		TIM_IT_Update  |                                				//TIM �ж�Դ
		TIM_IT_Trigger,                                 				//TIM �����ж�Դ 
		ENABLE                                          				//ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                 	//TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;       	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 	//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);                                          	//ʹ��TIMx����
}













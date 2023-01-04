#include "IR_NEC.h"

void IR_ENC_Init(uint16_t psc)							//�����߽����ʼ��
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);		//ʹ��ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;					//��������ģʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);							//��ʼ��GPIO��ģʽ

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);          	//ʱ��ʹ��

	TIM_DeInit(TIM1);
	TIM_TimeBaseStructure.TIM_Period = Step;                 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = (psc - 1);              	//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      	//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);              	//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;        		//TIM1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               	//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                              	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM1, ENABLE);                                       	//ʹ��TIMx����
}
unsigned char	IR_BT;		         								//����Ч�����أ�0��Ч��1��Ч
unsigned char	NEC[4];		         								//�����ţ�16λ�û��롢������������
unsigned int	cntStep;											//������
unsigned char	IRa, IRb;			 								//��λ״̬����
unsigned char	IRsync;				 								//ͬ����־
unsigned char	BitN;                								//λ��װ����

/*�������������������� ��׼ ����������������������*/
#define    Boot_Limit	    (((9000+4500) +2000)/Step)	  			//��������������    
#define    Boot_Lower	    (((9000+4500) -2000)/Step)	  			//��������������    
#define    Bit1_Limit       ((2250 +800)/Step)	          			//��1����������
#define    Bit0_Limit       ((1125 +400)/Step)			  			//��0����������

/*������������������������������������������������
������������NEC���ڲ������뷨����ʱ�жϣ��½��ز�ѯ����ʱ�䣩
ȫ�ֱ�����IR_BT = 0��Ч
				 1��Ч���̰�
������������������������������������������������*/
void IR_NEC(void)
{
	cntStep++;		   												//��������

	IRb = IRa;		   												//�ϴε�λ״̬
	IRa = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);					//��ǰ��λ״̬

	if (IRb && !IRa)				  	  													//�Ƿ��½��أ��ϴθߣ���ǰ�ͣ�
	{
		if (cntStep > Boot_Limit)      								//����ͬ��ʱ�䣿
			IRsync = 0;				  								//ͬ��λ��0
		else if (cntStep > Boot_Lower)								//���뿪ʼ
		{
			IRsync = 1;
			BitN = 32;
		}															//ͬ��λ��1��װ��λ����			  
		else if (IRsync)																	//�����ͬ��
		{
			if (cntStep > Bit1_Limit)								//�ٴ��ж��Ƿ�����
				IRsync = 0;
			else
			{
				NEC[3] >>= 1;
				if (cntStep > Bit0_Limit)
					NEC[3] |= 0x80;    								//��0���롰1��
				if (--BitN == 0)
				{
					IRsync = 0;										//ͬ��λ��0
					IR_BT = 1; 										//����ɹ����ɹ���־��1
				}
				else if ((BitN & 0x07) == 0)												//NEC[3]ÿװ��8λ���ƶ�����һ�Σ��� BitN%8 == 0��
				{
					NEC[0] = NEC[1];
					NEC[1] = NEC[2];
					NEC[2] = NEC[3];
				}
			}
		}
		cntStep = 0;   												//��������0
	}
}

/*******************************************************************************
 * @name     :void TIM1_IRQHandler(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :TIM1�жϷ��������Ժ����ǰ������н���
*******************************************************************************/

void TIM1_UP_IRQHandler(void)   									//TIM1�ж�
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) 				//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  				//���TIMx���жϴ�����λ:TIM �ж�Դ 

		IR_NEC();													//������NEC���ڲ������뷨����ʱ�жϣ��½��ز�ѯ����ʱ�䣩
		if (1 == IR_BT)												//ң�ؼ��
		{
			KeyHandle();      										//ң�صİ�������		  
			IR_BT = 0;		        								//����Ч��־
		}
	}
}


/*******************************************************************************
 * @name     :void KeyHandle(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :ң�صİ�������
*******************************************************************************/
void KeyHandle(void)
{
	float fade = 0;
	switch (NEC[2])
	{
		case 0x0c:
			Cube_MODE = 1;											//����Ƶ��ģʽ
			clearAll();												//������л���
			break;													//����1
		case 0x18:
			Cube_MODE = 2;											//��������ģʽ
			NVIC_SystemReset();
//			mode = 0;
//			gCounter = 0;
//			modeNext = 0;
//			showLED = 0;
//			setLED = 0;
//			eNum = 0;
//			modeWait = 0;
//			modeWaitUp = 0;
//			rgb_dir = 0;
//			eCounter = 0;
//			eCounter2 = 0;
//			eInterval1 = 0;
//			eInterval2 = 0;
//			eFadeout = 0;
//			eFadeoutDone = 0;
//			counter = 0;
//	
//			SpeedSum = 0;
//			NumCount = 0;
//			pictrue_order = 0;										//������ʾ��˳��
//			clearAll();												//������л���
			break;													//����2
		case 0x5e:
			Cube_MODE = 3;											//����ҹ��ģʽ
//			clearAll();												//������л���
			light_red = 20;
			light_green = 0;
			light_blue = 0;											//ҹ����ɫ����
			break;													//����3
		case 0x08:
			if(3 == Cube_MODE)
			{
				if(light_red <= 240)
					light_red += 10;
			}
			break;													//����4
		case 0x1c:
			if(3 == Cube_MODE)
			{
				if(light_green <= 240)
					light_green += 10;
			}
			else if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = 0;
				Add_Z = 1;            								//λ��ƫ����
			}
			break;													//����5
		case 0x5a:
			if(3 == Cube_MODE)
			{
				if(light_blue <= 240)
					light_blue += 10;
			}
			break;													//����6
		case 0x42:
			if(3 == Cube_MODE)
			{
				if(light_red >= 10)
					light_red -= 10;
			}
			break;													//����7
		case 0x52:
			if(3 == Cube_MODE)
			{
				if(light_green >= 10)
					light_green -= 10;
			}
			else if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = 0;
				Add_Z = -1;            								//λ��ƫ����
			}
			break;													//����8
		case 0x4a:
			if(3 == Cube_MODE)
			{
				if(light_blue >= 10)
					light_blue -= 10;
			}
			break;													//����9
		case 0x16:
			Cube_MODE = 0;											//������λ��ģʽ
			clearAll();												//������л���
			break;													//����0
		case 0x19:
			// -key
			if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = -1;
				Add_Z = 0;            								//λ��ƫ����
			}
			else
			{
				fade = fadeMax;    // don't change directly as other IRQ may need fadeMax
				if (fade < 20) 
					fade -= 3;
				else 
					fade -= 10;
				
				if (fade > 50) 
					fade -= 10;
				
				if (fade < 3) 
					fade = 3;
				fadeMax = fade;
			}
			break;													//-��
		case 0x0d:
			Cube_MODE = 4;											//����̰����ģʽ
			SpeedSum = 0;
			NumCount = 0;
			clearAll();												//������л���
			Snake_Start();											//�����ʼ��
			Snake_Above();											//��ʳ�ﲢ���ж�ʳ���Ƿ�����������
			Snake_Show(10, 1, 0, 0, 10, 0);							//̰���ߵ���ʾ����
			break;													//OK��/C��
		case 0x07:
			// rew key
			if(0 == Cube_MODE)
			{
				if(tf_readRead < 16)
					tf_readRead += 2;
			}
			else if(4 == Cube_MODE)
			{
				Add_X = -1;
				Add_Y = 0;
				Add_Z = 0;            								//λ��ƫ����
			}
			else
				prevGraphic();
			break;													//���˼�
		case 0x15:
			// pause key
			if(0 == Cube_MODE)
			{
				tf_readStop = !tf_readStop;
			}
			else
			{
				if (power == 2)
					power = 1;
				else if (power == 1)
					power = 2;
			}
			break;													//��ͣ��
		case 0x09:
			// ff key
			if(0 == Cube_MODE)
			{
				if(tf_readRead > 4)
					tf_readRead -= 2;
			}
			else if(4 == Cube_MODE)
			{
				Add_X = 1;
				Add_Y = 0;
				Add_Z = 0;            								//λ��ƫ����
			}
			else
				nextGraphic();
			break;													//�����
		case 0x44:
			break;													//MODE��/TEST��
		case 0x40:
			// + key
			if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = 1;
				Add_Z = 0;            								//λ��ƫ����
			}
			else
			{
				fade = fadeMax;   // don't change directly as other IRQ may need fadeMax
				if (fade < 20) 
					fade += 3;
				else 
					fade += 10;
				
				if (fade > 50)
					fade += 10;
				if (fade > 100) 
					fade = 100;
				fadeMax = fade;
			}
			break;													//+��
		case 0x43:
			break;													//���ؼ�
		case 0x45:
			// power key
			if (power == 0)
			{
				power = 1;
				setAll(BLACK);
			}
			else
			{
				setAll(BLACK);
				delay(10);
				power = 0;
			}
			break;													//Power
		case 0x47:
			break;													//MENU��
		default:
			break;
	}
}




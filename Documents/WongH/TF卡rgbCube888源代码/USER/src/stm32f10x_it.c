#include "stm32f10x_it.h"
#include "time_show.h"
#include "graphics.h"

#define TIMERSR 	(TIM_IT_Update ^ 0xffff)

const uint8_t DigitChar[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
const uint16_t ScanTimeData[8] = {ScanTime << 0,ScanTime << 1,ScanTime << 2,ScanTime << 3,
								  ScanTime << 4,ScanTime << 5,ScanTime << 6,ScanTime << 7};

void TIM2_IRQHandler(void)
{
	static uint8_t Layer = 0;							//LED�Ĳ�ɨ�����
	static uint8_t Digit = 0;							//������ʾ��ʱ��+λ��
	if ((TIM2->SR & TIM_IT_Update) != (uint16_t)RESET && 
		(TIM2->DIER & TIM_IT_Update) != (uint16_t)RESET)	//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM2->SR = TIMERSR;								//���TIMx���жϴ�����λ:TIM �ж�Դ 

		if (++Layer >= 8)								//888�Ĺ�������Ҫɨ��8��
		{
			Layer = 0;									//��ɨ�������0
			if (++Digit >= 8)							//����4���Ҷȵ���
				Digit = 0;								//�Ҷȵ��ڱ�����0
			//TIM_SetAutoreload(TIM2, ScanTime << Digit); //д���µ�LED�������ֵ		
			TIM2->ARR = ScanTimeData[Digit];			//д���µ�LED�������ֵ		
		}

		rgb_OE_SET;										//�ر����ݵ�ʹ�ܶ�
		Anode(7 - Layer);								//��ѡ��
		Send_Data(DigitChar[Digit], Layer);				//����ˢ��				
		rgb_OE_RESET;									//�����ݵ�ʹ�ܶ�

		randCount++;									//���������������
	}
}


#define	LED_ON   	GPIOB->BSRR = 1 << 6   
#define LED_OFF 	GPIOB->BRR = 1 << 6  
uint8_t flickerFlag  = 0;

void TIM3_IRQHandler(void)
{
	static uint16_t flagCount = 0;
	static uint8_t tf_num = 0;
	if ((TIM3->SR & TIM_IT_Update) != (uint16_t)RESET && 
		(TIM3->DIER & TIM_IT_Update) != (uint16_t)RESET) 	//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM3->SR = TIMERSR;								//���TIMx���жϴ�����λ:TIM �ж�Դ 

		switch (Cube_MODE)								//ѡ����ʾ��ģʽ
		{
			case 0:
				if(++tf_num >= tf_readRead)
				{
					tf_num = 0;
					if(1 == tf_readflag)
						tf_readflag = 2;
				}
				break;
			case 1:
				break;
			case 2:
				controlGraphics();
				//Cartoon();							//������ʾ
			case 3:										//ҹ��ģʽ
				break;
			case 4:
				Snake_scrolling();						//����ʾ�ƶ�
				break;
		}

		if(++flagCount >= 100)							//500ms
		{
			flickerFlag = !flickerFlag;	
			flagCount = 0;
			
			if(flickerFlag)
				LED_ON;
			else
				LED_OFF;
		}
	}
}


void TIM4_IRQHandler(void)
{
	static uint16_t fft_Num = 0;
	if ((TIM4->SR & TIM_IT_Update) != (uint16_t)RESET && 
		(TIM4->DIER & TIM_IT_Update) != (uint16_t)RESET) 	//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM4->SR = TIMERSR;									//���TIMx���жϴ�����λ:TIM �ж�Դ 

		fftIn[fft_Num] = Get_ADC(ADC_Channel_2);
		if (++fft_Num > fft_N)
			fft_Num = 0;
	}
}


/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
  /*void PPP_IRQHandler(void)
  {
  }*/

  /**
	* @}
	*/


	/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

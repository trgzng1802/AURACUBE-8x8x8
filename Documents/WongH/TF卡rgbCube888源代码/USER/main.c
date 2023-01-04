#include "stm32f10x.h"
#include "led.h"
#include "timer.h"
#include "calculate.h"
#include "snake.h"
#include "adc.h"
#include "fft.h"
#include "ir_nec.h"
#include "Time_Show.h"
#include "graphics.h"


#include "malloc.h"  
#include "exfuns.h"
#include "MMC_SD.h" 
#include "fattester.h"	 


#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"	 



void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			//����GPIOx��ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}


void SystemClock(uint32_t pllMull)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	
	RCC_DeInit();
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);
	do
	{
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;  
	} while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CR & RCC_CR_HSERDY) != RESET)
		HSEStatus = (uint32_t)0x01;
	else
		HSEStatus = (uint32_t)0x00;

	if (HSEStatus == (uint32_t)0x01)
	{
		FLASH->ACR |= FLASH_ACR_PRFTBE;
		FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
		RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | pllMull);

		RCC->CR |= RCC_CR_PLLON;

		while((RCC->CR & RCC_CR_PLLRDY) == 0) { }

		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08) { }
	}
}

void ID_ms(uint32_t ms)
{
	uint32_t i;

	for (i = 0; i < SystemCoreClock / (300 * 1000 / ms); i++)
	{
	}
}

volatile uint32_t CPUID[3];


//���CPUID�Ƿ��Ѿ�ע�ᣬû��ע��ֱ�ӿ�סCPU������
void CheckCPU_ID(void)
{
	uint32_t i = 0;
	uint32_t ID_0 = 0, ID_1 = 0, ID_2 = 0, MiWen = 0;
	CPUID[0] = *(vu32*)(0x1FFFF7E8);
	CPUID[1] = *(vu32*)(0x1FFFF7EC);
	CPUID[2] = *(vu32*)(0x1FFFF7F0);
	
	ID_0 = (CPUID[0] ^ 0xffffffff) | CPUID[1];
	ID_1 = CPUID[1] | (CPUID[2] ^ 0xffffffff);
	ID_2 = (CPUID[2] ^ 0xffffffff) | (CPUID[0] ^ 0xffffffff);

	
	MiWen = (ID_0 ^ ID_1) ^ ID_2;
	
	//ID�Բ��ϣ�����û��ע��
	while (0XB83812EF != MiWen)							//ͼ��ID
	{
		SystemClock(RCC_CFGR_PLLMULL9);					//72M Ҫ���ò�������USB
		LED_Init();
		
		ID_ms(1800);
		USB_Port_Set(0); 								// USB�ȶϿ�
		ID_ms(700);
		USB_Port_Set(1);								// USB�ٴ�����
		Set_USBClock();
		USB_Interrupts_Config();
		USB_Init();
		while(1)
		{
			usb_printf("0X%8X\r\n",MiWen);
			i = 5000000;
			while(--i);
		}
	}
	//ID���ϣ������Ѿ�ע��
}


int main(void)
{
	uint8_t i = 0;
	
	CheckCPU_ID();						//���CPUID�Ƿ��Ѿ�ע�ᣬû��ע��ֱ�ӿ�סCPU������
	
	tf_readRead = 8;
	random8();
	setup();
	GPIO_Configuration();				//��ʼ��GPIO����
	NVIC_Configuration();				//�ж����ȼ��ķ�������
	IR_ENC_Init(128);					//�����߽����ʼ��
	LED_Init();
	
	fft_ADC_Init();						//��fft�ɼ������ݽ���ADC�ĳ�ʼ��
	Timer2_Init(ScanFosc, ScanTime);	//��ʱ����ʼ��  
	Timer3_Init(12800, 60);           	//������ʾ��ʱ����ʼ��	
	Timer4_Init(1280, 10);				//10K��ADC������           						


	exfuns_init();						//Ϊfatfs��ر��������ڴ�				 
	mem_init();							//��ʼ���ڴ��	
	
	i = 0;
	while(SD_Initialize())				//���SD��
	{
		if(++i > 60)
			break;
	}								   	
 	exfuns_init();						//Ϊfatfs��ر��������ڴ�				 
  	f_mount(fs[0],"0:",1); 				//����SD�� 

	Cube_MODE = 2;
	
	while (1)
	{
		if(1 != Cube_MODE)
			TIM_Cmd(TIM4, DISABLE); 
		else
			TIM_Cmd(TIM4, ENABLE); 
		
		
		if (0 == Cube_MODE)
		{
			mf_scan_files("0:\\rgbCUBE888");
		}
		else if (1 == Cube_MODE)
		{
			fft_Data();								//����fft��ADC�����ݲɼ�
			fft_Convert(fftData);					//N��fft���㺯��,fft����ת��������
			fft_powerMag();							//fft�������ֵ������fftOut�������
			fft_Display();							//fft���㴦��֮�����ʾ����
		}
		else if (2 == Cube_MODE)
		{
			while (2 == Cube_MODE)
			{
				loop();
			}
		}
		else if (3 == Cube_MODE)
		{
			ClearRGB(0,light_green);				//����ɫ��ֵ
			ClearRGB(2,light_blue);					//����ɫ��ֵ
			ClearRGB(1,light_red);					//����ɫ��ֵ
		}			
	}
}


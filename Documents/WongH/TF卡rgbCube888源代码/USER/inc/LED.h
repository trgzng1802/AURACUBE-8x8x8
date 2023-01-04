#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"
#include "stdlib.h"
#include "graphics.h"

extern uint8_t tf_readflag;
extern uint8_t tf_readRead;
extern uint8_t tf_readStop;

extern uint8_t Cube_MODE;													//����������ʾģʽ
extern uint8_t pictrue_order;												//������ʾ��˳��
extern uint32_t randCount;													//���������������
extern int16_t SpeedSum, NumCount;											//�����ٶȣ�˳��
extern uint8_t Color_red, Color_green, Color_blue;							//���������ɫ����
extern uint8_t light_red, light_green, light_blue;							//ҹ����ɫ����

typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} colour;


//����IO �ߵ�ƽ
#define	rgb_OE_SET    		GPIOB->BSRR = 1 << 15    
#define	rgb_ST_SET    		GPIOC->BSRR = 1 << 6    
#define	rgb_CLK_SET   		GPIOC->BSRR = 1 << 7    
#define	rgb_DAT_B_SET  		GPIOB->BSRR = 1 << 13   
#define	rgb_DAT_A_SET  		GPIOB->BSRR = 1 << 12   

#define	HC138_A_SET   		GPIOA->BSRR = 1 << 8    
#define	HC138_B_SET    		GPIOC->BSRR = 1 << 9    
#define	HC138_C_SET    		GPIOC->BSRR = 1 << 8    

	//����IO �͵�ƽ
#define	rgb_OE_RESET    	GPIOB->BRR = 1 << 15    
#define	rgb_ST_RESET    	GPIOC->BRR = 1 << 6    
#define	rgb_CLK_RESET   	GPIOC->BRR = 1 << 7   
#define	rgb_DAT_B_RESET  	GPIOB->BRR = 1 << 13   
#define	rgb_DAT_A_RESET  	GPIOB->BRR = 1 << 12   

#define	HC138_A_RESET		GPIOA->BRR = 1 << 8    
#define	HC138_B_RESET		GPIOC->BRR = 1 << 9    
#define	HC138_C_RESET    	GPIOC->BRR = 1 << 8    


#define ScanTime 		7													//������С��ɨ��ʱ��
#define ScanFosc 		90													//����ɨ��Ƶ��,128Mʱ��


// 3 LED Fields
extern uint8_t rgbled[3][1536];												//��ÿ��G��R��B����ɫ��ʽˢ��
extern uint8_t showLED;
extern uint8_t setLED;
extern uint8_t power;

extern const uint8_t rgb_order[192];										//rgbLED��ˢ��˳��,ˢ��˳��G��R��B
extern uint8_t setAdd;

void randomColour(uint8_t *gray_red, uint8_t *gray_green, uint8_t *gray_blue);	//ȡ���������ɫ����
uint32_t random(uint8_t max);
uint32_t random32(uint32_t max);
uint8_t random8(void);
void clearAll(void);														//������л���
void ClearRGB(char Crgb, int8_t rank);										//����ɫ��ֵ
void GPIO_Configuration(void);          									//��ʼ��GPIO
void NVIC_Configuration(void);												//�ж����ȼ��ķ������� 
void Anode(uint8_t temp);               									//��(����)��ѡ��
void Send_Data(uint8_t rgbBit, uint8_t layer);								//����ˢ��	

void set(uint8_t x, uint8_t y, uint8_t z, uint8_t R, uint8_t G, uint8_t B);
void setPlaneX(uint8_t x, uint8_t R, uint8_t G, uint8_t B);
void setPlaneY(uint8_t y, uint8_t R, uint8_t G, uint8_t B);
void setPlaneZ(uint8_t z, uint8_t R, uint8_t G, uint8_t B);
void clear(uint8_t x, uint8_t y, uint8_t z);
void setAll(uint8_t R, uint8_t G, uint8_t B);
void delay(uint32_t us);
void delay_ms(uint32_t ms);
void dimmer(uint8_t R, uint8_t G, uint8_t B, uint8_t *oR, uint8_t *oG, uint8_t *oB, float percent);
void brighter(uint8_t R, uint8_t G, uint8_t B, uint8_t *oR, uint8_t *oG, uint8_t *oB, float percent);
uint8_t getR(uint8_t x, uint8_t y, uint8_t z);
uint8_t getG(uint8_t x, uint8_t y, uint8_t z);
uint8_t getB(uint8_t x, uint8_t y, uint8_t z);
void hueToRGB(int hue, int brightness, uint8_t *oR, uint8_t *oG, uint8_t *oB);
int isClear(uint8_t buffer, uint8_t x, uint8_t y, uint8_t z);
int isClearAll(uint8_t buffer);

#define BLACK  0x00, 0x00, 0x00
#define BLUE   0x00, 0x00, 0xff
#define GREEN  0x00, 0xff, 0x00
#define ORANGE 0xff, 0x45, 0x00
#define PINK   0xff, 0x14, 0x44
#define PURPLE 0xff, 0x00, 0xff
#define RED    0xff, 0x00, 0x00
#define WHITE  0xff, 0xff, 0xff
#define YELLOW 0xff, 0xff, 0x00
#define OLIVE  0x66, 0xcc, 0x33
#define TURQUOISE 0x00, 0xce, 0xd1
#define AQUA   0x33, 0xcc, 0x99
#define GRAY   0x44, 0x44, 0x44
#endif


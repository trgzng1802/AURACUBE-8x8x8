#include "LED.h"

uint8_t tf_readflag = 0;
uint8_t tf_readRead = 0;
uint8_t tf_readStop = 0;

uint8_t Cube_MODE = 2;															//����������ʾģʽ
uint8_t pictrue_order = 0;														//������ʾ��˳��
uint32_t randCount = 0;															//���������������
int16_t SpeedSum = 0, NumCount = 0;												//�����ٶȣ�˳��
uint8_t Color_red = 0, Color_green = 0, Color_blue = 0;							//���������ɫ����
uint8_t light_red = 1, light_green = 0, light_blue = 0;							//ҹ����ɫ����
uint8_t setAdd = 0;
uint8_t showLED = 0;
uint8_t power = 1;
uint8_t setLED = 0;
uint8_t rgbled[3][1536];

void delay_ms(uint32_t ms)
{
	uint32_t i;

	for (i = 0; i < SystemCoreClock / (300 * 1000 / ms); i++)
	{
		if(2 != Cube_MODE)
			return;
	}
}

void delay(uint32_t us)
{
	uint32_t x;
	for (x = 0; x < us; x++)
	{
		delay_ms(15);
		if(2 != Cube_MODE)
			return;
	}
}

void setPlaneX(uint8_t x, uint8_t R, uint8_t G, uint8_t B)
{
	uint8_t y, z;
	for (y = 0; y < 8; y++)
	{
		for (z = 0; z < 8; z++)
			set(x, y, z, R, G, B);
	}
}

void setPlaneY(uint8_t y, uint8_t R, uint8_t G, uint8_t B)
{
	uint8_t x, z;
	for (x = 0; x < 8; x++)
	{
		for (z = 0; z < 8; z++)
			set(x, y, z, R, G, B);
	}
}

void setPlaneZ(uint8_t z, uint8_t R, uint8_t G, uint8_t B)
{
	uint8_t x, y;
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 8; x++)
			set(x, y, z, R, G, B);
	}
}

void dimmer(uint8_t R, uint8_t G, uint8_t B, uint8_t *oR, uint8_t *oG, uint8_t *oB, float percent)
{
	float calcR, calcG, calcB;
	calcR = R - (R*percent);
	calcG = G - (G*percent);
	calcB = B - (B*percent);
	if (calcR > 0)
		*oR = (int)calcR;
	else
		*oR = 0;
	if (calcG > 0)
		*oG = (int)calcG;
	else
		*oG = 0;
	if (calcB > 0)
		*oB = (int)calcB;
	else
		*oB = 0;
}

void brighter(uint8_t R, uint8_t G, uint8_t B, uint8_t *oR, uint8_t *oG, uint8_t *oB, float percent)
{
	if (R == 0 && G == 0 && B == 0)
	{
		R = 10;
		G = 10;
		B = 10;
	}
	if (R*(1 + percent) < 255)
		*oR = R*(1 + percent);
	else
		*oR = 255;
	if (G*(1 + percent) < 255)
		*oG = G*(1 + percent);
	else
		*oG = 255;
	if (B*(1 + percent) < 255)
		*oB = B*(1 + percent);
	else
		*oB = 255;
}

/*******************************************************************************
 * @name     :void randomColor(int8_t *gray_red,int8_t *gray_green,int8_t *gray_blue)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :ȡ���������ɫ����
*******************************************************************************/
void randomColour(uint8_t *gray_red, uint8_t *gray_green, uint8_t *gray_blue)
{
	while (1)																	//ȡ�������ɫ
	{
		srand(5 * randCount + 7 * TIM1->CNT);									//������
		*gray_red = (int8_t)(rand() % 256);										//ȡ�����
		srand(3 * randCount + 9 * TIM1->CNT);									//������
		*gray_green = rand() % 256;												//ȡ�����
		srand(7 * randCount + 5 * TIM1->CNT);									//������
		*gray_blue = rand() % 256;												//ȡ�����
		if (*gray_red != 0 || *gray_green != 0 || *gray_blue != 0)				//ȷ������ȡ��0,0,0
			break;
	}
}

uint32_t random(uint8_t max)
{
	return (rand() % max);
}

uint32_t random32(uint32_t max)
{
	return (rand() % max);
}

uint8_t random8()
{
	srand(5 * randCount + 7 * TIM1->CNT);
	return(rand() % 8);
}

/*******************************************************************************
 * @name     :void ClearRGB(char Crgb,int8_t rank)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :����ɫ��ֵ
*******************************************************************************/
void ClearRGB(char Crgb, int8_t rank)
{
	uint8_t i = 0, j = 0;
	Crgb %= 3;
	rank %= 256;
	for (j = 0; j < 8; j++)
		for (i = 0; i < 64; i++)
			rgbled[setLED][rgb_order[3 * i + Crgb] + 192 * j] = rank;
}


/*******************************************************************************
 * @name     :void Clear(uint16_t layerA)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :�������
*******************************************************************************/
void clearLayer(uint16_t layerA)
{
	uint16_t i = 0;
	layerA = 192 * layerA;
	for (i = 0; i < 192; i++)
		rgbled[setLED][i + layerA] = 0;
}

/*******************************************************************************
 * @name     :void ClearALL(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :������л���
*******************************************************************************/
void setAll(uint8_t R, uint8_t G, uint8_t B)
{
	uint16_t layerA = 0;
	char i, j = 0;
	for (i = 0; i < 8; i++)
	{
		layerA = 192 * i;
		for (j = 0; j < 64; j++)
		{
			rgbled[setLED][rgb_order[j * 3 + 1] + layerA] = R;
			rgbled[setLED][rgb_order[j * 3 + 0] + layerA] = G;
			rgbled[setLED][rgb_order[j * 3 + 2] + layerA] = B;
		}
	}
}

/*******************************************************************************
 * @name     :void ClearALL(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :������л���
*******************************************************************************/
void clearAll(void)
{
	char i = 0;
	for (i = 0; i < 8; i++)
		clearLayer(i);																//������л���*/
}

/*******************************************************************************
 * @name     :void NVIC_Configuration(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :���ȼ��������ȼ�����
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
}

/*******************************************************************************
 * @name     :void Anode(uint8_t temp)
 * @param    :temp�����ͨ���β�
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :��ѡ��
*******************************************************************************/
void Anode(uint8_t temp)
{
	//	switch(temp)
	//	{
	//		case 0: HC138_A_RESET; HC138_B_RESET; HC138_C_RESET; break;
	//		case 1: HC138_A_SET;   HC138_B_RESET; HC138_C_RESET; break;
	//		case 2: HC138_A_RESET; HC138_B_SET;   HC138_C_RESET; break;
	//		case 3: HC138_A_SET;   HC138_B_SET;   HC138_C_RESET; break;
	//		case 4: HC138_A_RESET; HC138_A_RESET; HC138_C_SET;   break;
	//		case 5: HC138_A_SET;   HC138_B_RESET; HC138_C_SET;   break;
	//		case 6: HC138_A_RESET; HC138_B_SET;   HC138_C_SET;   break;
	//		case 7: HC138_A_SET;   HC138_B_SET;   HC138_C_SET;   break;
	//	}

	if (temp & 0x01)
		HC138_A_SET;
	else
		HC138_A_RESET;

	if (temp & 0x02)
		HC138_B_SET;
	else
		HC138_B_RESET;

	if (temp & 0x04)
		HC138_C_SET;
	else
		HC138_C_RESET;
}

/*******************************************************************************
 * @name     :const uint8_t rgb_order[192]
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :ˢ�����ݵ�˳��
*******************************************************************************/
const uint8_t rgb_order[192] = 													//rgbLED��ˢ��˳��,ˢ��˳��G��R��B
{
191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176, 	167,166,165,164,163,162,161,160,
159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144, 	168,169,170,171,172,173,174,175,

143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128, 	119,118,117,116,115,114,113,112,
111,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96, 		120,121,122,123,124,125,126,127,

95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,	71,70,69,68,67,66,65,64,
63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48, 	72,73,74,75,76,77,78,79,

47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,	23,22,21,20,19,18,17,16,
15,14,13,12,11,10,9,8,7,5,4,6,3,2,1,0,				24,25,26,27,28,29,30,31,
};

/*******************************************************************************
 * @name     :void Send_Data(uint8_t rgbBit,uint8_t layerA)
 * @param    :rgbBit��4λ��ȵĵڼ�λ
 * @param    :layerA�����ݵĵڼ���
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :���ݵ�ˢ��
*******************************************************************************/
void Send_Data(uint8_t rgbBit, uint8_t layerA)
{
	// 5 bit colour - off for bit 6 to stop blowing chips !
	uint8_t i = 0, j = 0;
	uint16_t Sum = 0;
	Sum = layerA * 192;															//��������ݵ�λ��
	if (showLED != 3)
	{
		if (eNum & 8)
		{
			for (j = 0; j < 2; j++)
			{
				for (i = 0; i < 96; i++)
				{
					if ((rgbled[0][i + Sum]) & rgbBit || (rgbled[1][i + Sum]) & rgbBit)  // change this to >>2 and remove rgbBit !=5 to go to full resolution (6 bits)
						rgb_DAT_B_SET;													//Ϊ������ߵ�ƽ
					else
						rgb_DAT_B_RESET;												//Ϊ������͵�ƽ

					if ((rgbled[0][i + 96 + Sum]) & rgbBit || (rgbled[1][i + 96 + Sum]) & rgbBit)  // change this to >>2 and remove rgbBit !=5 to go to full resolution (6 bits)
						rgb_DAT_A_SET;													//Ϊ������ߵ�ƽ
					else
						rgb_DAT_A_RESET;												//Ϊ������͵�ƽ
					
					rgb_CLK_RESET;														//���õͣ�Ϊ�γ�������׼��
					rgb_CLK_SET;														//�øߣ��γ������أ���������		   
				}
			}
		}
		else
		{
			for (j = 0; j < 2; j++)
			{
				for (i = 0; i < 96; i++)
				{
					if ((rgbled[showLED][i + Sum]) & rgbBit)  // change this to >>2 and remove rgbBit !=5 to go to full resolution (6 bits)
						rgb_DAT_B_SET;													//Ϊ������ߵ�ƽ
					else
						rgb_DAT_B_RESET;												//Ϊ������͵�ƽ

					if ((rgbled[showLED][i + 96 + Sum]) & rgbBit)  // change this to >>2 and remove rgbBit !=5 to go to full resolution (6 bits)
						rgb_DAT_A_SET;													//Ϊ������ߵ�ƽ
					else
						rgb_DAT_A_RESET;												//Ϊ������͵�ƽ
					
					rgb_CLK_RESET;														//���õͣ�Ϊ�γ�������׼��
					rgb_CLK_SET;														//�øߣ��γ������أ���������		   
				}
			}
		}
	}
	else
	{
		rgb_DAT_B_RESET;															//Ϊ������͵�ƽ
		rgb_DAT_A_RESET;															//Ϊ������͵�ƽ
		for (j = 0; j < 2; j++)
		{
			for (i = 0; i < 96; i++)
			{
				rgb_CLK_RESET;															//���õͣ�Ϊ�γ�������׼��
				rgb_CLK_SET;															//�øߣ��γ������أ���������		   
			}
		}
	}
	rgb_ST_RESET;																	//��������������õ͵�ƽ���������ݱ����������������
	rgb_ST_SET;																		//������������øߵ�ƽ�������������
}

/*******************************************************************************
 * @name     :void ColorPoint(int8_t X,int8_t Y,int8_t Z,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut)
 * @brief    :X��x���λ��(��Χ0--7)
 * @param    :Y��y���λ��(��Χ0--7)
 * @param    :Z��z���λ��(��Χ0--7)
 * @param    :red����ɫ�Ĵ�С(��Χ0--255)
 * @param    :green����ɫ�Ĵ�С(��Χ0--255)
 * @param    :blue����ɫ�Ĵ�С(��Χ0--255)
 * @param    :Add_Cut�����ӻ��Ǽ��٣�0Ϊ���٣�����Ϊ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :���ѡ������ɫ����
*******************************************************************************/
void set(uint8_t x, uint8_t y, uint8_t z, uint8_t R, uint8_t G, uint8_t B)
{
	int count_i = 0, count_j = 0;
	x %= 8;													//����X�᲻����7
	y %= 8;													//����Y�᲻����7
	z %= 8;													//����Z�᲻����7
	count_i = (7 - x) * 3 + z * 24;									//���㵱ǰ�ĵ�������λ��
	count_j = 192 * (7 - y);										//���㵱ǰ�ĵ��ڵڼ���
	if (setAdd == 0)
	{
		rgbled[setLED][rgb_order[count_i + 1] + count_j] = R;		//д�뵱ǰ�ĵ�ĺ�ɫ
		rgbled[setLED][rgb_order[count_i + 0] + count_j] = G;		//д�뵱ǰ�ĵ����ɫ
		rgbled[setLED][rgb_order[count_i + 2] + count_j] = B;		//д�뵱ǰ�ĵ����ɫ	
	}
	else
	{
		rgbled[setLED][rgb_order[count_i + 1] + count_j] += R;		//д�뵱ǰ�ĵ�ĺ�ɫ
		rgbled[setLED][rgb_order[count_i + 0] + count_j] += G;		//д�뵱ǰ�ĵ����ɫ
		rgbled[setLED][rgb_order[count_i + 2] + count_j] += B;		//д�뵱ǰ�ĵ����ɫ			
		
		if (rgbled[setLED][rgb_order[count_i + 0] + count_j] > 255)
			rgbled[setLED][rgb_order[count_i + 0] + count_j] = 255;
		if (rgbled[setLED][rgb_order[count_i + 1] + count_j] > 255) 
			rgbled[setLED][rgb_order[count_i + 1] + count_j] = 255;
		if (rgbled[setLED][rgb_order[count_i + 2] + count_j] > 255) 
			rgbled[setLED][rgb_order[count_i + 2] + count_j] = 255;
	}
}

uint8_t getR(uint8_t x, uint8_t y, uint8_t z)
{
	uint8_t R = 0;
	int count_i = 0, count_j = 0;
	z %= 8;													//����X�᲻����7
	y %= 8;													//����Y�᲻����7
	z %= 8;													//����Z�᲻����7
	count_i = (7 - x) * 3 + z * 24;									//���㵱ǰ�ĵ�������λ��
	count_j = 192 * (7 - y);										//���㵱ǰ�ĵ��ڵڼ���
	R = rgbled[setLED][rgb_order[count_i + 1] + count_j];
	return (R);
}

uint8_t getG(uint8_t x, uint8_t y, uint8_t z)
{
	uint8_t G = 0;
	int count_i = 0, count_j = 0;
	z %= 8;													//����X�᲻����7
	y %= 8;													//����Y�᲻����7
	z %= 8;													//����Z�᲻����7
	count_i = (7 - x) * 3 + z * 24;									//���㵱ǰ�ĵ�������λ��
	count_j = 192 * (7 - y);										//���㵱ǰ�ĵ��ڵڼ���
	G = rgbled[setLED][rgb_order[count_i + 0] + count_j];
	return (G);
}

uint8_t getB(uint8_t x, uint8_t y, uint8_t z)
{
	uint8_t B = 0;
	int count_i = 0, count_j = 0;
	z %= 8;													//����X�᲻����7
	y %= 8;													//����Y�᲻����7
	z %= 8;													//����Z�᲻����7
	count_i = (7 - x) * 3 + z * 24;									//���㵱ǰ�ĵ�������λ��
	count_j = 192 * (7 - y);										//���㵱ǰ�ĵ��ڵڼ���
	B = rgbled[setLED][rgb_order[count_i + 2] + count_j];
	return (B);
}

int isClear(uint8_t buffer, uint8_t x, uint8_t y, uint8_t z)
{
	uint8_t ret;
	uint8_t oldSet;
	oldSet = setLED;
	setLED = buffer;
	if (getR(x, y, z) == 0 && getG(x, y, z) == 0 && getB(x, y, z) == 0) ret = 1;
	else ret = 0;
	setLED = oldSet;
	return(ret);
}

int isClearAll(uint8_t buffer)
{
	uint32_t i;
	uint8_t ret = 1;
	for (i = 0; i < 1536; i++)
	{
		if (rgbled[buffer][i] != 0) ret = 0;
	}
	return(ret);
}

void clear(uint8_t x, uint8_t y, uint8_t z)
{
	int count_i = 0, count_j = 0;
	x %= 8;													//����X�᲻����7
	y %= 8;													//����Y�᲻����7
	z %= 8;													//����Z�᲻����7
	count_i = (7 - x) * 3 + z * 24;									//���㵱ǰ�ĵ�������λ��
	count_j = 192 * (7 - y);										//���㵱ǰ�ĵ��ڵڼ���
	rgbled[setLED][rgb_order[count_i + 1] + count_j] = 0;			//д�뵱ǰ�ĵ�ĺ�ɫ
	rgbled[setLED][rgb_order[count_i + 0] + count_j] = 0;			//д�뵱ǰ�ĵ����ɫ
	rgbled[setLED][rgb_order[count_i + 2] + count_j] = 0;			//д�뵱ǰ�ĵ����ɫ	
}

void hueToRGB(int hue, int brightness, uint8_t *oR, uint8_t *oG, uint8_t *oB)
{
	unsigned int scaledHue = (hue * 6);
	unsigned int segment = scaledHue / 256; // segment 0 to 5 around the
											// color wheel
	unsigned int segmentOffset = scaledHue - (segment * 256); // position within the segment

	unsigned int complement = 0;
	unsigned int prev = (brightness * (255 - segmentOffset)) / 256;
	unsigned int next = (brightness *  segmentOffset) / 256;

	switch (segment) 
	{
		case 0:      // red
			*oR = brightness;
			*oG = next;
			*oB = complement;
			break;
		case 1:     // yellow
			*oR = prev;
			*oG = brightness;
			*oB = complement;
			break;
		case 2:     // green
			*oR = complement;
			*oG = brightness;
			*oB = next;
			break;
		case 3:    // cyan
			*oR = complement;
			*oG = prev;
			*oB = brightness;
			break;
		case 4:    // blue
			*oR = next;
			*oG = complement;
			*oB = brightness;
			break;
		case 5:      // magenta
		default:
			*oR = brightness;
			*oG = complement;
			*oB = prev;
			break;
	}
}

/*******************************************************************************
 * @name     :void GPIO_Configuration(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :GPIO�ӿ�ģʽ�����ó�ʼ��
*******************************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);//����GPIOx��ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}







#include "time_show.h"


/*******************************************************************************
 * @name     :void flash0(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :һ��һ�����ӣ���ʾ©������״
*******************************************************************************/
void flash0(uint8_t flashorder)
{
	if(++SpeedSum >= 5)																	//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount)
			clearAll();																	//������л���
		switch(NumCount/64)
		{
			case 0:
			case 1:
				randomColour(&Color_red,&Color_green,&Color_blue);						//ȡ�������ɫ
				Funnel_Shape(NumCount,Color_red,Color_green,Color_blue);				//һ�����γ�©������״
			break;
			case 2:
			case 3:
				Funnel_Shape(NumCount-128,0,0,0);										//һ��������©������״
			break;
			case 4:
				randomColour(&Color_red,&Color_green,&Color_blue);						//ȡ�������ɫ
				Funnel_Shape(NumCount-256,Color_red,Color_green,Color_blue);			//һ�����γ�©������״
				Funnel_Shape(383-NumCount,Color_red,Color_green,Color_blue);			//һ�����γ�©������״
			break;
			case 5:
				Funnel_Shape(383-NumCount,0,0,0);										//һ��������©������״
				Funnel_Shape(NumCount-256,0,0,0);										//һ��������©������״
			break;
			case 6:
				if(NumCount < 392)
					set(0,NumCount-384,0,Color_red,Color_green,Color_blue);	//���ѡ������ɫ����
				else
					line(0,0,NumCount-391,0,7,NumCount-391,Color_red,Color_green,Color_blue);	//3ά�����л���
			break;
		}

		if(++NumCount >= 399)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash1(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :ǰ����һ��һ�е��ƶ�
*******************************************************************************/
void flash1(uint8_t flashorder)
{
	if(++SpeedSum >= 10)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount)
		{
			clearAll();																	//������л���
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
		}
		Line_Change(NumCount,Color_red,Color_green,Color_blue);							//���������仯
		if(++NumCount >= 32)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash2(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :����һ����Ч��
*******************************************************************************/
void flash2(uint8_t flashorder)
{
	if(++SpeedSum >= 6)																	//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
//		if(0 == NumCount)
//		{
//			clearAll();																	//������л���
//			randomColor(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
//		}
		switch(NumCount/15)
		{
			case 0:
				if(0 != NumCount)
					Page(NumCount-1,0,0,0,0);											//ȥ��֮ǰ�Ļ�����
				Page(NumCount,Color_red,Color_green,Color_blue,0);					//����һ����Ч����һ��һ�����ʾ
			break;
			case 1:
				if(15 != NumCount)
					Page(30-NumCount,0,0,0,4);										//ȥ��֮ǰ�Ļ�����
				Page(29-NumCount,Color_red,Color_green,Color_blue,4);					//����һ����Ч����һ��һ�����ʾ
			break;
			case 2:
				if(30 != NumCount)
					Page(NumCount-31,0,0,0,5);										//ȥ��֮ǰ�Ļ�����
				Page(NumCount-30,Color_red,Color_green,Color_blue,5);					//����һ����Ч����һ��һ�����ʾ
			break;
			case 3:
				if(45 != NumCount)
					Page(60-NumCount,0,0,0,3);										//ȥ��֮ǰ�Ļ�����
				Page(59-NumCount,Color_red,Color_green,Color_blue,3);					//����һ����Ч����һ��һ�����ʾ
			break;
			case 4:
				if(60 != NumCount)
					Page(NumCount-61,0,0,0,2);										//ȥ��֮ǰ�Ļ�����
				Page(NumCount-60,Color_red,Color_green,Color_blue,2);					//����һ����Ч����һ��һ�����ʾ
			break;
			case 5:
				if(75 != NumCount)
					Page(90-NumCount,0,0,0,6);										//ȥ��֮ǰ�Ļ�����
				Page(89-NumCount,Color_red,Color_green,Color_blue,6);					//����һ����Ч����һ��һ�����ʾ
			break;
			case 6:
				if(90 != NumCount)
					Page(NumCount-91,0,0,0,7);										//ȥ��֮ǰ�Ļ�����
				Page(NumCount-90,Color_red,Color_green,Color_blue,7);					//����һ����Ч����һ��һ�����ʾ
			break;
			case 7:
				if(105 != NumCount)
					Page(120-NumCount,0,0,0,1);										//ȥ��֮ǰ�Ļ�����
				Page(119-NumCount,Color_red,Color_green,Color_blue,1);				//����һ����Ч����һ��һ�����ʾ
			break;
			default:
				if(NumCount < 127)
					line(0,0,127-NumCount,0,7,127-NumCount,BLACK);	//3ά�����л���
				else
					set(0,NumCount-127,0,Color_red,Color_green,Color_blue);	//���ѡ������ɫ����
			break;
		}
		if(++NumCount >= 134)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}	
	
/*******************************************************************************
 * @name     :void flash3(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :��ֱxy�������Ч��
*******************************************************************************/
void flash3(uint8_t flashorder)
{
	if(++SpeedSum >= 10)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount)
		{
			clearAll();																	//������л���
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
		}
		
		if(NumCount < 8)
			set(NumCount,7,7,Color_red,Color_green,Color_blue);				//���ѡ������ɫ����
		else if(NumCount < 15)
			line(0,7,14-NumCount,7,7,14-NumCount,Color_red,Color_green,Color_blue);	//3ά�����л���
		else if(NumCount < 41)
			Change_PlaneXY(NumCount-15,Color_red,Color_green,Color_blue);				//��ֱxy�������Ч��
		if(++NumCount >= 41)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash4(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :4����������תЧ��
*******************************************************************************/
void flash4(uint8_t flashorder)
{
	if(++SpeedSum >= 15)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount)
		{
			clearAll();																	//������л���
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
		}
		Box_Change(NumCount,Color_red,Color_green,Color_blue,0);						//4����������תЧ��
		if(++NumCount >= 108)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash5(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :DNA��תЧ��
*******************************************************************************/
void flash5(uint8_t flashorder)
{
	if(++SpeedSum >= 5)																	//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(15 == NumCount)
		{
			clearAll();																	//������л���
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
		}
		if(NumCount < 7)
			line(0,0,7-NumCount,7,0,7-NumCount,BLACK);		//3ά�����л���
		else if(NumCount < 15)
			set(14-NumCount,0,0,BLACK);				//���ѡ������ɫ����
		else if(NumCount < 23)
			set(NumCount-15,NumCount-15,0,Color_red,Color_green,Color_blue);	//���ѡ������ɫ����
		else if(NumCount < 30)
			line(0,0,NumCount-22,7,7,NumCount-22,Color_red,Color_green,Color_blue);	//3ά�����л���
		else if(NumCount < 285)
			DNA_Change(NumCount-30,Color_red,Color_green,Color_blue);					//DNA��תЧ��
		if(++NumCount >= 285)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash6(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :���˵ı仯Ч��
*******************************************************************************/
void flash6(uint8_t flashorder)
{
	if(++SpeedSum >= 10)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount)
		{
			clearAll();																	//������л���
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
		}
		Waveform(NumCount,Color_red,Color_green,Color_blue);							//���˵ı仯Ч��
		if(++NumCount >= 204)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash7(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :��ӡͼ��
*******************************************************************************/
void flash7(uint8_t flashorder)
{
	if(++SpeedSum >= 5)																	//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount%77)
		{
			clearAll();																	//������л���
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
		}
		print(NumCount,Dat_print+NumCount/77*8,Color_red,Color_green,Color_blue,1,0);	//��ӡͼ��
		if(++NumCount >= 1155)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash8(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :������Ļ
*******************************************************************************/
void flash8(uint8_t flashorder)
{
	if(++SpeedSum >= 15)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount)
		{
			clearAll();																	//������л���
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
		}
		scrollText(NumCount);
		//Mov_Show(NumCount,MathSum,Color_red,Color_green,Color_blue,1);					//������Ļ
		if(++NumCount >= 152)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

const uint8_t Circle[29]={
0,1,2,3,4,5,6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48,40,32,24,16,8,0
};
/*******************************************************************************
 * @name     :void flash9(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :����ƽ��
*******************************************************************************/
void flash9(uint8_t flashorder)
{
	char i,j;
	if(++SpeedSum >= 15)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount)
		{
			clearAll();																	//������л���
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
		}
		if(NumCount < 50)
		{
			switch(NumCount/29)
			{
				case 0:
					if(NumCount > 7)
					i = Circle[NumCount-8]%8;
					j = Circle[NumCount-8]/8;
					line(i,j,0,i,j,7,0,0,0);											//ȥ��֮ǰ��һ��
				case 1:
					i = Circle[NumCount%29]%8;
					j = Circle[NumCount%29]/8;
					line(i,j,0,i,j,7,Color_red,Color_green,Color_blue);				//3ά�����л���
				break;
			}
		}
		else if(NumCount < 56)
		{
			i = NumCount-49;
			line(1,0,i,6,0,i,0,0,0);												
			line(1,7,i,6,7,i,0,0,0);												
			line(0,1,i,0,6,i,0,0,0);												
			line(7,1,i,7,6,i,0,0,0);												
		}
		else if(NumCount < 62)
		{
			i = (NumCount-54)/2;
			Box(i,i,i,7-i,7-i,7-i,Color_red,Color_green,Color_blue,0,0);				//3ά�����л�����
		}
		else if(NumCount < 70)
		{
			i = (69-NumCount)/2;
			Box(i,i,i,7-i,7-i,7-i,0,0,0,0,0);											//3ά�����л�����
		}
			
		if(++NumCount >= 70)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash10(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :��ȡ����ͼƬ
*******************************************************************************/
void flash10(uint8_t flashorder)
{
	char i,j;
	int mm,kk;
	if(++SpeedSum >= 15)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount%20)
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
			
		for(j = 0; j < 8; j++)
		{
			mm = 192*j;
			for(i = 0; i < 64; i++)
			{
				kk = 3*i;
		//		if(Shape[i+NumCount%154*64] & (0x80 >> j))
				{
					rgbled[setLED][rgb_order[kk+1]+mm] = Color_red; 			
					rgbled[setLED][rgb_order[kk+0]+mm] = Color_green;			
					rgbled[setLED][rgb_order[kk+2]+mm] = Color_blue;	
				}	
		//		else
				{
					rgbled[setLED][rgb_order[kk+0]+mm] = 0; 			
					rgbled[setLED][rgb_order[kk+1]+mm] = 0;			
					rgbled[setLED][rgb_order[kk+2]+mm] = 0;	
				}
			}				
		}		
		
		if(++NumCount >= 308)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash11(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :ģ�Ⲩ��ͼ��
*******************************************************************************/
void flash11(uint8_t flashorder)
{
	char i,j;
	int mm,kk;
	if(++SpeedSum >= 15)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		if(0 == NumCount%20)
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
			
		for(j = 0; j < 8; j++)
		{
			mm = 192*j;
			for(i = 0; i < 64; i++)
			{
				kk = 3*i;
	//			if(Waveled[i+NumCount%29*64] & (0x80 >> j))
				{
					rgbled[setLED][rgb_order[kk+1]+mm] = Color_red; 			
					rgbled[setLED][rgb_order[kk+0]+mm] = Color_green;			
					rgbled[setLED][rgb_order[kk+2]+mm] = Color_blue;	
				}	
	//			else
				{
					rgbled[setLED][rgb_order[kk+0]+mm] = 0; 			
					rgbled[setLED][rgb_order[kk+1]+mm] = 0;			
					rgbled[setLED][rgb_order[kk+2]+mm] = 0;	
				}
			}				
		}		
		
		if(++NumCount >= 116)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void flash12(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :��ȡ��������
*******************************************************************************/
void flash12(uint8_t flashorder)
{
	char i,j;
	if(++SpeedSum >= 15)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
			
		for(j = 0; j < 8; j++)
		{
//			mm = 192*j;
	//		nn = 32*j;
			for(i = 0; i < 32; i++)
			{
		//		kk = 6*i;
	/*			rgbled[rgb_order[kk+0]+mm] =  Dmax[768*NumCount+i+nn] & 0x0f;			//(��ɫ)ȡ���ݵĵ�4λ				
				rgbled[rgb_order[kk+3]+mm] = (Dmax[768*NumCount+i+nn] >> 4)& 0x0f;		//(��ɫ)ȡ���ݵĸ�4λ				
				rgbled[rgb_order[kk+1]+mm] =  Dmax[768*NumCount+i+nn+256] & 0x0f;		//(��ɫ)ȡ���ݵĵ�4λ				
				rgbled[rgb_order[kk+4]+mm] = (Dmax[768*NumCount+i+nn+256] >> 4)& 0x0f;	//(��ɫ)ȡ���ݵĸ�4λ				
				rgbled[rgb_order[kk+2]+mm] =  Dmax[768*NumCount+i+nn+512] & 0x0f;		//(��ɫ)ȡ���ݵĵ�4λ				
				rgbled[rgb_order[kk+5]+mm] = (Dmax[768*NumCount+i+nn+512] >> 4)& 0x0f;	//(��ɫ)ȡ���ݵĸ�4λ				*/
			}				
		}					

		if(++NumCount >= 275)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}




/*******************************************************************************
 * @name     :void BOX_move(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :��������ƶ����仯
*******************************************************************************/
/*void BOX_move(uint8_t flashorder)
{
	static int8_t colorR1,colorR2,colorR3,colorR4,colorG1,colorG2,colorG3,colorG4,colorB1,colorB2,colorB3,colorB4;
	int i,j;
	if(++SpeedSum >= 30)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		
		if(0 == NumCount || 23 == NumCount || 63 == NumCount || 87 == NumCount)
		{
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
			if(0 == NumCount)
			{
				randomColour(&colorR1,&colorG1,&colorB1);								//ȡ�������ɫ
				randomColour(&colorR2,&colorG2,&colorB2);								//ȡ�������ɫ
				randomColour(&colorR3,&colorG3,&colorB3);								//ȡ�������ɫ
				randomColour(&colorR4,&colorG4,&colorB4);								//ȡ�������ɫ
			}
		}
			
		clearAll();																		//������л���
		if(NumCount < 23)
		{
			i = 12*NumCount;
			Box(BoxDat[i+0] & 0x0f,BoxDat[i+1] & 0x0f,BoxDat[i+2] & 0x0f,
				BoxDat[i+0] >> 4,BoxDat[i+1] >> 4,BoxDat[i+2] >> 4,colorR1,colorG1,colorB1,1,0);				//3ά�����л�����
			Box(BoxDat[i+3] & 0x0f,BoxDat[i+4] & 0x0f,BoxDat[i+5] & 0x0f,
				BoxDat[i+3] >> 4,BoxDat[i+4] >> 4,BoxDat[i+5] >> 4,colorR2,colorG2,colorB2,1,0);				//3ά�����л�����
			Box(BoxDat[i+6] & 0x0f,BoxDat[i+7] & 0x0f,BoxDat[i+8] & 0x0f,
				BoxDat[i+6] >> 4,BoxDat[i+7] >> 4,BoxDat[i+8] >> 4,colorR3,colorG3,colorB3,1,0);				//3ά�����л�����
			Box(BoxDat[i+9] & 0x0f,BoxDat[i+10] & 0x0f,BoxDat[i+11] & 0x0f,
				BoxDat[i+9] >> 4,BoxDat[i+10] >> 4,BoxDat[i+11] >> 4,colorR4,colorG4,colorB4,1,0);				//3ά�����л�����
		}
		else if(NumCount < 167)
		{
			if(NumCount < 95)
			{
				i = 207+3*NumCount;							//i = 12*23+3*(NumCount-23);
				j = (NumCount-23)/8;
			}
			else if(NumCount < 167)
			{
				i = 3*NumCount-9;							//i = 12*23+3*(NumCount-95);
				j = (NumCount-95)/8;
			}
			switch(j)
			{
				case 2:
				case 5:
				case 8:
					set(BoxDat[i+0],BoxDat[i+1],BoxDat[i+2],Color_red,Color_green,Color_blue);						//���ѡ������ɫ����
				break;
				default:
					if(NumCount < 95)
						Box(BoxDat[i+0] & 0x0f,BoxDat[i+1] & 0x0f,BoxDat[i+2] & 0x0f,
							BoxDat[i+0] >> 4,BoxDat[i+1] >> 4,BoxDat[i+2] >> 4,Color_red,Color_green,Color_blue,1,0);		//3ά�����л�����
					else	
						Box(BoxDat[i+0] & 0x0f,BoxDat[i+1] & 0x0f,BoxDat[i+2] & 0x0f,
								BoxDat[i+0] >> 4,BoxDat[i+1] >> 4,BoxDat[i+2] >> 4,Color_red,Color_green,Color_blue,0,0);	//3ά�����л�����
				break;
			}
		}
		
		if(++NumCount >= 167)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}
*/

void Line_Cut(uint8_t mode,uint8_t size,int8_t red,int8_t green,int8_t blue)
{
	size %= 3;
	line(2-size,3-size,mode,2-size,4+size,mode,red,green,blue);
	line(3-size,2-size,mode,4+size,2-size,mode,red,green,blue);
	line(3-size,5+size,mode,4+size,5+size,mode,red,green,blue);
	line(5+size,3-size,mode,5+size,4+size,mode,red,green,blue);
}

void Line_Cut1(uint8_t mode,uint8_t size,int8_t red,int8_t green,int8_t blue)
{
	size %= 3;
	//��������
//	Line(mode,0,size,mode,3,size,red,green,blue,1);
//	Line(mode,2-size,4,mode,2-size,7,red,green,blue,1);
//	Line(mode,4,7-size,mode,7,7-size,red,green,blue,1);
//	Line(mode,5+size,0,mode,5+size,3,red,green,blue,1);
	//����ǰ��
	line(0,mode,size,3,mode,size,red,green,blue);
	line(2-size,mode,4,2-size,mode,7,red,green,blue);
	line(4,mode,7-size,7,mode,7-size,red,green,blue);
	line(5+size,mode,0,5+size,mode,3,red,green,blue);
}

/*******************************************************************************
 * @name     :void Line_AddCut(uint8_t flashorder)
 * @param    :flashorder��ѡ����һ�ε���ʾ����
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :���������Ӽ���
*******************************************************************************/
void Line_AddCut(uint8_t flashorder)
{
	char i,j;
	int Number;
	if(++SpeedSum >= 8)																	//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		
		if(0 == NumCount || 264 == NumCount)
		{
			clearAll();																	//������л���
			randomColour(&Color_red,&Color_green,&Color_blue);							//ȡ�������ɫ
			Color_red++;																//ȷ��ÿ����ɫ����
			if(Color_red > 15)
				Color_red = 15;
			Color_green++;
			if(Color_green > 15)
				Color_green = 15;
			Color_blue++;
			if(Color_blue > 15)
				Color_blue = 15;
		}
		
		if((NumCount >= 0 && NumCount < 192) || (NumCount >= 264 && NumCount < 456))
		{
			i = NumCount%8;
			j = NumCount/8;
			if(NumCount < 192)
				Number = NumCount/64;
			else
				Number = (NumCount-72)/64;
//				Number = (NumCount-264)/64+3;
			//����
			switch(Number)
			{
				case 0:
					line(0,i,j,7,i,j,Color_red,0,0);									//3ά�����л���,���Ӻ�ɫ
				break;
				case 1:
					line(0,7-i,15-j,7,7-i,15-j,Color_red,Color_green,0);				//3ά�����л���,������ɫ
				break;
				case 2:
					line(0,i,j-16,7,i,j-16,Color_red,Color_green,Color_blue);			//3ά�����л���,������ɫ
				break;
				
				case 3:
					line(i,0,j-33,i,7,j-33,0,0,Color_blue);							//3ά�����л���,������ɫ
				break;
				case 4:
					line(48-j,0,7-i,48-j,7,7-i,Color_red,0,Color_blue);				//3ά�����л���,���Ӻ�ɫ
				break;
				case 5:
					line(j-49,0,i,j-49,7,i,Color_red,Color_green,Color_blue);			//3ά�����л���,������ɫ
				break;
			}
		}
		else if((NumCount >= 192 && NumCount < 264) || (NumCount >= 456 && NumCount < 528))
		{
			if(NumCount < 264)
			{
				j = 2-NumCount%3;
				i = NumCount/3;
			}
			else
			{
				j = NumCount/8;
				i = NumCount%8;
			}
			//����
			switch(NumCount/24)
			{
				case 8:
					Line_Cut(i-64,j,0,Color_green,Color_blue);							//ȥ����ɫ
				break;
				case 9:
					Line_Cut(79-i,j,0,Color_green,0);									//ȥ����ɫ
				break;
				case 10:
					Line_Cut(i-80,j,0,0,0);												//ȥ����ɫ
				break;
				
				case 19:
					Line_Cut1(i,49-j,Color_red,0,Color_blue);							//ȥ����ɫ
				break;
				case 20:
					Line_Cut1(7-i,52-j,0,0,Color_blue);									//ȥ����ɫ
				break;
				case 21:
					Line_Cut1(i,55-j,0,0,0);											//ȥ����ɫ
				break;
			}
		}
		
		if(++NumCount >= 528)															//�����Ĵ���
		{
			NumCount = 0;
			pictrue_order = flashorder;													//������һ������
		}
	}
}

/*******************************************************************************
 * @name     :void Cartoon(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :������ʾ
*******************************************************************************/
void Cartoon(void)
{
	switch(pictrue_order)
	{
		case 0:
			flash7(1);																	//��ӡͼ��
		break;
		case 1:
			flash9(2);																	//����ƽ��
		break;
		case 2:
			flash9(3);
			//BOX_move(3);																//��������ƶ����仯
		break;
		case 3:
			flash0(4);																	//©������״
		break;
		case 4:
			flash2(5);																	//����һ����Ч��
		break;
		case 5:
			flash4(6);																	//4����������תЧ��
		break;
		case 6:
			flash3(7);																	//��ֱxy�������Ч��
		break;
		case 7:
			flash5(8);																	//DNA��תЧ��
		break;
		case 8:
			flash6(9);																	//���˵ı仯Ч��
		break;
		case 9:
			flash11(10);																//ģ�Ⲩ��ͼ��
		break;
		case 10:
			Line_AddCut(11);															//���������Ӽ���
		break;
		case 11:
			flash8(12);																	//������Ļ
		break;
		case 12:
			flash12(13);																//��ȡ��������
		break;
		case 13:
			flash10(1);																	//��ȡ������ʾͼƬ
		break;
	}
//			flash1(0);																	//���������仯
}

/*******************************************************************************
 * @name     :void ReadW25Q64(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :��ȡ�ڴ����������
*******************************************************************************/
void ReadW25Q64(void)
{
	if(++SpeedSum >= 10)																//�ٶȿ���
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
//		SPI_Flash_Read(Read_Buf,4096*NowSection+768*W25QxxAddress+3,768);				//��ȡflash��һ���Զ��������ݣ�����ÿ�ζ�����ַ�����Ч��
//		AxesConvert();																	//������ת������������
//		W25QxxAddress++;
//		if(W25QxxAddress >= W25QxxFrame)												//�ж�һ��������Ҫ��ʾ��֡��
//		{
//			W25QxxAddress = 0;															//��ǰ�������ĵ�ַ��0	
//			NowSection++;																//��ǰ����������	
//			
//			SPI_Flash_Read(W25QxxTempAA,4096*NowSection,3);   							//��ȡflash
//			W25QxxFrame = W25QxxTempAA[2];												//����ÿ��������Ҫ��ʾ��֡��
//			//W25QxxSection = W25QxxTempAA[0]+(W25QxxTempAA[1] << 8);					//������Ҫ��ȡ����������
//			
//			if(NowSection >= W25QxxSection)												//�ж������Ƿ�����Ҫ��ʾ�����ֵ
//			{
//				NowSection = 0;
//				SPI_Flash_Read(W25QxxTempAA,0,3);   									//��ȡflash
//				W25QxxFrame = W25QxxTempAA[2];											//����ÿ��������Ҫ��ʾ��֡��
//				W25QxxSection = W25QxxTempAA[0]+(W25QxxTempAA[1] << 8);					//������Ҫ��ȡ����������
//			}
//		}	
	}			
}

/*******************************************************************************
 * @name     :void Snake_scrolling(void)
 * @author   :ͼ��ʵ���ҡ�ͼ��
 * @details  :����ʾ���ƶ�
*******************************************************************************/
void Snake_scrolling(void)																
{
	if(++SpeedSum >= 40)																//�����ƶ����ٶ�
	{
		SpeedSum = 0;																	//�ٶȿ��Ʊ�����0
		Snake_Show(200,10,0,0,200,0);														//̰���ߵ���ʾ����
		Snake_Move();																	//̰���ߵ������ƶ�
		if(1 == Collide())																//�ж�̰�����Ƿ�����ײ
		{
			Snake_Start();																//�����ʼ��
			Snake_Above();																//��ʳ�ﲢ���ж�ʳ���Ƿ�����������
		}
		Snake_Feed();																	//�ж��Ƿ��ʳ��Ծͳ��ȼ�1�����򲻼ӣ������ж��Ƿ�ﵽ��󳤶�
	}
}















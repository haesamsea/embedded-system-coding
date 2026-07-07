#include "device_driver.h"

void Key_Poll_Init(void)
{
	Macro_Set_Bit(RCC->APB2ENR, 3);
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 24);
}

#define COUNT_FOR_CHAT 		20000

static int Key_Check_Input(void)
{
	return ~Macro_Extract_Area(GPIOB->IDR, 0x3, 6) & 0x3;
}

/*
아무 키가 안눌렸으면 0
key0이 눌려있으면 1
key1이 눌려있으면 2
key가 둘다 눌려있으면 3
*/
int Key_Get_Pressed(void)
{
	unsigned int i, k;

	for(;;)
	{
		k = Key_Check_Input();
		for(i=0; i<COUNT_FOR_CHAT; i++)
		{
			if(k != Key_Check_Input())
			{
				break;
			}
		}
		if(i == COUNT_FOR_CHAT) break;
	}
	return k;
}

/*key가 눌렸으면 대기 하나도 안눌리면 return*/
void Key_Wait_Key_Released(void)
{
	while(Key_Get_Pressed());
}

/*key가 눌릴때까지 대기 눌리면 key값 return*/
int Key_Wait_Key_Pressed(void)
{
	int k;

	while((k = Key_Get_Pressed()) == 0);
	return k;
}

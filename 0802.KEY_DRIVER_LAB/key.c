#include "device_driver.h"

void Key_Poll_Init(void)
{
	Macro_Set_Bit(RCC->APB2ENR, 3);
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 24);
}

static int Key_Check_Input(void)
{
	return Macro_Extract_Area(~GPIOB->IDR, 0x3, 6);
}

int Key_Get_Pressed(void)
{
	/* N 만큼 같은 값이 읽혀야 Key 값으로 판정 */
	unsigned int i, k;
	for (;;) {
		k = Key_Check_Input();
		for (i = 0; i < N; i++) {
			if (k != key_Check_Input()) break;
		}
		if (i = N) break;
	}
}

void Key_Wait_Key_Released(void)
{
	// KEY눌리면 함수에 대기, 하나도 안눌리면 RETURN
	while (Key_Get_Pressed());
	return;
}

int Key_Wait_Key_Pressed(void)
{
	int key_val;
	//KEY 눌릴때까지 대기, 눌리면 KEY값 RETURN
	do {
		key_val = Key_Get_Pressed();
	} while (key_val == 0);
	
	return key_val;
}
 
#include "device_driver.h"

void LED_Init(void)
{
	/* 다음 코드는 수정하지 마시오 */
	Macro_Set_Bit(RCC->APB2ENR, 3);
	/*LED PB[9:8]을 출력으로 설정, 초기 모두 OFF*/
	Macro_Write_Block(GPIOB->CRH, 0XFF, 0X66, 0);
	Macro_Set_Area(GPIOB->ODR, 0X3, 8);
}

void LED_Display(unsigned int num)
{	
	/*
	num[1:0] == pb[9:8]에 대응
          |led0 | led1 |
	00 -> | off | off  |
	01 -> | on  | off  |
	10 -> | off | on   |
	11 -> | on  | on   |
	*/
	Macro_Write_Block(GPIOB->ODR, 0X3, ~num, 8);
}

void LED_All_On(void)
{
	Macro_Clear_Area(GPIOB->ODR, 0X3, 8);
}

void LED_All_Off(void)
{
	Macro_Set_Area(GPIOB->ODR, 0X3, 8);
}

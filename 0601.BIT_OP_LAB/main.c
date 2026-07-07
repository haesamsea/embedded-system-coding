#include "device_driver.h"

#if 0

void Main(void)
{
	RCC->APB2ENR |= (1<<3);

	GPIOB->CRH = 0x66 << 0;
	GPIOB->ODR = 0x1 << 8;
}

#endif

#if 0

void Main(void)
{
	/* 이 부분은 임의로 바꾸지 마시오 */
	RCC->APB2ENR |= (1<<3);

	/* 비트 연산을 이용하여 LED0을 ON, LED1을 OFF로 하는 코드를 설계하시오 */




}

#endif

/* Bit 연산 Macro 활용 */

#if 0

void Main(void)
{
	/* 이 부분은 수정하지 말 것 */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	/* Macro를 이용하여 LED0을 ON, LED1을 OFF로 하는 코드를 설계하시오 */



}

#endif

/* Bit 연산 Macro 활용 LED Toggling */

#if 1

void Main(void)
{
	volatile int i;

	/* 이 부분은 수정하지 말 것 */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	/* 매크로를 이용하여 초기에 LED 모두 OFF */
	Macro_Write_Block(GPIOB->CRH, 0XFF, 0X66, 0);
	Macro_Set_Area(GPIOB->ODR, 0X3, 8);

	for(;;)
	{
	/* LED 반전 및 Delay, Delay는 0x80000으로 설정 */
		Macro_Invert_Area(GPIOB->ODR, 0X3, 8);
		
		for (i = 0; i < 0x80000; i++);
	}
}

#endif

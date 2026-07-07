#include "device_driver.h"

#if 1

/* 반드시 Option.h의 조건부 컴파일로 변경해야 한다 */

void Main(void)
{
	LED_Init();
	Uart_Init(115200);
	Uart1_Printf("SysClock = 8MHz(HSI)\n");

	for(;;)
	{
		volatile int i;

		LED_All_On();
		for(i=0; i<0x100000; i++);
		LED_All_Off();
		for(i=0; i<0x100000; i++);
		Uart1_Printf(".");
	}
}

#endif

#if 0

/* 반드시 Option.h의 조건부 컴파일로 변경해야 한다 */

void Main(void)
{
	Clock_Init();

	LED_Init();
	Uart_Init(115200);
	Uart1_Printf("SysClock = 72MHz(HSE+PLL)\n");

	for(;;)
	{
		volatile int i;

		LED_All_On();
		for(i=0; i<0x100000; i++);
		LED_All_Off();
		for(i=0; i<0x100000; i++);
		Uart1_Printf(".");
	}
}

#endif

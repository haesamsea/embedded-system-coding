#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

void Main(void)
{
	volatile int i;

	Sys_Init();
	Uart_Printf("UART Echo-Back Test\n");

	for(;;)
	{
		Uart1_Printf("\n키보드로 받는 글자 10개를 echo-back\n");
		Uart1_Printf("\n키보드를 누르면 다시 PC로 글자를 전송한다 (10글자)\n");

		for(i=0; i<10; i++)
		{
			Uart1_Printf("\n>");
			Uart1_Printf("%c", Uart1_Get_Char());
		}

		Uart1_Printf("\n계속 LED Toggling하고 있으며 키보드의 x를 누르면 종료 함");

		do
		{
			LED_Display(0x1);
			for(i=0; i<0x100000; i++);
			LED_Display(0x2);
			for(i=0; i<0x100000; i++);
		}while(Uart1_Get_Pressed() != 'x');
	}
}

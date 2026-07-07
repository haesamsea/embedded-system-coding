#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
}

void Main(void)
{
	Sys_Init();
	LED_Display(1);
	
	Uart_Printf("Compiler Test\n");

	for(;;)
	{
		Uart_Printf("Keyboard를 누르시오 => ");
		char x = Uart1_Get_Char();
		Uart_Printf("%c\n", x);
	}
}


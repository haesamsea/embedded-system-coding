#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

#if 0

void Main(void)
{
	Sys_Init();
	 //Uart_Printf("UART Echo-Back Test\n");

	while (!Macro_Check_Bit_Set(USART1->SR, 7));
	USART1->DR = 'A';

	while (!Macro_Check_Bit_Set(USART1->SR, 7));
	USART1->DR = 'B';

	while (!Macro_Check_Bit_Set(USART1->SR, 7));
	USART1->DR = 'C';
}

#endif

#if 1

void Main(void)
{
	Sys_Init();
	Uart_Printf("UART Echo-Back Test\n");

	for(;;)
	{
		unsigned char data;

		// 받은 글자를 다시 UART로 출력한다
		while (!Macro_Check_Bit_Set(USART1->SR, 5))
		USART1->DR = data;

		while (!Macro_Check_Bit_Set(USART1->SR, 7))
		return USART1->DR;
	}
}

#endif



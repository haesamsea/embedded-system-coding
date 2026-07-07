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
	Sys_Init();

	for(;;)
	{
		volatile int j;

		Uart_Printf("Chattering 제거 방식 Key_Get_Pressed() 동작 시험\n");

		for(;;)
		{
			int k;

			if((k = Key_Get_Pressed()) != 0)
			{
				Uart_Printf("Key Pressed! => [%d]\n", k);
				Key_Wait_Key_Released();
			}

			else
			{
				Uart_Printf("#\n");
				for(j=0; j<0x80000; j++);
			}
		}
	}
}

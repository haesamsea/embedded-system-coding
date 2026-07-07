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
		int i;

		Uart_Printf("Key_Get_Pressed() 함수 동작 시험\n");
		Uart_Printf("Key를 누르면 Key Pressed! 인쇄, 안 눌리면 계속 # 인쇄 => 10회 동작\n");

		for(i = 0; i<10; i++)
		{
			for(;;)
			{
				if(Key_Get_Pressed())
				{
					Uart_Printf("Key Pressed! [%d]\n", i);
					Key_Wait_Key_Released();
					break;
				}

				else
				{
					Uart_Printf("#\n");
					for(j=0; j<0x80000; j++);
				}
			}
		}

		Uart_Printf("\nKey_Wait_Key_Pressed(), Key_Wait_Key_Released() 함수 동작 시험\n");
		Uart_Printf("Key를 누르면 ON 떼면 OFF => 10회 동작\n");

		for(i = 0; i<10; i++)
		{
			j = Key_Wait_Key_Pressed();
			Uart_Printf("Key [%d] Pressed! [%d]\n", j, i);
			LED_All_On();
			Key_Wait_Key_Released();
			LED_All_Off();
		}
	}
}

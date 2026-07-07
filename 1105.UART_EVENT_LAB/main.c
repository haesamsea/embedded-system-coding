#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();

	SCB->VTOR = 0x08003000;
	SCB->SHCSR = 0;
}

extern volatile int Key_Value;
extern volatile int Uart1_Rx_In;
extern volatile int Uart1_Rx_Data;

void Main(void)
{
	Sys_Init();
	Uart1_Printf("UART Interrupt Test\n");

	Key_ISR_Enable(1);
	Uart1_RX_Interrupt_Enable(1);

	for(;;)
	{
		if(Key_Value)
		{
			Uart1_Printf("KEY=%d\n", Key_Value);
			Key_Value = 0;
		}

	    if(Uart1_Rx_In)
	    {
			Uart1_Printf("RX Data=%c\n", Uart1_Rx_Data);
			Uart1_Rx_In = 0;
	    }

		LED_Display(1);
		TIM2_Delay(200);
		LED_Display(2);
		TIM2_Delay(200);
	}
}

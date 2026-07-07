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

void Main(void)
{
	volatile int i;

	Sys_Init();
	Uart1_Printf("Nested IRQ Test\n");

	/* Set Priority: 0: Highest, 15: Lowest */
	NVIC_SetPriorityGrouping(3); 	// Binary Point = 4 (Group = 16)
	NVIC_SetPriority(30, 1); 		// TIM4
	NVIC_SetPriority(23, 2); 		// EXTI9_5
	NVIC_SetPriority(37, 3); 		// USART1

	Key_ISR_Enable(1);
	Uart1_RX_Interrupt_Enable(1);
	TIM4_Repeat_Interrupt_Enable(1, 100);

	for(;;)
	{
		Uart1_Printf(".");
		for(i=0; i<0x100000; i++);
	}
}

#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

#if 1

void Main(void)
{
	int i;

	Sys_Init();
	Uart1_Printf("TIM2 stopwatch test\n");

	for(i=1; i<=10; i++)
	{
		LED_Display(i%4);
		TIM2_Stopwatch_Start();
		SysTick_Run(100*i);
		while(!SysTick_Check_Timeout());
		SysTick_Stop();
		Uart1_Printf("[%d] Elapsed Time = %f msec\n", i, TIM2_Stopwatch_Stop()/1000.);
	}
}

#endif

#if 0

void Main(void)
{
	Sys_Init();
	Uart1_Printf("TIM2 delay test\n");

	for(;;)
	{
		LED_Display(0x1);
		TIM2_Delay(1000);
		LED_Display(0x2);
		TIM2_Delay(1000);
		Uart1_Printf(".");
	}
}

#endif

#if 0

void Main(void)
{
	int i = 1;

	Sys_Init();
	Uart1_Printf("TIM4 repeat timeout test\n");

	TIM4_Repeat(500);
	SysTick_Run(500);

	for(;;)
	{
		if(TIM4_Check_Timeout())
		{
			LED_Display(i%4);
			Uart1_Printf("Timer4 [%d]\n", i++);
			if(i>40) TIM4_Stop();
		}

	    if(SysTick_Check_Timeout())
	    {
			Uart1_Printf("SysTick [%d]\n", i++);
			if(i>40) SysTick_Stop();
	    }
	}
}

#endif

#if 0

void Main(void)
{
	int i = 1;

	Sys_Init();

	Uart1_Printf("TIM4 variable interval test\n");

	TIM4_Repeat(50);

	for(;;)
	{
		if(TIM4_Check_Timeout())
		{
			LED_Display(i%4);
			Uart1_Printf("[%d]", i++);
			if(i>20) i = 1;
			TIM4_Change_Value(50 * i);
		}
	}
}

#endif

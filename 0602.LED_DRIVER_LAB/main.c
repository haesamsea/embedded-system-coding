#include "device_driver.h"

void Main(void)
{
	volatile int i, j;

	LED_Init();

	for(i=0;i<16;i++)
	{
		LED_Display(i);
		for(j=0; j<0x40000; j++);
	}

	for(;;)
	{
		LED_All_Off();
		for(j=0; j<0x20000; j++);

		LED_All_On();
		for(j=0; j<0x20000; j++);
	}
}

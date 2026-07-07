#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
}

/* Key 인식 */

#if 0

void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Test #1\n");

	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOB->CRL,0XFF, 0X44, 24);
	Macro_Write_Block(GPIOB->CRH, 0XFF, 0X66, 0);

	for(;;)
	{
		// KEY0이 눌렸으면 LED0를 ON, 안 눌렸으면 OFF
		//if (Macro_Check_Bit_Clear(GPIOB->IDR, 6))
			//PB8이 ON
		//	Macro_Set_Bit(GPIOB->ODR, 9);
		//Macro_Write_Block(GPIOB->ODR, 0X1, Macro_Extract_Area(GPIOB->IDR, 0X1, 6), 8);

		// KEY1이 눌렸으면 LED1를 ON, 안 눌렸으면 OFF
		//if (Macro_Check_Bit_Clear(GPIOB->IDR, 7))
			//PB9가 ON
		//	Macro_Set_Bit(GPIOB->ODR, 9);
		//Macro_Write_Block(GPIOB->ODR, 0X1, Macro_Extract_Area(GPIOB->IDR, 0X1, 7), 9);

		Macro_Write_Block(GPIOB->ODR, 0X3, Macro_Extract_Area(GPIOB->IDR, 0X3, 6), 8);

	}
}

#endif

/* Key에 의한 LED Toggling */

#if 1

void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Toggling #1\n");


	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOB->CRL, 0XFF, 0X44, 24);
	Macro_Write_Block(GPIOB->CRH, 0XFF, 0X66, 0);

	for(;;)
	{
		// KEY0가 눌릴때마다 LED0의 값을 Toggling
		if ((interlock != 0) && Macro_Check_Bit_Clear(GPIOB->IDR, 6)) {
			Macro_Invert_Bit(GPIOB->ODR, 8);
			interlock = 0;
		}
		else if ((interlock == 0) && Macro_Check_Bit_Set(GPIOB->IDR, 6)) {
			interlock == 1;
		}

	}
}

#endif

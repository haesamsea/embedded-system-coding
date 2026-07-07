#include "device_driver.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void Uart1_Init(int baud)
{
	double div;
	unsigned int mant;
	unsigned int frac;

	/*GPIOA 클럭 활성화*/
	Macro_Set_Bit(RCC->APB2ENR, 2);
	/*USART1 클럭 활성화*/
	Macro_Set_Bit(RCC->APB2ENR, 14);

	/*
	PA9: TX, 신호를 내보냄(AF Push-Pull)
	PA10: RX, 외부 신호를 받아들임(Input Pull-up/Pull-down) 
	*/
	Macro_Write_Block(GPIOA->CRH, 0xff, 0x8a, 4);
	/* PA10(RX) PULL UP 입력으로 설정*/
	Macro_Set_Bit(GPIOA->ODR, 10);

	/* Baud Rate 계산 */
	div = PCLK2/(16. * baud);
	mant = (int)div;
	frac = (int)((div - mant) * 16. + 0.5);
	mant += frac >> 4;
	frac &= 0xf;

	USART1->BRR = (mant<<4)+(frac<<0);
	// 8비트 데이터, 패리티 없음, 송수신 둘 다 사용, USART 자체 활성화
	USART1->CR1 = (1<<13)|(0<<12)|(0<<10)|(1<<3)|(1<<2);
	// 프레임 형식
	USART1->CR2 = 0<<12;
	// 흐름 제어/DMA
	USART1->CR3 = 0;
}

void Uart1_Send_Byte(char data)
{
	if(data=='\n')
	{
		while(Macro_Check_Bit_Clear(USART1->SR, 7));
		USART1->DR = 0x0d;
	}

	while(Macro_Check_Bit_Clear(USART1->SR, 7));
	USART1->DR = data;
}

void Uart1_Send_String(char *pt)
{
	while(*pt!=0)
	{
		Uart1_Send_Byte(*pt++);
	}
}

void Uart1_Printf(char *fmt,...)
{
	va_list ap;
	char string[256];

	va_start(ap,fmt);
	vsprintf(string,fmt,ap);
	Uart1_Send_String(string);
	va_end(ap);
}

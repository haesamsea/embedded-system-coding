#include "stm32f10x.h"
#include "option.h"
#include "macro.h"
#include "malloc.h"

// Uart.c

#define Uart_Init			Uart1_Init
#define Uart_Send_Byte		Uart1_Send_Byte
#define Uart_Send_String	Uart1_Send_String
#define Uart_Printf			Uart1_Printf

extern void Uart1_Init(int baud);
extern void Uart1_Send_Byte(char data);
extern void Uart1_Send_String(char *pt);
extern void Uart1_Printf(char *fmt,...);

// Led.c

extern void LED_Init(void);
extern void LED_Display(unsigned int num);
extern void LED_All_On(void);
extern void LED_All_Off(void);

#include "device_driver.h"

#define PWM_TICK_HZ     1000000
#define PWM_FREQ        1000
#define PWM_PERIOD      (PWM_TICK_HZ / PWM_FREQ)
#define SPEED_MAX       9

#define DIR_STOP    0
#define DIR_CW      1
#define DIR_CCW     2

static int g_dir = DIR_STOP;
static int g_speed = 5;

static void Motor_Delay(void)
{
	volatile int i;
	for (i = 0; i < 100000; i++);
}

static unsigned int Motor_Duty(void)
{
	return (PWM_PERIOD * g_speed) / (SPEED_MAX + 1);
}

void MOTOR_Init(void)
{
	Macro_Set_Bit(RCC->APB2ENR, 2);
	Macro_Write_Block(GPIOA->CRL, 0xff, 0xbb, 8);

	Macro_Set_Bit(RCC->APB1ENR, 0);

	TIM2->CR1 = 0;
	TIM2->PSC = (unsigned int)(TIMXCLK / (double)PWM_TICK_HZ + 0.5) - 1;
	TIM2->ARR = PWM_PERIOD - 1;

	Macro_Write_Block(TIM2->CCMR2, 0x7, 0x6, 4);
	Macro_Set_Bit(TIM2->CCMR2, 3);
	Macro_Write_Block(TIM2->CCMR2, 0x7, 0x6, 12);
	Macro_Set_Bit(TIM2->CCMR2, 11);

	TIM2->CCR3 = 0;
	TIM2->CCR4 = 0;

	TIM2->CCER = (1 << 8) | (1 << 12);

	Macro_Set_Bit(TIM2->EGR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);

	g_dir = DIR_STOP;
}

int MOTOR_Get_State(void)
{
	return g_dir;
}

void MOTOR_Off(void)
{
	TIM2->CCR3 = 0;
	TIM2->CCR4 = 0;
	g_dir = DIR_STOP;
}

void MOTOR_CW(void)
{
	if (g_dir == DIR_CW) return;

	MOTOR_Off();
	Motor_Delay();

	TIM2->CCR4 = 0;
	TIM2->CCR3 = Motor_Duty();
	g_dir = DIR_CW;
}

void MOTOR_CCW(void)
{
	if (g_dir == DIR_CCW) return;

	MOTOR_Off();
	Motor_Delay();

	TIM2->CCR3 = 0;
	TIM2->CCR4 = Motor_Duty();
	g_dir = DIR_CCW;
}

void MOTOR_On(void)
{
	MOTOR_CW();
}

void MOTOR_Change(void)
{
	if (g_dir == DIR_STOP) return;

	if (g_dir == DIR_CW)  MOTOR_CCW();
	else                  MOTOR_CW();
}

void MOTOR_Set_Speed(int level)
{
	if (level < 1) level = 1;
	if (level > SPEED_MAX) level = SPEED_MAX;
	g_speed = level;

	if (g_dir == DIR_CW)       TIM2->CCR3 = Motor_Duty();
	else if (g_dir == DIR_CCW) TIM2->CCR4 = Motor_Duty();
}

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
	MOTOR_Init();

	Uart_Printf("Motor bidirectional + PWM speed control\n");
	Uart_Printf("KEY0: ON/OFF,  KEY1: CW/CCW toggle\n");
	Uart_Printf("UART S:Stop F:CW R:CCW,  1~9:Speed\n");

	for (;;)
	{
		int k = Key_Get_Pressed();

		if (k == 1) {
			Uart_Printf("KEY0 -> ON/OFF\n");
			if (MOTOR_Get_State() == DIR_STOP) MOTOR_On();
			else                                MOTOR_Off();
			Key_Wait_Key_Released();
		}
		else if (k == 2) {
			Uart_Printf("KEY1 -> Direction toggle\n");
			MOTOR_Change();
			Key_Wait_Key_Released();
		}
		else if (k == 3) {
			Uart_Printf("KEY0+KEY1 ignored\n");
			Key_Wait_Key_Released();
		}

		char c = Uart1_Get_Pressed();

		if (c == 'S' || c == 's') {
			Uart_Printf("UART -> Stop\n");
			MOTOR_Off();
		}
		else if (c == 'F' || c == 'f') {
			Uart_Printf("UART -> CW\n");
			MOTOR_CW();
		}
		else if (c == 'R' || c == 'r') {
			Uart_Printf("UART -> CCW\n");
			MOTOR_CCW();
		}
		else if (c >= '1' && c <= '9') {
			int lv = c - '0';
			MOTOR_Set_Speed(lv);
			Uart_Printf("UART -> Speed %d\n", lv);
		}
	}
}
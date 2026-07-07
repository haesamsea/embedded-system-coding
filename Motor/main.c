#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

void MOTOR_Init(void)
{
	Macro_Set_Bit(RCC->APB2ENR, 2); //gpioa
	Macro_Write_Block(GPIOA->CRL, 0xff, 0x33, 8); //모드 변경
	Macro_Set_Area(GPIOA->ODR, 0x3, 2); // 정지상태
}

int MOTOR_Get_State(void)
{
	return Macro_Extract_Area(GPIOA->ODR, 0x3, 2);
}

void MOTOR_On(void)
{
	//시계방향으로 세팅
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 2);
}

void MOTOR_Change(void)
{
	unsigned int cur = MOTOR_Get_State();

	if (cur == 0x3) { // 꺼진 상태 -> 무시
		return;
	}

	MOTOR_Off();
	volatile int i; for (i = 0; i < 100000; i++); 
	Macro_Write_Block(GPIOA->ODR, 0x3, ~cur, 2);  // 반전
}

void MOTOR_CW(void)
{
	unsigned int cur = MOTOR_Get_State();

	if (cur == 0x3) { // 꺼진 상태 -> 무시
		return;
	}

	if (cur == 0x1) { // CW로 돌아가고 있는 상황 -> 무시
		return;
	}

	MOTOR_Off();
	volatile int i; for (i = 0; i < 100000; i++);
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 2);
}

void MOTOR_CCW(void)
{
	unsigned int cur = MOTOR_Get_State();

	if (cur == 0x3) { // 꺼진 상태 -> 무시
		return;
	}

	if (cur == 0x2) { // CCW로 돌아가고 있는 상황 -> 무시
		return;
	}

	MOTOR_Off();
	volatile int i; for (i = 0; i < 100000; i++);
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 2);
}

void MOTOR_Off(void)
{
	Macro_Set_Area(GPIOA->ODR, 0x3, 2);
}


void Main(void)
{
	int k;

	Sys_Init();
	MOTOR_Init();

	Uart_Printf("motor 양방향 동작\n");
	Uart_Printf("key0을 누를 시 on off\n");
	Uart_Printf("key1을 누를 시 cw ccw\n");
		
	for (;;)
	{
		k = Key_Get_Pressed();
		//버튼을 누를 때까지 대기

		// key0을 누름 -> motor on, off
		if (k == 1) {
			Uart_Printf("Key Pressed! => [%d]\n", k);
			if (MOTOR_Get_State() == 0x3) {
				MOTOR_On();
			}
			else MOTOR_Off();	
			
			Key_Wait_Key_Released();	
		}

		// key1을 누름 -> motor cw, ccw
		if (k == 2) {
			Uart_Printf("Key Pressed! => [%d]\n", k);
			MOTOR_Change();
			
			Key_Wait_Key_Released();	
		}
		
		//key 1과 2를 동시에 누름	
		if (k == 3) {
			Uart_Printf("Key Pressed! => [%d] (동시 입력 무시)\n", k);	
			Key_Wait_Key_Released();
		}

		char c = Uart1_Get_Pressed();

		//정지
		if (c == 'S') {
			MOTOR_Off();
		}

		//정회전
		if (c == 'F') {
			MOTOR_CW();
		}

		//역회전
		if (c == 'R') {
			MOTOR_CCW();
		}
	}
}
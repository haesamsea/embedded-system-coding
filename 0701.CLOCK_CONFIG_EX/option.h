/* HSI(8MHz) 사용시 */

#if 1

#define SYSCLK	8000000
#define HCLK	SYSCLK
#define PCLK2	HCLK
#define PCLK1	HCLK

#endif

/* HSE(72MHz) 사용시 */

#if 0

#define SYSCLK	72000000
#define HCLK	SYSCLK
#define PCLK2	HCLK
#define PCLK1	(HCLK/2)
#define TIMXCLK ((HCLK == PCLK1)?(PCLK1):(PCLK1*2))

#endif

#define RAM_START	0x20000000
#define RAM_END		0x20004FFF
#define HEAP_BASE	(((unsigned int)&__ZI_LIMIT__ + 0x7) & ~0x7)
#define HEAP_SIZE	(4*1024)
#define HEAP_LIMIT	(HEAP_BASE + HEAP_SIZE)
#define STACK_LIMIT	(HEAP_LIMIT + 8)
#define STACK_BASE	(RAM_END + 1)
#define STACK_SIZE	(STACK_BASE - STACK_LIMIT)


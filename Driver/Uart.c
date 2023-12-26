#include "global.h"                  // Device heade


#define UART1_MAXBUFLEN	(40)
#if (UART1_MAXBUFLEN>255)
#error "UART buffer must be less than 256 bytes because of head/rear data size is 8-bit unsigned char."
#endif

static volatile struct _uart_param_tag{
	uint8_t front;
	uint8_t rear;
	char buffer[UART1_MAXBUFLEN];
} g_uart1_param;

/**
  * @brief  ����1��ʼ��
  * @param  t_baud�����ڲ�����
  * @retval None
  */
void Usart1_Init(uint16_t t_baud) {
	COMx_InitDefine USART_InitStructure;
	USART_InitStructure.UART_Mode = UART_8bit_BRTx;//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	USART_InitStructure.UART_BRT_Use = BRT_Timer2;//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	USART_InitStructure.UART_BaudRate = t_baud;		//������, һ�� 110 ~ 115200
	USART_InitStructure.UART_RxEnable = ENABLE;		//��������,   ENABLE��DISABLE
	USART_InitStructure.BaudRateDouble = DISABLE;	//�����ʼӱ�, ENABLE��DISABLE
	USART_InitStructure.UART_Interrupt = ENABLE;	//�ж�ʹ��, ENABLE/DISABLE;
	USART_InitStructure.UART_Polity = PolityHigh; //���ȼ�,     PolityLow,PolityHigh
	USART_InitStructure.UART_P_SW = UART1_SW_P36_P37;//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(����ʹ���ڲ�ʱ��)
	USART_Init(USART1, &USART_InitStructure);
}

uint8_t uart1_Read(void *vbuf,uint8_t len)
{
	uint8_t i = 0;
	char *buf = (char *)vbuf;
	for(i-0; i<len; i++)
	{
		EA = 0;
		if(g_uart1_param.front == g_uart1_param.rear)
		{
			EA = 1;//�жӿգ���ִ�г��Ӳ���
			break;
		}
		buf[i] = g_uart1_param.buffer[g_uart1_param.front];
		g_uart1_param.front = (g_uart1_param.front + 1) % UART1_MAXBUFLEN;
		EA = 1;
		_nop_();
	}
	return i;
}

void uart1_Write(const void *vbuf,uint8_t len)
{
	uint8_t i;
	const char *buf = (const char*)vbuf;
	for(i=0; i<len; i++)
	{
		SBUF = buf[i];
		while(TI == 0);
		TI = 0;
	}
}

/********************* UART1�жϺ���************************/
void USART1_IRQHandler (void) interrupt UART1_VECTOR
{
	uint8_t val;
	if(RI)
	{
		val = SBUF;
		RI = 0;
		if( (g_uart1_param.rear + 1) % UART1_MAXBUFLEN == g_uart1_param.front )
		{
			return;//�ж���
		}
		else
		{
			g_uart1_param.buffer[g_uart1_param.rear] = val;
			g_uart1_param.rear = (g_uart1_param.rear + 1) % UART1_MAXBUFLEN;
		}
	}
}

//implemented for printf()
char putchar(char c)
{
	SBUF = c;
	while(TI == 0);
	TI = 0;
	return c;
}

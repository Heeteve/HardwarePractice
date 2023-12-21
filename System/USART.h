
#ifndef __USART_H
#define __USART_H	 

#include "global.h"                  // Device heade

#define	COM_TX1_Lenth	128
#define	COM_RX1_Lenth	128
#define	COM_TX2_Lenth	128
#define	COM_RX2_Lenth	128

#define	USART1	1
#define	USART2	2

#define	UART_ShiftRight	0		//ͬ����λ���
#define	UART_8bit_BRTx	(1<<6)	//8λ����,�ɱ䲨����
#define	UART_9bit		(2<<6)	//9λ����,�̶�������
#define	UART_9bit_BRTx	(3<<6)	//9λ����,�ɱ䲨����

#define	UART1_SW_P30_P31	0
#define	UART1_SW_P36_P37	(1<<6)
#define	UART1_SW_P16_P17	(2<<6)	//����ʹ���ڲ�ʱ��
#define	UART2_SW_P10_P11	0
#define	UART2_SW_P46_P47	1


#define	TimeOutSet1		5
#define	TimeOutSet2		5

#define	BRT_Timer1	1
#define	BRT_Timer2	2


typedef struct
{ 
	unsigned char	UART_Mode;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	unsigned char	UART_BRT_Use;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2
	unsigned long	UART_BaudRate;		//������,       ENABLE,DISABLE
	unsigned char	Morecommunicate;	//���ͨѶ����, ENABLE,DISABLE
	unsigned char	UART_RxEnable;		//�������,   ENABLE,DISABLE
	unsigned char	BaudRateDouble;		//�����ʼӱ�, ENABLE,DISABLE
	unsigned char	UART_Interrupt;		//�жϿ���,   ENABLE,DISABLE
	unsigned char	UART_Polity;		//���ȼ�,     PolityLow,PolityHigh
	unsigned char	UART_P_SW;			//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(����ʹ���ڲ�ʱ��)
	unsigned char	UART_RXD_TXD_Short;	//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE

} COMx_InitDefine; 


unsigned char	USART_Init(unsigned char UARTx, COMx_InitDefine *COMx);


#endif


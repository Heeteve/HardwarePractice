#include "USART.h"


//禁止串2接收
#define		TI2					(S2CON & 2) != 0
#define		RI2					(S2CON & 1) != 0
#define		SET_TI2()			S2CON |=  2
#define		CLR_TI2()			S2CON &= ~2
#define		CLR_RI2()			S2CON &= ~1
#define		S2TB8_SET()			S2CON |=  8
#define		S2TB8_CLR()			S2CON &= ~8
#define		S2_Int_en()			IE2   |=  1		//串口2允许中断
#define		S2_USE_P10P11()		P_SW2 &= ~1		//UART2 使用P1口	默认
#define		S2_USE_P46P47()		P_SW2 |=  1		//UART2 使用P4口

#define		S3_USE_P00P01()		P_SW2 &= ~2		//UART3 使用P0口	默认
#define		S3_USE_P50P51()		P_SW2 |=  2		//UART3 使用P5口
#define		S4_USE_P02P03()		P_SW2 &= ~4		//UART4 使用P0口	默认
#define		S4_USE_P52P53()		P_SW2 |=  4		//UART4 使用P5口

uint8_t USART_Init(uint8_t UARTx, COMx_InitDefine *COMx)
{
	uint32_t	j;
	
	if(UARTx == USART1)
	{
//		COM1.id = 1;
//		COM1.TX_read    = 0;
//		COM1.TX_write   = 0;
//		COM1.B_TX_busy  = 0;
//		COM1.RX_Cnt     = 0;
//		COM1.RX_TimeOut = 0;
//		COM1.B_RX_OK    = 0;
//		for(i=0; i<COM_TX1_Lenth; i++)	TX1_Buffer[i] = 0;
//		for(i=0; i<COM_RX1_Lenth; i++)	RX1_Buffer[i] = 0;

		if(COMx->UART_Mode > UART_9bit_BRTx)	return 2;	//模式错误
		if(COMx->UART_Polity == PolityHigh)		PS = 1;	//高优先级中断
		else									PS = 0;	//低优先级中断
		SCON = (SCON & 0x3f) | COMx->UART_Mode;
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			j = (CFG_SYSFREQ / 4) / COMx->UART_BaudRate;	//按1T计算
			if(j >= 65536UL)	return 2;	//错误
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer1)
			{
				TR1 = 0;
				AUXR &= ~0x01;		//S1 BRT Use Timer1;
				TMOD &= ~(1<<6);	//Timer1 set As Timer
				TMOD &= ~0x30;		//Timer1_16bitAutoReload;
				AUXR |=  (1<<6);	//Timer1 set as 1T mode
				TH1 = (uint8_t)(j>>8);
				TL1 = (uint8_t)j;
				ET1 = 0;	//禁止中断
				TMOD &= ~0x40;	//定时
				INT_CLKO &= ~0x02;	//不输出时钟
				TR1  = 1;
			}
			else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				AUXR &= ~(1<<4);	//Timer stop
				AUXR |= 0x01;		//S1 BRT Use Timer2;
				AUXR &= ~(1<<3);	//Timer2 set As Timer
				AUXR |=  (1<<2);	//Timer2 set as 1T mode
				T2H = (uint8_t)(j>>8);
				T2L = (uint8_t)j;
				IE2  &= ~(1<<2);	//禁止中断
				AUXR &= ~(1<<3);	//定时
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return 2;	//错误
		}
		else if(COMx->UART_Mode == UART_ShiftRight)
		{
			if(COMx->BaudRateDouble == ENABLE)	AUXR |=  (1<<5);	//固定波特率SysClk/2
			else								AUXR &= ~(1<<5);	//固定波特率SysClk/12
		}
		else if(COMx->UART_Mode == UART_9bit)	//固定波特率SysClk*2^SMOD/64
		{
			if(COMx->BaudRateDouble == ENABLE)	PCON |=  (1<<7);	//固定波特率SysClk/32
			else								PCON &= ~(1<<7);	//固定波特率SysClk/64
		}
		if(COMx->UART_Interrupt == ENABLE)	ES = 1;	//允许中断
		else								ES = 0;	//禁止中断
		if(COMx->UART_RxEnable == ENABLE)	REN = 1;	//允许接收
		else								REN = 0;	//禁止接收
		P_SW1 = (P_SW1 & 0x3f) | (COMx->UART_P_SW & 0xc0);	//切换IO
		if(COMx->UART_RXD_TXD_Short == ENABLE)	CLK_DIV |=  (1<<4);	//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
		else									CLK_DIV &= ~(1<<4);
		return	0;
	}

	if(UARTx == USART2)
	{
//		COM2.id = 2;
//		COM2.TX_read    = 0;
//		COM2.TX_write   = 0;
//		COM2.B_TX_busy  = 0;
//		COM2.RX_Cnt     = 0;
//		COM2.RX_TimeOut = 0;
//		COM2.B_RX_OK    = 0;
//		for(i=0; i<COM_TX2_Lenth; i++)	TX2_Buffer[i] = 0;
//		for(i=0; i<COM_RX2_Lenth; i++)	RX2_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			if(COMx->UART_Polity == PolityHigh)		IP2 |=  1;	//高优先级中断
			else									IP2 &= ~1;	//低优先级中断
			if(COMx->UART_Mode == UART_9bit_BRTx)	S2CON |=  (1<<7);	//9bit
			else									S2CON &= ~(1<<7);	//8bit
			j = (CFG_SYSFREQ / 4) / COMx->UART_BaudRate;	//按1T计算
			if(j >= 65536UL)	return 2;	//错误
			j = 65536UL - j;
			AUXR &= ~(1<<4);	//Timer stop
			AUXR &= ~(1<<3);	//Timer2 set As Timer
			AUXR |=  (1<<2);	//Timer2 set as 1T mode
			T2H = (uint8_t)(j>>8);
			T2L = (uint8_t)j;
			IE2  &= ~(1<<2);	//禁止中断
			AUXR |=  (1<<4);	//Timer run enable
		}
		else	return 2;	//模式错误
		if(COMx->UART_Interrupt == ENABLE)	IE2   |=  1;		//允许中断
		else								IE2   &= ~1;		//禁止中断
		if(COMx->UART_RxEnable == ENABLE)	S2CON |=  (1<<4);	//允许接收
		else								S2CON &= ~(1<<4);	//禁止接收
		P_SW2 = (P_SW2 & ~1) | (COMx->UART_P_SW & 0x01);	//切换IO
	}
	return	0;
}



/********************* UART1中断函数************************/
//void UART1_int (void) interrupt UART1_VECTOR
//{
//	if(RI)
//	{
//		RI = 0;
//		if(COM1.B_RX_OK == 0)
//		{
//			if(COM1.RX_Cnt >= COM_RX1_Lenth)	COM1.RX_Cnt = 0;
//			RX1_Buffer[COM1.RX_Cnt++] = SBUF;
//			COM1.RX_TimeOut = TimeOutSet1;
//		}
//	}

//	if(TI)
//	{
//		TI = 0;
//		if(COM1.TX_read != COM1.TX_write)
//		{
//		 	SBUF = TX1_Buffer[COM1.TX_read];
//			if(++COM1.TX_read >= COM_TX1_Lenth)		COM1.TX_read = 0;
//		}
//		else	COM1.B_TX_busy = 0;
//	}
//}

/********************* UART2中断函数************************/
//void UART2_int (void) interrupt UART2_VECTOR
//{
//	if(RI2)
//	{
//		CLR_RI2();
//		if(COM2.B_RX_OK == 0)
//		{
//			if(COM2.RX_Cnt >= COM_RX2_Lenth)	COM2.RX_Cnt = 0;
//			RX2_Buffer[COM2.RX_Cnt++] = S2BUF;
//			COM2.RX_TimeOut = TimeOutSet2;
//		}
//	}

//	if(TI2)
//	{
//		CLR_TI2();
//		if(COM2.TX_read != COM2.TX_write)
//		{
//		 	S2BUF = TX2_Buffer[COM2.TX_read];
//			if(++COM2.TX_read >= COM_TX2_Lenth)		COM2.TX_read = 0;
//		}
//		else	COM2.B_TX_busy = 0;
//	}

//}




#include "global.h"

/*System ticks*/
static volatile unsigned long idata g_sys_ticks;
static unsigned int code g_timer0_init_val = 65536UL - (CFG_SYSFREQ/12/1000);
/*Timer 0 as system tick timer. 1KHZ */
void SysTick_Init(void) {
	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����
	TIM_InitStructure.TIM_Mode      = TIM_16Bit;			//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityHigh;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;			//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = g_timer0_init_val;	//��ֵ,
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2
}

void timer0_ISR(void) interrupt 1
{
	TL0 = g_timer0_init_val & 0xff;
	TH0 = g_timer0_init_val >> 8;
	g_sys_ticks ++;
}

uint32_t time_GetTicks(void)
{
	unsigned long ticks;
	EA = 0;
	ticks = g_sys_ticks;
	EA = 1;
	return ticks;
}

#if (CFG_SYSFREQ == 22118400 && INS_VER == INS_VER_Y5)
static void Delay1us()
{
	unsigned char i;

	i = 3;
	while (--i);
}
static void Delay10us()
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 52;
	while (--i);
}
static void Delay100us()
{
	unsigned char i, j;

	i = 3;
	j = 26;
	do
	{
		while (--j);
	} while (--i);
}
#endif

void DelayUs(uint16_t us)
{
	for(;us>=100;us-=100) Delay100us();
	for(;us>=10;us-=10) Delay10us();
	for(;us>0;us--) Delay1us();
}

void DelayMs(uint16_t ms) {
	uint32_t oldticks;
	uint32_t ticks;
	oldticks  = time_GetTicks();
	do {
  	ticks = time_GetTicks();
  } while (ticks - oldticks < ms);
}


int	Timer_Inilize(uint8_t TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer3)	return 1;	//�ղ���

	if(TIM == Timer0)
	{
		TR0 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//�����ж�
		else									ET0 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//�����ȼ��ж�
		else									PT0 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//����������Ƶ
		else										TMOD &= ~0x04;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//���ʱ��
		else							INT_CLKO &= ~0x01;	//�����ʱ��

		TH0 = (uint8_t)(TIMx->TIM_Value >> 8);
		TL0 = (uint8_t)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer1)
	{
		TR1 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//�����ж�
		else									ET1 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//�����ȼ��ж�
		else									PT1 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x30) | (TIMx->TIM_Mode << 4);	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//����������Ƶ
		else										TMOD &= ~0x40;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//���ʱ��
		else							INT_CLKO &= ~0x02;	//�����ʱ��

		TH1 = (uint8_t)(TIMx->TIM_Value >> 8);
		TL1 = (uint8_t)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer2)
	{
		AUXR &= ~(1<<4);	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//�����ж�
		else										IE2  &= ~(1<<2);	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//����������Ƶ
		else										AUXR &= ~(1<<3);	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//���ʱ��
		else							INT_CLKO &= ~0x04;	//�����ʱ��

		T2H = (uint8_t)(TIMx->TIM_Value >> 8);
		T2L = (uint8_t)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//��ʼ����
		return	0;		//�ɹ�
	}
	return 2;	//����
}

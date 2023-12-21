#include "global.h"                  // Device heade

sbit	PWMB_PIN = P0^4;		//定义PWM输出引脚。
sbit	PWMA_PIN = P0^5;		//定义PWM输出引脚。
static uint16_t		PWM_high,PWM_low;	//中间变量，用户请勿修改。
/**
  * @brief 马达GPIO初始化
  * @param  None
  * @retval None
  */
static void Motor_GPIO_Init(void) {

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_OUT_PP;
	GPIO_InitStructure.GPIO_Pin = Left_MotoA_Pin | Left_MotoB_Pin | Right_MotoA_Pin | Right_MotoB_Pin | Right_MotoPWM_Pin | Left_MotoPWM_Pin;
	GPIO_Init(Motor_Port, &GPIO_InitStructure);

	GPIO_SetBits(Motor_Port, Left_MotoA_Pin | Left_MotoB_Pin | Right_MotoA_Pin | Right_MotoB_Pin | Right_MotoPWM_Pin | Left_MotoPWM_Pin);
}

void Motor_PWM_Init(void) {
	TIM_InitTypeDef		TIM_InitStructure;					//结构定义

	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//指定中断优先级, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE或DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - PWM_DUTY;	//初值,
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer1,&TIM_InitStructure);				//初始化	  Timer0,Timer1,Timer2

	Motor_GPIO_Init();
}

/**************** 计算PWM重装值函数 *******************/
static void	LoadPWM(uint16_t i)
{
	uint16_t	j;
	j = 65536UL - PWM_DUTY + i;	//计算PWM低电平时间
	i = 65536UL - i;			//计算PWM高电平时间
	EA = 0;
	PWM_high = i;	//装载PWM高电平时间
	PWM_low  = j;	//装载PWM低电平时间
	EA = 1;
}

/********************* Timer1中断函数************************/
void timer1_int (void) interrupt 3
{
	if(PWMB_PIN)
	{
		TH1 = (uint8_t)(PWM_high >> 8);	//如果是输出低电平，则装载高电平时间。
		TL1 = (uint8_t)PWM_high;
		PWMB_PIN = 0;
		PWMA_PIN = 0;
	}
	else
	{
		TH1 = (uint8_t)(PWM_low >> 8);	//如果是输出高电平，则装载低电平时间。
		TL1 = (uint8_t)PWM_low;
		PWMB_PIN = 1;
		PWMA_PIN = 1;
	}
}

/********************* Timer3中断函数************************/
/*STC15F2K没有定时器3*/
//void timer3_int (void) interrupt 19
//{
//
//	P1 = 0;
//	if(PWMA_PIN)
//	{
//		T3H = (uint8_t)(PWM_high >> 8);	//如果是输出低电平，则装载高电平时间。
//		T3L = (uint8_t)PWM_high;
//		PWMA_PIN = 0;
//	}
//	else
//	{
//		T3H = (uint8_t)(PWM_low >> 8);	//如果是输出高电平，则装载低电平时间。
//		T3L = (uint8_t)PWM_low;
//		PWMA_PIN = 1;
//	}
//}

void Motor_Run(uint8_t dir, uint16_t speed) {
	speed < PWM_HIGH_MIN ?			speed = PWM_HIGH_MIN:speed; //如果写入小于最小占空比数据，则强制为最小占空比。
	speed > PWM_HIGH_MAX ?			speed = PWM_HIGH_MAX:speed; //如果写入大于最大占空比数据，则强制为最大占空比。

	switch (dir) {
		case FORWARD:
				LeftMotor_Go();
				RightMotor_Go();
				LoadPWM(speed);
				break;
		case BACKWARDS:
				LeftMotor_Back();
				RightMotor_Back();
				LoadPWM(speed);
				break;
		case TURNLEFT:
				LeftMotor_Stop();
				RightMotor_Go();
				LoadPWM(speed);
				break;
		case TURNRIGHT:
				LeftMotor_Go();
				RightMotor_Stop();
				LoadPWM(speed);
				break;
		case SPINTURNLEFT:
				LeftMotor_Back();
				RightMotor_Go();
				LoadPWM(speed);
				break;
		case SPINTURNRIGHT:
				LeftMotor_Go();
				RightMotor_Back();
				LoadPWM(speed);
				break;
		case STOP:
				LeftMotor_Stop();
				RightMotor_Stop();
				LoadPWM(speed);
				break;
		default:
				LeftMotor_Stop();
				RightMotor_Stop();
				break;
	}
}
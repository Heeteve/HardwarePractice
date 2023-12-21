#include "global.h"                  // Device heade

sbit	PWMB_PIN = P0^4;		//����PWM������š�
sbit	PWMA_PIN = P0^5;		//����PWM������š�
static uint16_t		PWM_high,PWM_low;	//�м�������û������޸ġ�
/**
  * @brief ���GPIO��ʼ��
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
	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����

	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - PWM_DUTY;	//��ֵ,
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer1,&TIM_InitStructure);				//��ʼ��	  Timer0,Timer1,Timer2

	Motor_GPIO_Init();
}

/**************** ����PWM��װֵ���� *******************/
static void	LoadPWM(uint16_t i)
{
	uint16_t	j;
	j = 65536UL - PWM_DUTY + i;	//����PWM�͵�ƽʱ��
	i = 65536UL - i;			//����PWM�ߵ�ƽʱ��
	EA = 0;
	PWM_high = i;	//װ��PWM�ߵ�ƽʱ��
	PWM_low  = j;	//װ��PWM�͵�ƽʱ��
	EA = 1;
}

/********************* Timer1�жϺ���************************/
void timer1_int (void) interrupt 3
{
	if(PWMB_PIN)
	{
		TH1 = (uint8_t)(PWM_high >> 8);	//���������͵�ƽ����װ�ظߵ�ƽʱ�䡣
		TL1 = (uint8_t)PWM_high;
		PWMB_PIN = 0;
		PWMA_PIN = 0;
	}
	else
	{
		TH1 = (uint8_t)(PWM_low >> 8);	//���������ߵ�ƽ����װ�ص͵�ƽʱ�䡣
		TL1 = (uint8_t)PWM_low;
		PWMB_PIN = 1;
		PWMA_PIN = 1;
	}
}

/********************* Timer3�жϺ���************************/
/*STC15F2Kû�ж�ʱ��3*/
//void timer3_int (void) interrupt 19
//{
//
//	P1 = 0;
//	if(PWMA_PIN)
//	{
//		T3H = (uint8_t)(PWM_high >> 8);	//���������͵�ƽ����װ�ظߵ�ƽʱ�䡣
//		T3L = (uint8_t)PWM_high;
//		PWMA_PIN = 0;
//	}
//	else
//	{
//		T3H = (uint8_t)(PWM_low >> 8);	//���������ߵ�ƽ����װ�ص͵�ƽʱ�䡣
//		T3L = (uint8_t)PWM_low;
//		PWMA_PIN = 1;
//	}
//}

void Motor_Run(uint8_t dir, uint16_t speed) {
	speed < PWM_HIGH_MIN ?			speed = PWM_HIGH_MIN:speed; //���д��С����Сռ�ձ����ݣ���ǿ��Ϊ��Сռ�ձȡ�
	speed > PWM_HIGH_MAX ?			speed = PWM_HIGH_MAX:speed; //���д��������ռ�ձ����ݣ���ǿ��Ϊ���ռ�ձȡ�

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
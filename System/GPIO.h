
#ifndef	__GPIO_H
#define	__GPIO_H


#define	GPIO_PullUp		0	//����׼˫���
#define	GPIO_HighZ		1	//��������
#define	GPIO_OUT_OD		2	//��©���
#define	GPIO_OUT_PP		3	//�������

#define	GPIO_Pin_0		((unsigned char)0x01) 	//IO���� Px.0
#define	GPIO_Pin_1		((unsigned char)0x02)	//IO���� Px.1
#define	GPIO_Pin_2		((unsigned char)0x04)	//IO���� Px.2
#define	GPIO_Pin_3		((unsigned char)0x08)	//IO���� Px.3
#define	GPIO_Pin_4		((unsigned char)0x10)	//IO���� Px.4
#define	GPIO_Pin_5		((unsigned char)0x20)	//IO���� Px.5
#define	GPIO_Pin_6		((unsigned char)0x40)	//IO���� Px.6
#define	GPIO_Pin_7		((unsigned char)0x80)	//IO���� Px.7
#define	GPIO_Pin_All	((unsigned char)0xFF)	//IO��������
	
#define	GPIO_P0			0		//
#define	GPIO_P1			1
#define	GPIO_P2			2
#define	GPIO_P3			3
#define	GPIO_P4			4
#define	GPIO_P5			5


typedef struct
{
	unsigned char	GPIO_Mode;		//IOģʽ,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	unsigned char	GPIO_Pin;		//Ҫ���õĶ˿�	
} GPIO_InitTypeDef;

int	GPIO_Init(unsigned char GPIO, GPIO_InitTypeDef *GPIOx);
void GPIO_SetBits(unsigned char GPIOx, unsigned char GPIO_Pin);
void GPIO_ResetBits(unsigned char GPIOx, unsigned char GPIO_Pin);
bit GPIO_ReadInputDataBit(unsigned char GPIOx, unsigned char GPIO_Pin);

#endif

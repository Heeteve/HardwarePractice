#ifndef _CONFIG_H_
#define _CONFIG_H_

/*board enumeration*/
#define BOARD_RICHBOT_STC15
//#define BOARD_RICHBOT_STC12
//#define BOARD_RICHBOT_STC89

/*CPU type enumeration*/
#define CPU_TYPE_STC12 0
#define CPU_TYPE_STC15 1
#define CPU_TYPE_STC89 2
/*Instruction set version enumeration*/
#define INS_VER_Y1 1
#define INS_VER_Y3 3
#define INS_VER_Y5 5


/*Board configuration.*/
#ifdef BOARD_RICHBOT_STC12 
#define CPU_TYPE  CPU_TYPE_STC12
#define CFG_SYSFREQ 11059200UL
#define INS_VER INS_VER_Y3
#define CPU_FLASH 61440
#define CPU_SRAM 1280
#endif

#ifdef BOARD_RICHBOT_STC15 
#define CPU_TYPE  CPU_TYPE_STC15
#define CFG_SYSFREQ 22118400UL
#define INS_VER INS_VER_Y5
#define CPU_FLASH 62464
#define CPU_SRAM 2048
#endif

#ifdef BOARD_RICHBOT_STC89 
#define CPU_TYPE  CPU_TYPE_STC89
#define CFG_SYSFREQ 11059200UL
#define INS_VER INS_VER_Y1
#define CPU_FLASH 8192
#define CPU_SRAM 512
#endif


#define		ENABLE		1
#define		DISABLE		0

//========================================

#define	PolityLow			0	//低优先级中断
#define	PolityHigh			1	//高优先级中断

//========================================

#define Main_Fosc_KHZ	(CFG_SYSFREQ / 1000)

/*STC15 SFR*/
#if (CPU_TYPE == CPU_TYPE_STC15)
#include "STC15F2K60S2.H"
#include	"GPIO.h"
#include	"PCA.h"
#endif
/*STC12 SFR*/
#if (CPU_TYPE == CPU_TYPE_STC12)
#include "STC12C5A60S2.H"
#include	"GPIO.h"
#include	"PCA.h"
#endif
/*STC89 SFR*/
#if (CPU_TYPE == CPU_TYPE_STC89)
#include <REGX52.H>
#endif

//sfr	AUXR = 0x8E;
//sfr INT_CLKO = 0x8F;
//sfr IE2   = 0xAF;	//STC12C5A60S2系列


/*   interrupt vector */
#define		INT0_VECTOR		0
#define		TIMER0_VECTOR	1
#define		INT1_VECTOR		2
#define		TIMER1_VECTOR	3
#define		UART1_VECTOR	4
#define		ADC_VECTOR		5
#define		LVD_VECTOR		6
#define		PCA_VECTOR		7
#define		UART2_VECTOR	8
#define		SPI_VECTOR		9
#define		INT2_VECTOR		10
#define		INT3_VECTOR		11
#define		TIMER2_VECTOR	12
#define		INT4_VECTOR		16
#define		UART3_VECTOR	17
#define		UART4_VECTOR	18
#define		TIMER3_VECTOR	19
#define		TIMER4_VECTOR	20


#define	TRUE	1
#define	FALSE	0

#endif



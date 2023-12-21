#include "global.h"                  // Device heade


/*************	功能说明	**************

本文件为STC15xxx系列的端口初始化程序,用户几乎可以不修改这个程序.


******************************************/



//========================================================================
// 函数: uint8t	GPIO_Init(uint8t GPIO, GPIO_InitTypeDef *GPIOx)
// 描述: 初始化IO口.
// 参数: GPIOx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
int	GPIO_Init(unsigned char GPIO, GPIO_InitTypeDef *GPIOx)
{
	if(GPIO > GPIO_P5)				return 1;	//空操作
	if(GPIOx->GPIO_Mode > GPIO_OUT_PP)	return 2;	//错误
	if(GPIO == GPIO_P0)
	{
		if(GPIOx->GPIO_Mode == GPIO_PullUp)		P0M1 &= ~GPIOx->GPIO_Pin,	P0M0 &= ~GPIOx->GPIO_Pin;	 //上拉准双向口
		if(GPIOx->GPIO_Mode == GPIO_HighZ)		P0M1 |=  GPIOx->GPIO_Pin,	P0M0 &= ~GPIOx->GPIO_Pin;	 //浮空输入
		if(GPIOx->GPIO_Mode == GPIO_OUT_OD)		P0M1 |=  GPIOx->GPIO_Pin,	P0M0 |=  GPIOx->GPIO_Pin;	 //开漏输出
		if(GPIOx->GPIO_Mode == GPIO_OUT_PP)		P0M1 &= ~GPIOx->GPIO_Pin,	P0M0 |=  GPIOx->GPIO_Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P1)
	{
		if(GPIOx->GPIO_Mode == GPIO_PullUp)		P1M1 &= ~GPIOx->GPIO_Pin,	P1M0 &= ~GPIOx->GPIO_Pin;	 //上拉准双向口
		if(GPIOx->GPIO_Mode == GPIO_HighZ)		P1M1 |=  GPIOx->GPIO_Pin,	P1M0 &= ~GPIOx->GPIO_Pin;	 //浮空输入
		if(GPIOx->GPIO_Mode == GPIO_OUT_OD)		P1M1 |=  GPIOx->GPIO_Pin,	P1M0 |=  GPIOx->GPIO_Pin;	 //开漏输出
		if(GPIOx->GPIO_Mode == GPIO_OUT_PP)		P1M1 &= ~GPIOx->GPIO_Pin,	P1M0 |=  GPIOx->GPIO_Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P2)
	{
		if(GPIOx->GPIO_Mode == GPIO_PullUp)		P2M1 &= ~GPIOx->GPIO_Pin,	P2M0 &= ~GPIOx->GPIO_Pin;	 //上拉准双向口
		if(GPIOx->GPIO_Mode == GPIO_HighZ)		P2M1 |=  GPIOx->GPIO_Pin,	P2M0 &= ~GPIOx->GPIO_Pin;	 //浮空输入
		if(GPIOx->GPIO_Mode == GPIO_OUT_OD)		P2M1 |=  GPIOx->GPIO_Pin,	P2M0 |=  GPIOx->GPIO_Pin;	 //开漏输出
		if(GPIOx->GPIO_Mode == GPIO_OUT_PP)		P2M1 &= ~GPIOx->GPIO_Pin,	P2M0 |=  GPIOx->GPIO_Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P3)
	{
		if(GPIOx->GPIO_Mode == GPIO_PullUp)		P3M1 &= ~GPIOx->GPIO_Pin,	P3M0 &= ~GPIOx->GPIO_Pin;	 //上拉准双向口
		if(GPIOx->GPIO_Mode == GPIO_HighZ)		P3M1 |=  GPIOx->GPIO_Pin,	P3M0 &= ~GPIOx->GPIO_Pin;	 //浮空输入
		if(GPIOx->GPIO_Mode == GPIO_OUT_OD)		P3M1 |=  GPIOx->GPIO_Pin,	P3M0 |=  GPIOx->GPIO_Pin;	 //开漏输出
		if(GPIOx->GPIO_Mode == GPIO_OUT_PP)		P3M1 &= ~GPIOx->GPIO_Pin,	P3M0 |=  GPIOx->GPIO_Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P4)
	{
		if(GPIOx->GPIO_Mode == GPIO_PullUp)		P4M1 &= ~GPIOx->GPIO_Pin,	P4M0 &= ~GPIOx->GPIO_Pin;	 //上拉准双向口
		if(GPIOx->GPIO_Mode == GPIO_HighZ)		P4M1 |=  GPIOx->GPIO_Pin,	P4M0 &= ~GPIOx->GPIO_Pin;	 //浮空输入
		if(GPIOx->GPIO_Mode == GPIO_OUT_OD)		P4M1 |=  GPIOx->GPIO_Pin,	P4M0 |=  GPIOx->GPIO_Pin;	 //开漏输出
		if(GPIOx->GPIO_Mode == GPIO_OUT_PP)		P4M1 &= ~GPIOx->GPIO_Pin,	P4M0 |=  GPIOx->GPIO_Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P5)
	{
		if(GPIOx->GPIO_Mode == GPIO_PullUp)		P5M1 &= ~GPIOx->GPIO_Pin,	P5M0 &= ~GPIOx->GPIO_Pin;	 //上拉准双向口
		if(GPIOx->GPIO_Mode == GPIO_HighZ)		P5M1 |=  GPIOx->GPIO_Pin,	P5M0 &= ~GPIOx->GPIO_Pin;	 //浮空输入
		if(GPIOx->GPIO_Mode == GPIO_OUT_OD)		P5M1 |=  GPIOx->GPIO_Pin,	P5M0 |=  GPIOx->GPIO_Pin;	 //开漏输出
		if(GPIOx->GPIO_Mode == GPIO_OUT_PP)		P5M1 &= ~GPIOx->GPIO_Pin,	P5M0 |=  GPIOx->GPIO_Pin;	 //推挽输出
	}
	return 0;	//成功
}


void GPIO_SetBits(unsigned char GPIOx, unsigned char GPIO_Pin)
{  
  
	if(GPIOx == GPIO_P0) {
		P0 |= GPIO_Pin;
	}
	if(GPIOx == GPIO_P1) {
		P1 |=  GPIO_Pin;
	}
	if(GPIOx == GPIO_P2) {
		P2 |=  GPIO_Pin;
	}
	if(GPIOx == GPIO_P3) {
		P3 |=  GPIO_Pin;
	}
	if(GPIOx == GPIO_P4) {
		P4 |=  GPIO_Pin;
	}
	if(GPIOx == GPIO_P5) {
		P5 |=  GPIO_Pin;
	}
}


void GPIO_ResetBits(unsigned char GPIOx, unsigned char GPIO_Pin)
{
	if(GPIOx == GPIO_P0) {
		P0 &= ~GPIO_Pin;
	}
	if(GPIOx == GPIO_P1) {
		P1 &= ~GPIO_Pin;
	}
	if(GPIOx == GPIO_P2) {
		P2 &= ~GPIO_Pin;
	}
	if(GPIOx == GPIO_P3) {
		P3 &= ~GPIO_Pin;
	}
	if(GPIOx == GPIO_P4) {
		P4 &= ~GPIO_Pin;
	}
	if(GPIOx == GPIO_P5) {
		P5 &= ~GPIO_Pin;
	}
}

bit GPIO_ReadInputDataBit(uint8_t GPIOx, uint8_t GPIO_Pin) {
	uint8_t _IO_image_ = 0xff;
	if(GPIOx == GPIO_P0) {
		_IO_image_ = P0;
		_IO_image_ &= GPIO_Pin;
		return _IO_image_;
	}
	if(GPIOx == GPIO_P1) {
		_IO_image_ = P1;
		_IO_image_ &= GPIO_Pin;
		return _IO_image_;
	}
	if(GPIOx == GPIO_P2) {
		_IO_image_ = P2;
		_IO_image_ &= GPIO_Pin;
		return _IO_image_;
	}
	if(GPIOx == GPIO_P3) {
		_IO_image_ = P3;
		_IO_image_ &= GPIO_Pin;
		return _IO_image_;
	}
	if(GPIOx == GPIO_P4) {
		_IO_image_ = P4;
		_IO_image_ &= GPIO_Pin;
		return _IO_image_;
	}
	if(GPIOx == GPIO_P5) {
		_IO_image_ = P5;
		_IO_image_ &= GPIO_Pin;
		return _IO_image_;
	}
	return 0;
}

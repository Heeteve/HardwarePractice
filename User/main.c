#include "global.h"

/**
 * @brief 系统初始化
 * @note 初始化SysTick定时器，初始化OLED显示，
 * 初始化电机PWM，初始化串口波特率9600，
 * 初始化红外遥控接收、蜂鸣器、循迹传感器、避障传感器。
 */
void System_Init(void) {
    SysTick_Init();
    DelayMs(1);
    OLED_Init();
    OLED_ShowString(1, 1, "Initing...");
    Motor_PWM_Init();
    Usart1_Init(9600);
    Buzzer_GPIO_Init();
    Infrared_Init();
    IR_Track_GPIO_Init();
    IR_Avoid_GPIO_Init();
    DelayMs(100);
}

void main(void) {
    System_Init();
    DelayMs(100);
    OLED_Clear();
    while (TRUE)
    {
        Controller();
        DelayMs(200);
    }
}

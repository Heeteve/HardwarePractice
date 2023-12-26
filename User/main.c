#include "global.h"

void System_Init(void) {
    SysTick_Init();
    DelayMs(1);
    Motor_PWM_Init();
    OLED_Init();
    OLED_ShowString(1, 1, "Initing...");
    Usart1_Init(9600);
    Buzzer_GPIO_Init();
    IR_Track_GPIO_Init();
    IR_Avoid_GPIO_Init();
    // Ultrasound_Init();
    // Ultrasound_PCA_SoftTimer_Init();
    DelayMs(100);
}

void main(void) {
    // float dis = 0.0;
    // char xdata oled_buf[16] = {0};
    System_Init();
    DelayMs(500);
    OLED_Clear();
    /*//蜂鸣器测试
    DelayMs(1000);
    Buzzer_TurnOn(1);
    OLED_ShowString(4, 1, "buzzING");
    DelayMs(1000);
    Buzzer_TurnOn(0);
    OLED_Clear();
    OLED_ShowString(4, 1, "Nop");*/

    //循迹测试
    while (1) {
        // Get_Track_Action_Old();
        Get_Track_Action();
        // Get_Track_Action_Single();
    }

    /*// 避障测试
    Avoid_Start();*/

    /*//超声波测试
    while (1) {
        //显示到OLED
        dis = Get_DistanceValue();
        sprintf(oled_buf, "%0.1fCM", dis);
        OLED_ShowString(1, 1, oled_buf);
                OLED_ShowString(3, 1, "AAA");
        DelayMs(1000);
    }*/
}

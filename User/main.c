#include "global.h"

void System_Init(void) {
    SysTick_Init();
    DelayMs(1);
    Motor_PWM_Init();
    OLED_Init();
    OLED_ShowString(1, 1, "Initing...");
    Usart1_Init(9600);
    Buzzer_GPIO_Init();
    // IR_Track_GPIO_Init();
    // IR_Avoid_GPIO_Init();
    Ultrasound_Init();
    Ultrasound_PCA_SoftTimer_Init();
    DelayMs(100);
}

void main(void) {
    // float dis = 0.0;
    // char xdata oled_buf[16] = {0};
    System_Init();
    DelayMs(1000);
    OLED_Clear();
    /*//∑‰√˘∆˜≤‚ ‘
    DelayMs(1000);
    Buzzer_TurnOn(1);
    OLED_ShowString(4, 1, "buzzING");
    DelayMs(1000);
    Buzzer_TurnOn(0);
    OLED_Clear();
    OLED_ShowString(4, 1, "Nop");*/

    /*//—≠º£≤‚ ‘
    while (1) {
        // get_action_old();
        Get_Action();
        // get_action_single();
    }*/

    // ±‹’œ≤‚ ‘
    Avoid_Start();

    /*//≥¨…˘≤®≤‚ ‘
    while (1) {
        //œ‘ æµΩOLED
        dis = Get_DistanceValue();
        sprintf(oled_buf, "%0.1fCM", dis);
        OLED_ShowString(1, 1, oled_buf);
                OLED_ShowString(3, 1, "AAA");
        DelayMs(1000);
    }*/

}

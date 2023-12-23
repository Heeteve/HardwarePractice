#include "global.h"
#include "track_test.h"
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
    // uint16_t LLL = 0, RRR = 0;
    float dis = 0.0;
    char xdata oled_buf[16] = {0};
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

    /*//OLED≤‚ ‘
    OLED_Clear();
    OLED_ShowString(1, 1, oled_buf);
    OLED_ShowString(2, 1, "1234567890123456");
    OLED_ShowString(3, 1, "A");
    OLED_ShowString(4, 16, "a");*/

    /*//—≠º£≤‚ ‘
    while (1) {
        // get_action_old();
        get_action();
        // get_action_single();
    }*/

    /*// ±‹’œ≤‚ ‘
    while (1) {
        Get_AvoidSensor_State(&LLL, &RRR);
        sprintf(oled_buf, "%d", LLL);
        OLED_ShowString(1, 1, "L:");
        OLED_ShowString(1, 3, oled_buf);
        sprintf(oled_buf, "%d", RRR);
        OLED_ShowString(1, 14, "R:");
        OLED_ShowString(1, 16, oled_buf);
        DelayMs(50);
    }*/

    //≥¨…˘≤®≤‚ ‘
    while (1) {
        //œ‘ æµΩOLED
        dis = Get_DistanceValue();
        sprintf(oled_buf, "%0.1fCM", dis);
        OLED_ShowString(1, 1, oled_buf);
        DelayMs(1000);
    }

}

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

avoid_test() { // ±‹’œ≤‚ ‘
    char xdata oled_buf[16] = {0};
    uint16_t LLL = 1, FFF = 1;
    while (1) {
        Get_AvoidSensor_State(&LLL, &FFF);
        if (FFF==0) // «∞”–
        {
            OLED_ShowString(1, 1, "F:0 R:0");
            // Motor_Run(STOP, PWM_DUTY / 100 * 100);
            Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 100);
            DelayMs(450);
            Motor_Run(STOP, PWM_DUTY / 100 * 100);
        }
        else if (LLL==0 && FFF==1) // ◊Û”–£¨«∞Œﬁ
        {
            OLED_ShowString(1, 1, "F:0 R:1");
            Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 80);
        }
        else if (LLL==1 && FFF==1) //ø’
        {
            OLED_ShowString(1, 1, "F:1 R:1");
            /*Motor_Run(FORWARD, PWM_DUTY / 100 * 100);
            DelayMs(150);
            // µ±◊Ûø’ ± º÷’◊Û◊™
            do
            {
                Get_AvoidSensor_State(&LLL, &FFF);
                Motor_Run(TURNLEFT, PWM_DUTY / 100 * 70);
            } while (LLL==1 && FFF==1);*/
            DelayMs(100);
            Motor_Run(TURNLEFT, PWM_DUTY / 100 * 80);

        }

        OLED_ShowString(1, 1, "F:");
        OLED_ShowString(1, 14, "R:");

        DelayMs(50);
    }
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

    //—≠º£≤‚ ‘
    while (1) {
        // get_action_old();
        Get_Action();
        // get_action_single();
    }

    /*// ±‹’œ≤‚ ‘
    avoid_test();*/

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

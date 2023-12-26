#include "global.h"

void IR_Avoid_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = IR_Avoid_S5_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(IR_Avoid_S5_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = IR_Avoid_S6_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(IR_Avoid_S6_PORT, &GPIO_InitStructure);
}

void Get_AvoidSensor_State(uint16_t *p_S5, uint16_t *p_S6) {
    *p_S5 = GPIO_ReadInputDataBit(IR_Avoid_S5_PORT, IR_Avoid_S5_PIN);
    *p_S6 = GPIO_ReadInputDataBit(IR_Avoid_S6_PORT, IR_Avoid_S6_PIN);
}

void Avoid_Start() { // 避障测试
    uint16_t LLL = 1, FFF = 1;
    while (TRUE) {
        Get_AvoidSensor_State(&LLL, &FFF);
        if (FFF == 0) // 前有
        {
            OLED_ShowString(1, 1, "F:1");
            // Motor_Run(STOP, PWM_DUTY / 100 * 100);
            Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 100);
            DelayMs(450);
            Motor_Run(STOP, PWM_DUTY / 100 * 100);
        } else if (LLL == 0 && FFF == 1) // 左有，前无
        {
            OLED_ShowString(1, 1, "L:1 F:0");
            Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 80);
        } else if (LLL == 1 && FFF == 1) //空
        {
            OLED_ShowString(1, 1, "L:0 F:0");
            /*Motor_Run(FORWARD, PWM_DUTY / 100 * 100);
            DelayMs(150);
            // 当左空时始终左转
            do
            {
                Get_AvoidSensor_State(&LLL, &FFF);
                Motor_Run(TURNLEFT, PWM_DUTY / 100 * 70);
            } while (LLL==1 && FFF==1);*/
            DelayMs(100);
            Motor_Run(TURNLEFT, PWM_DUTY / 100 * 80);
        }
        DelayMs(50);
    }
}
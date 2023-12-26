
#include "global.h"

void IR_Track_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = IR_Track_S1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(IR_Track_S1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = IR_Track_S2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(IR_Track_S2_PORT, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = IR_Track_S3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(IR_Track_S3_PORT, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = IR_Track_S4_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(IR_Track_S4_PORT, &GPIO_InitStructure);
}

void Get_TrackSensor_State(uint16_t *p_S1, uint16_t *p_S2, uint16_t *p_S3, uint16_t *p_S4) {
    *p_S1 = GPIO_ReadInputDataBit(IR_Track_S1_PORT, IR_Track_S1_PIN);
    *p_S2 = GPIO_ReadInputDataBit(IR_Track_S2_PORT, IR_Track_S2_PIN);
    *p_S3 = GPIO_ReadInputDataBit(IR_Track_S3_PORT, IR_Track_S3_PIN);
    *p_S4 = GPIO_ReadInputDataBit(IR_Track_S4_PORT, IR_Track_S4_PIN);
}

void get_action_old(void) { // 稳定版
    uint16_t LL = 0, CL = 0, CR = 0, RR = 0; // 左，中左，中右，右
    Get_TrackSensor_State(&LL, &CL, &CR, &RR);
    if (LL == 1 && CL == 1 && CR == 1 && RR == 1) { //全白
        Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 50);
    }
    if (LL == 0 && CL == 0 && CR == 0 && RR == 0) { //全黑
        Motor_Run(FORWARD, PWM_DUTY / 100 * 50);
    }

    // if (LL == 1 && CL == 0 && CR == 0 && RR == 0) { //中右黑，右转
    //     OLED_ShowString(1, 1, "LL CL CR RR");
    //     OLED_ShowString(2, 1, "0 1 1 1");
    //     turnRdeg(45);
    // }

    if (LL == 1 && CL == 0 && CR == 0 && RR == 1) { //中间黑
        Motor_Run(FORWARD, PWM_DUTY / 100 * 80);
    }
    if (LL == 1 && CL == 0 && CR == 1 && RR == 1) { //中左黑
        Motor_Run(TURNLEFT, PWM_DUTY / 100 * 60);
    }

    if (LL == 1 && CL == 1 && CR == 0 && RR == 1) { //中右黑
        Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 60);
    }
    if (LL == 1 && CL == 1 && CR == 1 && RR == 0) { //右黑
        Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 60);
    }
    if (LL == 0 && CL == 1 && CR == 1 && RR == 1) { //左黑
        Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 60);
    }
}
void Get_Action(void) { // 不稳定版
    uint16_t LL = 0, CL = 0, CR = 0, RR = 0; // 左，中左，中右，右
    Get_TrackSensor_State(&LL, &CL, &CR, &RR);
    if (LL == 1 && CL == 1 && CR == 1 && RR == 1) { //全白
        Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 65);
    }
    if (LL == 0 && CL == 0 && CR == 0 && RR == 0) { //全黑
        Motor_Run(FORWARD, PWM_DUTY / 100 * 82);
    }

    // if (LL == 1 && CL == 0 && CR == 0 && RR == 0) { //中右黑，右转
    //     OLED_ShowString(1, 1, "LL CL CR RR");
    //     OLED_ShowString(2, 1, "0 1 1 1");
    //     turnRdeg(45);
    // }

    if (LL == 1 && CL == 0 && CR == 0 && RR == 1) { //中间黑
        Motor_Run(FORWARD, PWM_DUTY / 100 * 82);
    }
    if (LL == 1 && CL == 0 && CR == 1 && RR == 1) { //中左黑
        Motor_Run(TURNLEFT, PWM_DUTY / 100 * 75);
    }

    if (LL == 1 && CL == 1 && CR == 0 && RR == 1) { //中右黑
        Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 75);
    }
    if (LL == 1 && CL == 1 && CR == 1 && RR == 0) { //右黑
        Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 75);
    }
    if (LL == 0 && CL == 1 && CR == 1 && RR == 1) { //左黑
        Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 75);
        DelayMs(100);
    }
}

void get_action_single(void) { //只使用RR
    uint16_t LL = 0, CL = 0, CR = 0, RR = 0; // 左，中左，中右，右
    Get_TrackSensor_State(&LL, &CL, &CR, &RR);
    if (LL == 0) {
        Motor_Run(TURNLEFT, PWM_DUTY / 100 * 60);
        DelayMs(1);
        Motor_Run(FORWARD, PWM_DUTY / 100 * 60);
        DelayMs(10);
    } else {
        OLED_ShowString(1, 1, "LL CL CR RR");
        OLED_ShowString(2, 1, "0  0  0  0");
        Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 50);
    }
}

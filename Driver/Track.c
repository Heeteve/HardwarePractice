#include "global.h"

/**
 * @brief 初始化红外循迹传感器GPIO引脚
 */
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

/**
 * @brief 获取循迹传感器状态
 * @param p_S1 指向存储传感器S1状态的变量的指针
 * @param p_S2 指向存储传感器S2状态的变量的指针
 * @param p_S3 指向存储传感器S3状态的变量的指针
 * @param p_S4 指向存储传感器S4状态的变量的指针
 * @return 无
 */
void Get_TrackSensor_State(uint16_t *p_S1, uint16_t *p_S2, uint16_t *p_S3, uint16_t *p_S4) {
    *p_S1 = GPIO_ReadInputDataBit(IR_Track_S1_PORT, IR_Track_S1_PIN);
    *p_S2 = GPIO_ReadInputDataBit(IR_Track_S2_PORT, IR_Track_S2_PIN);
    *p_S3 = GPIO_ReadInputDataBit(IR_Track_S3_PORT, IR_Track_S3_PIN);
    *p_S4 = GPIO_ReadInputDataBit(IR_Track_S4_PORT, IR_Track_S4_PIN);
}

void Track_Start() {
    while (TRUE)
    {
        Get_Track_Action();
    }
}

void Get_Track_Action_Old(void) { // 慢速稳定版
    uint16_t LL = 0, CL = 0, CR = 0, RR = 0; // 左，中左，中右，右
    Get_TrackSensor_State(&LL, &CL, &CR, &RR);
    if (LL == 1 && CL == 1 && CR == 1 && RR == 1) { //全白
        Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 50);
    }
    if (LL == 0 && CL == 0 && CR == 0 && RR == 0) { //全黑
        Motor_Run(FORWARD, PWM_DUTY / 100 * 50);
    }
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
void Get_Track_Action(void) { // 快速稳定版
    uint16_t LL = 0, CL = 0, CR = 0, RR = 0; // 左，中左，中右，右
    Get_TrackSensor_State(&LL, &CL, &CR, &RR);
    if (LL == 1 && CL == 1 && CR == 1 && RR == 1) { //全白
        Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 65);
    }
    if (LL == 0 && CL == 0 && CR == 0 && RR == 0) { //全黑
        Motor_Run(FORWARD, PWM_DUTY / 100 * 82);
    }
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

void Get_Track_Action_Single(void) { // 单传感器版
    uint16_t LL = 0, CL = 0, CR = 0, RR = 0; // 左，中左，中右，右
    Get_TrackSensor_State(&LL, &CL, &CR, &RR);
    if (LL == 0) {
        OLED_ShowString(1, 1, "LL");
        OLED_ShowString(2, 1, "1");
        Motor_Run(TURNLEFT, PWM_DUTY / 100 * 60);
        DelayMs(1);
        Motor_Run(FORWARD, PWM_DUTY / 100 * 60);
        DelayMs(10);
    } else {
        OLED_ShowString(1, 1, "LL");
        OLED_ShowString(2, 1, "0");
        Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 50);
    }
}

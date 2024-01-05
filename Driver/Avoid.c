#include "global.h"

/**
 * @brief 初始化红外避障传感器GPIO引脚
 */
void IR_Avoid_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = IR_Avoid_S1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(IR_Avoid_S1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = IR_Avoid_S2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(IR_Avoid_S2_PORT, &GPIO_InitStructure);
}

/**
 * @brief 获取避障传感器状态
 * @param p_S1 指向避障传感器S1状态的变量的指针
 * @param p_S2 指向避障传感器S2状态的变量的指针
 * @return None
 */
void Get_AvoidSensor_State(uint16_t *p_S1, uint16_t *p_S2) {
    *p_S1 = GPIO_ReadInputDataBit(IR_Avoid_S1_PORT, IR_Avoid_S1_PIN);
    *p_S2 = GPIO_ReadInputDataBit(IR_Avoid_S2_PORT, IR_Avoid_S2_PIN);
}

/**
 * @brief 启动避障程序
 * @note 这个函数不断检查避障传感器的状态，并根据传感器读数执行相应的动作。
 * 如果机器人前方有障碍物，它会停下来并进行向右旋转。
 * 如果左侧有障碍物但前方没有，它会向右转。
 * 如果左侧和前方都没有障碍物，它会向左转。
 */
void Avoid_Start() {
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
            // 当左空时始终左转
            DelayMs(100);
            Motor_Run(TURNLEFT, PWM_DUTY / 100 * 80);
        }
        DelayMs(50);
    }
}
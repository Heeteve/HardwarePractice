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


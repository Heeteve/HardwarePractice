
#include "global.h"                  // Device heade

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
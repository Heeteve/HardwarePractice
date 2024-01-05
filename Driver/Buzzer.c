#include "global.h"                  // Device heade

/**
 * @brief 初始化蜂鸣器GPIO引脚
 */
void Buzzer_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_PullUp;
    GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
}

/**
 * @brief 开启或关闭蜂鸣器
 *
 * @param on 0:关闭，1:开启
 */
void Buzzer_TurnOn(uint8_t on) {
    if (!on) {
        GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
    } else {
        GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN);
    }
}
#include "global.h"                  // Device heade

void Buzzer_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_PullUp;
    GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);

}

void Buzzer_TurnOn(uint8_t on) {
    if (!on) {
        GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
    } else {
        GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN);
    }
}
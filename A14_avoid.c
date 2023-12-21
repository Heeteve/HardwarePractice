   1          #include "global.h"   
   2          
   3          void IR_Avoid_GPIO_Init(void) {
   4   1        GPIO_InitTypeDef GPIO_InitStructure;
   5   1        
   6   1        GPIO_InitStructure.GPIO_Pin = IR_Avoid_S5_PIN;
   7   1        GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
   8   1        GPIO_Init(IR_Avoid_S5_PORT, &GPIO_InitStructure);
   9   1        
  10   1        GPIO_InitStructure.GPIO_Pin = IR_Avoid_S6_PIN;
  11   1        GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
  12   1        GPIO_Init(IR_Avoid_S6_PORT, &GPIO_InitStructure);
  13   1      }
  14          
  15          void Get_AvoidSensor_State(uint16_t *p_S5, uint16_t *p_S6) {
  16   1        *p_S5 = GPIO_ReadInputDataBit(IR_Avoid_S5_PORT, IR_Avoid_S5_PIN);
  17   1        *p_S6 = GPIO_ReadInputDataBit(IR_Avoid_S6_PORT, IR_Avoid_S6_PIN);
  18   1      }
  19          
  20          
#include "global.h" // Device header

void Ultrasound_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = Ultrasound_TRIG_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_OUT_PP;
    GPIO_Init(Ultrasound_TRIG_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = Ultrasound_ECHO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(Ultrasound_ECHO_PORT, &GPIO_InitStructure);
}

void Ultrasound_PCA_SoftTimer_Init(void) {
    PCA_InitTypeDef PCA_InitStructure;

    PCA_InitStructure.PCA_Clock = PCA_Clock_12T;
    PCA_InitStructure.PCA_Mode = PCA_Mode_SoftTimer;
    PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;
    PCA_Init(PCA0, &PCA_InitStructure);
}

/**
 * @brief  获取超声波测距距离
 * @param  None
 * @retval 返回距离CM，-1 没到测距周期，-2 未检测到超声波，-3 测距超时
 */
float Get_DistanceValue(void) {
    static uint32_t oldticks;
    uint32_t ticks = time_GetTicks();
    uint16_t t_microsecond;
    char xdata disBuf[16] = {0}; /*显存*/
    float t_distance = 0;

    if (ticks - oldticks < 100) return -1;
    oldticks = ticks;
    sprintf(disBuf, "%d", ticks);
    OLED_ShowString(2,1,disBuf);
    GPIO_SetBits(Ultrasound_TRIG_PORT, Ultrasound_TRIG_PIN); /*发送触发信号*/
    DelayMs(1);
    GPIO_ResetBits(Ultrasound_TRIG_PORT, Ultrasound_TRIG_PIN);

    while (!GPIO_ReadInputDataBit(Ultrasound_ECHO_PORT, Ultrasound_ECHO_PIN)) {
        ticks = time_GetTicks();
        if (ticks - oldticks > 100) {
            oldticks = ticks;
            return -2;
        }
    } /*等待Echo信号的高电平*/

    CH = 0; //清除PCA计数器
    CL = 0;
    CR = 1; //启动PCA计数器

    while (GPIO_ReadInputDataBit(Ultrasound_ECHO_PORT, Ultrasound_ECHO_PIN)) {
        ticks = time_GetTicks();
        if (ticks - oldticks > 100) {
            oldticks = ticks;
            return -3;
        }
    } /*等待Echo信号的低电平*/

    t_microsecond = CH;
    t_microsecond <<= 8;
    t_microsecond |= CL;
    CH = 0;
    CL = 0;
    CR = 0;

    /*距离计算：程序设定PCA以系统时钟的12分频进行计数
      在不考虑温度的情况下超声波传输速度为每微秒0.034厘米
    */
    t_distance = (t_microsecond * ((float)1000000 / (CFG_SYSFREQ / 12) * 0.034)) / 2;
    sprintf(disBuf, "%0.1fCM", t_distance);
    OLED_ShowString(1, 1, disBuf);

    return t_distance;
}

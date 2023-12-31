#include "global.h"
// 红外接收模块

unsigned char Time_width; // NEC协议时间定义（单位：微秒）
unsigned char Ir_Value[4];
unsigned char i, j, count;
uint8_t command = 0;
uint16_t Speed_Delay = 100; // 电机启动时长
char str[16];

/**
 * @brief 红外遥控接受初始化
 */
void Infrared_Init() {
    // 设置为INT0 中断
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = IR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_Init(GPIO_P3, &GPIO_InitStructure);

    // 设置INT1中断
    IT1 = 1; // INT1下降沿触发
    EX1 = 1; // INT1中断允许
    EA = 1; // 总中断允许
}

/**
 * @brief 解码NEC红外信号
 */
void decodeIR() interrupt INT1_VECTOR {
    EA = 0;
    Time_width = 0;
    EX0 = 0;  // 关闭中断防止干扰
    if (IR_PIN == 0) // 判断是否是正确的信号，排除干扰
    {
        count = 95;                          // 90 * 0.1ms = 9ms,超过说明接收到错误的信号
        while ((IR_PIN == 0) && (count > 0)) // 等待9ms的低电平过去
        {
            DelayUs(100);
            count--;
        }
        if (IR_PIN == 1) // 9ms低电平已过去
        {
            count = 50;                          // 45 * 0.1ms = 4.5ms
            while ((IR_PIN == 1) && (count > 0)) // 等待4.5ms的高电平过去
            {
                DelayUs(100);
                count--;
            }
            for (i = 0; i < 4; i++) // 共有4组数据
            {
                for (j = 0; j < 8; j++) // 接收一组数据
                {
                    count = 6;                           // 6*0.1ms=0.6ms=600us
                    while ((IR_PIN == 0) && (count > 0)) // 等待560us低电平过去
                    {
                        DelayUs(100);
                        count--;
                    }
                    count = 55;                          // 50*0.1ms=5ms
                    while ((IR_PIN == 1) && (count > 0)) // 计算高电平的时间宽度
                    {
                        DelayUs(100); // 2.24ms/0.1ms=23
                        Time_width++; // 最长计算到23  55-23=32
                        count--;
                        if (Time_width > 35) // 20*0.1=2.8ms>2.24ms
                        {                    // 说明已经超出信号范围
                            EX0 = 1;         // 打开外部中断
                            return;          // 错误则直接结束中断
                        }
                    }
                    Ir_Value[i] >>= 1;   // i表示第几组数据
                    if (Time_width >= 8) // 如果高电平大于1.12ms，
                    {                    // 那么是1，否则默认为0，直接移位
                        Ir_Value[i] |= 0x80;
                    }
                    Time_width = 0; // 用完要清零
                }
            }
        }
        if (Ir_Value[2] != ~Ir_Value[3]) { return; } // 错误则重新开始，退出中断
    }

    command = Ir_Value[2];
    OLED_Clear();    // 清屏
    sprintf(str, "0x%X", command);
    OLED_ShowString(3, 1, str);

    EA = 1;
}

/**
 * @brief 红外控制函数，根据红外遥控器的输入执行相应的动作。
 */
void Controller(void) {
    switch (Ir_Value[2]) {
        /*运动控制*/
    case K_UP:
        Motor_Run(FORWARD, PWM_DUTY / 100 * 100);
        OLED_ShowString(1, 1, "UP");
        DelayMs(Speed_Delay);
        Motor_Run(STOP, 0);
        break;
    case K_DOWN:
        Motor_Run(BACKWARDS, PWM_DUTY / 100 * 100);
        OLED_ShowString(1, 1, "DOWN");
        DelayMs(Speed_Delay);
        Motor_Run(STOP, 0);
        break;
    case K_LEFT:
        Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 70);
        OLED_ShowString(1, 1, "SPINLEFT");
        DelayMs(Speed_Delay);
        Motor_Run(STOP, 0);
        break;
    case K_RIGHT:
        Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 70);
        OLED_ShowString(1, 1, "SPINRIGHT");
        DelayMs(Speed_Delay);
        Motor_Run(STOP, 0);
        break;
    case K_SPINLEFT:
        Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 100);
        OLED_ShowString(1, 1, "SPINLEFT 90");
        DelayMs(400);
        Motor_Run(STOP, 0);
        break;
    case K_SPINRIGHT:
        Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 100);
        OLED_ShowString(1, 1, "SPINRIGHT 90");
        DelayMs(400);
        Motor_Run(STOP, 0);
        break;
    case K_PLUS:
        Motor_Run(TURNLEFT, PWM_DUTY / 100 * 100);
        OLED_ShowString(1, 1, "LEFT Front");
        DelayMs(Speed_Delay);
        Motor_Run(STOP, 0);
        break;
    case K_MINUS:
        Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 100);
        OLED_ShowString(1, 1, "RIGHT Front");
        DelayMs(Speed_Delay);
        Motor_Run(STOP, 0);
        break;
        /*功能控制*/
    case K_STOP: // 电源键进入避障
        Motor_Run(STOP, 0);
        OLED_ShowString(1, 1, "STOP");
        Avoid_Start();
        break;
    case K_SOUND:
        OLED_ShowString(1, 1, "SOUND");
        Buzzer_TurnOn(1);
        DelayMs(200);
        Buzzer_TurnOn(0);
        break;
    case K_LIGHT: // 灯光键进入循迹
        OLED_ShowString(1, 1, "LIGHT");
        Track_Start();
        break;
    case K_0: // 长直行
        Motor_Run(FORWARD, PWM_DUTY / 100 * 100);
        OLED_ShowString(1, 1, "0");
        DelayMs(1000);
        Motor_Run(STOP, 0);
        break;
    case K_1:
        OLED_ShowString(2, 1, "LEN: Short");
        Speed_Delay = 50;
        break;
    case K_2:
        OLED_ShowString(2, 1, "LEN: Normal");
        Speed_Delay = 100;
        break;
    case K_3:
        OLED_ShowString(2, 1, "LEN: Long");
        Speed_Delay = 500;
        break;
    case K_8: // 超长直行
        Motor_Run(FORWARD, PWM_DUTY / 100 * 100);
        OLED_ShowString(1, 1, "GO GO GO");
        DelayMs(3400);
        Motor_Run(STOP, 0);
        break;
    case K_9:
        OLED_ShowString(1, 1, "Stop");
        Motor_Run(STOP, 0);
        break;
    default:
        OLED_ShowString(1, 1, "DEFAULT");
        Motor_Run(STOP, 0);
        break;
    }
    for (i = 0; i < 4; i++) {
        Ir_Value[i] = 0;
    }
}
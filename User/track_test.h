#include "global.h"
#include "turn90_test.h"
void Get_Track_Action_Old(void) { // 稳定版
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
void Get_Track_Action(void) { // 不稳定版
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

void Get_Track_Action_Single(void) { //只使用RR
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


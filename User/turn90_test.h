#define turnL90 440
#define turnR90 440
#define turnR45 200

void turnRdeg(int deg) {
    switch (deg) {
    case 45:
        Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 100);
        DelayMs(turnR45);
        Motor_Run(STOP, PWM_DUTY / 100 * 100);
        DelayMs(1);
        break;
    case 90:
        Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 100);
        DelayMs(turnR90);
        Motor_Run(STOP, PWM_DUTY / 100 * 100);
        DelayMs(1);
    default:
        break;
    }
}


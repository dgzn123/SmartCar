#include "PWM.h"
/*
********************************************************************************************************
*                                            Project Driver Code
*                                      Brushless Motor PWM Driver
*
*                             (c) Copyright 2026 Henan Polytechnic University
*                       School of Computer Science and Technology, 510 Laboratory
*                                   All Rights Reserved
*
*  File Name   : motor_pwm.c
*  Description : Bottom driver for brushless motor, implementing PWM output
*                and motor speed closed-loop control function.
*  Author      : 510 Laboratory
*  Date        : 2026-04-25
*
*  Statement   : This code is only for internal laboratory learning,
*                scientific research and project development.
*                Unauthorized secondary distribution and commercial
*                use are strictly prohibited.
*********************************************************************************************************
*/

void PWM_Init(void)
{


  //PWM-IO初始化
    //ATOM_PWM_InitConfig(IfxGtm_ATOM3_4_TOUT98_P11_9_OUT, 0, 50);
    //ATOM_PWM_InitConfig(IfxGtm_ATOM3_4_TOUT98_P11_9_OUT, 0, 50);

    //SERVO_SetPwmValue(servoStr.thresholdMiddle);
    //SERVO_SetPwmValue(1500);
}

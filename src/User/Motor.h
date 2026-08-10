#ifndef __MOTOR_H__
#define __MOTOR_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "include.h"

/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

#define  MOTOR_PWM_MAX   		    1000//400		//OCR=95%,防止占空比过大烧毁MOS管
#define  MOTOR_PWM_MIN			    -1000 //-400		//OCR=95%
#define  MOTOR_SPEED_MAX		    2.2f	 	//电机最大转速(m/s) (0.017,8.04)
//#define  PI					        3.141593f   //π
#define  MOTOR_CONTROL_CYCLE	    0.01f    	//速度控制周期T=10ms

/**
* @brief    电机参数
**/
typedef struct 
{
	float ReductionRatio ;					    //电机减速比
	float EncoderLine ; 						//编码器线数=光栅数16*4
	float EncoderValue;				    //电机实时速度
	float DiameterWheel;						//车轮直径:mm
	boolean CloseLoop;							    //闭环模式
	uint16_t Counter;							//线程计数器
}MotorStruct;


extern MotorStruct motorStr;


void MOTOR_Init(void);
void MOTOR_SetPwmValue(signed int pwm);
void MOTOR_ControlLoop(float speed);
void MOTOR_Timer(void);


//===========================================  End Of File  ===========================================//
#endif

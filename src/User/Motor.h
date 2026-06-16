#ifndef __PWM_H__
#define __PWM_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "include.h"

/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

#define  MOTOR_PWM_MAX   		    1000//400		//OCR=95%,��ֹ��ռ�ձ���������MOS��
#define  MOTOR_PWM_MIN			    -1000 //-400		//OCR=95%
#define  MOTOR_SPEED_MAX		    2.2f	 	//������ת��(m/s) (0.017,8.04)
//#define  PI					        3.141593f   //��
#define  MOTOR_CONTROL_CYCLE	    0.01f    	//�����������T��10ms

/**
* @brief    ������
**/
typedef struct 
{
	float ReductionRatio ;					    //������ٱ�
	float EncoderLine ; 						//����������=��դ��16*4
	float EncoderValue;				    //������ʵʱ�ٶ�
	float DiameterWheel;						//����ֱ����mm
	boolean CloseLoop;							    //����ģʽ
	uint16_t Counter;							//�̼߳�����
}MotorStruct;


extern MotorStruct motorStr;


void MOTOR_Init(void);
void MOTOR_SetPwmValue(signed int pwm);
void MOTOR_ControlLoop(float speed);
void MOTOR_Timer(void);


//===========================================  End Of File  ===========================================//
#endif



/*************************************************************************
 *  ÎÄ¼þÃû³Æ£ºSTM32 to LQType.h
 *  ¹¦ÄÜËµÃ÷£ºÉùÃ÷Ò»Ð©ÁúÇñ¿â²»°üº¬£¬µ«ÒÆÖ²³ÌÐò±ØÐëÓÃµ½µÄ¿â»òÕßdefine¡£Ä¿µÄÊÇ²»ÓÃ
 *          ÐÞ¸ÄÁúÇñ¿â£¬·½±ãÑ§Ï°Õß¿´¶®´úÂë¡£
 *  ²ÎÊýËµÃ÷£ºÎÞ
 *  º¯Êý·µ»Ø£ºÎÞ
 *     ×÷Õß£ººÓÄÏÀí¹¤´óÑ§Âþ»­¼¼ÊõÑÐ¾¿Éç£¨ÂþÑÐÉç£©Ð¡Âþ
 *  ÐÞ¸ÄÊ±¼ä£º2024Äê4ÔÂ23ÈÕ
 *  ±¸    ×¢£ºÊ¹ÓÃÊ±Ö±½ÓÒýÓÃinclude.h¼´¿É¡£
 *************************************************************************/

#ifndef _STM32_TO_LQTYPE_H_
#define _STM32_TO_LQTYPE_H_


#include "Delay.h"
#include "Encoder.h"
#include "Gpio.h"
#include "Pid.h"
#include "Motor.h"
#include "Flash.h"
#include "Soc.h"
#include "Timer.h"
#include "Icar.h"
#include "Servo.h"
#include "Rgb.h"
#include "Usb.h"


//#include "stdbool.h"     //ºÍPlatform_Types.h³åÍ»£¬½ûÓÃ
//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª//
//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª³õ´ú»úÒý½ÅÅäÖÃÄ¿Â¼¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª//
//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª//

//P15_3             PC13    MCU_SOC_IIC_SDA soft iic    O_PP    50M
//P15_4             PC14    MCU_SOC_IIC_SCL soft iic    O_PP    50M
//P15_2             PC15    MCU_SOC_ALRT
//P15_8             PA2     MCU_KEY_INA                 floating            1   1   R/F
//P15_6             PA3     MCU_BUZZER                  O_PP    2M
//P10_3             PA6     MCU_ENCODER_A       TIM3    I_F
//P10_1             PA7     MCU_ENCODER_B       TIM3    I_F
//P15_7             PB12    MCU_LED_SYS                 O_PP    2M
//ATOM3_CH6_P11_11  PB6     MCU_SERVO_PWM_A     TIM4    AF_PP   50M
//P13_2             PB4     GPIO_EXTEND_B
//P13_1             PB3     GPIO_EXTEND_A               O_PP    50M
//P14_1             PA10    MCU_USB_USART1_RTX          I_F     50M         2   1   USART_Mode_Rx
//P14_0             PA9     MCU_USB_USART1_TXD          AF_PP   50M                 USART_Mode_Tx
//ATOM2_CH4_P11_9   PA8     MCU_MOTOR_PWM   TIM1        AF_PP   50M
//P11_3             PB14    MCU_MOTOR_DIR               O_PP    50M

//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª//
//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª³õ´ú»úÒý½ÅÅäÖÃÄ¿Â¼¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª//
//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª//


#define ANGLE_TO_RAD(x)     ( (x) * PI / 180.0 )                                // ½Ç¶È×ª»»Îª»¡¶È
#define RAD_TO_ANGLE(x)     ( (x) * 180.0 / PI )                                // »¡¶È×ª»»Îª½Ç¶È
#define PI                  ( 3.1415926535898 )

typedef uint32 u32;
typedef uint16 u16;
typedef uint8  u8;

typedef union
{
    uint8_t U8_Buff[2];
    uint16_t U16;
    int16_t S16;
}Bint16_Union;

typedef union
{
    uint8_t U8_Buff[4];
    float Float;
    unsigned long U32;
}Bint32_Union;





#endif

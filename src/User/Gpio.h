#ifndef __GPIO_H__
#define __GPIO_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/

#include "include.h"
#include "../APP/LQ_GPIO_LED.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

#define LED_ON          	(PIN_Write(P15_7, 0))
#define LED_OFF       		(PIN_Write(P15_7, 1))
#define LED_REV       		(LED_Ctrl(LEDSYS, RVS))

#define BUZZER_ON           (PIN_Write(P15_6, 1))
#define BUZZER_OFF          (PIN_Write(P15_6, 0))
#define BUZZER_REV          (LED_Ctrl(LEDBUZ, RVS))

/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/
/**
* @brief    蜂鸣器音效
**/
typedef enum 
{
    BuzzerOk = 0,						//确认提示音
	BuzzerWarnning,						//报警提示音
	BuzzerSysStart,						//开机提示音
    BuzzerDing,                         //叮=====(￣▽￣*)
    BuzzerFinish,                       //结束提示音
}BuzzerEnum;


/**
* @brief    按键和LED相关
**/
typedef struct 
{
	boolean KeyPress;					    //按键输入-B
	uint16_t CounterLed;				//LED闪烁计数器
}GpioStruct;


/**
* @brief    蜂鸣器相关
**/
typedef struct 
{
	boolean Enable;						//使能标志
	uint16_t Times;					    //鸣叫次数
	uint16_t Counter;				    //计数器
	uint16_t Cut;					    //间隔时间
	boolean Silent;						//是否禁用蜂鸣器
}BuzzerStruct;


extern GpioStruct gpioStr;
extern BuzzerStruct buzzerStr;

void GPIO_Initialize(void);
void GPIO_Timer(void);
void EXTI2_IRQHandler(void);
void GPIO_Handle(void);
void GPIO_BuzzerEnable(BuzzerEnum buzzer);
void EXTI2_IRQHandler(void);
#endif

//===========================================  End Of File  ===========================================//


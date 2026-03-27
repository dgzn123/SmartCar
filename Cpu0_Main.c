/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC264DA核心板
【编    写】chiusir
【E-mail】chiusir@163.com
【软件版本】V1.2 版权所有，单位使用请先联系授权
【最后更新】2023年11月10日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】AURIX Development Studio1.6版本
【Target 】 TC264DA/TC264D
【Crystal】 20.000Mhz
【SYS PLL】 200MHz
________________________________________________________________
基于iLLD_1_0_1_11_0底层程序,

使用例程的时候，建议采用没有空格的英文路径，
除了CIF为TC264DA独有外，其它的代码兼容TC264D
本库默认初始化了EMEM：512K，如果用户使用TC264D，注释掉EMEM_InitConfig()初始化函数。
工程下\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c第164行左右。
=================================================================
程序配套视频地址：https://space.bilibili.com/95313236
=================================================================
-----------------------------------------------------------------
 默认屏幕显示接口，用户可以使用TFT或者OLED模块
TFTSPI_CS     P20_14     龙邱TC母板 CS管脚 默认拉低，可以不用
TFTSPI_SCK    P20_11     龙邱TC母板 SPI SCK管脚
TFTSPI_SDI    P20_10     龙邱TC母板 SPI MOSI管脚
TFTSPI_DC     P20_12     龙邱TC母板 D/C管脚
TFTSPI_RST    P20_13     龙邱TC母板 RESET管脚
-----------------------------------------------------------------
OLED_CK       P20_14     龙邱TC母板OLED CK管脚
OLED_DI       P20_11     龙邱TC母板OLED DI管脚
OLED_RST      P20_10     龙邱TC母板OLED RST管脚
OLED_DC       P20_12     龙邱TC母板OLED DC管脚
OLED_CS       P20_13     龙邱TC母板OLED CS管脚 默认拉低，可以不用
----------------------------------------------------------------
默认按键接口
KEY0p         P22_0      龙邱TC母板上按键0
KEY1p         P22_1      龙邱TC母板上按键1
KEY2p         P22_2      龙邱TC母板上按键2
DSW0p         P33_9      龙邱TC母板上拨码开关0
DSW1p         P33_11     龙邱TC母板上拨码开关1
-----------------------------------------------------------------
默认LED接口
LED0p         P10_6      龙邱TC母板核心板上LED0 翠绿
LED1p         P10_5      龙邱TC母板核心板上LED1 蓝灯
LED2p         P20_6      龙邱TC母板上LED0
LED3p         P20_7      龙邱TC母板上LED1
-----------------------------------------------------------------
默认蜂鸣器接口
BEEPp         P33_8      龙邱TC母板上蜂鸣器接口
-----------------------------------------------------------------
定时器
有两个CCU6模块  每个模块有两个独立定时器  触发定时器中断 定时器中断服务函数在LQ_CCU6.c文件中
推荐使用CCU6模块，STM用作系统时钟或者延时；
-----------------------------------------------------------------
功能说明：
定时器测试模块，主函数中只负责定时器的初始化，定时器中的回调函数在LQ_CCU6.c文件中，编译烧录后，会发现LED灯会对应定时时间闪烁
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include <IfxCpu.h>
#include <IfxScuCcu.h>
#include <IfxScuWdt.h>
#include <IfxStm.h>
#include <IfxStm_reg.h>
#include <stdio.h>

#include "include.h"
App_Cpu0 g_AppCpu0;                       // brief CPU 0 global data
IfxCpu_mutexLock mutexCpu0InitIsOk = 1;   // CPU0 初始化完成标志位
volatile char mutexCpu0TFTIsOk=0;         // CPU1 0占用/1释放 TFT

/*************************************************************************
*  函数名称：int core0_main (void)
*  功能说明：CPU0主函数
*  参数说明：无
*  函数返回：无
*  修改时间：2023年11月10日
*  备    注：
*************************************************************************/
int core0_main (void)
{

	// 关闭CPU总中断
	IfxCpu_disableInterrupts();

	// 关闭看门狗，如果不设置看门狗喂狗需要关闭
	IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
	IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

	// 读取总线频率
	g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
	g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
	g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
	g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);



	// LED灯所用P10.6和P10.5初始化

	//GPIO_LED_Init();

	// 开启CPU总中断
	IfxCpu_enableInterrupts();

	// 通知CPU1，CPU0初始化完成
	IfxCpu_releaseMutex(&mutexCpu0InitIsOk);
	// 切记CPU0,CPU1...不可以同时开启屏幕显示，否则冲突不显示
	mutexCpu0TFTIsOk=0;         // CPU1： 0占用/1释放 TFT


//   CCU6_InitConfig(CCU60, CCU6_Channel0, 100 * 1000);//CCU6初始化200ms
//	CCU6_InitConfig(CCU61, CCU6_Channel0, 400 * 1000);//CCU6初始化400ms
//	CCU6_InitConfig(CCU60, CCU6_Channel1, 200 * 1000);//CCU6初始化800ms
	CCU6_InitConfig(CCU61, CCU6_Channel1, 1 * 1000);//CCU6初始化1600ms
	UART_InitConfig(UART0_RX_P14_1,UART0_TX_P14_0, 115200);
	PIN_InitConfig(P15_8,PIN_MODE_INPUT,0);
	PIN_Exti(P15_8, PIN_IRQ_MODE_RISING_FALLING);


	        Delay_Ms(100);                      //启动延时：等待系统稳定
	        FLASH_LoadAllConfig();              //加载系统配置

	        ICAR_Init();                        //智能车参数初始化

	        ENCODER_Init();                     //编码器初始化

	        GPIO_Initialize();                  //GPIO初始化

	        PID_Init();                         //PID参数初始化
	        MOTOR_Init();                       //电机初始化
	        SERVO_Init();                       //舵机初始化

	        USB_Edgeboard_Init();               //USB通信初始化

	        SOC_Init();                         //电量计初始化

	        RGB_Init();                         //RGB灯通信初始化

	        Delay_Ms(100);                      //启动延时：等待系统稳定

	        PIN_InitConfig(P20_8,PIN_MODE_OUTPUT,0);
	        PIN_InitConfig(P20_9,PIN_MODE_OUTPUT,0);
	        PIN_InitConfig(P21_4,PIN_MODE_OUTPUT,0);
	        PIN_InitConfig(P21_5,PIN_MODE_OUTPUT,0);
	        //CCU6_InitConfig(CCU60, CCU6_Channel1 , 100*1000);       //系统主线程定时器初始化

	        GPIO_BuzzerEnable(BuzzerSysStart);  //开机音效


	//定时器的中断函数在LQ_CCU6.c文件中
    while (1)	//主循环
    {

      /*PIN_Write(P20_8,1);
        Delay_Ms(100);
        PIN_Write(P20_8,0);
        Delay_Ms(100);
        PIN_Write(P20_8,1);
        Delay_Ms(100);
        PIN_Write(P20_8,0);
        Delay_Ms(100);
        PIN_Write(P20_8,1);
*/
/*
                PIN_Write(P20_9,1);
                Delay_Ms(100);
                PIN_Write(P20_9,0);
                Delay_Ms(100);
                PIN_Write(P20_9,1);
                Delay_Ms(100);
                PIN_Write(P20_9,0);
                Delay_Ms(100);
                PIN_Write(P20_9,1);
*/
/*
        PIN_Write(P21_4,1);
        Delay_Ms(100);
        PIN_Write(P21_4,0);
        Delay_Ms(100);
        PIN_Write(P21_4,1);
        Delay_Ms(100);
        PIN_Write(P21_4,0);
        Delay_Ms(100);
        PIN_Write(P21_4,1);
*/

                        GPIO_Handle();                  //GPIO控制：LED/蜂鸣器

                        SOC_Handle();                   //电量计采样

                        ICAR_Handle();                  //智能车控制

                        FLASH_Handle();                 //Flash存储

                        USB_Edgeboard_Handle();         //USB通信控制
                        //LED_OFF ;




    }


}






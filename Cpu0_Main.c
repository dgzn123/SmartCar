/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��chiusir
��E-mail��chiusir@163.com
�������汾��V1.2 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2023��11��10��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��AURIX Development Studio1.6�汾
��Target �� TC264DA/TC264D
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________
����iLLD_1_0_1_11_0�ײ����,
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include <IfxCpu.h>
#include <IfxScuCcu.h>
#include <IfxScuWdt.h>
#include <IfxStm.h>
#include <IfxStm_reg.h>
#include <stdio.h>

#include "include.h"
App_Cpu0 g_AppCpu0;
IfxCpu_mutexLock mutexCpu0InitIsOk = 1;
volatile char mutexCpu0TFTIsOk=0;

int core0_main (void)
{
	IfxCpu_disableInterrupts();

	IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
	IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

	g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
	g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
	g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
	g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

	IfxCpu_enableInterrupts();
	IfxCpu_releaseMutex(&mutexCpu0InitIsOk);
	mutexCpu0TFTIsOk=0;

	// ---- �����ʼ�� ----
	UART_InitConfig(UART0_RX_P14_1, UART0_TX_P14_0, 115200);
	PIN_InitConfig(P15_8, PIN_MODE_INPUT, 0);
	PIN_Exti(P15_8, PIN_IRQ_MODE_RISING_FALLING);

	Delay_Ms(100);

	ICAR_Init();
	ENCODER_Init();
	GPIO_Initialize();
	PID_Init();
	MOTOR_Init();
	SERVO_Init();
		USB_Edgeboard_Init();
		IMU_Init();

	Delay_Ms(100);

	PIN_InitConfig(P20_8, PIN_MODE_OUTPUT, 0);
	PIN_InitConfig(P20_9, PIN_MODE_OUTPUT, 0);
	PIN_InitConfig(P21_4, PIN_MODE_OUTPUT, 0);
	PIN_InitConfig(P21_5, PIN_MODE_OUTPUT, 0);

	// ϵͳ1ms��ʱ����ʹ��CCU60
	// �ֶ�ʹ��CCU60ģ�飨��Safety ENDINIT����ΪCLC�Ĵ�����Safety ENDINIT������
	{
		uint16 safetyPw = IfxScuWdt_getSafetyWatchdogPassword();
		IfxScuWdt_clearSafetyEndinit(safetyPw);
		MODULE_CCU60.CLC.B.DISR = 0U;  // ����ʹ��ģ��ʱ��
		IfxScuWdt_setSafetyEndinit(safetyPw);
	}
	CCU6_InitConfig(CCU60, CCU6_Channel0, 1000);

	GPIO_BuzzerEnable(BuzzerSysStart);

	while (1)
	{
		GPIO_Handle();
		ICAR_Handle();
		USB_Edgeboard_Handle();
		IMU_Handle();
	}
}

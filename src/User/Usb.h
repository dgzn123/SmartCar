/*************************************************************************
 *  文件名称：Usb.h
 *  功能说明：USB通信代码
 *     作者：河南理工大学漫画技术研究社（漫研社）小漫
 *  修改时间：2024年4月23日
 *  备    注：无
 *************************************************************************/
#ifndef __USB_H__
#define __USB_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "include.h"                                     //模块互联头文件

#define USB_FRAME_HEAD               0x42                //USB通信序列帧头
#define USB_FRAME_LENMIN             4                   //USB通信序列字节最短长度
#define USB_FRAME_LENMAX             30                  //USB通信序列字节最长长度

#define USB_ADDR_HEART               0x00                //监测软件心跳
#define USB_ADDR_CONTROL             0x01                //智能车控制
#define USB_ADDR_SPEEDMODE           0x02                //速控模式
#define USB_ADDR_SERVOTHRESHOLD      0x03                //舵机阈值
#define USB_ADDR_BUZZER              0x04                //蜂鸣器音效
#define USB_ADDR_LIGHT               0x05                //LED灯效
#define USB_ADDR_KEYINPUT            0x06                //按键输入
#define USB_ADDR_BATTERY             0x07                //电池信息

//仅限自检软件通信使用
#define USB_ADDR_INSPECTOR           0x0A                //智能车自检软件连接心跳
#define USB_ADDR_SELFCHECK           0x0B                //智能车自检开始
#define USB_ADDR_SPEEDBACK           0x08                //车速信息反馈：m/s


typedef struct
{
    boolean receiveStart;                                      //数据接收开始
    uint8 receiveIndex;                                   //接收序列
    boolean receiveFinished;                                   //数据队列接收并校验完成
    uint8 receiveBuff[USB_FRAME_LENMAX];                  //USB接收队列：临时接收
    uint8 receiveBuffFinished[USB_FRAME_LENMAX];          //USB接收队列：校验成功
    uint16 counter;                                       //计数器
    uint16 counterDrop;                                   //掉线计数器

    uint16 counterSend;                                   //自检数据发送计数器
    boolean connected;                                         //上位机通信连接状态
    boolean inspectorEnable;                                   //智能汽车自检软件连接使能
}UsbStruct;


extern UsbStruct usbStr;

void USB_Edgeboard_Init(void);
void USB_Edgeboard_TransmitByte(uint8 data);
void USART1_IRQHandler(void);
void USB_Edgeboard_Timr(void);
void USB_Edgeboard_Handle(void);
void USB_Edgeboard_TransmitKey(uint16_t time);

//智能车自检
void USB_Edgeboard_ServoThreshold(uint8_t chanel);
void USB_Edgeboard_KeyPress(uint16_t time);
void USB_Edgeboard_BatteryInfo(void);
void USB_Edgeboard_CarSpeed(void);
void USB_Edgeboard_Selfcheck(uint8_t step);


#endif

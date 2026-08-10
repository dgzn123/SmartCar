#include "Rgb.h"
#include "LQ_GPIO.h"
#include "LQ_GTM.h"
#include "IfxDma_Dma.h"
#include "IfxSrc.h"
/*
********************************************************************************************************
*                                               示例代码
*                                             EXAMPLE  CODE
*
*                             (c) Copyright 2021; SaiShu.Lcc.; Leo
*                                 版权所属[北京赛曙科技有限公司]
*
*               The code is for internal use only, not for commercial transactions(开源学习,请勿商用).
*               The code ADAPTS the corresponding hardware circuit board(代码使用CarDo智控板),
*               the specific details consult the professional(欢迎联系我们).
*********************************************************************************************************
*/

/*
 * WS2812 驱动引脚：P15_4 -> ATOM1_CH7 800kHz PWM + DMA
 *
 * ATOM1_CH7 在 100MHz (CMU CLK0) 下，800kHz 频率 -> 周期计数 = 125 个时钟。
 * CM1(比较值)控制高电平持续时间（即 0~CM1 高电平，CM1~125 低电平）：
 *   位 0 ：  CM1=40  (高电平持续时间 0.4us)
 *   位 1 ：  CM1=80  (高电平持续时间 0.8us)
 *   复位    CM1=0   (高电平持续时间 0us，帧间隔>50us 使灯复位 48*1.25us=60us)
 *
 * DMA 通道 0 将 CM1 值写入 ATOM1_CH7.SR1 影子寄存器，每帧开始时重新装载。
 * 由 ATOM1_CH7 CM0 的匹配信号(IfxSrc_Tos_dma)触发，实现精确的波形控制。
 */

#define RGB_PIN            IfxGtm_ATOM1_7_TOUT75_P15_4_OUT   /* P15_4 */
#define RGB_GTM            &MODULE_GTM
#define RGB_ATOM           IfxGtm_Atom_1
#define RGB_ATOM_CH        IfxGtm_Atom_Ch_7
#define RGB_DMA_CHANNEL    IfxDma_ChannelId_0

#define RGB_PWM_FREQ       800000UL                          /* WS2812 800kHz */
#define RGB_BIT_PERIOD     (ATOM_PWM_CLK / RGB_PWM_FREQ)     /* 125 */
#define RGB_DUTY_0         ((uint32)(RGB_BIT_PERIOD * 0.32f))/* ~40 → 0 */
#define RGB_DUTY_1         ((uint32)(RGB_BIT_PERIOD * 0.64f))/* ~80 → 1 */
#define RGB_RESET_PERIODS  48                                /* 48*1.25us=60us >50us */

#define RGB_TOTAL_BITS     (RGB_NUM * 24)
#define RGB_FRAME_LEN      (RGB_TOTAL_BITS + RGB_RESET_PERIODS)

/* 状态灯参数（可现场调参） */
#define RGB_SPEED_STOP          0.03f   /* |速度|小于此值(m/s)判为停车 */
#define RGB_STOP_SAMPLES        3       /* 连续3个采样点(30ms)即确定停车 */
#define RGB_SHORT_WIN           5       /* 短平均窗口(50ms) */
#define RGB_LONG_WIN            20      /* 长平均窗口(200ms) */
#define RGB_ACCEL_THR           0.05f   /* 加减速阈值(m/s)：短长平均差超过则判加速/减速 */
#define RGB_DEBOUNCE_SAMPLES    20      /* 状态候选连续保持次数(200ms @ 10ms采样) */
#define RGB_TURN_DEVIATION      60      /* 舵机偏差阈值，超过该值视为转弯方向 */
#define RGB_TURN_HOLD_MS        150     /* 转弯方向持续确认时间(ms) */

RgbStruct rgbStr;

static uint32_t          rgbDmaBuffer[RGB_FRAME_LEN];
static IfxDma_Dma        rgbDma;
static IfxDma_Dma_Channel rgbDmaCh;
static uint8_t           rgbReady = 0;


/**
* @brief        将一帧颜色数据转换成 CM1 值数组，24 位 GRB 从高位到低位依次处理
* @param        buffer：目标数组（每个元素等于 CM1 比较值）
* @ref
* @author       Leo
* @note
**/
static void RGB_EncodeFrame(uint32_t *buffer)
{
    uint32_t i;

    for (i = 0; i < RGB_NUM; i++)
    {
        unsigned long dat = rgbStr.buffColors[i];
        unsigned long grb = ((dat & 0x00FF00) << 8) | ((dat & 0xFF0000) >> 8) | (dat & 0x0000FF); /* RGB->GRB */
        int b;

        for (b = 0; b < 24; b++)
        {
            *buffer++ = (grb & 0x800000) ? RGB_DUTY_1 : RGB_DUTY_0;
            grb <<= 1;
        }
    }

    for (i = 0; i < RGB_RESET_PERIODS; i++)
        *buffer++ = 0;                                      /* 帧间隔 */
}


/**
* @brief        通过 DMA 通道发送一帧数据，等待前一帧发送完成后再重新初始化
* @param
* @ref
* @author       Leo
* @note
**/
static void RGB_DmaSend(void)
{
    while (IfxDma_Dma_isChannelTransactionPending(&rgbDmaCh)) {}
    IfxDma_Dma_setChannelSourceAddress(&rgbDmaCh, (uint32)rgbDmaBuffer);
    IfxDma_Dma_setChannelTransferCount(&rgbDmaCh, RGB_FRAME_LEN);
    IfxDma_enableChannelTransaction(rgbDma.dma, RGB_DMA_CHANNEL);
}


/**
* @brief        DMA 通道初始化函数
*                源地址：rgbDmaBuffer，每次移动 1 个数据(32bit)。
*                目的地址：ATOM1_CH7.SR1，地址固定，写入影子寄存器。
*                传输由每次 CM0 的匹配信号触发 1 次移动。
* @param
* @ref
* @author       Leo
* @note
**/
static void RGB_DmaInit(void)
{
    IfxDma_Dma_Config        dmaModuleCfg;
    IfxDma_Dma_ChannelConfig dmaCfg;

    IfxDma_Dma_initModuleConfig(&dmaModuleCfg, &MODULE_DMA);
    IfxDma_Dma_initModule(&rgbDma, &dmaModuleCfg);

    IfxDma_Dma_initChannelConfig(&dmaCfg, &rgbDma);
    dmaCfg.channelId                      = RGB_DMA_CHANNEL;
    dmaCfg.sourceAddress                  = (uint32)rgbDmaBuffer;
    dmaCfg.sourceAddressIncrementStep     = IfxDma_ChannelIncrementStep_1;
    dmaCfg.sourceAddressCircularRange     = IfxDma_ChannelIncrementCircular_none;
    dmaCfg.sourceCircularBufferEnabled    = FALSE;

    dmaCfg.destinationAddress               = (uint32)&MODULE_GTM.ATOM[RGB_ATOM].CH7.SR1;
    dmaCfg.destinationAddressCircularRange  = IfxDma_ChannelIncrementCircular_none;
    dmaCfg.destinationCircularBufferEnabled = TRUE;   /* 固定目的地址 */

    dmaCfg.transferCount                  = RGB_FRAME_LEN;
    dmaCfg.requestMode                    = IfxDma_ChannelRequestMode_oneTransferPerRequest;
    dmaCfg.operationMode                  = IfxDma_ChannelOperationMode_single;
    dmaCfg.moveSize                       = IfxDma_ChannelMoveSize_32bit;
    dmaCfg.blockMode                      = IfxDma_ChannelMove_1;
    dmaCfg.requestSource                  = IfxDma_ChannelRequestSource_peripheral;
    dmaCfg.hardwareRequestEnabled         = FALSE;   /* 初始不使能，由 RGB_DmaSend 每次发送时使能 */
    dmaCfg.channelInterruptEnabled        = FALSE;
    IfxDma_Dma_initChannel(&rgbDmaCh, &dmaCfg);
}


/**
* @brief        RGB 灯初始化
* @param
* @ref
* @author       Leo
* @note
**/
void RGB_Init(void)
{
    volatile Ifx_SRC_SRCR *src;

    /* 800kHz PWM：P15_4，CMU CLK0 时钟已被设为 100MHz，请勿修改或破坏系统时钟频率 */
    ATOM_PWM_InitConfig(RGB_PIN, 0, RGB_PWM_FREQ);

    /* 将 ATOM1_CH7 的 CM0(比较器)匹配信号路由到 DMA 通道 0 */
    src = IfxGtm_Atom_Ch_getSrcPointer(RGB_GTM, RGB_ATOM, RGB_ATOM_CH);
    IfxGtm_Atom_Ch_setNotification(&MODULE_GTM.ATOM[RGB_ATOM], RGB_ATOM_CH,
                                   IfxGtm_IrqMode_pulse, TRUE, FALSE);
    IfxSrc_init(src, IfxSrc_Tos_dma, (uint8)RGB_DMA_CHANNEL);
    IfxSrc_enable(src);

    RGB_DmaInit();
    rgbReady = 1;

    Delay_Ms(10);
}


/**
* @brief        设置多灯灯效
* @param
* @ref
* @author       Leo
* @note
**/
void RGB_SetAllLight(unsigned long *colorBuff)
{
    uint32_t i;

    if (!rgbReady)
        return;

    for (i = 0; i < RGB_NUM; i++)
        rgbStr.buffColors[i] = colorBuff[i];

    RGB_EncodeFrame(rgbDmaBuffer);
    RGB_DmaSend();
}


/**
* @brief        设置灯光颜色
* @param
* @ref
* @author       Leo
* @note
**/
void RGB_SetAllColor(unsigned long color)
{
    uint32_t i;

    if (!rgbReady)
        return;

    for (i = 0; i < RGB_NUM; i++)
        rgbStr.buffColors[i] = color;

    RGB_EncodeFrame(rgbDmaBuffer);
    RGB_DmaSend();
}


/**
* @brief        颜色渐变算法
* @param
* @ref
* @author       Leo
* @note         误差 <= 2
**/
uint32_t RGB_SetColorToColor(unsigned long color0, unsigned long color1)
{
    unsigned char Red0, Green0, Blue0;  /* 起始三原色(0xRRGGBB) */
    unsigned char Red1, Green1, Blue1;  /* 结果三原色(0xRRGGBB) */
    int           RedMinus, GreenMinus, BlueMinus; /* 颜色差（color1 - color0） */
    unsigned char NStep;                            /* 需要步数 */
    float         RedStep, GreenStep, BlueStep;     /* 各色步进值 */
    unsigned long color;                            /* 结果色 */
    unsigned char i;

    Red0   = (unsigned char)((color0 >> 16) & 0xFF);
    Green0 = (unsigned char)((color0 >> 8)  & 0xFF);
    Blue0  = (unsigned char)(color0 & 0xFF);

    Red1   = (unsigned char)((color1 >> 16) & 0xFF);
    Green1 = (unsigned char)((color1 >> 8)  & 0xFF);
    Blue1  = (unsigned char)(color1 & 0xFF);

    RedMinus   = Red1   - Red0;
    GreenMinus = Green1 - Green0;
    BlueMinus  = Blue1  - Blue0;

    NStep = ( abs(RedMinus)   > abs(GreenMinus) ) ? abs(RedMinus)   : abs(GreenMinus);
    NStep = ( NStep           > abs(BlueMinus)  ) ? NStep           : abs(BlueMinus);

    RedStep   = (float)RedMinus   / NStep;
    GreenStep = (float)GreenMinus / NStep;
    BlueStep  = (float)BlueMinus  / NStep;

    for (i = 0; i < NStep; i++)
    {
        color = ((unsigned long)(Red0   + (int)(RedStep   * i)) << 16) |
                ((unsigned long)(Green0 + (int)(GreenStep * i)) << 8)  |
                ((unsigned long)(Blue0  + (int)(BlueStep  * i)));
        RGB_SetAllColor(color);
        Delay_Ms(1);                                            /* 渐变速度 */
    }

    return color1;
}


/* 状态机：当前显示状态 */
typedef enum
{
    RGB_STATE_CONST,    /* 匀速 -> 白 */
    RGB_STATE_ACCEL,    /* 加速 -> 绿 */
    RGB_STATE_DECEL,    /* 减速 -> 蓝 */
    RGB_STATE_STOP      /* 停车 -> 黑 */
} RGB_State_t;


/**
* @brief        根据每 10ms 采样的当前速度分类为 匀速/加速/减速/停车
* @param        无
* @ref
* @author
* @note         用短平均(50ms)与长平均(200ms)的差值判断趋势，对毛刺更稳
**/
static RGB_State_t RGB_Classify(void)
{
    static float    hist[RGB_LONG_WIN];        /* 200ms 速度环形缓冲 */
    static uint8_t  histIdx = 0;               /* 当前写入位(满时即最旧值) */
    static uint8_t  histCnt = 0;               /* 已存入的有效采样数 */
    static uint8_t  stopCnt = RGB_STOP_SAMPLES;/* 连续3次(30ms)才确定停车 */
    float cur      = icarStr.SpeedFeedback;
    float shortAvg = 0.0f;
    float longAvg  = 0.0f;
    float diff;
    uint8_t k;
    uint8_t nShort;

    /* 存入当前速度 */
    hist[histIdx] = cur;
    histIdx = (uint8_t)((histIdx + 1) % RGB_LONG_WIN);
    if (histCnt < RGB_LONG_WIN)
        histCnt++;

    /* 停车：|v| 小于阈值，连续 3 次 */
    if (cur < RGB_SPEED_STOP && cur > -RGB_SPEED_STOP)
    {
        if (stopCnt < 250)                     /* 防溢出 */
            stopCnt++;
    }
    else
        stopCnt = 0;
    if (stopCnt >= RGB_STOP_SAMPLES)
        return RGB_STATE_STOP;

    /* 长平均(200ms)：从最旧到最新 */
    for (k = 0; k < histCnt; k++)
        longAvg += hist[(histIdx + k) % RGB_LONG_WIN];
    longAvg /= (float)histCnt;

    /* 短平均(50ms，取最新的 nShort 个) */
    nShort = (histCnt < RGB_SHORT_WIN) ? histCnt : (uint8_t)RGB_SHORT_WIN;
    for (k = 0; k < nShort; k++)
        shortAvg += hist[(histIdx + histCnt - 1 - k) % RGB_LONG_WIN];
    shortAvg /= (float)nShort;

    diff = shortAvg - longAvg;
    if (diff > RGB_ACCEL_THR)
        return RGB_STATE_ACCEL;
    if (diff < -RGB_ACCEL_THR)
        return RGB_STATE_DECEL;
    return RGB_STATE_CONST;
}


/**
* @brief        1ms timer callback: drive-status LED (accel/brake/turn)
* @param        无
* @ref
* @author
* @note         CCU60 1ms 中断中调用；每 10ms 判定一次状态，候选状态需连续保持 200ms 才切换
**/
void RGB_Timer(void)
{
    static uint32_t   tick        = 0;
    static uint16_t   turnCnt     = 0;
    static uint32_t   lastColor   = RGB_COLOR_BLACK;
    static int8_t     lastTurn    = 0;
    static RGB_State_t dispState  = RGB_STATE_STOP;    /* 当前显示状态 */
    static RGB_State_t pendingState = RGB_STATE_STOP;  /* 候选状态(未确认) */
    static uint16_t   pendingCnt  = RGB_DEBOUNCE_SAMPLES; /* 候选连续次数 */
    RGB_State_t       candidate;
    uint32_t          i;
    uint32_t          base;
    int16_t           dev;
    int8_t            turn = 0;
    unsigned long     colors[RGB_NUM];

    if (!rgbReady)
        return;

    if (++tick < 10)
        return;                                 /* 每 10ms 处理一次 */
    tick = 0;

    /* ---------- 状态分类 + 防抖(200ms) ---------- */
    candidate = RGB_Classify();

    if (candidate == pendingState)
    {
        if (pendingCnt < 0xFFFFu)
            pendingCnt++;
    }
    else
    {
        pendingState = candidate;
        pendingCnt   = 0;
    }

    if (pendingCnt >= RGB_DEBOUNCE_SAMPLES)
        dispState = pendingState;

    /* ---------- 颜色映射 ---------- */
    base = RGB_COLOR_WHITE;
    switch (dispState)
    {
        case RGB_STATE_ACCEL: base = RGB_COLOR_GREEN; break;  /* 加速 -> 绿 */
        case RGB_STATE_DECEL: base = RGB_COLOR_BLUE;  break;  /* 减速 -> 蓝 */
        case RGB_STATE_STOP:  base = RGB_COLOR_BLACK; break;  /* 停车 -> 黑 */
        default: break;                                       /* 匀速 -> 白 */
    }

    /* ---------- 转弯状态 ---------- */
    dev = (int16_t)icarStr.ServoPwmSet - (int16_t)servoStr.thresholdMiddle;

    if (dev > (int16_t)RGB_TURN_DEVIATION || dev < -(int16_t)RGB_TURN_DEVIATION)
        turnCnt++;
    else
        turnCnt = 0;

    if ((uint32_t)turnCnt * 10u >= RGB_TURN_HOLD_MS)
        turn = (dev > 0) ? (int8_t)1 : (int8_t)(-1);

    /* ---------- 组装颜色 ---------- */
    for (i = 0; i < RGB_NUM; i++)
        colors[i] = base;

    if (base != RGB_COLOR_BLACK && turn != 0)
    {
        if (turn > 0)                           /* 左转: 1~9 号灯 */
            for (i = 0; i < 9; i++)
                colors[i] = RGB_COLOR_YELLOW;
        else                                    /* 右转: 10~18 号灯 */
            for (i = 9; i < RGB_NUM; i++)
                colors[i] = RGB_COLOR_YELLOW;
    }

    /* 状态变化才刷帧，避免每 ms 重发 DMA */
    if (base != lastColor || turn != lastTurn)
    {
        RGB_SetAllLight(colors);
        lastColor = base;
        lastTurn  = turn;
    }
}



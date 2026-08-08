#include "Imu.h"
#include "LQ_SOFTI2C.h"

int LQ_I2C_Read(unsigned char addr, unsigned char reg, unsigned int len, unsigned char *buf);

ImuStruct imuStr;

void IMU_Init(void)
{
    IIC_Init();
    imuStr.counter = 0;
    imuStr.ready = FALSE;
}

void IMU_Timer(void)
{
    imuStr.counter++;
    if(imuStr.counter >= 5)
    {
        imuStr.counter = 0;
        imuStr.ready = TRUE;
    }
}

void IMU_Handle(void)
{
    if(!imuStr.ready)
        return;

    imuStr.ready = FALSE;

    uint8_t data[6];
    if(LQ_I2C_Read(IMU_I2C_ADDR, IMU_REG_ROLL, IMU_READ_LEN, data) == 0)
    {
        uint8_t check = 0;
        Bint32_Union speed;
        uint8_t buff[14];
        buff[0] = 0x42;
        buff[1] = 0x09;
        buff[2] = 0x0E;

        buff[3] = data[0];
        buff[4] = data[1];
        buff[5] = data[2];
        buff[6] = data[3];
        buff[7] = data[4];
        buff[8] = data[5];

        /* Keep attitude and measured speed in one frame. */
        speed.Float = icarStr.SpeedFeedback;
        buff[9] = speed.U8_Buff[0];
        buff[10] = speed.U8_Buff[1];
        buff[11] = speed.U8_Buff[2];
        buff[12] = speed.U8_Buff[3];

        for(int i = 0; i < 13; i++)
            check += buff[i];
        buff[13] = check;

        for(int i = 0; i < 14; i++)
            USB_Edgeboard_TransmitByte(buff[i]);
    }
}

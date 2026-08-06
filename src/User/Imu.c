#include "Imu.h"
#include "LQ_SOFTI2C.h"

ImuStruct imuStr;

void IMU_Init(void)
{
    IIC_Init();
    imuStr.counter = 0;
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
        uint8_t buff[10];
        buff[0] = 0x42;
        buff[1] = 0x09;
        buff[2] = 0x0A;

        buff[3] = data[0];
        buff[4] = data[1];
        buff[5] = data[2];
        buff[6] = data[3];
        buff[7] = data[4];
        buff[8] = data[5];

        for(int i = 0; i < 9; i++)
            check += buff[i];
        buff[9] = check;

        for(int i = 0; i < 10; i++)
            USB_Edgeboard_TransmitByte(buff[i]);
    }
}

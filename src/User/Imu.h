#ifndef __IMU_H__
#define __IMU_H__

#include "include.h"

#if 0

#define IMU_I2C_ADDR      0x50
#define IMU_REG_ROLL      0x3D
#define IMU_READ_LEN      6

typedef struct {
    uint16_t counter;
    boolean ready;
} ImuStruct;

extern ImuStruct imuStr;

void IMU_Init(void);
void IMU_Timer(void);
void IMU_Handle(void);

#endif
#endif

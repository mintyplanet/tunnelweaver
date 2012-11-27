#ifndef ADXL345_H
#define ADXL345_H
#include "terasic_includes.h"

#define ADXL345_DEVICE (0xA6) 
#define ADXL345_POWER_CTL 0x2d
#define ADXL345_DATAX0 0x32
#define ADXL345_DATAX1 0x33
#define ADXL345_DATAY0 0x34
#define ADXL345_DATAY1 0x35
#define ADXL345_DATA_FORMAT 0x31

bool ADXL345_init();
alt_u32 read_X();
alt_u32 read_Y();

#endif

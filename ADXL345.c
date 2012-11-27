#include "i2c.h"
#include "ADXL345.h"

bool ADXL345_init(){
	//set input/output direction and set inital bits.
	JP2_init();
	//Power on the acelerometer
	if (!I2C_Write(0, 0, ADXL345_DEVICE, ADXL345_POWER_CTL, 8)) 
		return FALSE;
	if (!I2C_Write (0, 0, ADXL345_DEVICE, ADXL345_DATA_FORMAT, 0))
		return FALSE;
	return TRUE;
}

alt_u32 read_X(){
	alt_u32 result = 0;
	alt_u8 r;
	if (!I2C_Read(0, 0, ADXL345_DEVICE, ADXL345_DATAX0, &r))
		return -1;
	result = (r|result); 
	if (!I2C_Read(0, 0, ADXL345_DEVICE, ADXL345_DATAX1, &r))
		return -1;
	result = (r << 8 | result);
	return result;
}

alt_u32 read_Y(){
	alt_u32 result = 0;
	alt_u8 r;
	if (!I2C_Read(0, 0, ADXL345_DEVICE, ADXL345_DATAY0, &r))
		return -1;
	result = (r|result); 
	if (!I2C_Read(0, 0, ADXL345_DEVICE, ADXL345_DATAY1, &r))
		return -1;
	result = (r << 8 | result);
	return result;
}


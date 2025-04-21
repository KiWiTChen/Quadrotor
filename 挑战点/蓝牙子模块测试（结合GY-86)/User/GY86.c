#include "stm32f4xx.h"                  // Device header
#include "MyIIC.h"
#define MPU6050_ADDRESS 0xD0
#define MPU6050_SMPLRT_DIV 0X19 //预分频器

#define MPU6050_CONFIG 0x1A
#define MPU6050_GYRO_CONFIG 0X1B
#define MPU6050_ACCEL_CONFIG 0X1C

#define MPU6050_ACCEL_XOUT_H 0X3B
#define MPU6050_ACCEL_XOUT_L 0X3C
#define MPU6050_ACCEL_YOUT_H 0X3D
#define MPU6050_ACCEL_YOUT_L 0X3E
#define MPU6050_ACCEL_ZOUT_H 0X3F
#define MPU6050_ACCEL_ZOUT_L 0X40
#define MPU6050_TEMP_OUT_H 0X41
#define MPU6050_TEMP_OUT_L 0X42
#define MPU6050_GYRO_XOUT_H 0X43
#define MPU6050_GYRO_XOUT_L 0X44
#define MPU6050_GYRO_YOUT_H 0X45
#define MPU6050_GYRO_YOUT_L 0X46
#define MPU6050_GYRO_ZOUT_H 0X47
#define MPU6050_GYRO_ZOUT_L 0X48

#define MPU6050_INT_PIN_CFG 0X37
#define MPU6050_USER_CTRL 0x6A 

#define MPU6050_PWR_MGMT_1 0X6B 
#define MPU6050_PWR_MGMT_2 0X6C

#define MPU6050_WHO_AM_I 0X75

#define HMC5883L_ADDRESS 0x1E
#define HMC5883L_WRITE_ADDRESS 0x3C
#define HMC5883L_READ_ADDRESS 0x3D

#define HMC5883L_CONFIGA 0x00
#define HMC5883L_CONFIGB 0x01
#define HMC5883L_MODE 0x02

#define HMC5883L_STATUS 0x09

#define HMC5883L_X_M 0x03
#define HMC5883L_X_L 0x04
#define HMC5883L_Y_M 0x05
#define HMC5883L_Y_L 0x06
#define HMC5883L_Z_M 0x07
#define HMC5883L_Z_L 0x08



void GY86_WriteRegister(uint8_t SlaveAddress, uint8_t RegisterAddress, uint8_t val){
	
	
	MyIIC_Start();
	MyIIC_SendByte(SlaveAddress|0x00);
	MyIIC_ReceiveACK();
	MyIIC_SendByte(	RegisterAddress);
	MyIIC_ReceiveACK();
	MyIIC_SendByte(val);
	MyIIC_ReceiveACK();
	MyIIC_Stop();
	
	
}

uint8_t GY86_ReadRegister(uint8_t SlaveAddress, uint8_t RegisterAddress){
	uint8_t val;
	
	MyIIC_Start();
  MyIIC_SendByte(SlaveAddress|0x00);
	MyIIC_ReceiveACK();
	MyIIC_SendByte(	RegisterAddress);
	MyIIC_ReceiveACK();
	
	MyIIC_Start();
	MyIIC_SendByte(SlaveAddress|0x01);
	MyIIC_ReceiveACK();
	val = MyIIC_ReceiveByte();
	MyIIC_SendACK(1);
	MyIIC_Stop();
	
	return val;
}

void MPU6050_Init(void){
	MyIIC_Init();
	GY86_WriteRegister(MPU6050_ADDRESS, MPU6050_PWR_MGMT_1, 0x01); //内置陀螺仪时钟
	GY86_WriteRegister(MPU6050_ADDRESS, MPU6050_PWR_MGMT_2, 0x00); 
	
  GY86_WriteRegister(MPU6050_ADDRESS, MPU6050_SMPLRT_DIV,0x09);
	
	GY86_WriteRegister(MPU6050_ADDRESS, MPU6050_CONFIG, 0x06);
  GY86_WriteRegister(MPU6050_ADDRESS, MPU6050_GYRO_CONFIG, 0x18);//选择满量程
	GY86_WriteRegister(MPU6050_ADDRESS, MPU6050_ACCEL_CONFIG, 0x18);
	
	GY86_WriteRegister(MPU6050_ADDRESS, MPU6050_INT_PIN_CFG, 0x80);//旁路使能
	GY86_WriteRegister(MPU6050_ADDRESS, MPU6050_USER_CTRL, 0x02);//开启主模式
	
}

void HMC5883L_Init(void){
	MyIIC_Init();
	GY86_WriteRegister(HMC5883L_WRITE_ADDRESS, HMC5883L_CONFIGA, 0x70);
	GY86_WriteRegister(HMC5883L_WRITE_ADDRESS, HMC5883L_CONFIGB, 0x20);
										
	GY86_WriteRegister(HMC5883L_WRITE_ADDRESS, HMC5883L_MODE, 0x00);
	

} 

void GY86_Init(void){
	MyIIC_Init();
	MPU6050_Init();
	HMC5883L_Init();
	
}

void GY86_GetData(uint16_t *x, uint16_t *y, uint16_t *z, int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                              int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)

{
	uint8_t BUF[6];
	BUF[0] = GY86_ReadRegister(HMC5883L_READ_ADDRESS, HMC5883L_X_M);
	BUF[1] = GY86_ReadRegister(HMC5883L_READ_ADDRESS, HMC5883L_X_L);
	BUF[2] = GY86_ReadRegister(HMC5883L_READ_ADDRESS, HMC5883L_Y_M);
	BUF[3] = GY86_ReadRegister(HMC5883L_READ_ADDRESS, HMC5883L_Y_L);
	BUF[4] = GY86_ReadRegister(HMC5883L_READ_ADDRESS, HMC5883L_Z_M);
	BUF[5] = GY86_ReadRegister(HMC5883L_READ_ADDRESS, HMC5883L_Z_L);
	
	*x = BUF[0]<<8 | BUF[1];
	*y = BUF[2]<<8 | BUF[3];
	*z = BUF[4]<<8 | BUF[5];
	
	uint8_t DataH, DataL;
	DataH = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H);
	DataL = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;

	DataH = GY86_ReadRegister(MPU6050_ADDRESS,MPU6050_ACCEL_YOUT_H);
	DataL = GY86_ReadRegister(MPU6050_ADDRESS,MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;

	DataH = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_ACCEL_ZOUT_H);
	DataL = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
                      
	
	DataH = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_GYRO_XOUT_H);
	DataL = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;

	DataH = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_GYRO_YOUT_H);
	DataL = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;

	DataH = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_GYRO_ZOUT_H);
	DataL = GY86_ReadRegister(MPU6050_ADDRESS, MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;


	
}			

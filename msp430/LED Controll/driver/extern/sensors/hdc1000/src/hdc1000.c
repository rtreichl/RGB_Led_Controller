///----------------------------------------------------------------------------------------
///
/// \file hdc1000.c
///
/// \brief 
///
/// \date 31.12.2015
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------


#include <driver.h>

volatile uint8_t HDC1000_PedingInterrupt;

void HDC1000_InterruptHandler();

uint16_t HDC1000_init()
{
	HDC1000_Config Config = {0};
	uint16_t *ptr_tmp = (uint16_t*) &Config;

	Config.RST = HDC1000_NORMAL_OPERATION;
	Config.HEAT = HDC1000_HEATER_OFF;
	Config.MODE = HDC1000_MODE_BOTH;
	Config.TRES = HDC1000_TEMP_RES_14_BIT;
	Config.HRES = HDC1000_HUMI_RES_14_BIT;
	Config.BTST = HDC1000_BAT_VOLT_HIGHER_2V8;

	SwapEndian(&Config);

	i2c_write_smbus_word(HDC1000_I2C_ADDR, HDC1000_CONFIG_REG, *ptr_tmp);
	//i2c_write_smbus(HDC1000_I2C_ADDR + 1, &smbus);
	//i2c_write_smbus(HDC1000_I2C_ADDR + 2, &smbus);
	//i2c_write_smbus(HDC1000_I2C_ADDR + 3, &smbus);

	HDC1000_INTERRUPT_PDIR &= ~HDC1000_INTERRUPT_BIT;
	HDC1000_INTERRUPT_PREN |= HDC1000_INTERRUPT_BIT;
	HDC1000_INTERRUPT_POUT |= HDC1000_INTERRUPT_BIT;
	HDC1000_INTERRUPT_PIES |= HDC1000_INTERRUPT_BIT;

	ext_interrupt_create(HDC1000_INTERRUPT_NUM, HDC1000_InterruptHandler);
	ext_interrupt_enable(HDC1000_INTERRUPT_NUM);
	return 0;
}

//uint16_t HDC1000_SetHeater(bool status)
//{
//	HDC1000_Config Config = {0};
//
//	Config.RST = HDC1000_NORMAL_OPERATION;
//	Config.HEAT = HDC1000_HEATER_OFF;
//	Config.MODE = HDC1000_MODE_BOTH;
//	Config.TRES = HDC1000_TEMP_RES_14_BIT;
//	Config.HRES = HDC1000_HUMI_RES_14_BIT;
//	Config.BTST = HDC1000_BAT_VOLT_HIGHER_2V8;
//
//	if (status == HDC1000_HEATER_ON)
//	{
//		Config.HEAT = HDC1000_HEATER_ON;
//	}
//	else
//	{
//		Config.HEAT = HDC1000_HEATER_OFF;
//	}
//	i2c_write_smbus(HDC1000_ADDR, &smbus);
//	return 0;
//}

//uint16_t HDC1000_GetHeater()
//{
//	uint16_t temp;
//	HDC1000_Config * received;
//	temp = be16toh(i2cReadWordData(this->Device, HDC1000_CONFIG_REG));
//	received = (HDC1000_Config *)&temp;
//	if (received->HEAT == HDC1000_HEATER_ON)
//	{
//		return HDC1000_HEATER_ON;
//	}
//	else
//	{
//		return HDC1000_HEATER_OFF;
//	}
//}

int16_t HDC1000_ReadRawTemperature()
{
	I2C_SMBUS_PACKAGE smbus;
	int16_t data;

	smbus.reg = HDC1000_TEMPERATURE_REG;
	smbus.n_bytes = 0;

	HDC1000_PedingInterrupt = 0;

	i2c_write_smbus_block(HDC1000_I2C_ADDR, &smbus);

	while (!HDC1000_PedingInterrupt){}

	i2c_read(HDC1000_I2C_ADDR, STOP, I2C_LITTLE_ENDIAN, 2, &data);

	data = SwapConstInt16(data);

	return data;
}

int16_t HDC1000_ReadTemperature()
{
	return (((int32_t)HDC1000_ReadRawTemperature() * 16500) >> 16) - 4000;
}

uint16_t HDC1000_ReadRawHumidity()
{
	I2C_SMBUS_PACKAGE smbus;
	uint16_t data;

	smbus.reg = HDC1000_HUMIDITY_REG;
	smbus.n_bytes = 0;

	HDC1000_PedingInterrupt = 0;

	i2c_write_smbus_block(HDC1000_I2C_ADDR, &smbus);

	while (!HDC1000_PedingInterrupt){}

	i2c_read(HDC1000_I2C_ADDR, STOP, I2C_LITTLE_ENDIAN, 2, &data);

	data = SwapConstInt16(data);

	return data;
}


uint16_t HDC1000_ReadHumidity()
{
	return ((uint32_t)HDC1000_ReadRawHumidity() * 10000) >> 16;
}

void HDC1000_InterruptHandler()
{
	HDC1000_PedingInterrupt = 1;
	return;
}

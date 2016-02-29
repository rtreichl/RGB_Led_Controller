#include <driver.h>

#define CC110L_SPI_BUS 0
#define CC110L_SPI_BAUD 5000000
#define CC110L_MISO_BIT BIT1
#define CC110L_MISO_PIN P2IN
#define CC110L_SPI_CS 15
#define CC110L_GPO0 18
#define CC110L_GPO2 23

uint16_t CC110L_SendCommand(uint8_t command)
{
	char received = 0;
	P1OUT &= ~BIT4;
	while (CC110L_MISO_PIN & CC110L_MISO_BIT)
			{
			};
	SPI_transfer(1, &command, &received);
	P1OUT |= BIT4;
 	return received;
}

uint16_t CC110L_CheckConfig(CC110L_CONFIG *Config)
{
	uint8_t addr;
	uint8_t status;
	uint8_t bytes[3];
	uint8_t fail = 0;
	uint8_t ok = 0;
	uint8_t *config2 = (uint8_t *)Config;
	CC110L_CONFIG tmp;
	uint8_t *config = (uint8_t *)&tmp;
	P1OUT &= ~BIT4;
	while (CC110L_MISO_PIN & CC110L_MISO_BIT)
		{
		};
	//cout << "Address: 0xREG = 0xMCU, 0xCTRL" << endl;
	for (addr =  (0x80 | CC110L_IOCFG2); addr <= (0x80 | CC110L_TEST0); addr++)
	{
		SPI_transfer(2, &addr, bytes);
		status = bytes[0];
		*config = bytes[1];
		//_delay_cycles(200);
		//SPI_transfer(1, &status, config);
		//cout << "Address: 0x" << hex << (int)(addr - 0x80) << "  = 0x" << hex << (int)*config2 << " , 0x" << hex << (int)*config;
		if (*config2 == *config)
			ok++;
			//cout << " OK" << endl;
		else
			fail++;
			//cout << " FAILD" << endl;
		config++;
		config2++;
	}

	addr = (0xC0 | CC110L_PA_TABLE0);
	SPI_transfer(3, &addr, bytes);
	//SPI_transfer(2, &status, &pa_table);

	P1OUT |= BIT4;
	return fail + (ok << 8);
}

uint16_t CC110L_WriteConfig(CC110L_CONFIG *Config)
{
	uint8_t addr;
	uint8_t status;
	uint8_t bytes[3];
	uint16_t pa_table = 0xC0;
	uint8_t *config = (uint8_t *)Config;
	P1OUT &= ~BIT4;
	while (CC110L_MISO_PIN & CC110L_MISO_BIT)
		{
		};
	for (addr =  CC110L_IOCFG2; addr <= CC110L_TEST0; addr++)
	{
		bytes[0] = addr;
		bytes[1] = *config;
		SPI_transfer(2, bytes, &status);
		//_delay_cycles(200);
		//SPI_transfer(1, config, &status);
		//cout << "Address: 0x" << hex << (int)(addr) << " = 0x" << hex << (int)*config << endl;
		config++;
	}

	addr = (0x40 | CC110L_PA_TABLE0);
	bytes[0] = addr;
	bytes[1] = 0xC0;
	bytes[2] = 0x00;
	SPI_transfer(3, bytes, &status);
	//SPI_transfer(2, &pa_table, &status);

	P1OUT |= BIT4;
	CC110L_CheckConfig(Config);
	return 0;
}

uint16_t CC110L_ReadStatus()
{
	char addr;
	char status;
	uint8_t bytes[2];
	CC110L_STATUS stat;
	char *Status = (char *)&stat;
	P1OUT &= ~BIT4;
	while (CC110L_MISO_PIN & CC110L_MISO_BIT)
		{
		};
	for (addr =  (0xC0 | CC110L_PARTNUM); addr <= (0xC0 | CC110L_RESERVED_0X3D); addr++)
	{
		SPI_transfer(2, &addr, bytes);
		status = bytes[0];
		*Status = bytes[1];
		//cout << "Address: 0x" << hex << (int)(addr - 0xC0) << "  = 0x" << hex << (int)*Status << endl;
		Status++;
	}
	P1OUT |= BIT4;
	return 0;
}

//int CC110L::RX()
//{
//	int compare;
//	char addr = CC110L_RXFIFO;
//	char status;
//	while (gpioRead(CC110L_MISO))
//	{
//	}
//	while (1) //Until dat Avialible
//	{
//		if ((RXBufferWrite + 1 == RXBufferRead) || RXBufferRead == 0 && RXBufferWrite + 1 == CC110L_BUFFER_SIZE)
//		{
//			return -1; //BUFFER FULL
//		}
//		spiXfer(this->Device, &addr, &status, 1);
//		delay(200);
//		spiRead(this->Device, this->RXBuffer+RXBufferWrite, 1);
//		RXBufferWrite++;
//		if (RXBufferWrite >= CC110L_BUFFER_SIZE)
//		{
//			RXBufferWrite = 0;
//		}
//	}
//	return 0;
//}
//
uint16_t CC110L_TX(void *data, uint8_t n_bytes)
{
	//uint8_t addr = CC110L_TXFIFO + CC110L_BURST;
	uint8_t status;
	P1OUT &= ~BIT4;

	while (CC110L_MISO_PIN & CC110L_MISO_BIT)
			{
			};
//		if (TXBufferWrite == TXBufferRead)
//		{
//			return -1; //Buffer Empty
//		}
	SPI_transmit(n_bytes, data, &status);
		//delay(200);
	//}
	P1OUT |= BIT4;
	return 0;
}

//int CC110L::SendData(char *Data)
//{
//	while (1) //Until dat Avialible
//	{
//		if ((TXBufferWrite + 1 == TXBufferRead) || TXBufferRead == 0 && TXBufferWrite + 1 == CC110L_BUFFER_SIZE)
//		{
//			return -1; //BUFFER FULL
//		}
//		*Data = this->TXBuffer[TXBufferWrite];
//		TXBufferWrite++;
//		if (TXBufferWrite >= CC110L_BUFFER_SIZE)
//		{
//			TXBufferWrite = 0;
//		}
//	}
//	return 0;
//}
//
//int CC110L::GetData()
//{
//	while (1) //Until dat Avialible
//	{
//		if (RXBufferWrite == RXBufferRead)
//		{
//			return -1; //Buffer Empty
//		}
//		return this->RXBuffer[RXBufferRead];
//		RXBufferRead++;
//		if (RXBufferRead >= CC110L_BUFFER_SIZE)
//		{
//			RXBufferRead = 0;
//		}
//	}
//	return 0;
//}

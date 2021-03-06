#ifndef CC110L_CONFIG
#define CC110L_CONFIG

#include "cc110l.h"
// Base frequency = 867.999939 
// Data rate = 38.3835 
// CRC autoflush = false 
// Data format = Normal mode 
// Modulation format = GFSK 
// Device address = 0 
// CRC enable = true 
// Deviation = 20.629883 
// Modulated = true 
// Preamble count = 4 
// Sync word qualifier mode = 30/32 sync word bits detected 
// Carrier frequency = 867.999939 
// TX power = 0 
// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// RX filter BW = 101.562500 
// Packet length = 255 
// Address config = No address check 
// Channel spacing = 199.951172 
// Manchester enable = false 

// Rf settings for CC110L
uint8_t CC110L_Settings[0x2F] = {
	0x29,   // IOCFG2             GDO2 Output Pin Configuration
	0x2E,   // IOCFG1             GDO1 Output Pin Configuration
	0x06,   // IOCFG0             GDO0 Output Pin Configuration
	0x47,   // FIFOTHR            RX FIFO and TX FIFO Thresholds
	0xD3,   // SYNC1              Sync Word, High Byte
	0x91,   // SYNC0              Sync Word, Low Byte
	0xFF,   // PKTLEN             Packet Length
	0x04,   // PKTCTRL1           Packet Automation Control
	0x05,   // PKTCTRL0           Packet Automation Control
	0x00,   // ADDR               Device Address
	0x00,   // CHANNR             Channel number
	0x06,   // FSCTRL1            Frequency Synthesizer Control
	0x00,   // FSCTRL0            Frequency Synthesizer Control
	0x21,   // FREQ2              Frequency Control Word, High Byte
	0x62,   // FREQ1              Frequency Control Word, Middle Byte
	0x76,   // FREQ0              Frequency Control Word, Low Byte
	0xCA,   // MDMCFG4            Modem Configuration
	0x83,   // MDMCFG3            Modem Configuration
	0x13,   // MDMCFG2            Modem Configuration
	0x22,   // MDMCFG1            Modem Configuration
	0xF8,   // MDMCFG0            Modem Configuration
	0x35,   // DEVIATN            Modem Deviation Setting
	0x07,   // MCSM2              Main Radio Control State Machine Configuration
	0x30,   // MCSM1              Main Radio Control State Machine Configuration
	0x18,   // MCSM0              Main Radio Control State Machine Configuration
	0x16,   // FOCCFG             Frequency Offset Compensation Configuration
	0x6C,   // BSCFG              Bit Synchronization Configuration
	0x43,   // AGCCTRL2           AGC Control
	0x40,   // AGCCTRL1           AGC Control
	0x91,   // AGCCTRL0           AGC Control
	0x00,   // RESERVED_0x1E      Not used
	0x00,   // RESERVED_0x1F      Not used
	0xFB,   // RESERVED_0X20      Use setting from SmartRF Studio
	0x56,   // FREND1             Front End RX Configuration
	0x10,   // FREND0             Front End TX Configuration
	0xE9,   // FSCAL3             Frequency Synthesizer Calibration
	0x2A,   // FSCAL2             Frequency Synthesizer Calibration
	0x00,   // FSCAL1             Frequency Synthesizer Calibration
	0x1F,   // FSCAL0             Frequency Synthesizer Calibration
	0x00,   // RESERVED_0x27      Not used
	0x00,   // RESERVED_0x28      Not used
	0x59,   // RESERVED_0X29      Use setting from SmartRF Studio
	0x7F,   // RESERVED_0X2A      Use setting from SmartRF Studio
	0x3F,   // RESERVED_0X2B      Use setting from SmartRF Studio
	0x81,   // TEST2              Various Test Settings
	0x35,   // TEST1              Various Test Settings
	0x09,   // TEST0              Various Test Settings
};

CC110L_CONFIG * CC110L_Config = (CC110L_CONFIG *)CC110L_Settings;

//#error Keep care register 0x1E, 0x1F, 0x27 and 0x28 are not defined on this list

#endif

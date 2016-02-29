/******************************************************************************
    Filename: cc11xL_spi.h  
    
    Description: header file that defines a minimum set of neccessary functions
                 to communicate with CC11xL over SPI as well as the regsister 
                 mapping.    
 
*******************************************************************************/

#ifndef CC110L_SPI_H
#define CC110L_SPI_H

#include <stdint.h>
#include "include/cc110l.h"

uint16_t CC110L_SendData(uint8_t *Data);
uint16_t CC110L_GetData();
uint16_t CC110L_CheckConfig();
uint16_t CC110L_WriteConfig(CC110L_CONFIG *Config);
uint16_t CC110L_ReadStatus();
uint16_t CC110L_SendCommand(uint8_t command);
uint16_t CC110L_TX(void *data, uint8_t n_bytes);

#endif// CC11xL_SPI_H

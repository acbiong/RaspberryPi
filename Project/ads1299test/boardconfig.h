#pragma once
#include "bcm2835.h"

/******************************************************************************
*                   Raspberry Pi                    ADS1299
*                -----------------             -----------------
*               |   PIN23/SPI1_SCK| --------> |SCLK          CLK|--DGND
*               |  PIN21/SPI1_MISO| <-------- |DOUT             |
*               |  PIN19/SPI1_MOSI| --------> |DIN              |
*               |           PIN7  | --------> |nCS              |
*               |           PIN11 | --------> |RESET            |
*               |           PIN12 | <-------- |nDRDY            |
*                -----------------             -----------------
******************************************************************************/

#define MAX_EEG_CHANNELS 8
#define ADS1299_CS_PIN    RPI_GPIO_P1_07
#define ADS1299_RST_PIN   RPI_GPIO_P1_11
#define ADS1299_DRDY_PIN  RPI_GPIO_P1_12

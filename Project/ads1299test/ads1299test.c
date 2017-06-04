// spi.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//
// Or you can test it before installing with:
// gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
// sudo ./spi
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include "includes.h"
#include <time.h>
#include "bcm2835.h"
#include "ads1299.h"
#include "boardconfig.h"
#include "socket2plot.h"

// Store the formatted string of the name of file in the output
void format_name(char *output) {
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	sprintf(output, "data-%d-%d-%d-%d-%d-%d.txt", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

int main(int argc, char **argv)
{
// If you call this, it will not actually access the GPIO
// Use for testing
//        bcm2835_set_debug(1);
	uint32_t status;
	int32_t sampleData[MAX_EEG_CHANNELS];
	FILE *fp = NULL;
	char filename[50];
	format_name(filename);
	fp = fopen(filename, "w");

	char inkey;

    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }

	ads1299GpioInit();

    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
    
	/*socket4plot sock = { 0, 0 };
	socketSetup("/tmp/demo_socket", &sock);
	char buffer[256];*/

    //// Send a byte to the slave and simultaneously read a byte back from the slave
    //// If you tie MISO to MOSI, you should read back what was sent
    //uint8_t send_data = 0x23;
    //uint8_t read_data = bcm2835_spi_transfer(send_data);
    //printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data, read_data);
    //if (send_data != read_data)
    //  printf("Do you have the loopback from MOSI to MISO connected?\n");

	ads1299_device_init(1);

	ads1299_soft_start_conversion();

	ads1299_start_rdatac();

	while (1)
	{
		if (bcm2835_gpio_eds(ADS1299_DRDY_PIN))
		{
			// Now clear the eds flag by setting it to 1
			bcm2835_gpio_set_eds(ADS1299_DRDY_PIN);
			ads1299_rdata32_generic(&status, sampleData);
			uint8_t ii = 0;
			if(fp != NULL)
			{
				for (ii = 0;ii < MAX_EEG_CHANNELS;ii++)
				{
					printf("%d\t", sampleData[ii]);
					fprintf(fp, "%d\t", sampleData[ii]);
				}
				printf("\n");
				/*bzero(buffer, 256);
				sprintf(buffer, "%d,%d,%d,%d,%d,%d,%d,%d", sampleData[0],
					sampleData[1], sampleData[2], sampleData[3], sampleData[4], sampleData[5], 
					sampleData[6], sampleData[7]);
				sendSocket(sock, buffer);*/
				fprintf(fp, "\n");
			}
		}
		else
		{
			//printf("Nothing!\n");
		}
	}

    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}


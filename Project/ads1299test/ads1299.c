/**
 *  \file ads1299.c
 *  \brief Some useful functions for using the ADS1299 EEG analog front-end from Texas Instruments.
 *	\details The ADS1299 is an SPI slave device. Communication with it requires at least one SPI master module on the host.
 *	\author Graham Kelly
 *	\version 1.0
 *	\date August 2014
 *
 *  All Atmel Software Framework libraries used herein are copyright Atmel and
 *  subject to their appropriate licenses, which allow free redistribution with
 *  some restrictions. These restrictions are listed in their appropriate files.
 *
 *  \page License
 *
 *  Brainboard firmware code is placed under the MIT license
 *  Copyright (c) 2014 Graham Kelly
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 */

 /*
  *ads1299.c
  *Created on: December 5, 2016
  *Co_Author: Bifei Liu
  */
#include "ads1299.h"

#ifdef __cplusplus
extern "C" {
#endif


	/**************************************************************************************************************************************************
	*               Function Definitions                                                                                                              *
	**************************************************************************************************************************************************/

	/* SYSTEM CONTROL FUNCTIONS **********************************************************************************************************************/

	ads1299_error_t	ads1299_device_init(uint8_t init_regs)
	{
		/* Power cycle ADS1299 */
	//	ADS1299_PWDN();
	//	delayMicroseconds(20);
	//	ADS1299_PWON();

		/* Allow oscillator warm-up */
	//	delay(1000);

		/* Tell chip to exit continuous data mode */
		ads1299_send_byte(ADS1299_OPC_SDATAC);
		/* Stop taking conversions; apparently not done automatically */
		ads1299_send_byte(ADS1299_OPC_STOP);

		if (init_regs)
		{
			/* Write to GPIO register, set all pins to driven-low output */
			ads1299_wreg(ADS1299_REGADDR_GPIO, ADS1299_REG_GPIO_GPIOC4_OUTPUT |
				ADS1299_REG_GPIO_GPIOD4_LOW |
				ADS1299_REG_GPIO_GPIOC3_OUTPUT |
				ADS1299_REG_GPIO_GPIOD3_LOW |
				ADS1299_REG_GPIO_GPIOC2_OUTPUT |
				ADS1299_REG_GPIO_GPIOD2_LOW |
				ADS1299_REG_GPIO_GPIOC1_OUTPUT |
				ADS1299_REG_GPIO_GPIOD1_LOW);

			/* Write to CONFIG1, set data rate to 250 Hz */
			ads1299_wreg(ADS1299_REGADDR_CONFIG1, ADS1299_REG_CONFIG1_RESERVED_VALUE |
				ADS1299_REG_CONFIG1_FMOD_DIV_BY_512);

			/* Write to CONFIG2 register, generate test signal internally */
			ads1299_wreg(ADS1299_REGADDR_CONFIG2, ADS1299_REG_CONFIG2_RESERVED_VALUE |
				ADS1299_REG_CONFIG2_CAL_INT |
				ADS1299_REG_CONFIG2_CAL_PULSE_FCLK_DIV_2_21);

			/* Write to CONFIG3, enable internal reference buffer, bias internally generated, bias buffer enabled */
			ads1299_wreg(ADS1299_REGADDR_CONFIG3, ADS1299_REG_CONFIG3_REFBUF_ENABLED |
				ADS1299_REG_CONFIG3_BIASREF_INT |
				ADS1299_REG_CONFIG3_BIASBUF_ENABLED);
			/* Reference settling time */
			delay(150);

			/* Write to CH1 settings register, set as normal input, gain 24 */
			ads1299_wreg(ADS1299_REGADDR_CH1SET, ADS1299_REG_CHNSET_CHANNEL_ON |
				ADS1299_REG_CHNSET_GAIN_24 |
				ADS1299_REG_CHNSET_SRB2_DISCONNECTED |
				ADS1299_REG_CHNSET_TEST_SIGNAL);
			/* Write to CH2 settings register, set as normal input, gain 24 */
			ads1299_wreg(ADS1299_REGADDR_CH2SET, ADS1299_REG_CHNSET_CHANNEL_ON |
				ADS1299_REG_CHNSET_GAIN_24 |
				ADS1299_REG_CHNSET_SRB2_DISCONNECTED |
				ADS1299_REG_CHNSET_NORMAL_ELECTRODE);
			/* Write to CH3 settings register, set as normal input, gain 24 */
			ads1299_wreg(ADS1299_REGADDR_CH3SET, ADS1299_REG_CHNSET_CHANNEL_ON |
				ADS1299_REG_CHNSET_GAIN_24 |
				ADS1299_REG_CHNSET_SRB2_DISCONNECTED |
				ADS1299_REG_CHNSET_TEST_SIGNAL);
			/* Write to CH4 settings register, set as normal input, gain 24 */
			ads1299_wreg(ADS1299_REGADDR_CH4SET, ADS1299_REG_CHNSET_CHANNEL_ON |
				ADS1299_REG_CHNSET_GAIN_24 |
				ADS1299_REG_CHNSET_SRB2_DISCONNECTED |
				ADS1299_REG_CHNSET_NORMAL_ELECTRODE);
			/* Write to CH5 settings register, set as normal input, gain 24 */
			ads1299_wreg(ADS1299_REGADDR_CH5SET, ADS1299_REG_CHNSET_CHANNEL_ON |
				ADS1299_REG_CHNSET_GAIN_24 |
				ADS1299_REG_CHNSET_SRB2_DISCONNECTED |
				ADS1299_REG_CHNSET_NORMAL_ELECTRODE);
			/* Write to CH6 settings register, set as normal input, gain 24 */
			ads1299_wreg(ADS1299_REGADDR_CH6SET, ADS1299_REG_CHNSET_CHANNEL_ON |
				ADS1299_REG_CHNSET_GAIN_24 |
				ADS1299_REG_CHNSET_SRB2_DISCONNECTED |
				ADS1299_REG_CHNSET_NORMAL_ELECTRODE);
			/* Write to CH5 settings register, set as normal input, gain 24 */
			ads1299_wreg(ADS1299_REGADDR_CH7SET, ADS1299_REG_CHNSET_CHANNEL_ON |
				ADS1299_REG_CHNSET_GAIN_24 |
				ADS1299_REG_CHNSET_SRB2_DISCONNECTED |
				ADS1299_REG_CHNSET_NORMAL_ELECTRODE);
			/* Write to CH6 settings register, set as normal input, gain 24 */
			ads1299_wreg(ADS1299_REGADDR_CH8SET, ADS1299_REG_CHNSET_CHANNEL_ON |
				ADS1299_REG_CHNSET_GAIN_24 |
				ADS1299_REG_CHNSET_SRB2_DISCONNECTED |
				ADS1299_REG_CHNSET_NORMAL_ELECTRODE);

			/* Write to MISC1 register, SRB1 on (ref electrode) */
	//		ads1299_wreg(ADS1299_REGADDR_MISC1, ADS1299_REG_MISC1_SRB1_ON);
		}
		return ADS1299_STATUS_OK;
	}



	/* REGISTER READ/WRITE FUNCTIONS *****************************************************************************************************************/

	ads1299_error_t ads1299_rreg(uint8_t reg_addr, uint8_t* read_reg_val_ptr)
	{
		uint8_t read_data = 0;

		ADS1299_CS_LOW();

		/* First byte: read command for specified register */
		bcm2835_spi_transfer(ADS1299_OPC_RREG | reg_addr);
		delayMicroseconds(1);

		/* Second byte: Read only 1 register (send n-1, where n is number of registers to read) */
		bcm2835_spi_transfer(0x00);
		delayMicroseconds(1);

		/* Read SPI RX register */
		read_data = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
		delayMicroseconds(1);
		*read_reg_val_ptr = (uint8_t)read_data;

		ADS1299_CS_HIGH();

		return ADS1299_STATUS_OK;
	}

	ads1299_error_t ads1299_wreg(uint8_t reg_addr, uint8_t reg_val_to_write)
	{
		ADS1299_CS_LOW();

		//SPI_HAL_Reconfig( ADS1299_SPI_DEV_ID);

		/* First byte: write command for specified register */
		bcm2835_spi_transfer(ADS1299_OPC_WREG | reg_addr);
		delayMicroseconds(1);

		/* Second byte: number of registers to write (1) */
		bcm2835_spi_transfer(0x00);
		delayMicroseconds(1);

		/* Third byte: write register value */
		bcm2835_spi_transfer(reg_val_to_write);
		delayMicroseconds(1);

		ADS1299_CS_HIGH();

		return ADS1299_STATUS_OK;
	}

	/* DATA RETRIEVAL FUNCTIONS **********************************************************************************************************************/

	//ads1299_error_t ads1299_rdata32_packet(volatile uint32_t sample_idx, bboard_data32bit_packet_t* packet_ptr)
	//{
	//
	//	volatile uint8_t channel_idx;
	//	union {
	//		uint32_t raw;
	//		uint8_t status[4];
	//	} __attribute__((packed)) statustemp;
	//	union {
	//		int32_t raw;
	//		uint8_t data[4];
	//	} __attribute__((packed)) sigtemp;
	//	statustemp.raw = 0;
	//	sigtemp.raw = 0;
	//
	//	/* Begin SPI comms */
	//	ADS1299_CS_LOW();
	//
	//	/* Function assumes we've already sent RDATA command or are in RDATAC mode */
	//
	//	/* Read in status word first (24 bits) */
	//	spi_read_packet(SPI_ADDRESS, &statustemp.status[1], 3);
	//	packet_ptr->eegstatus = statustemp.raw;
	//
	//	/* Begin reading in data */
	//	for (channel_idx = 0; channel_idx < MAX_EEG_CHANNELS; channel_idx++)
	//	{
	//		spi_read_packet(SPI_ADDRESS, &sigtemp.data[1], 3);
	//		packet_ptr->eegdata[sample_idx][channel_idx] = SIGN_EXT_24(sigtemp.raw);
	//	}
	//
	//	ADS1299_CS_HIGH();
	//
	//
	//	#endif	/*  */
	//	return ADS1299_STATUS_OK;
	//}
	//
	//ads1299_error_t ads1299_rdata24_packet(volatile uint32_t sample_idx, bboard_data24bit_packet_t* packet_ptr)
	//{
	//
	//	volatile uint8_t channel_idx;
	//
	//	uint8_t temp[3];
	//
	//	/* Begin SPI comms */
	//	ADS1299_CS_LOW();
	//
	//	/* Function assumes we've already sent RDATA command or are in RDATAC mode */
	//
	//	/* Read in status word first (24 bits) */
	//	spi_read_packet(SPI_ADDRESS, temp, 3);
	//	packet_ptr->eegstatus[0] = temp[0];
	//	packet_ptr->eegstatus[1] = temp[1];
	//	packet_ptr->eegstatus[2] = temp[2];
	//
	//	/* Begin reading in data */
	//	for (channel_idx = 0; channel_idx < MAX_EEG_CHANNELS; channel_idx++)
	//	{
	//		spi_read_packet(SPI_ADDRESS, temp, 3);
	//		packet_ptr->eegdata[sample_idx][channel_idx][0] = temp[0];
	//		packet_ptr->eegdata[sample_idx][channel_idx][1] = temp[1];
	//		packet_ptr->eegdata[sample_idx][channel_idx][2] = temp[2];
	//	}
	//
	//	ADS1299_CS_HIGH();
	//
	//
	//	#endif	/*  */
	//	return ADS1299_STATUS_OK;
	//}

	ads1299_error_t ads1299_rdata24_generic(volatile uint8_t status_array[], volatile uint8_t(*data_array)[MAX_EEG_CHANNELS][3])
	{
		volatile uint8_t channel_idx;

		/* Begin SPI comms */
		ADS1299_CS_LOW();

		//SPI_HAL_Reconfig( ADS1299_SPI_DEV_ID);

		/* Function assumes we've already sent RDATA command or are in RDATAC mode */

		/* Read in status word first (24 bits) */ //ads1299 data output is MSB first
		*(status_array--) = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
		*(status_array--) = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
		*status_array = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);

		/* Begin reading in data */
		for (channel_idx = 0; channel_idx < MAX_EEG_CHANNELS; channel_idx++)
		{
			(*data_array)[channel_idx][0] = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
			(*data_array)[channel_idx][1] = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
			(*data_array)[channel_idx][2] = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
		}

		ADS1299_CS_HIGH();

		return ADS1299_STATUS_OK;
	}

	ads1299_error_t ads1299_rdata32_generic(volatile uint32_t *status, volatile int32_t data_array[MAX_EEG_CHANNELS])
	{
		volatile uint8_t channel_idx;

		//Notice stm32 is little endian system, however the ads1299 chip is MSB first, namely big endian
		/*union {
			uint32_t raw;
			uint8_t status[4];
		} __attribute__((packed)) statustemp;*/

		union {
			uint32_t raw;
			uint8_t status[4];
		}statustemp;

		/*union {
			int32_t raw;
			uint8_t data[4];
		} __attribute__((packed)) sigtemp;*/

		union {
			int32_t raw;
			uint8_t data[4];
		}sigtemp;

		statustemp.raw = 0;
		sigtemp.raw = 0;

		ADS1299_CS_LOW();

		//SPI_HAL_Reconfig( ADS1299_SPI_DEV_ID);

		//for(uint16_t ii = 0; ii<30 ;ii++);

		/* Begin SPI comms */

		/* Function assumes we've already sent RDATA command or are in RDATAC mode */

		/* Read in status word first (24 bits) */
		statustemp.status[2] = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
		statustemp.status[1] = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
		statustemp.status[0] = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
		*status = statustemp.raw;

		/* Begin reading in data */
		for (channel_idx = 0; channel_idx < MAX_EEG_CHANNELS; channel_idx++)
		{
			sigtemp.data[2] = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
			sigtemp.data[1] = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
			sigtemp.data[0] = bcm2835_spi_transfer(ADS1299_OPC_DUMMY);
			data_array[channel_idx] = SIGN_EXT_24(sigtemp.raw);
		}

		ADS1299_CS_HIGH();

		return ADS1299_STATUS_OK;
	}

#ifdef __cplusplus
}
#endif

/*
 * adc_defines_includes_general_functions.c
 *
 *  Created on: Aug 8, 2025
 *      Author: AW
 */

/* Includes
 * ------------------------------------------------------------------*/
#include "adc_defines_includes_general_functions.h"



/* Function declarations
 * ------------------------------------------------------------------*/


/* HAL internal functions
 * ----------------------------------*/
void set_pin(uint16_t pin, GPIO_PinState state)
{
	if(pin == CS1)
	{
		HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, state);
	}else
	{
		HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, state);
	}
}



/* Send/Receive Data
 * ----------------------------------*/

// Send 8 Bit Data
void send_data8(uint8_t data)
{
	HAL_SPI_Transmit (&hspi3, &data, 1, HAL_MAX_DELAY);
}

// Send 8 Bit Data with STATUSBYTE receive
uint8_t send_data8_receive_STATUSBYTE(uint8_t data)
{
	uint8_t STATUSBYTE = 0;
	HAL_SPI_TransmitReceive (&hspi3, &data, &STATUSBYTE, 1, HAL_MAX_DELAY);
	return STATUSBYTE;
}

// Receive 8 Bit Data
uint8_t receive_data8()
{
	uint8_t data;
	HAL_SPI_Receive (&hspi3, &data, 1, HAL_MAX_DELAY);
	return data;
}

// Receive 16 Bit Data
uint16_t receive_data16()
{
	uint8_t data_buffer[2] = {0};
	uint16_t data = 0;
	HAL_SPI_Receive (&hspi3, data_buffer, 2, HAL_MAX_DELAY);
	data = ( (data_buffer[0] << 8) | data_buffer[1] );

	return data;
}


/* Send COMMANDBYTE general
 * ----------------------------------*/

// Send COMMANDBYTE
void send_COMMANDBYTE(uint16_t chipselect, uint8_t device_address, uint8_t regaddr_fastcmd, uint8_t cmd_type)
{
	uint8_t COMMANDBYTE = (device_address << 6) | (regaddr_fastcmd << 2) | cmd_type;

	set_pin(chipselect, HIGH);		// To be sure that Communication is not existing first
	set_pin(chipselect, LOW);		// Start SPI communication
	send_data8(COMMANDBYTE);

	if(cmd_type == FAST_COMM)
	{
		set_pin(chipselect, HIGH);		// End the SPI communication if it was a fast command
	}

	// End the SPI communication manually! If sending data to write after command byte
}

// Send COMMANDBYTE with STATUSBYTE receive
uint8_t send_COMMANDBYTE_receive_STATUSBYTE(uint16_t chipselect, uint8_t device_address, uint8_t regaddr_fastcmd, uint8_t cmd_type)
{
	uint8_t STATUSBYTE = 0;
	uint8_t COMMANDBYTE = (device_address << 6) | (regaddr_fastcmd << 2) | cmd_type;

	set_pin(chipselect, HIGH);		// To be sure that Communication is not existing first
	set_pin(chipselect, LOW);		// Start SPI communication
	STATUSBYTE = send_data8_receive_STATUSBYTE(COMMANDBYTE);

	if(cmd_type == FAST_COMM)
	{
		set_pin(chipselect, HIGH);		// End the SPI communication if it was a fast command
	}

	return STATUSBYTE;


	// End the SPI communication manually! If sending data to write after command byte
}


// Send COMMANDBYTE with a ready bitcode
void send_COMMANDBYTE_code(uint16_t chipselect, uint8_t commandbyte)
{
	set_pin(chipselect, HIGH);		// To be sure that Communication is not existing first
	set_pin(chipselect, LOW);		// Start SPI communication
	send_data8(commandbyte);

	// End the SPI communication manually!
}

uint8_t send_COMMANDBYTE_code_receive_STATUSBYTE(uint16_t chipselect, uint8_t commandbyte)
{
	uint8_t STATUSBYTE = 0;
	set_pin(chipselect, HIGH);		// To be sure that Communication is not existing first
	set_pin(chipselect, LOW);		// Start SPI communication
	STATUSBYTE = send_data8_receive_STATUSBYTE(commandbyte);
	return STATUSBYTE;

	// End the SPI communication manually!
}


/* Send COMMANDBYTE fast commands specific (Command type = FAST_COMM)
 * ----------------------------------*/

void send_COMMANDBYTE_fast_cmd_adc_conv_start(uint16_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, FC_ADC_CONV_START);
	set_pin(chipselect, HIGH);		// End the SPI communication if it was a fast command
	HAL_Delay(1);		// For the conversion time Tconv of about 300 to 400ns
}

uint8_t send_COMMANDBYTE_fast_cmd_adc_conv_start_receive_STATUSBYTE(uint16_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, FC_ADC_CONV_START);
	set_pin(chipselect, HIGH);		// End the SPI communication
	return STATUSBYTE;
}


void send_COMMANDBYTE_fast_cmd_adc_standby(uint16_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, FC_ADC_STANDBY);
	set_pin(chipselect, HIGH);		// End the SPI communication
}

uint8_t send_COMMANDBYTE_fast_cmd_adc_standby_receive_STATUSBYTE(uint16_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, FC_ADC_STANDBY);
	set_pin(chipselect, HIGH);		// End the SPI communication
	return STATUSBYTE;
}


void send_COMMANDBYTE_fast_cmd_adc_shutdown(uint16_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, FC_ADC_SHUTDOWN);
	set_pin(chipselect, HIGH);		// End the SPI communication
}

uint8_t send_COMMANDBYTE_fast_cmd_adc_shutdown_receive_STATUSBYTE(uint16_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, FC_ADC_SHUTDOWN);
	set_pin(chipselect, HIGH);		// End the SPI communication
	return STATUSBYTE;
}



void send_COMMANDBYTE_fast_cmd_full_shutdown(uint16_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, FC_FULL_SHUTDOWN);
	set_pin(chipselect, HIGH);		// End the SPI communication
}

uint8_t send_COMMANDBYTE_fast_cmd_full_shutdown_receive_STATUSBYTE(uint16_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, FC_FULL_SHUTDOWN);
	set_pin(chipselect, HIGH);		// End the SPI communication
	return STATUSBYTE;
}



void send_COMMANDBYTE_fast_cmd_full_reset(uint16_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, FC_FULL_RESET);
	set_pin(chipselect, HIGH);		// End the SPI communication
}

uint8_t send_COMMANDBYTE_fast_cmd_full_reset_receive_STATUSBYTE(uint16_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, FC_FULL_RESET);
	set_pin(chipselect, HIGH);		// End the SPI communication
	return STATUSBYTE;
}




/* Send COMMANDBYTE Read/Write commands (Command type = INC_WR || INC_RD)
 * ----------------------------------*/
void write_adc_reg8(uint16_t chipselect, uint8_t register_address, uint8_t wr_data)
{
	// Sending write command and sending data to write
	send_COMMANDBYTE(chipselect, DEV_ADDR, register_address, INC_WR);
	send_data8(wr_data);

	set_pin(chipselect, HIGH);		// End the SPI communication
}

uint8_t read_adc_reg8(uint16_t chipselect, uint8_t register_address)
{
	uint8_t data = 0;
	// Sending read command and sending data to write
	send_COMMANDBYTE(chipselect, DEV_ADDR, register_address, INC_RD);
	data = receive_data8();

	set_pin(chipselect, HIGH);		// End the SPI communication

	return data;
}

uint16_t read_adc_reg16(uint16_t chipselect, uint8_t register_address)
{
	uint16_t data = 0;
	// Sending read command and sending data to write
	send_COMMANDBYTE(chipselect, DEV_ADDR, register_address, INC_RD);
	data = receive_data16();

	set_pin(chipselect, HIGH);		// End the SPI communication

	return data;
}



/* Specific functions
 * ----------------------------------*/

// Reading the adc converted value, choose ADC par by CS
uint16_t read_adc_conv_value(uint16_t chipselect)
{
	uint16_t data = 0;
	data =  read_adc_reg16(chipselect, ADCDATA_ADDR);
	return data;
}

// Choose the two MUX entry Channels for the MUX outputs VIN+ and VIN-
void set_channels(uint16_t chipselect, uint8_t ch_vinplus, uint8_t ch_vinminus)
{
	uint8_t channel_set_bitcode = ( (ch_vinplus << 4) | ch_vinminus );
	write_adc_reg8(chipselect, MUX_ADDR, channel_set_bitcode);
}



/* Set Channel functions
 * ----------------------------------*/

// Choose the sensor J7 what is connected to CH0 and Ch1 of MUX of ADC U3 (CS1)
void set_channels_J7_CS1()
{
	set_channels(CS1, CH0, CH1);
}

// Choose the sensor J8 what is connected to CH0 and Ch1 of MUX of ADC U3 (CS1)
void set_channels_J8_CS1()
{
	set_channels(CS1, CH2, CH3);
}

// Choose the sensor J10 what is connected to CH0 and Ch1 of MUX of ADC U3 (CS1)
void set_channels_J10_CS1()
{
	set_channels(CS1, CH4, CH5);
}

// Choose the sensor J12 what is connected to CH0 and Ch1 of MUX of ADC U3 (CS1)
void set_channels_J12_CS1()
{
	set_channels(CS1, CH6, CH7);
}



// Choose the sensor J13 what is connected to CH0 and Ch1 of MUX of ADC U3 (CS1)
void set_channels_J13_CS2()
{
	set_channels(CS2, CH0, CH1);
}

// Choose the sensor J14 what is connected to CH0 and Ch1 of MUX of ADC U3 (CS1)
void set_channels_J14_CS2()
{
	set_channels(CS2, CH2, CH3);
}

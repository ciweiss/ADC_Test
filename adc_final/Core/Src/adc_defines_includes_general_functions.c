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
void set_pin(uint8_t pin, GPIO_PinState state)
{
	pin = state;
}



/* Send Data
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

void send_COMMANDBYTE_fast_cmd_adc_conv_start(uint8_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, ADC_CONV_START_CODE);
}

uint8_t send_COMMANDBYTE_fast_cmd_adc_conv_start_receive_STATUSBYTE(uint8_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, ADC_CONV_START_CODE);
	return STATUSBYTE;
}


void send_COMMANDBYTE_fast_cmd_adc_standby(uint8_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, ADC_STANDBY_CODE);
}

uint8_t send_COMMANDBYTE_fast_cmd_adc_standby_receive_STATUSBYTE(uint8_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, ADC_STANDBY_CODE);
	return STATUSBYTE;
}


void send_COMMANDBYTE_fast_cmd_adc_shutdown(uint8_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, ADC_SHUTDOWN_CODE);
}

uint8_t send_COMMANDBYTE_fast_cmd_adc_shutdown_receive_STATUSBYTE(uint8_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, ADC_SHUTDOWN_CODE);
	return STATUSBYTE;
}



void send_COMMANDBYTE_fast_cmd_full_shutdown(uint8_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, FULL_SHUTDOWN_CODE);
}

uint8_t send_COMMANDBYTE_fast_cmd_full_shutdown_receive_STATUSBYTE(uint8_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, FULL_SHUTDOWN_CODE);
	return STATUSBYTE;
}



void send_COMMANDBYTE_fast_cmd_full_reset(uint8_t chipselect)
{
	send_COMMANDBYTE_code(chipselect, FULL_RESET_CODE);
}

uint8_t send_COMMANDBYTE_fast_cmd_full_reset_receive_STATUSBYTE(uint8_t chipselect)
{
	uint8_t STATUSBYTE = 0;
	STATUSBYTE = send_COMMANDBYTE_code_receive_STATUSBYTE(chipselect, FULL_RESET_CODE);
	return STATUSBYTE;
}

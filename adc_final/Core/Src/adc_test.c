/*
 * adc_test.c
 *
 *  Created on: Aug 11, 2025
 *      Author: AW
 *
 *      ALL TESTING FUNCTIONS TO  THE ADC
 */



/* Includes
 * ------------------------------------------------------------------*/
#include "adc_test.h"


/* Variables
 * ------------------------------------------------------------------*/
int16_t adc_value_raw = 0;										// For reading raw adc value at once
int16_t adc_value_raw_Jx[6] = {0};								// For saving every adc sensor value in an array
const float factor = (float)VREF / (float)(1<<RESOLUTION);		// Factor for calculating the raw value to voltage value, the divider is equal to 2 to power of RESOLUTION
float adc_value_vol = 0;										// Voltage value in mV
char output[100];												// Just an output string
uint16_t chipselect = 0;										// Chipselect, needed for some functions


// This should be outputted at beginning (raw and voltage values will be outputted at suitable positions)
char standard_output_list[500] = "\033[2J\033[H__________________\r\n\nSensor: J7\r\nRaw value: \r\nVoltage value: \r\n________\n\r\nSensor: J8\r\nRaw value: \n\rVoltage value: \n\r________\n\r\nSensor: J10\n\rRaw value: \n\rVoltage value: \n\r________\n\r\nSensor: J12\n\rRaw value: \n\rVoltage value: \n\r________\n\r\nSensor: J13\n\rRaw value: \n\rVoltage value: \n\r________\n\r\nSensor: J14\n\rRaw value: \n\rVoltage value: \n\r__________________";
/*
 * Has following structure
	    __________________

		Sensor: J7
		Raw value:
		Voltage value:
		________
		Sensor: J8
		Raw value:
		Voltage value:
		________
		Sensor: J10
		Raw value:
		Voltage value:
		________
		Sensor: J12
		Raw value:
		Voltage value:
		________
		Sensor: J13
		Raw value:
		Voltage value:
		________
		Sensor: J14
		Raw value:
		Voltage value:
		__________________
*/


// Cursor-Positions for Raw Values
const char *cursor_raw[] = {
    "\033[4;16H",   // J7
    "\033[9;16H",   // J8
    "\033[14;16H",  // J10
    "\033[19;16H",  // J12
    "\033[24;16H",  // J13
    "\033[29;16H"   // J14
};

// Cursor-Positions for Voltage Values
const char *cursor_volt[] = {
    "\033[5;16H",   // J7
    "\033[10;16H",   // J8
    "\033[15;16H",  // J10
    "\033[20;16H",  // J12
    "\033[25;16H",  // J13
    "\033[30;16H"   // J14
};

const char turn_cursor_on[12] = "\033[?25h";
const char turn_cursor_off[12] = "\033[?25l";





/* Function declarations
 * ------------------------------------------------------------------*/

void uart_standard_list()
{
	// Output the standard list without values
	HAL_UART_Transmit(&huart1, (uint8_t*)standard_output_list, strlen(standard_output_list),HAL_MAX_DELAY);

	// Turn curser off (Otherwise curser jumps with every value update around)
	HAL_UART_Transmit(&huart1, (uint8_t*)turn_cursor_off, strlen(turn_cursor_off),HAL_MAX_DELAY);
}


// Testing the sensor J8 at ADC U3 (CS1)
uint16_t adc_conversion_and_feedback_Jx(uint8_t Jx)
{
	// Setting up chipselect and channel select
	switch (Jx)
	{
	case J7:
		set_channels_J7_CS1();
		chipselect = CS1;
		break;

	case J8:
		set_channels_J8_CS1();
		chipselect = CS1;
		break;

	case J10:
		set_channels_J10_CS1();
		chipselect = CS1;
		break;

	case J12:
		set_channels_J12_CS1();
		chipselect = CS1;
		break;

	case J13:
		set_channels_J13_CS2();
		chipselect = CS2;
		break;

	case J14:
		set_channels_J14_CS2();
		chipselect = CS2;
		break;
	}


	// Standard processes
	send_COMMANDBYTE_fast_cmd_adc_conv_start(chipselect);				// Start adc conversion
	adc_value_raw = (int16_t)read_adc_conv_value(chipselect);			// Read the conversion result

	return adc_value_raw;
}



void record_all_Jx_values()
{
	for (int jx = 1; jx <= 6; jx++)
	{
		adc_value_raw_Jx[jx-1] = adc_conversion_and_feedback_Jx(jx);
	}
}



void uart_all_Jx_values()
{


	for (int jx = 1; jx <= 6; jx++)
	{

		// Convert raw value to mV value
		adc_value_vol = adc_value_raw_Jx[jx-1] * factor;

		// Output the results
		sprintf(output, "%s%d", cursor_raw[jx-1], adc_value_raw_Jx[jx-1]);
		HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);

		sprintf(output, "%s%f", cursor_volt[jx-1], adc_value_vol);
		HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);
	}
}





void adc_test_routine()
{
	record_all_Jx_values();
	uart_all_Jx_values();
}


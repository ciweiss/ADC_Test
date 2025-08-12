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
int16_t adc_value_raw = 0;
const float factor = (float)VREF / (float)(1<<RESOLUTION);		// Factor for calculating the raw value to voltage value, the divider is equal to 2 to power of RESOLUTION
float adc_value_vol = 0;										// Voltage value in mV
char output[100];
uint16_t chipselect = 0;
int16_t adc_value_raw_Jx[6] = {0};


char standard_output_list[500] = "\r\n\n\n\n\n\n__________________\r\n\nSensor: J7\r\nRaw value: \r\nVoltage value: \r\n________\n\r\nSensor: J8\r\nRaw value: \n\rVoltage value: \n\r________\n\r\nSensor: J10\n\rRaw value: \n\rVoltage value: \n\r________\n\r\nSensor: J12\n\rRaw value: \n\rVoltage value: \n\r________\n\r\nSensor: J13\n\rRaw value: \n\rVoltage value: \n\r________\n\r\nSensor: J14\n\rRaw value: \n\rVoltage value: \n\r__________________";
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




/* Function declarations
 * ------------------------------------------------------------------*/

void uart_standard_list()
{
	// Output the standard list without values
	HAL_UART_Transmit(&huart1, (uint8_t*)standard_output_list, strlen(standard_output_list),HAL_MAX_DELAY);
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


		// Variables for output
		const char *sensor_name = NULL;



		// Determine the char
		switch (jx)
		{
		case J7:
			sensor_name = "J7";
			break;

		case J8:
			sensor_name = "J8";
			break;

		case J10:
			sensor_name = "J10";
			break;

		case J12:
			sensor_name = "J12";
			break;

		case J13:
			sensor_name = "J13";
			break;

		case J14:
			sensor_name = "J14";
			break;
		}



		// First case overview element (UI)
		if(jx == 1)
		{
			// Output the element
			sprintf(output, "\n\n\n\n\n\n__________________\r\n\n");
			HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);
		}



		// Convert raw value to mV value
		adc_value_vol = adc_value_raw_Jx[jx-1] * factor;



		// Output the results
		sprintf(output, "Sensor: %s\r\n", sensor_name);
		HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);

		sprintf(output, "Raw value: %d\r\n", adc_value_raw_Jx[jx-1]);
		HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);

		sprintf(output, "Voltage value: %f mV\r\n", adc_value_vol);
		HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);



		// Last case overview element (UI)
		if(jx == 6)
		{
			// Output the element
			sprintf(output, "__________________\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);
		}else
		{
			// Output the element
			sprintf(output, "________\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);
		}

		adc_value_raw_Jx[jx-1] = adc_conversion_and_feedback_Jx(jx);
		HAL_Delay(20);
	}
}





void adc_test_routine()
{
	record_all_Jx_values();
	uart_all_Jx_values();
}


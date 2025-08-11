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



/* Function declarations
 * ------------------------------------------------------------------*/
// Testing the sensor J8 at ADC U3 (CS1)
uint16_t testing_Jx(uint8_t Jx)
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
		      adc_value_raw_Jx[jx-1] = testing_Jx(jx);
			  HAL_Delay(20);
		  }
}





/*
	// Convert raw value to mV value
	adc_value_vol = adc_value_raw * factor;

	// Output the results
	sprintf(output, "Raw value: %d\r\n", adc_value_raw);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);
	sprintf(output, "Voltage value: %f mV\r\n\n\n", adc_value_vol);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);
 */



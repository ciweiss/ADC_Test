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
float adc_value_vol = 0;							// Voltage value in mV
char output[100];



/* Function declarations
 * ------------------------------------------------------------------*/


// Testing the sensor J8 at ADC U3 (CS1)
void testing_J8_CS1()
{
	// Standard processes
	set_channels_J8_CS1();								// Set channels to read J7
	send_COMMANDBYTE_fast_cmd_adc_conv_start(CS1);		// Start adc conversion
	adc_value_raw = (int16_t)read_adc_conv_value(CS1);			// Read the conversion result


	// Convert raw value to mV value
	adc_value_vol = adc_value_raw * factor;

	// Output the results

	// Output checks
	sprintf(output, "factor: %f\r\n", factor);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);


	sprintf(output, "\rMEASURE_BEGIN\r\n________\r\n\n");
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);

	sprintf(output, "Raw value: %d\r\n", adc_value_raw);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);
	sprintf(output, "Voltage value: %f mV\r\n", adc_value_vol);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);


	sprintf(output, "\nMEASURE_END\r\n________\r\n\n");
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);
}

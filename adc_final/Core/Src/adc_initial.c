/*
 * adc_initial.c
 *
 *  Created on: Aug 8, 2025
 *      Author: AW
 *
 *      ALL INITIAL FUNCTIONS TO SETUP THE ADC
 */



/* Includes
 * ------------------------------------------------------------------*/
#include "adc_initial.h"



/* Function declarations
 * ------------------------------------------------------------------*/

void adc_init()
{
	// Setting all CS pins to idle state
	set_pin(CS1, HIGH);
	set_pin(CS2, HIGH);

	// Reset all ADC parts (Reset all their registers to default values)
	send_COMMANDBYTE_fast_cmd_full_reset(CS1);
	send_COMMANDBYTE_fast_cmd_full_reset(CS2);

	// IMPORTANT!: Setting the internal clock for the ADC for both parts
	write_adc_reg8(CS1, CONFIG0_ADDR, INITIAL_CONFIG0_CODE);
	write_adc_reg8(CS2, CONFIG0_ADDR, INITIAL_CONFIG0_CODE);

	// Choosing channels for sensors J7 and J13
	set_channels_J7_CS1();
	set_channels_J13_CS2();

/*
	// debug
	uint8_t reg_value = read_adc_reg8(CS2, MUX_ADDR);
	char output[100];
			sprintf(output, "\r\nINITIAL: CS2 MUX_ADDR reg value: %02X\r\n", reg_value);
			HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output),HAL_MAX_DELAY);
*/
}

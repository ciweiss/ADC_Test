/*
 * adc_defines.h
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */

#ifndef INC_ADC_DEFINES_INCLUDES_GENERAL_FUNCTIONS_H_
#define INC_ADC_DEFINES_INCLUDES_GENERAL_FUNCTIONS_H_



#endif /* INC_ADC_DEFINES_INCLUDES_GENERAL_FUNCTIONS_H_ */



/* Includes
 * ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
extern SPI_HandleTypeDef hspi3;
extern UART_HandleTypeDef huart1;



/* Defines
 * ------------------------------------------------------------------*/

/* COMMANDBYTE
 * ----------------------------------*/

// Device Address
#define DEV_ADDR						0b01					// Device Address

// Fast Commands (When Command type = FAST_COMM)
#define ADC_CONV_START_CODE				0b1010				// ADC Conversion start/restart
#define ADC_STANDBY_CODE				0b1011				// ADC Standby mode
#define ADC_SHUTDOWN_CODE				0b1100				// ADC Shutdown mode
#define FULL_SHUTDOWN_CODE				0b1101				// Full shutdown of the wole part
#define FULL_RESET_CODE					0b1110				// Full RESET (Set all registers to default values)

// Register Addresses (When Command type != FAST_COMM) (Aim to write or read)
#define ADCDATA_ADDR					0x00					// ADC Output data register to read
#define CONFIG0_ADDR					0x1						// Only important for setting CLK to internal CLK, maybe also VREF_SEL
#define CONFIG3_ADDR					0x4						// TO change CONV_MODE (one shot, continous, etc.) if needed
#define IRQ_ADDR						0x5						// There is also the DR Status Bit (Data Ready) just if needed
#define MUX_ADDR						0x6						// To set the Channels for the MUX outputs VIN+ and VIN-

// Command Types
#define FAST_COMM						0b00					// Fast command
#define STATIC_RD						0b01					// Static Read
#define INC_WR							0b10					// Incremental Write (Abort with CS=HIGH)
#define INC_RD							0b11					// Incremental Read (Abort with CS=HIGH)


/* COMMANDBYTE data to write
 * ----------------------------------*/

// Initialising
#define INITIAL_CONFIG0_CODE					0b11100000		// Writing Config0 register with CLK_SEL = 0b10 (Internal CLK)

// Fast Commands
#define FC_ADC_CONV_START				(DEV_ADDR << 6) | (ADC_CONV_START_CODE << 2) | FAST_COMM	// COMMANDBYTE bitcode for fast command conversion start/restart
#define FC_ADC_STANDBY					(DEV_ADDR << 6) | (ADC_STANDBY_CODE << 2) | FAST_COMM
#define FC_ADC_SHUTDOWN					(DEV_ADDR << 6) | (ADC_SHUTDOWN_CODE << 2) | FAST_COMM
#define FC_FULL_SHUTDOWN				(DEV_ADDR << 6) | (FULL_SHUTDOWN_CODE << 2) | FAST_COMM
#define FC_FULL_RESET					(DEV_ADDR << 6) | (FULL_RESET_CODE << 2) | FAST_COMM



/* HAL Internal
 * ----------------------------------*/

// HIGH LOW
#define HIGH 			GPIO_PIN_SET
#define LOW				GPIO_PIN_RESET

// Pinnames
#define CS1				CS1_Pin
#define CS2				CS2_Pin
#define IRQ1			IRQ1_EXTI_Pin
#define IRQ2			IRQ2_EXTI_Pin




/* Function Prototypes
 * ------------------------------------------------------------------*/


/* HAL internal functions
 * ----------------------------------*/
void set_pin(uint8_t pin, GPIO_PinState state);


/* Send Data
 * ----------------------------------*/

// Send 8 Bit Data
void send_data8(uint8_t data);

// Send 8 Bit Data with STATUSBYTE receive
uint8_t send_data8_receive_STATUSBYTE(uint8_t data);



/* Send COMMANDBYTE general
 * ----------------------------------*/

// Send COMMANDBYTE
void send_COMMANDBYTE(uint16_t chipselect, uint8_t device_address, uint8_t regaddr_fastcmd, uint8_t cmd_type);

// Send COMMANDBYTE with STATUSBYTE receive
uint8_t send_COMMANDBYTE_receive_STATUSBYTE(uint16_t chipselect, uint8_t device_address, uint8_t regaddr_fastcmd, uint8_t cmd_type);

// Send COMMANDBYTE with a ready bitcode
void send_COMMANDBYTE_code(uint16_t chipselect, uint8_t commandbyte);
uint8_t send_COMMANDBYTE_code_receive_STATUSBYTE(uint16_t chipselect, uint8_t commandbyte);


/* Send COMMANDBYTE fast commands specific (Command type = FAST_COMM)
 * ----------------------------------*/
void send_COMMANDBYTE_fast_cmd_adc_conv_start(uint8_t chipselect);
uint8_t send_COMMANDBYTE_fast_cmd_adc_conv_start_receive_STATUSBYTE(uint8_t chipselect);

void send_COMMANDBYTE_fast_cmd_adc_standby(uint8_t chipselect);
uint8_t send_COMMANDBYTE_fast_cmd_adc_standby_receive_STATUSBYTE(uint8_t chipselect);

void send_COMMANDBYTE_fast_cmd_adc_shutdown(uint8_t chipselect);
uint8_t send_COMMANDBYTE_fast_cmd_adc_shutdown_receive_STATUSBYTE(uint8_t chipselect);

void send_COMMANDBYTE_fast_cmd_full_shutdown(uint8_t chipselect);
uint8_t send_COMMANDBYTE_fast_cmd_full_shutdown_receive_STATUSBYTE(uint8_t chipselect);

void send_COMMANDBYTE_fast_cmd_full_reset(uint8_t chipselect);
uint8_t send_COMMANDBYTE_fast_cmd_full_reset_receive_STATUSBYTE(uint8_t chipselect);

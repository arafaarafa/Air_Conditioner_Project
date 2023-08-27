/**
 * @file BUZZER_interface.c
 * @brief Buzzer module implementation.
 *
 * This file contains the implementation of the buzzer module functions for initialization,
 * starting, and stopping the buzzer.
 *
 * @date 22/8/2023
 * @author Arafa Arafa
 */

#include "BUZZER_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"





/**
 * @brief Static configuration structure for the buzzer.
 */
static buzzer_str_config_t st_gs_buzzerConfig;

/**
 * @brief Enumeration for buzzer states during initialization.
 */
static buzzer_enu_state_init_t enu_gs_buzzerState = BUZZER_NOT_INIT;


buzzer_enu_return_state_t BUZZER_init (buzzer_str_config_t* ptr_str_buzzer_config)
{
	buzzer_enu_return_state_t enu_return_state = BUZZER_E_OK;
	dio_enu_return_state_t	enu_dio_return_state = DIO_OK;
	if (ptr_str_buzzer_config != NULL){

		enu_dio_return_state = DIO_init(ptr_str_buzzer_config->enu_port, ptr_str_buzzer_config->enu_pin, DIO_PIN_OUTPUT);
		if(enu_dio_return_state != DIO_OK){
			enu_return_state = BUZZER_E_NOT_OK;
		}else{
			st_gs_buzzerConfig.enu_port = ptr_str_buzzer_config->enu_port;
			st_gs_buzzerConfig.enu_pin = ptr_str_buzzer_config->enu_pin;
			enu_gs_buzzerState = BUZZER_INIT;	
		}
		
	}else{
		enu_return_state = BUZZER_NULL_PTR;
	}
	return enu_return_state;
}

buzzer_enu_return_state_t BUZZER_start(void)
{
	buzzer_enu_return_state_t enu_return_state = BUZZER_E_OK;
	if(enu_gs_buzzerState != BUZZER_NOT_INIT){
		DIO_write_pin(st_gs_buzzerConfig.enu_port,st_gs_buzzerConfig.enu_pin, DIO_PIN_HIGH_LEVEL);
		
	}else{
		enu_return_state = BUZZER_E_NOT_OK;
	}
	return enu_return_state;
}

buzzer_enu_return_state_t BUZZER_stop(void)
{
	buzzer_enu_return_state_t enu_return_state = BUZZER_E_OK;
	if(enu_gs_buzzerState != BUZZER_NOT_INIT){
		DIO_write_pin(st_gs_buzzerConfig.enu_port,st_gs_buzzerConfig.enu_pin, DIO_PIN_LOW_LEVEL);
		
	}else{
		enu_return_state = BUZZER_E_NOT_OK;
	}
	
	return enu_return_state;
}
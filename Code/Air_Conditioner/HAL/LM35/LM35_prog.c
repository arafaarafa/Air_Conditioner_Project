/**
 * @file LM35_prog.c
 * @brief LM35 Temperature Sensor module implementation.
 *
 * This file contains the implementation of the functions for interfacing with the LM35 temperature sensor.
 *
 * @date 4/21/2023
 * @author Arafa Arafa
 */ 

#include "LM35_interface.h"


/**
 * @brief ADC callback function to convert ADC reading to temperature.
 *
 * This function converts the ADC reading to temperature in degrees Celsius.
 *
 * @param[in,out] data Pointer to the ADC reading (double) to be converted to temperature.
 */
static void LM35_adc_to_temp(void *data){
	
	*((double*)data) = *((double*)data)/LM35_VOLT_PER_DEGREE;
}

lm35_enu_return_state_t LM35_init(lm35_str_channel_t *lm35_obj, lm35_str_config_t *lm35_config){
	lm35_enu_return_state_t enu_return_state = LM35_OK;
	if(lm35_obj == NULL){
		enu_return_state =LM35_NOK;
	}
	else{
		ADC_init(&(lm35_config->str_lm35_adc_config));
		ADC_channel_init(&(lm35_obj->str_lm35_channel));	
	}
	return enu_return_state;
}

lm35_enu_return_state_t LM35_read_temp(lm35_str_channel_t *lm35_obj,lm35_str_config_t *lm35_config, double *temp){
	lm35_enu_return_state_t enu_return_state = LM35_OK;
	double data = 0;
	if((lm35_obj == NULL) || (lm35_config == NULL)){
		enu_return_state =LM35_NOK;
	}
	else{
		
		ADC_channel_read(&(lm35_config->str_lm35_adc_config), &(lm35_obj->str_lm35_channel), &data);
		*temp = data/LM35_VOLT_PER_DEGREE;
	}
	return enu_return_state;
	
}

lm35_enu_return_state_t LM35_read_temp_INT(lm35_str_channel_t *lm35_obj, lm35_str_config_t *lm35_config, double *temp, void(*callback)(adc_str_config_t **ptr_ptr_str_adc_config, double **ptr_ptr_do_data)){
	lm35_enu_return_state_t enu_return_state = LM35_OK;
	if(lm35_obj == NULL){
		enu_return_state =LM35_NOK;
	}
	else{
		
		ADC_channel_read_INT(&(lm35_config->str_lm35_adc_config), &(lm35_obj->str_lm35_channel), callback, LM35_adc_to_temp);
	}
	return enu_return_state;
}

/**
 * @file ADC_prog.c
 * @brief ADC module implementation.
 *
 * This file contains the implementation of the ADC module functions.
 *
 * @date 4/21/2023
 * @author Arafa Arafa
 */


#include "ADC_private.h"
#include "ADC_interface.h"
#include "../AVR_ARCH/ISR_interface.h"

/**< Quantisation step value for ADC conversion. */
static double Quantisation_step; 

/**< Callback function for ADC conversion. */
static void(*callback_ISR)(adc_str_config_t **adc_config, double **data); 

/**< Callback function for ADC conversion completion. */
static void(*adc_end_ISR)(void *data);

adc_enu_return_state_t ADC_init(adc_str_config_t *adc_config){
	adc_enu_return_state_t enu_return_state = ADC_OK;
	if(adc_config != NULL){
		
		ADCSRA_ADD =	(1<<ADC_ENABLE)|(adc_config->adc_enu_prescaler)|(adc_config->adc_enu_interrupt<<ADC_INT_ENABLE);
		ADMUX_ADD =	 (adc_config->adc_enu_vref<<ADC_VREF_SELECT) | (adc_config->adc_enu_interrupt<<ADC_LEFT_ADJUST_RESULT);
		uint16_t result = ADC_START_VALUE_OF_REGISTER;
		for(int i= U8_ONE_VALUE; i<ADC_BIT_RESOLUTION;i++){
			result *= ADC_START_VALUE_OF_REGISTER;
			
		}
		Quantisation_step= ((double)ADC_EXTERNAL_VREF_VOLT)/(result);
		
	}
	else{
		enu_return_state = ADC_NULL_PTR;
		
		
	}
	return enu_return_state; 
}

adc_enu_return_state_t ADC_channel_init(adc_str_channel_config_t *adc_channel_config){
	adc_enu_return_state_t enu_return_state = ADC_OK;
	if(adc_channel_config != NULL){
		if(adc_channel_config->enu_channel_port == PORTA){
			DIO_init(adc_channel_config->enu_channel_port, adc_channel_config->enu_channel_pin, DIO_PIN_INPUT);
		}else{
			enu_return_state = ADC_INVALID_PORT;
		}
	}
	else{
		enu_return_state = ADC_NULL_PTR;
	}
	
	return enu_return_state; 
}

adc_enu_return_state_t ADC_channel_read(adc_str_config_t *adc_config, adc_str_channel_config_t *adc_channel_config, double *data){
	adc_enu_return_state_t enu_return_state = ADC_OK;
	if( (adc_channel_config != NULL) || (data != NULL) || (adc_config != NULL)){
		if(adc_channel_config->enu_channel_port == PORTA){
			while(READ_BIT(ADCSRA_ADD, ADC_START_CONVERSION) == U8_ONE_VALUE);
			ADMUX_ADD  = (ADC_ADMUX_MASK & ADMUX_ADD) | adc_channel_config->enu_channel_pin;
			SET_BIT(ADCSRA_ADD, ADC_START_CONVERSION);
			while(READ_BIT(ADCSRA_ADD, ADC_INT_FLAG) == U8_ZERO_VALUE);
			uint16_t adc_data_temp= U8_ZERO_VALUE;
			if(adc_config->adc_enu_DATA_L_R == ADC_DATA_ADJUST_RIGHT){
				adc_data_temp = ADCL_ADD;
				adc_data_temp |=(ADCH_ADD<< ADC_SHIFT_BY_8);
			}else{
				adc_data_temp = (ADCL_ADD>>ADC_SHIFT_BY_6);
				adc_data_temp |=(ADCH_ADD<<ADC_SHIFT_BY_2);
			}
			
			*data = Quantisation_step*adc_data_temp;
		}else{
			enu_return_state = ADC_INVALID_PORT;
		}
	}else{
		enu_return_state = ADC_NULL_PTR;
	}
	
	return enu_return_state;
	
}


adc_enu_return_state_t ADC_channel_read_INT(adc_str_config_t *adc_config, adc_str_channel_config_t *adc_channel_config, void(*callback)(adc_str_config_t **adc_config, double **data), void(*adc_end_ISR_func)(void *data)){
	adc_enu_return_state_t enu_return_state = ADC_OK;
	if(adc_channel_config == NULL || adc_channel_config->enu_channel_port != PORTA || callback == NULL){
		if(adc_channel_config->enu_channel_port != PORTA){
			while(READ_BIT(ADCSRA_ADD, ADC_START_CONVERSION) == U8_ONE_VALUE);
			callback_ISR = callback;
			adc_end_ISR = adc_end_ISR_func;
			ADMUX_ADD  = (ADC_ADMUX_MASK & ADMUX_ADD) | adc_channel_config->enu_channel_pin;
			sei();
			SET_BIT(ADCSRA_ADD, ADC_INT_ENABLE);
			SET_BIT(ADCSRA_ADD, ADC_START_CONVERSION);
		}else{
			enu_return_state = ADC_INVALID_PORT;
		}	
		
	}
	else{
		enu_return_state = ADC_NULL_PTR;
	}
	
	return enu_return_state;
}
static void ADC_channel_read_ISR(adc_str_config_t	**adc_config, double **data){
		uint16_t adc_data_temp = U8_ZERO_VALUE;
		CLEAR_BIT(ADCSRA_ADD, ADC_INT_ENABLE);
		if((*adc_config)->adc_enu_DATA_L_R == ADC_DATA_ADJUST_RIGHT){
			
			adc_data_temp = ADCL_ADD;
			adc_data_temp |=(ADCH_ADD<<ADC_SHIFT_BY_8);
			}else{
			adc_data_temp = (ADCL_ADD>>ADC_SHIFT_BY_6);
			adc_data_temp |=(ADCH_ADD<<ADC_SHIFT_BY_2);
		}
		**data = Quantisation_step*adc_data_temp;
	
}


ISR(ADC){
	double *data;
	adc_str_config_t *adc_config;
	if(callback_ISR != NULL)
		(*callback_ISR)(&adc_config, &data);
	ADC_channel_read_ISR(&adc_config, &data);
	if(adc_end_ISR != NULL)
		(*adc_end_ISR)(data);
	
	callback_ISR = NULL;
	adc_end_ISR = NULL;
}
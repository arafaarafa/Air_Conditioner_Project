/**
 * @file KEYPAD_prog.c
 * @brief Keypad module implementation.
 *
 * This file contains the implementation of the keypad module functions for initialization and reading key inputs.
 *
 * @date 22/8/2023
 * @author Arafa Arafa
 */

#include "KEYPAD_interface.h"


/**
 * @brief Keypad matrix for key mapping.
 *
 * This 2-dimensional array represents the layout of the keypad, where each element corresponds to a key.
 * Rows represent the keypad rows, and columns represent the keypad columns. The characters within the array
 * indicate the keys associated with the respective row and column.
 */
static uint8_t keypad[KEYPAD_ROWS_MAX][KEYPAD_COLS_MAX] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
	

keypad_enu_return_state_t KEYPAD_init(keypad_str_config_t *ptr_str_keypad_config)
{
	keypad_enu_return_state_t enu_return_state = KEYPAD_E_OK;
	if(ptr_str_keypad_config == NULL)
	{
		enu_return_state=KEYPAD_E_NOT_OK;
	}
	else
	{
		
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < KEYPAD_ROWS_MAX; u8_counter++){
			DIO_init(ptr_str_keypad_config->str_row_pins[u8_counter].enu_port, ptr_str_keypad_config->str_row_pins[u8_counter].enu_pin, DIO_PIN_INPUT);
			DIO_write_pin(ptr_str_keypad_config->str_row_pins[u8_counter].enu_port, ptr_str_keypad_config->str_row_pins[u8_counter].enu_pin, DIO_PIN_HIGH_LEVEL);
		}
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < KEYPAD_COLS_MAX; u8_counter++){
			DIO_init(ptr_str_keypad_config->str_col_pins[u8_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_counter].enu_pin, DIO_PIN_OUTPUT);
			DIO_write_pin(ptr_str_keypad_config->str_col_pins[u8_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_counter].enu_pin, DIO_PIN_HIGH_LEVEL);
		}
	}
	return enu_return_state;
}


keypad_enu_return_state_t KEYPAD_read (keypad_str_config_t *ptr_str_keypad_config, uint8_t *ptr_u8_data){
	
	keypad_enu_return_state_t enu_return_state=KEYPAD_E_OK;
	uint8_t u8_col_counter;
	uint8_t u8_row_counter;
	uint8_t	u8_catched_data_flag = U8_ZERO_VALUE;
	dio_enu_level_t enu_pin_level;
	

	
	if((ptr_str_keypad_config == NULL) || (ptr_u8_data == NULL)){
		enu_return_state = KEYPAD_NULL_PTR;
	}else{
		
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < KEYPAD_COLS_MAX; u8_counter++){
			DIO_write_pin(ptr_str_keypad_config->str_col_pins[u8_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_counter].enu_pin, DIO_PIN_HIGH_LEVEL);
		}
		
		for(u8_col_counter = U8_ZERO_VALUE; (u8_col_counter < KEYPAD_COLS_MAX) && (u8_catched_data_flag != U8_ONE_VALUE); u8_col_counter++)
		{
			DIO_write_pin(ptr_str_keypad_config->str_col_pins[u8_col_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_col_counter].enu_pin, DIO_PIN_LOW_LEVEL);
			for(u8_row_counter = U8_ZERO_VALUE; u8_row_counter<KEYPAD_ROWS_MAX; u8_row_counter++)
			{
				DIO_read_pin(ptr_str_keypad_config->str_row_pins[u8_row_counter].enu_port, ptr_str_keypad_config->str_row_pins[u8_row_counter].enu_pin, &enu_pin_level);
				if(enu_pin_level == DIO_PIN_LOW_LEVEL)
				{
					while(enu_pin_level == DIO_PIN_LOW_LEVEL)
					{
						DIO_read_pin(ptr_str_keypad_config->str_row_pins[u8_row_counter].enu_port, ptr_str_keypad_config->str_row_pins[u8_row_counter].enu_pin, &enu_pin_level);
					}
					*ptr_u8_data = keypad[u8_row_counter][u8_col_counter];
					u8_catched_data_flag = U8_ONE_VALUE;
					break;
				}
				
			}
			DIO_write_pin(ptr_str_keypad_config->str_col_pins[u8_col_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_col_counter].enu_pin, DIO_PIN_HIGH_LEVEL);
		}
		
	}
	
	if(u8_catched_data_flag != U8_ONE_VALUE)
	{   
		*ptr_u8_data = 'N';
		enu_return_state = KEYPAD_NO_DATA;
	}
	else
	{
		
	}
	return enu_return_state;
}
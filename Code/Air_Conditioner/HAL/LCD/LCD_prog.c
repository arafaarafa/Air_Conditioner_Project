/**
 * @file LCD_prog.c
 * @brief LCD module implementation.
 *
 * This file contains the implementation of functions to control an LCD display.
 *
 * @date 22/8/2023
 * @author Arafa Arafa
 */

#include "LCD_interface.h"


/**
 * @brief Helper function to enable LCD command/data transmission.
 *
 * This function is a helper function used to enable the LCD command/data transmission by toggling the enable pin.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 */
static void ENABLE(lcd_str_config_t* ptr_str_config);

/**
 * @brief Delay function for approximately 3 milliseconds.
 *
 * This function implements a delay loop to approximate a delay of 3 milliseconds.
 */
static void delay_3_ms(void);

/**
 * @brief Initialize the LCD.
 *
 * This function initializes the LCD based on the provided configuration.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @return Operation status: LCD_E_OK if successful, LCD_E_NOT_OK if initialization failed.
 */
lcd_enu_return_state_t LCD_init(lcd_str_config_t* ptr_str_config)
{
	lcd_enu_return_state_t enu_return_state = LCD_E_OK;
	
	enu_return_state |=DIO_init(ptr_str_config->str_RSpin.enu_port, ptr_str_config->str_RSpin.enu_pin, DIO_PIN_OUTPUT);
	enu_return_state |=DIO_init(ptr_str_config->str_RWpin.enu_port, ptr_str_config->str_RWpin.enu_pin, DIO_PIN_OUTPUT);
	enu_return_state |=DIO_init(ptr_str_config->str_Epin.enu_port, ptr_str_config->str_Epin.enu_pin, DIO_PIN_OUTPUT);
	
	if(ptr_str_config->enu_mode == LCD_4_BIT_MODE)
	{
		
		
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < LCD_MAX_DATA_PINS_MOD_4; u8_counter++){
			enu_return_state |=DIO_init(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin, DIO_PIN_OUTPUT);
		}
		LCD_cmd(ptr_str_config, LCD_CMD_CURSOR_HOME);
		LCD_cmd(ptr_str_config, LCD_4BITS_2LINES_58DM);
		LCD_cmd(ptr_str_config, LCD_DISPLAY_ON_CUR_OFF_BLOCK_OFF);
		LCD_cmd(ptr_str_config, LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_OFF);
		LCD_cmd(ptr_str_config, LCD_CMD_CLEAR);						
								
	}else if(ptr_str_config->enu_mode == LCD_8_BIT_MODE){
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < LCD_MAX_DATA_PINS_MOD_8; u8_counter++){
			enu_return_state |=DIO_init(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin, DIO_PIN_OUTPUT);
		}
		LCD_cmd(ptr_str_config, LCD_8BITS_2LINES_58DM);
		LCD_cmd(ptr_str_config, LCD_DISPLAY_ON_CUR_OFF_BLOCK_OFF);
		LCD_cmd(ptr_str_config, LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_OFF);
		LCD_cmd(ptr_str_config, LCD_CMD_CLEAR);
							
	}else{
		enu_return_state=LCD_E_NOT_OK;						
	}
	return enu_return_state;
}

/**
 * @brief Clear the LCD screen.
 *
 * This function clears the LCD screen by sending the appropriate command.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @return Operation status: LCD_E_OK if successful, LCD_E_NOT_OK if clearing failed.
 */
	lcd_enu_return_state_t LCD_clear (lcd_str_config_t* ptr_str_config)
	{

		lcd_enu_return_state_t enu_return_state=LCD_E_OK;
		enu_return_state |= LCD_cmd(ptr_str_config,LCD_CMD_CLEAR);
		delay_3_ms();
		return enu_return_state;

	}

/**
 * @brief Set the cursor position on the LCD.
 *
 * This function sets the cursor position on the LCD screen.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @param[in] copy_enu_row Selected row for the cursor.
 * @param[in] copy_enu_col Selected column for the cursor.
 * @return Operation status: LCD_E_OK if successful, LCD_E_NOT_OK if setting the cursor failed.
 */
lcd_enu_return_state_t LCD_setCursor (lcd_str_config_t* ptr_str_config, lcd_enu_row_select_t copy_enu_row, lcd_enu_col_select_t copy_enu_col)
{
	lcd_enu_return_state_t enu_return_state=LCD_E_OK;
	if(copy_enu_row == LCD_ROW_1)
	{
		LCD_cmd(ptr_str_config, LCD_DDRAM_START_ADD_LINE_1 + copy_enu_col);
		
	}else if(copy_enu_row == LCD_ROW_2){
		LCD_cmd(ptr_str_config, LCD_DDRAM_START_ADD_LINE_2 + copy_enu_col);	

	}else{
		
		enu_return_state=LCD_E_NOT_OK;
	}

	return enu_return_state;

}

/**
 * @brief Write a string to the LCD.
 *
 * This function writes a null-terminated string to the LCD.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @param[in] ptr_u8_data Pointer to the string data to be written.
 * @return Operation status: LCD_E_OK if successful, LCD_NULL_PTR if NULL pointer provided.
 */
lcd_enu_return_state_t LCD_writeString (lcd_str_config_t *ptr_str_config, uint8_t *ptr_u8_data)
{
	uint8_t u8_char_counter = 0;
	lcd_enu_return_state_t enu_return_state=LCD_E_OK;
	if(ptr_u8_data == NULL)
	{
		enu_return_state = LCD_NULL_PTR;
	}

	else
	{
		while(ptr_u8_data[u8_char_counter] !='\0')
		{
			LCD_char(ptr_str_config,ptr_u8_data[u8_char_counter]);
			u8_char_counter++;
			
		}
	}
	return enu_return_state;
	

}

/**
 * @brief Write a special character to the LCD.
 *
 * This function writes a special character to the LCD screen.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @param[in] u8_SpChar The type of special character to be written.
 * @return Operation status: LCD_E_OK if successful.
 */
lcd_enu_return_state_t LCD_writeSpChar (lcd_str_config_t *ptr_str_config, u8_en_lcdSpCharType u8_SpChar)
{   lcd_enu_return_state_t enu_return_state=LCD_E_OK;
	uint8_t sp_char[]= {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};
	uint8_t i;
	LCD_cmd(ptr_str_config,LCD_CGRAM_START_ADD+( u8_SpChar* LCD_1_BYTE));
	for(i=U8_ZERO_VALUE;i<LCD_1_BYTE;i++)
	{
		LCD_char(ptr_str_config,sp_char[i]);
	}	
	
	LCD_cmd(ptr_str_config,LCD_DDRAM_START_ADD_LINE_2);
	LCD_char(ptr_str_config,LCD_BELL);
	return enu_return_state;
}

/**
 * @brief Send a command to the LCD.
 *
 * This function sends a command to the LCD screen.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @param[in] cmd The command to be sent.
 * @return Operation status: LCD_E_OK if successful, LCD_E_NOT_OK if sending the command failed.
 */
lcd_enu_return_state_t LCD_cmd(lcd_str_config_t *ptr_str_config,uint8_t cmd)
{   lcd_enu_return_state_t enu_return_state=LCD_E_OK;
	lcd_enu_return_state_t u8_bit_counter = LCD_MSB_INDEX;
	DIO_write_pin(ptr_str_config->str_Epin.enu_port,ptr_str_config->str_Epin.enu_pin,DIO_PIN_LOW_LEVEL);
	DIO_write_pin(ptr_str_config->str_RSpin.enu_port,ptr_str_config->str_RSpin.enu_pin,DIO_PIN_LOW_LEVEL);
	DIO_write_pin(ptr_str_config->str_RWpin.enu_port,ptr_str_config->str_RWpin.enu_pin,DIO_PIN_LOW_LEVEL);
	if(ptr_str_config->enu_mode == LCD_4_BIT_MODE)
	{
		for(sint8_t u8_counter = LCD_MAX_DATA_PINS_MOD_4 - U8_ONE_VALUE; u8_counter >= U8_ZERO_VALUE; u8_counter--){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
			}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();
	   for(sint8_t u8_counter = LCD_MAX_DATA_PINS_MOD_4-U8_ONE_VALUE; u8_counter >= U8_ZERO_VALUE; u8_counter--){
		   if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
			   DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
			}else{
			   DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
		   }
		   u8_bit_counter--;
	   }
		ENABLE(ptr_str_config);
		delay_3_ms();
	}
	else if(ptr_str_config->enu_mode == LCD_8_BIT_MODE)
	{
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < LCD_MAX_DATA_PINS_MOD_8; u8_counter++){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
				}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();	
	}
	else
	{
		//do nothing
		enu_return_state=LCD_E_NOT_OK;
	}
	delay_3_ms();
	return enu_return_state;
}

/**
 * @brief Write a character to the LCD.
 *
 * This function writes a character to the LCD screen.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @param[in] cmd The character to be written.
 */
void LCD_char(lcd_str_config_t *ptr_str_config, uint8_t cmd)
{
	lcd_enu_return_state_t u8_bit_counter = LCD_MSB_INDEX;
	DIO_write_pin(ptr_str_config->str_Epin.enu_port,ptr_str_config->str_Epin.enu_pin,DIO_PIN_LOW_LEVEL);
	DIO_write_pin(ptr_str_config->str_RSpin.enu_port,ptr_str_config->str_RSpin.enu_pin,DIO_PIN_HIGH_LEVEL);
	DIO_write_pin(ptr_str_config->str_RWpin.enu_port,ptr_str_config->str_RWpin.enu_pin,DIO_PIN_LOW_LEVEL);
	
	
	if(ptr_str_config->enu_mode == LCD_4_BIT_MODE)
	{
		
		for(sint8_t u8_counter = LCD_MAX_DATA_PINS_MOD_4-U8_ONE_VALUE; u8_counter >= U8_ZERO_VALUE; u8_counter--){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
				}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();
		for(sint8_t u8_counter = LCD_MAX_DATA_PINS_MOD_4-U8_ONE_VALUE; u8_counter >= U8_ZERO_VALUE; u8_counter--){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
				}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();
	}
	else if(ptr_str_config->enu_mode == LCD_8_BIT_MODE)
	{
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < LCD_MAX_DATA_PINS_MOD_8; u8_counter++){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
				}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();
	}
	else
	{
		//do nothing
	}
}

static void ENABLE(lcd_str_config_t* ptr_str_config)
{
	
	DIO_write_pin(ptr_str_config->str_Epin.enu_port, ptr_str_config->str_Epin.enu_pin, DIO_PIN_HIGH_LEVEL);
	delay_3_ms();
	DIO_write_pin(ptr_str_config->str_Epin.enu_port, ptr_str_config->str_Epin.enu_pin, DIO_PIN_LOW_LEVEL);


}

void delay_3_ms(void){
	static uint32_t u32_desired_ticks = 5000;
	for(volatile uint32_t u32_counter = 0; u32_counter < u32_desired_ticks; u32_counter++);
	
}
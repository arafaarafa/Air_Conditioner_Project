/**
 * @file App_prog.c
 * @brief Application Program File
 *
 * This file contains the implementation of the main application functions.
 *
 * @date 23/8/2023
 * @author Arafa Arafa
 */

#include "APP_interface.h"


void APP_timer1OvfHandeler(void);

uint8_t gs_ptr_str_curTempToString[APP_TEMP_STRING_SIZE];
/** Timer configuration for Timer 1 */
static timerm_str_config_t gs_str_timer_1_config;



/** LM35 temperature sensor configuration */
static lm35_str_config_t	gs_lm35_str_config;
static lm35_str_channel_t	gs_str_lm35_str_channel_config;

/** LCD configuration */
lcd_str_config_t gs_str_lcd_config;

/** Keypad configuration */
keypad_str_config_t gs_str_keypad_config;

/** Buzzer configuration */
static buzzer_str_config_t gs_str_buzzer_config;

/** Program state variable */
static u8_programStateType u8_en_gs_programState = APP_WELCOME;

/** Delay variable */
static uint8_t gs_u8_delay = 0;

/** Default temperature setting */
const  uint8_t u8_gc_defaultTemp = 20;

/** Current temperature variable */
static double gs_d_curTemp = 20.0;

/** Program temperature variable */
static uint8_t u8_gs_programTemp = 0;

/**
 * @brief Convert an integer to a string.
 *
 * @param copy_u8_num The integer to convert.
 * @param ptr_string Pointer to the string to store the result.
 */
static void intToString(uint8_t copy_u8_num, uint8_t *ptr_string);

/**
 * @brief Delay for a specified number of half-seconds.
 *
 * @param u8_delay_half_sec Number of half-seconds to delay.
 */
static void delay_half_sec(uint8_t u8_delay_half_sec);


void APP_start(void)
{
	
	APP_init();
												
	TIMER_MANGER_start(gs_str_timer_1_config.enu_prescaller,gs_str_timer_1_config.enu_timer_no);
	
	while(1)
	{
		while(u8_en_gs_programState == APP_WELCOME)
		{
			APP_welcome();
		}
		while(u8_en_gs_programState == APP_SET_TEMP)
		{
			APP_set();
		}
		while(u8_en_gs_programState == APP_WORKING)
		{
			APP_working();
		}
	}
}

void APP_init(void)
{
	// Initialize timer 1 in Normal mode with OVF interrupt enabled and interrupt period every 0.5 ms
	gs_str_timer_1_config.enu_timer_no = TIMER_1;
	gs_str_timer_1_config.enu_timer_mode = TIMER_NORMAL_MODE;
	gs_str_timer_1_config.u16_timer_initial_value = APP_TIMER_1_INIT_VALUE;
	gs_str_timer_1_config.ptr_call_back_func =  APP_timer1OvfHandeler;
	gs_str_timer_1_config.enu_prescaller = F_CPU_1024;	
	
	TIMER_MANGER_init(&gs_str_timer_1_config);
	
	
	// Initialize The Temp. sensor 
	gs_str_lm35_str_channel_config.str_lm35_channel.enu_channel_pin = PIN7;
	gs_str_lm35_str_channel_config.str_lm35_channel.enu_channel_port = PORTA;
	gs_lm35_str_config.str_lm35_adc_config.adc_enu_vref = ADC_EXTERNAL_VREF;
	gs_lm35_str_config.str_lm35_adc_config.adc_enu_prescaler = ADC_PRESCALER_2;
	LM35_init(&gs_str_lm35_str_channel_config, &gs_lm35_str_config);
	
	
	
	
	// Initialize the LCD
	gs_str_lcd_config.enu_mode = LCD_4_BIT_MODE;
	
	gs_str_lcd_config.str_data_pins[0].enu_port = PORTC;
	gs_str_lcd_config.str_data_pins[0].enu_pin	 = PIN0;
	
	gs_str_lcd_config.str_data_pins[1].enu_port	 = PORTC;
	gs_str_lcd_config.str_data_pins[1].enu_pin	 = PIN1;
	
	gs_str_lcd_config.str_data_pins[2].enu_port	 = PORTC;
	gs_str_lcd_config.str_data_pins[2].enu_pin	 = PIN2;
	
	gs_str_lcd_config.str_data_pins[3].enu_port	 = PORTC;
	gs_str_lcd_config.str_data_pins[3].enu_pin	 = PIN3;
	
	gs_str_lcd_config.str_RSpin.enu_port = PORTC;
	gs_str_lcd_config.str_RSpin.enu_pin = PIN4;
	
	gs_str_lcd_config.str_RWpin.enu_port = PORTC;
	gs_str_lcd_config.str_RWpin.enu_pin	= PIN5;
	
	gs_str_lcd_config.str_Epin.enu_port = PORTC	;
	gs_str_lcd_config.str_Epin.enu_pin	= PIN6;
	
	LCD_init(&gs_str_lcd_config);
	
	
	
	
	
	// Initialize the keypad
	gs_str_keypad_config.str_col_pins[0].enu_port = PORTA;
	gs_str_keypad_config.str_col_pins[0].enu_pin  = PIN4;
	
	gs_str_keypad_config.str_col_pins[1].enu_port = PORTA;
	gs_str_keypad_config.str_col_pins[1].enu_pin  = PIN5;
	
	gs_str_keypad_config.str_col_pins[2].enu_port = PORTA;
	gs_str_keypad_config.str_col_pins[2].enu_pin  = PIN6;
	
	
	gs_str_keypad_config.str_row_pins[0].enu_port = PORTA;
	gs_str_keypad_config.str_row_pins[0].enu_pin  = PIN0;
	
	gs_str_keypad_config.str_row_pins[1].enu_port = PORTA;
	gs_str_keypad_config.str_row_pins[1].enu_pin  = PIN1 ;
	
	gs_str_keypad_config.str_row_pins[2].enu_port = PORTA;
	gs_str_keypad_config.str_row_pins[2].enu_pin  = PIN2 ;
	
	gs_str_keypad_config.str_row_pins[3].enu_port = PORTA;
	gs_str_keypad_config.str_row_pins[3].enu_pin  = PIN3 ;
	
	KEYPAD_init(&gs_str_keypad_config);
	
	
	// Initialize Buzzer
	gs_str_buzzer_config.enu_port = PORTB;
	gs_str_buzzer_config.enu_pin = PIN0;
	BUZZER_init(&gs_str_buzzer_config);
}

void APP_welcome(void)
{
	LCD_clear(&gs_str_lcd_config);
	LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_1);
	
	LCD_writeString(&gs_str_lcd_config,(uint8_t*)"Welcome");
	delay_half_sec(APP_DELAY_1_S);
	
	LCD_clear(&gs_str_lcd_config);
	LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_1);
	
	LCD_writeString(&gs_str_lcd_config, (uint8_t*)"default Temp is");
	
	LCD_setCursor(&gs_str_lcd_config,LCD_ROW_2,LCD_COL_1);

	LCD_writeString(&gs_str_lcd_config, (uint8_t*)"20");
	delay_half_sec(APP_DELAY_1_S);

	
	u8_gs_programTemp = u8_gc_defaultTemp;
	u8_en_gs_programState = APP_SET_TEMP;
}

void APP_set(void)
{
	uint8_t u8_loadingChar[] = "|";
	uint8_t u8_emptyChar[] = " ";
	uint8_t u8_keypadData = 0;
	

	LCD_clear(&gs_str_lcd_config);
	
	LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_1);


	LCD_writeString(&gs_str_lcd_config, (uint8_t*)"Set Initial Temp");
	delay_half_sec(APP_DELAY_0_5_S);

	LCD_clear(&gs_str_lcd_config);
	LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_1);

	LCD_writeString(&gs_str_lcd_config, (uint8_t*)"Min=18");
	LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_11);
	LCD_writeString(&gs_str_lcd_config, (uint8_t*)"Max=35");
	
	for (uint8_t u8_index = 19 ; u8_index <= u8_gs_programTemp ;u8_index++)
	{
		
		LCD_setCursor(&gs_str_lcd_config,LCD_ROW_2,u8_index-19);
		LCD_writeString(&gs_str_lcd_config, (uint8_t*)u8_loadingChar);
	}
	while(1)
	{
		intToString(u8_gs_programTemp, gs_ptr_str_curTempToString);
		LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_8);
		LCD_writeString(&gs_str_lcd_config, gs_ptr_str_curTempToString);
		
		KEYPAD_read(&gs_str_keypad_config, &u8_keypadData);
		
		if (u8_keypadData == APP_INCREMENT_BTN)
		{

			if (u8_gs_programTemp < 35)
			{
				u8_gs_programTemp++;
				
				LCD_setCursor(&gs_str_lcd_config,LCD_ROW_2, u8_gs_programTemp-19);
				LCD_writeString(&gs_str_lcd_config, (uint8_t*)u8_loadingChar);
			}
		}
		else if (u8_keypadData == APP_DECREMENT_BTN)
		{
			// Decrement
			if (u8_gs_programTemp >18)
			{
				u8_gs_programTemp--;
				LCD_setCursor(&gs_str_lcd_config,LCD_ROW_2, u8_gs_programTemp-18);
				LCD_writeString(&gs_str_lcd_config, (uint8_t*)u8_emptyChar);
			}
		}
		else if (u8_keypadData == APP_SET_BTN)
		{
			// Set
			u8_en_gs_programState = APP_WORKING;
			break;
		}
		else{
			// do nothing
		}
	}
	
}

void APP_working(void)
{
	uint8_t u8_keypadData = 0;
	
	// print current temp
	LCD_clear(&gs_str_lcd_config);
	LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_1);
	LCD_writeString(&gs_str_lcd_config, (uint8_t*)"Current Temp = ");
	
	
	while(u8_en_gs_programState == APP_WORKING)
	{
		// read the temp from the sensor
		LM35_read_temp(&gs_str_lm35_str_channel_config, &gs_lm35_str_config, &gs_d_curTemp);		
		LCD_setCursor(&gs_str_lcd_config,LCD_ROW_2,LCD_COL_2);
		intToString((uint8_t)gs_d_curTemp,gs_ptr_str_curTempToString);
		LCD_writeString(&gs_str_lcd_config, gs_ptr_str_curTempToString);
		//APP_printString(gs_d_curTemp);
		//LCD_writeString((uint8_t*)ch_arrs_curTempToString);
		if (gs_d_curTemp > u8_gs_programTemp)
		{
			
			LCD_writeSpChar(&gs_str_lcd_config, LCD_BELL);
			
			
			// start the BUZZER
			BUZZER_start();
		}
		else{
			LCD_setCursor(&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
			LCD_writeString(&gs_str_lcd_config, (uint8_t*)" ");
			BUZZER_stop();
		}
		
		KEYPAD_read(&gs_str_keypad_config, &u8_keypadData);
		switch(u8_keypadData)
		{
			case  APP_NO_BTN :
				break;
			case  APP_RESET_BTN :
				// reset
				// Stop the BUZZER
				BUZZER_stop();
				
				// Set the program temp with the default temp
				u8_gs_programTemp = u8_gc_defaultTemp;
				
				// clear LCD and print Temp value is resettled to 20
				LCD_clear(&gs_str_lcd_config);
				LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_1);
				
				LCD_writeString(&gs_str_lcd_config, (uint8_t*)"Temp value is");
				LCD_setCursor(&gs_str_lcd_config,LCD_ROW_2,LCD_COL_1);
				
				LCD_writeString(&gs_str_lcd_config, (uint8_t*)"resettled to 20");
				delay_half_sec(APP_DELAY_1_S);
				
				// change the program state
				u8_en_gs_programState = APP_SET_TEMP;
				break;
			
			case APP_ADJUST_BTN : 
				// adjust
				
				// Stop the BUZZER
				BUZZER_stop();
				
				// change the program state
				u8_en_gs_programState = APP_SET_TEMP;
				break;
			default:
				
				// Invalid button
				LCD_clear(&gs_str_lcd_config);
				LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_1);
				LCD_writeString(&gs_str_lcd_config, (uint8_t*)"the operation is");
				LCD_setCursor(&gs_str_lcd_config,LCD_ROW_2,LCD_COL_1);
				
				LCD_writeString(&gs_str_lcd_config, (uint8_t*)"not allowed");
				delay_half_sec(APP_DELAY_1_S);
				
				// print current temp
				LCD_clear(&gs_str_lcd_config);
				LCD_setCursor(&gs_str_lcd_config,LCD_ROW_1,LCD_COL_1);
				LCD_writeString(&gs_str_lcd_config, (uint8_t*)"Current Temp = ");
				break;
		}
	}
	
}

void APP_timer1OvfHandeler(void)
{
	gs_u8_delay++;

	TIMER_MANGER_setValue(gs_str_timer_1_config.enu_timer_no,gs_str_timer_1_config.u16_timer_initial_value);
}


void intToString(uint8_t copy_u8_num, uint8_t *ptr_string) {
	uint8_t u8_digit_counter = U8_ZERO_VALUE;

	if (copy_u8_num == U8_ZERO_VALUE) {
		u8_digit_counter = U8_ONE_VALUE;
		} else {
		uint8_t temp = copy_u8_num;  // Store a temporary copy of the number
		while (temp != U8_ZERO_VALUE) {
			temp /= APP_SELECT_TENS_DIGIT;
			u8_digit_counter++;
		}
	}
	u8_digit_counter++;


	uint8_t u8_string_counter = u8_digit_counter - U8_ONE_VALUE;  // Start from the end of the buffer
	ptr_string[u8_string_counter] = APP_NULL_TERMINATION_STRING;  // Null-terminate the string

	if (copy_u8_num == U8_ZERO_VALUE) {
		ptr_string[--u8_string_counter] = APP_0_CHAR;  // Handle the special case of zero
		} else {
		while (copy_u8_num > U8_ZERO_VALUE && u8_string_counter > U8_ZERO_VALUE) {
			ptr_string[--u8_string_counter] = '0' + (copy_u8_num % APP_SELECT_TENS_DIGIT); // Convert the digit to character
			copy_u8_num /= APP_SELECT_TENS_DIGIT;
		}
	}
}

void delay_half_sec(uint8_t u8_delay_half_sec){
	
	gs_u8_delay = 0;
	TIMER_MANGER_start(gs_str_timer_1_config.enu_prescaller,gs_str_timer_1_config.enu_timer_no);
	while(gs_u8_delay <= u8_delay_half_sec);
	TIMER_MANGER_stop(gs_str_timer_1_config.enu_timer_no);
	
	
}
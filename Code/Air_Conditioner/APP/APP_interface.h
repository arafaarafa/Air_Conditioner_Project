/**
 * @file APP_interface.h
 *
 * @brief This is the interface file for the application module.
 *
 * This file contains function prototypes and constants used in the application module.
 *
 * @date 23/8/2023
 * @author Arafa Arafa
 */

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

//#include <stdlib.h>

#include "../HAL/BUZZER/BUZZER_interface.h"
#include "../HAL/KEYPAD/KEYPAD_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/LM35/LM35_interface.h"
#include "../HAL/TIMER_manager/TIMER_manger_interface.h"

#define APP_DELAY_1_S				2 /**< Delay in seconds */
#define APP_DELAY_0_5_S				1  /**< Delay in half seconds */



/* To get first digit of number by division */
#define APP_SELECT_TENS_DIGIT				10

/* Value of zero in char */
#define APP_0_CHAR							'0'

/* NULL termination during the loop on string */
#define APP_NULL_TERMINATION_STRING			'\0'
#define APP_TEMP_STRING_SIZE		5 /**< Size of the temperature string buffer */
#define APP_TIMER_1_INIT_VALUE		61448
#define APP_RESET_BTN				'5' /**< Reset button value */
#define APP_ADJUST_BTN				'4' /**< Adjust button value */
#define APP_INCREMENT_BTN			'1' /**< Increment button value */
#define APP_DECREMENT_BTN			'2' /**< Decrement button value */
#define APP_SET_BTN					'3' /**< Set button value */
#define APP_NO_BTN					78  /**< No button value */


#define APP_PORT					0
#define APP_PIN						1

typedef uint8_t u8_programStateType;

#define APP_WELCOME				((u8_programStateType)0x00) /**< Welcome state */
#define APP_SET_TEMP			((u8_programStateType)0x01) /**< Set temperature state */
#define APP_WORKING				((u8_programStateType)0x02) /**< Working state */

/**
 * @brief Start the application.
 *
 * This function initializes the necessary components and enters the main application loop.
 */
void APP_start(void);

/**
 * @brief Initialize the application.
 *
 * This function initializes various components and configurations required by the application.
 */
void APP_init(void);


/**
 * @brief Display a welcome message and set the default temperature.
 */
void APP_welcome(void);

/**
 * @brief Set the initial desired temperature.
 */
void APP_set(void);

/**
 * @brief Monitor the current temperature and control the buzzer.
 */
void APP_working(void);

/**
 * @brief Timer overflow interrupt handler.
 *
 * This function is called when Timer 1 overflows, providing a delay mechanism.
 */
void APP_timer0OvfHandeler(void);

/**
 * @brief Print the current temperature on the LCD.
 *
 * @param copy_d_temp The current temperature to display.
 */
void APP_printString(double copy_d_temp);

#endif /* APP_H	*/
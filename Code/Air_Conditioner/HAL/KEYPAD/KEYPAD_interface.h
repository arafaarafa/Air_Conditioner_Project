/**
 * @file keypad_interface.h
 * @brief Keypad module interface.
 *
 * This file defines the interface for the keypad module, including data structures and function declarations.
 *
 * @date 22/8/2023
 * @author Arafa Arafa
 */


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_


#include "../../MCAL/DIO/DIO_interface.h"

/** Maximum number of rows in the keypad matrix. */
#define KEYPAD_ROWS_MAX             4

/** Maximum number of columns in the keypad matrix. */
#define KEYPAD_COLS_MAX             3

/** Structure to represent a single unit of the keypad (a pin). */
typedef struct
{
	dio_enu_port_t enu_port; /**< Port of the keypad pin. */
	dio_enu_pin_t enu_pin;   /**< Pin of the keypad pin. */
}keypad_str_unit_t;

/** Configuration structure for the keypad module. */
typedef struct
{
    keypad_str_unit_t str_row_pins[KEYPAD_ROWS_MAX]; /**< Array of row pins configuration. */
	keypad_str_unit_t str_col_pins[KEYPAD_COLS_MAX]; /**< Array of column pins configuration. */
}keypad_str_config_t;


/** Enumeration of possible return states for keypad module functions. */
typedef enum{
		KEYPAD_E_OK,       /**< Operation completed successfully. */
		KEYPAD_E_NOT_OK,   /**< Operation not successful. */
		KEYPAD_NULL_PTR,   /**< Null pointer provided as argument. */
		KEYPAD_NO_DATA     /**< No key data found. */
}keypad_enu_return_state_t;

/**
 * @brief Initialize the keypad.
 *
 * This function initializes the keypad by configuring row pins as inputs and column pins as outputs.
 *
 * @param[in] ptr_str_keypad_config Pointer to the keypad configuration structure.
 * @return Operation status: KEYPAD_E_OK if successful, KEYPAD_E_NOT_OK if initialization failed.
 */
keypad_enu_return_state_t KEYPAD_init(keypad_str_config_t *ptr_str_keypad_config);

/**
 * @brief Read key input from the keypad.
 *
 * This function reads the key input from the keypad by scanning rows and columns.
 *
 * @param[in] ptr_str_keypad_config Pointer to the keypad configuration structure.
 * @param[out] ptr_u8_data Pointer to store the read key data.
 * @return Operation status: KEYPAD_E_OK if successful, KEYPAD_NULL_PTR if NULL pointer provided, KEYPAD_NO_DATA if no key data found.
 */
keypad_enu_return_state_t KEYPAD_read(keypad_str_config_t *ptr_str_keypad_config, uint8_t *ptr_u8_data);



#endif /* KEYPAD_INTERFACE_H	*/
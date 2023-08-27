/*
 * LCD_interface.h
 *
 * Created: 22/8/2023 
 *  Author: Arafa Arafa
 *
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "LCD_cmd.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../STD_LIB/bit_math.h"

// Number of bits in a byte
#define LCD_1_BYTE							8

// Index of the Most Significant Bit (MSB) in a byte
#define LCD_MSB_INDEX		                7

// Maximum number of data pins for LCD (8 data pins)
#define LCD_MAX_DATA_PINS                   8

// Maximum number of data pins modulo 4
#define LCD_MAX_DATA_PINS_MOD_4				4

// Maximum number of data pins modulo 8
#define LCD_MAX_DATA_PINS_MOD_8				8

// Enumeration for LCD operating modes
typedef enum {
    LCD_4_BIT_MODE,
    LCD_8_BIT_MODE,
    LCD_INVALID_MODE
} lcd_enu_mode_t;

// Enumeration for selecting LCD rows
typedef enum {
	LCD_ROW_1 = 0,
	LCD_ROW_2,
} lcd_enu_row_select_t;

// Enumeration for selecting LCD columns
typedef enum {
	LCD_COL_1 = 0, LCD_COL_2, LCD_COL_3, LCD_COL_4,
	LCD_COL_5, LCD_COL_6, LCD_COL_7, LCD_COL_8,
	LCD_COL_9, LCD_COL_10, LCD_COL_11, LCD_COL_12,
	LCD_COL_13, LCD_COL_14, LCD_COL_15, LCD_COL_16,
} lcd_enu_col_select_t;

// Structure to represent a unit (port and pin)
typedef struct {
	dio_enu_port_t enu_port; // Port of the unit
	dio_enu_pin_t enu_pin;   // Pin of the unit
} lcd_str_unit_t;

// Configuration structure for LCD
typedef struct {
	lcd_enu_mode_t enu_mode;           // LCD mode (4-bit or 8-bit)
	lcd_str_unit_t str_data_pins[LCD_MAX_DATA_PINS]; // Data pins
	lcd_str_unit_t str_RSpin;           // RS pin
	lcd_str_unit_t str_RWpin;           // RW pin
	lcd_str_unit_t str_Epin;            // E pin
} lcd_str_config_t;

// Enumeration for LCD return states
typedef enum {
    LCD_E_OK,
    LCD_E_NOT_OK,
	LCD_NULL_PTR
} lcd_enu_return_state_t;

// Type definition for special character types in LCD
typedef uint8_t u8_en_lcdSpCharType;

// Predefined special character value for a bell symbol
#define LCD_BELL					((u8_en_lcdSpCharType)0X03)



/**
 * @brief Initialize the LCD.
 *
 * This function initializes the LCD based on the provided configuration.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @return Operation status: LCD_E_OK if successful, LCD_E_NOT_OK if initialization failed.
 */
lcd_enu_return_state_t LCD_init (lcd_str_config_t *ptr_str_config);

/**
 * @brief Send a command to the LCD.
 *
 * This function sends a command to the LCD screen.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @param[in] cmd The command to be sent.
 * @return Operation status: LCD_E_OK if successful, LCD_E_NOT_OK if sending the command failed.
 */
lcd_enu_return_state_t LCD_cmd(lcd_str_config_t *ptr_str_config, uint8_t copy_u8_cmd);

/**
 * @brief Write a character to the LCD.
 *
 * This function writes a character to the LCD screen.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @param[in] cmd The character to be written.
 */
void LCD_char(lcd_str_config_t *ptr_str_config, uint8_t copy_u8_data);


/**
 * @brief Clear the LCD screen.
 *
 * This function clears the LCD screen by sending the appropriate command.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @return Operation status: LCD_E_OK if successful, LCD_E_NOT_OK if clearing failed.
 */
lcd_enu_return_state_t LCD_clear (lcd_str_config_t* ptr_str_config);

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
lcd_enu_return_state_t LCD_setCursor (lcd_str_config_t *ptr_str_config, lcd_enu_row_select_t copy_enu_row, lcd_enu_col_select_t copy_enu_col);

/**
 * @brief Write a string to the LCD.
 *
 * This function writes a null-terminated string to the LCD.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @param[in] ptr_u8_data Pointer to the string data to be written.
 * @return Operation status: LCD_E_OK if successful, LCD_NULL_PTR if NULL pointer provided.
 */
lcd_enu_return_state_t LCD_writeString (lcd_str_config_t *ptr_str_config, uint8_t *ptr_u8_data);

/**
 * @brief Write a special character to the LCD.
 *
 * This function writes a special character to the LCD screen.
 *
 * @param[in] ptr_str_config Pointer to the LCD configuration structure.
 * @param[in] u8_SpChar The type of special character to be written.
 * @return Operation status: LCD_E_OK if successful.
 */
lcd_enu_return_state_t LCD_writeSpChar (lcd_str_config_t *ptr_str_config, u8_en_lcdSpCharType copy_u8_SpChar);


#endif /* LCD_INTERFACE_H	*/
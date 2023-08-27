/**
 * @file LCD.h
 * @brief LCD module command definitions.
 *
 * This file contains definitions of commands and addresses for controlling an LCD display.
 *
 * @date 4/16/2023
 * @author Arafa Arafa
 */




#ifndef LCD_CMD_H_
#define LCD_CMD_H_

/**
 * @brief Start address for defining custom CGRAM characters.
 */
#define LCD_CGRAM_START_ADD				0x40

/**
 * @brief Start address of DDRAM for the first line.
 */
#define LCD_DDRAM_START_ADD_LINE_1		0x80

/**
 * @brief Start address of DDRAM for the second line.
 */
#define LCD_DDRAM_START_ADD_LINE_2		0xC0

/**
 * @brief Command to clear the display.
 */
#define LCD_CMD_CLEAR					0x01

/**
 * @brief Command to return the cursor to the home position.
 */
#define LCD_CMD_CURSOR_HOME				0x02 

/**
 * @brief Entry mode command: Increment cursor and shift display to the right.
 */
#define LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_ON 0x07 

/**
 * @brief Entry mode command: Increment cursor and shift display off.
 */
#define LCD_CMD_ENTRY_MODE_INCREMENT_OFF_SHIFT_OFF 0x04

/**
 * @brief Entry mode command: Increment cursor with display shift.
 */
#define LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_OFF	0x06

/**
 * @brief Entry mode command: Increment cursor off and shift display.
 */
#define LCD_CMD_ENTRY_MODE_INCREMENT_OFF_SHIFT_ON	0x05

/**
 * @brief Command to shift the cursor to the left.
 */
#define LCD_MOVE_CURSOR_SHIFT_LEFT		0x10

/**
 * @brief Command to shift the cursor to the right.
 */
#define LCD_MOVE_CURSOR_SHIFT_RIGHT		0x14

/**
 * @brief Command to shift the entire display to the left.
 */
#define LCD_DISPLAY_SHIFT_LEFT			0x18

/**
 * @brief Command to shift the entire display to the right.
 */
#define LCD_DISPLAY_SHIFT_RIGHT			0x1C

/**
 * @brief Command to turn on display, cursor, and blinking block.
 */
#define LCD_DISPLAY_ON_CUR_ON_BLOCK_ON	0x0F

/**
 * @brief Command to turn off display, cursor, and blinking block.
 */
#define LCD_DISPLAY_OFF_CUR_OFF_BLOCK_OFF	0x08

/**
 * @brief Command to turn on display, cursor off, and blinking block off.
 */
#define LCD_DISPLAY_ON_CUR_OFF_BLOCK_OFF	0x0C

/**
 * @brief Command to turn on display, cursor on, and blinking block off.
 */
#define LCD_DISPLAY_ON_CUR_ON_BLOCK_OFF		0x0E

/**
 * @brief Command to turn on display, cursor off, and blinking block on.
 */
#define LCD_DISPLAY_ON_CUR_OFF_BLOCK_ON		0x0D

/**
 * @brief Command for 4-bit mode, 2-line display, and 5x8 dot matrix.
 */
#define LCD_4BITS_2LINES_58DM				0x28

/**
 * @brief Command for 8-bit mode, 2-line display, and 5x11 dot matrix.
 */
#define	LCD_8BITS_2LINES_511DM				0x32

/**
 * @brief Command for 8-bit mode, 2-line display, and 5x8 dot matrix.
 */
#define LCD_8BITS_2LINES_58DM				0x38

#endif /* LCD_CMD_H_ */
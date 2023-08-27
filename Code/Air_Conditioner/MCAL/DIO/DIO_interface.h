/**
 * @file DIO_interface.h
 * @brief Digital Input/Output (DIO) Interface Header File
 *
 * This header file defines enums, data types, and function prototypes for the Digital Input/Output (DIO) module.
 * It provides functionalities to initialize pins, write to pins, and read from pins on different ports.
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#include "../../STD_LIB/bit_math.h"
#include "../../STD_LIB/std_types.h"


/** @defgroup DIOEnums DIO Enums */
/** @{ */

/**
 * @brief Enumeration of available ports for the DIO module.
 */
typedef enum {
    PORTA = 0, /**< Port A */
    PORTB,     /**< Port B */
    PORTC,     /**< Port C */
    PORTD      /**< Port D */
} dio_enu_port_t;


/**
 * @brief Enumeration of available pins for the DIO module.
 */
typedef enum {
    PIN0 = 0, /**< Pin 0 */
    PIN1,     /**< Pin 1 */
    PIN2,     /**< Pin 2 */
    PIN3,     /**< Pin 3 */
    PIN4,     /**< Pin 4 */
    PIN5,     /**< Pin 5 */
    PIN6,     /**< Pin 6 */
    PIN7      /**< Pin 7 */
} dio_enu_pin_t;


/**
 * @brief Enumeration of DIO pin levels.
 */
typedef enum {
    DIO_PIN_LOW_LEVEL,  /**< Low level */
    DIO_PIN_HIGH_LEVEL  /**< High level */
} dio_enu_level_t;





/**
 * @brief Enumeration of DIO return states.
 */
typedef enum {
    DIO_OK,             /**< Operation successful */
    DIO_INVALID_PIN,    /**< Invalid pin provided */
    DIO_INVALID_PORT    /**< Invalid port provided */
} dio_enu_return_state_t;



/**
 * @brief Enumeration of DIO pin directions.
 */
typedef enum {
    DIO_PIN_INPUT = 0,  /**< Input direction */
    DIO_PIN_OUTPUT      /**< Output direction */
} dio_u8_enu_direction_t;

/** @} */




/** @defgroup DIOFunctionProtos DIO Function Prototypes */
/** @{ */


/**
 * @brief Initialize a pin for the DIO module.
 *
 * This function initializes a pin with the specified port and pin number to the provided direction.
 *
 * @param copy_enu_port The port to which the pin belongs.
 * @param copy_enu_pin The pin number to initialize.
 * @param copy_enu_direction The direction (input or output) to set for the pin.
 * @return The return state of the pin initialization.
 */
dio_enu_return_state_t DIO_init (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_u8_enu_direction_t copy_enu_direction);

/**
 * @brief Write a level to a pin for the DIO module.
 *
 * This function writes the specified level to the pin on the provided port and pin number.
 *
 * @param copy_enu_port The port to which the pin belongs.
 * @param copy_enu_pin The pin number to write.
 * @param copy_enu_state The level (high or low) to write to the pin.
 * @return The return state of writing to the pin.
 */
dio_enu_return_state_t DIO_write_pin (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_enu_level_t copy_enu_state);

/**
 * @brief Read the level of a pin for the DIO module.
 *
 * This function reads the level of the specified pin on the provided port and pin number.
 *
 * @param copy_enu_port The port to which the pin belongs.
 * @param copy_enu_pin The pin number to read.
 * @param ptr_enu_state Pointer to the variable where the read level will be stored.
 * @return The return state of reading the pin.
 */
dio_enu_return_state_t DIO_read_pin (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_enu_level_t	*ptr_enu_state);

/** @} */

#endif /* DIO_INTERFACE_H_ */
/**
 * @file DIO_private.h
 * @brief DIO Private Header File
 *
 * This header file defines macros that access the hardware registers for DIO configuration and manipulation.
 * It provides direct register definitions for data direction, write, and read operations on different ports.
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

//#include <avr/io.h>

#define DIO_MAX_PINS   8 /**< Maximum number of pins in a port */
#define DIO_MAX_PORTS  4 /**< Maximum number of ports */

/* Data Direction Registers */
#define  DATA_DIRECTION_PORTA	    (*((volatile uint8_t *) 0x3A))
#define  DATA_DIRECTION_PORTB	    (*((volatile uint8_t *) 0x37))
#define  DATA_DIRECTION_PORTC	    (*((volatile uint8_t *) 0x34))
#define  DATA_DIRECTION_PORTD	    (*((volatile uint8_t *) 0x31))

/* Write Registers */
#define  WR_PORT_A					(*((volatile uint8_t *) 0x3B))
#define  WR_PORT_B					(*((volatile uint8_t *) 0x38))
#define  WR_PORT_C					(*((volatile uint8_t *) 0x35))
#define  WR_PORT_D					(*((volatile uint8_t *) 0x32))

/* Read Registers */
#define  RE_PORT_A					(*((volatile uint8_t *) 0x39))
#define  RE_PORT_B					(*((volatile uint8_t *) 0x36))
#define  RE_PORT_C					(*((volatile uint8_t *) 0x33))
#define  RE_PORT_D					(*((volatile uint8_t *) 0x30))

#endif  /* DIO_PRIVATE_H_ */
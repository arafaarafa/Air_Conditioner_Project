/**
 * @file DIO_prog.c
 * @brief DIO Implementation File
 *
 * This source file contains the implementation of the DIO (Digital Input/Output) module's interface functions.
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */

#include "DIO_interface.h"
#include "DIO_private_.h"

dio_enu_return_state_t DIO_init (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_u8_enu_direction_t copy_enu_direction)
{
	dio_enu_return_state_t enu_return_state = DIO_OK;

	if (copy_enu_pin < DIO_MAX_PINS)
	{
		if (copy_enu_port == PORTA)
		{
			DATA_DIRECTION_PORTA |= copy_enu_direction << copy_enu_pin;
			
		}
		else if (copy_enu_port == PORTB)
		{
			DATA_DIRECTION_PORTB |= copy_enu_direction << copy_enu_pin;
			
		}
		else if (copy_enu_port == PORTC)
		{
			DATA_DIRECTION_PORTC |= copy_enu_direction << copy_enu_pin;
			
		}
		else if (copy_enu_port == PORTD)
		{
			DATA_DIRECTION_PORTD |= copy_enu_direction << copy_enu_pin;
			
		}
		else
		{
			enu_return_state = DIO_INVALID_PORT;
		}
		
	}
	else{
		enu_return_state = DIO_INVALID_PIN;
	}

	return enu_return_state;
}

dio_enu_return_state_t DIO_write_pin (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_enu_level_t copy_enu_state)
{

	dio_enu_return_state_t enu_return_state = DIO_OK;

	if (copy_enu_pin < DIO_MAX_PINS)
	{
		if (copy_enu_port == PORTA)
		{
			if (copy_enu_state == DIO_PIN_HIGH_LEVEL)
			{
				WR_PORT_A |= (U8_ONE_VALUE << copy_enu_pin);
			}
			else{
				WR_PORT_A &= ~(U8_ONE_VALUE << copy_enu_pin);
			}
			return DIO_OK;
		}
		else if (copy_enu_port == PORTB)
		{
			if (copy_enu_state == DIO_PIN_HIGH_LEVEL)
			{
				WR_PORT_B |= (U8_ONE_VALUE << copy_enu_pin);
			}
			else{
				WR_PORT_B &= ~(U8_ONE_VALUE << copy_enu_pin);
			}
			return DIO_OK;
		}
		else if (copy_enu_port == PORTC)
		{
			if (copy_enu_state == DIO_PIN_HIGH_LEVEL)
			{
				WR_PORT_C |= (U8_ONE_VALUE << copy_enu_pin);
			}
			else{
				WR_PORT_C &= ~(U8_ONE_VALUE << copy_enu_pin);
			}
			return DIO_OK;
		}
		else if (copy_enu_port == PORTD)
		{
			if (copy_enu_state == DIO_PIN_HIGH_LEVEL)
			{
				WR_PORT_D |= (U8_ONE_VALUE << copy_enu_pin);
			}
			else{
				WR_PORT_D &= ~(U8_ONE_VALUE << copy_enu_pin);
			}
			return DIO_OK;
		}
		else
		{
			enu_return_state = DIO_INVALID_PORT;
		}
		
	}
	else{
		enu_return_state = DIO_INVALID_PIN;
	}



	return enu_return_state;
}

dio_enu_return_state_t DIO_read_pin (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_enu_level_t	*ptr_enu_state)
{

	dio_enu_return_state_t enu_return_state = DIO_OK;

	if (copy_enu_pin < DIO_MAX_PINS)
	{
		if (copy_enu_port == PORTA)
		{
			*ptr_enu_state = ((RE_PORT_A & (U8_ONE_VALUE<<copy_enu_pin))>>copy_enu_pin);
			
		}
		else if (copy_enu_port == PORTB)
		{
			*ptr_enu_state = ((RE_PORT_B & (U8_ONE_VALUE<<copy_enu_pin))>>copy_enu_pin);
			
		}
		else if (copy_enu_port == PORTC)
		{
			*ptr_enu_state = ((RE_PORT_C & (U8_ONE_VALUE<<copy_enu_pin))>>copy_enu_pin);
			
		}
		else if (copy_enu_port == PORTD)
		{
			*ptr_enu_state = ((RE_PORT_D & (U8_ONE_VALUE<<copy_enu_pin))>>copy_enu_pin);
			
		}
		else
		{
			enu_return_state = DIO_INVALID_PORT;
		}
		
	}
	else{
		enu_return_state = DIO_INVALID_PIN;
	}

	return enu_return_state;
}
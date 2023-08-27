/**
 * @file ADC_private.h
 * @brief ADC module private register definitions.
 *
 * This file contains the definitions of private registers and bit fields
 * used by the ADC module.
 *
 * @date 8/22/2023
 * @author Arafa Arafa
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ACSR_ADD	(*((volatile uint8_t *)0x28))
#define ANALOG_COMPARATOR_DISABLE	7
#define ANALOG_COMPARATOR_INTERRUPT_FLAG	4
#define ANALOG_COMPARATOR_INTERRUPT_ENABLE	3

#define ADMUX_ADD	(*((volatile uint8_t *)0x27))
#define ADC_VREF_SELECT	6
#define ADC_LEFT_ADJUST_RESULT	5


#define ADCSRA_ADD	(*((volatile uint8_t *)0x26))
#define ADC_ENABLE	7
#define ADC_START_CONVERSION	6
#define ADC_INT_FLAG	4
#define ADC_INT_ENABLE	3


#define ADCH_ADD	(*((volatile uint8_t *)0x25))
#define ADCL_ADD	(*((volatile uint8_t *)0x24))


#define ADC_ADCH	(*((volatile uint8_t *)0x25))
#define ADC_ADCL	(*((volatile uint8_t *)0x24))


#define ADC_ADMUX_MASK					((uint8_t)0xE0)
#define ADC_SHIFT_BY_8					((uint8_t)8)
#define ADC_SHIFT_BY_6					((uint8_t)6)
#define ADC_SHIFT_BY_2					((uint8_t)2)
#define ADC_START_VALUE_OF_REGISTER		((uint8_t)2)


#endif
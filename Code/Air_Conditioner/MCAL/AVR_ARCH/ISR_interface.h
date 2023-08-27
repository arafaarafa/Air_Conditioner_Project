/**
 * @file ISR_INTERFACE.h
 * @brief Interrupt Service Routine (ISR) Interface Header File
 *
 * This header file defines macros for handling interrupts, including enabling and disabling
 * interrupts and defining interrupt vector names. It also provides macros for declaring
 * interrupt service routines (ISRs).
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */


#ifndef ISR_INTERFACE_H_
#define ISR_INTERFACE_H_


/** @defgroup InterruptControlMacros Interrupt Control Macros */
/** @{ */

/**
 * @brief Enable global interrupts.
 */
#define sei() __asm__ __volatile__("sei" ::: "memory")

/**
 * @brief Disable global interrupts.
 */
#define cli() __asm__ __volatile__("cli" ::: "memory")
/** @} */



/** @defgroup InterruptVectors Interrupt Vectors */
/** @{ */

#define EXT_INT0 __vector_1
#define EXT_INT1 __vector_2
#define EXT_INT2 __vector_3
#define TIMER2_COMP __vector_4
#define TIMER2_OVF __vector_5
#define TIMER1_CAPT __vector_6
#define TIMER1_COMPA __vector_7
#define TIMER1_COMPB __vector_8
#define TIMER1_OVF __vector_9
#define TIMER0_COMP __vector_10
#define TIMER0_OVF __vector_11
#define SPI_STC __vector_12
#define USART_RXC __vector_13
#define USART_UDRE __vector_14
#define USART_TXC __vector_15
#define ADC __vector_16
#define EE_RDY __vector_17
#define ANA_COMP __vector_18
#define TWI __vector_19
#define SPM_RDY __vector_20

/** @} */



/**
 * @brief Macro to declare an interrupt service routine (ISR).
 *
 * This macro is used to declare an interrupt service routine and associate it with a specific
 * interrupt vector. It uses the __attribute__((signal,used)) attribute for the ISR function.
 *
 * Example usage:
 * @code{.c}
 * ISR(EXT_INT0)
 * {
 *     // Your ISR code here
 * }
 * @endcode
 *
 * @param INT_VECT The interrupt vector to associate with the ISR.
 */
#define ISR(INT_VECT) void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)



#endif /* ISR_INTERFACE_H_ */
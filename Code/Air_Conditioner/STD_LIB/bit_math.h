/**
 * @file bit_math.h
 * @brief This file contains macros and functions for bitwise operations.
 *
 * Created: 21/8/2023
 * Author: Arafa Arafa
 */ 

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#include "std_types.h"


/**
 * @brief Mask for a single bit (Least Significant Bit)
 */
#define BIT_MASK  (uint8_t)1

/**
 * @brief Mask for an 8-bit register (all bits set)
 */
#define U8_BIT_REG_MASK                                     ((uint8_t)0xFF)

/**
 * @brief Mask for a 16-bit register (all bits set)
 */
#define U16_BIT_REG_MASK                                    ((uint16_t)0xFFFF)

/**
 * @brief Value representing '1' in an 8-bit context
 */
#define  U8_ONE_VALUE	                                    ((uint8_t)1)

/**
 * @brief Value representing '0' in an 8-bit context
 */
#define  U8_ZERO_VALUE                                      ((uint8_t)0)




/**
 * @brief Set a specific bit in an 8-bit register.
 * @param REG The register to modify.
 * @param BIT_POSN The position of the bit to set.
 */
#define SET_BIT(REG,BIT_POSN)                               (REG |=  (BIT_MASK << BIT_POSN))


/**
 * @brief Clear a specific bit in an 8-bit register.
 * @param REG The register to modify.
 * @param BIT_POSN The position of the bit to clear.
 */
#define CLEAR_BIT(REG,BIT_POSN)                             (REG &= ~(BIT_MASK << BIT_POSN))


/**
 * @brief Toggle a specific bit in an 8-bit register.
 * @param REG The register to modify.
 * @param BIT_POS The position of the bit to toggle.
 */
#define TOGGLE_BIT(REG,BIT_POS)                             (REG ^=  (BIT_MASK << BIT_POS) )

/**
 * @brief Read a specific bit in an 8-bit register.
 * @param REG The register to read from.
 * @param BIT_POS The position of the bit to read.
 * @return The value of the specified bit (0 or 1).
 */
#define READ_BIT(REG,BIT_POS)                               ((REG & (BIT_MASK<<BIT_POS)) >> BIT_POS)

/**
 * @brief Clear all bits in an 8-bit register.
 * @param REG The register to clear.
 */
#define CLEAR_REG(REG)		                                (REG = ((uint8_t)U8_ZERO_VALUE))


#endif /* BIT_MATH_H_ */
/**
 * @file STD_TYPES.h
 * @brief Standard data type definitions.
 *
 * This file contains the standard data types used in the project.
 *
 * @date 8/21/2023
 * @author Arafa Arafa
 */


#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#ifndef FALSE
/** @brief False value */
#define FALSE       (0u)
#endif

#ifndef TRUE
/** @brief True value */
#define TRUE        (1u)
#endif


/** @brief High logic level value */
#define HIGH        (1u)

/** @brief Low logic level value */
#define LOW         (0u)

/** @brief Null pointer value */
#define NULL    ((void*)0)

typedef unsigned char         uint8_t;          /*           0 .. 255             */
typedef signed char           sint8_t;          /*        -128 .. +127            */
typedef unsigned short        uint16_t;         /*           0 .. 65535           */
typedef signed short          sint16_t;         /*      -32768 .. +32767          */
typedef unsigned long         uint32_t;         /*           0 .. 4294967295      */
typedef signed long           sint32_t;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64_t;         /*       0..18446744073709551615  */
typedef signed long long      sint64_t;
typedef float                 float32_t;
typedef double                float64_t;

typedef void(*ptr_to_v_fun_in_void_t)(void);



#endif /* STD_TYPES_H_ */
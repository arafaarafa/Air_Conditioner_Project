/*
 * TIMER_interface.h
 *
 * Created: 21/8/2023 3:37:27 PM
 *  Author:  Arafa Arafa
 */ 


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_
/**********************************  section 1: Includes ********************************************************/
#include "../../STD_LIB/bit_math.h"
#include "../../STD_LIB/std_types.h"
#include "../DIO/DIO_interface.h"
//#include "../EXT_Interrupt/interrupt.h"


/**********************************  section 2: Macro Declarations ***********************************************/
#define  INTIALIZE_TIMER_WITH_ZERO   (0)

/**********************************  section 3: Macro Like Function Declarations *************************** *****/


/**********************************  section 4: Data Type Declarations  ******************************************/

typedef enum{
	TIMER_OK,
	TIMER_NOT_OK,
}timer_enu_return_state_t;

typedef enum
{
	TIMER_0,
	TIMER_1,
	TIMER_2,
	INVALID_TIMER_TYPE
}timer_enu_timer_number_t;

typedef enum
{
	NO_CLOCK,
	F_CPU_CLOCK,
	F_CPU_8,
	F_CPU_32,
	F_CPU_64,
	F_CPU_128,
	F_CPU_256,
	F_CPU_1024,
	TIMER_EXTERNAL_CLK_FALLING_EDGE,
	TIMER_EXTERNAL_CLK_RISING_EDGE,
	INVALID_TIMER_CLK
}timer_enu_clock_t;

typedef enum
{
	TIMER_NORMAL_MODE=0,
	TIMER_PHASE_CORRECT_PWM_MODE,
	TIMER_CTC_MODE,
	TIMER_FAST_PWM_MODE,
	INVALID_TIMER_MODE
}timer_enu_timer_Mode_t;

typedef enum
{
	CTC_OUTPUT_COMPARE_MODE_DISCONNECTED=0,
	CTC_OUTPUT_COMPARE_MODE_TOGGLE,
	CTC_OUTPUT_COMPARE_MODE_CLEAR,
	CTC_OUTPUT_COMPARE_SET,
	CTC_INVALID_TIMER_OUTPUT_COMPARE_MODE
}timer_enu_output_compare_mode_t;

typedef enum
{
	FAST_OUTPUT_COMPARE_MODE_DISCONNECTED=0,
	FAST_OUTPUT_COMPARE_MODE_TOGGLE,
	FAST_OUTPUT_COMPARE_MODE_NON_INVERTED,
	FAST_OUTPUT_COMPARE_MODE_INVERTED,
	FAST_INVALID_TIMER_FAST_PWM_MODE
}timer_enu_fast_pwm_mode_t;

typedef enum
{
	PC_OUTPUT_COMPARE_MODE_DISCONNECTED=0,
	PC_OUTPUT_COMPARE_MODE_TOGGLE,
	PC_OUTPUT_COMPARE_MODE_NON_INVERTED,
	PC_OUTPUT_COMPARE_MODE_INVERTED,
	PC_INVALID_TIMER_PHASE_CORRECT_PWM_MODE
}timer_enu_phase_correct_pwm_mode_t;

typedef struct
{
	timer_enu_timer_number_t  enu_timer_no;  /* @ref timer_enu_timer_number_t*/
	timer_enu_clock_t enu_timer_clock; /* @ref timer_enu_clock_t*/
	timer_enu_timer_Mode_t  enu_timer_mode;  /* @ref TimerMode_t*/
	timer_enu_output_compare_mode_t enu_output_compare_mode;	/* @ref Output_Compare_Mode_t*/
	timer_enu_fast_pwm_mode_t  enu_fast_pwm_mode;		/* @ref FAST_PWM_MODE_t 8-bit resolution only*/
	timer_enu_phase_correct_pwm_mode_t enu_phase_correct_pwm_mode;		/* @ref enu_phase_correct_pwm_mode  8-bit resolution only*/
	uint16_t u16_timer_InitialValue;		/* the pre-loaded value on Timer/Counter Register*/
	uint16_t u16_timer_compare_MatchValue;		/* the top value on Output Compare Register*/
}timer_str_config_t;


/**********************************  section 5: Function Declarations ********************************************/

/*
 * Description:  Function to Initialize Timer Driver
 *                 - Working in Interrupt Mode
 *                 - Choose Timer initial value
 *                 - Choose Timer_ID (TIMER_0, TIMER_1, TIMER_2)
 *                 - Choose enu_timer_mode (OverFlow, Compare,PWM)
 *                 - if using CTC mode choose Timer compare match value  And choose enu_output_compare_mode
 * 
 *@param A Reference of the Timer configuration
 * @return status of the function
 *  TIMER_OK :the function done successfully
 *  TIMER_NOT_OK :the function has issues performing the function
 */
timer_enu_return_state_t TIMERx_init(const timer_str_config_t * ptr_str_timer_Config);
/*
* Description : TIMER START COUNTING BY CONFIGURE THE TIMER CLOCK
* @param copy_enu_timer_clk :timer clock configuration with pres-scaler 
		copy_enu_timer_number  :timer channel : TIMER_0,TIMER_1,TIMER_2 
* @return Std_ReturnType: status of the function
*  TIMER_OK :the function done successfully
*  TIMER_NOT_OK :the function has issues performing the function
*/
timer_enu_return_state_t TIMERx_start(const timer_enu_clock_t copy_enu_timer_clk,const timer_enu_timer_number_t copy_enu_timer_number);
/*
* Description : Call the Call Back function in the application after timer did its job
* @param A pointer to function & the  timer type
* @return status of the function
*  TIMER_OK :the function done successfully
*  TIMER_NOT_OK :the function has issues performing the function
*/
timer_enu_return_state_t TIMERx_setCallBack( ptr_to_v_fun_in_void_t ptr_v_fun_in_v, const timer_enu_timer_number_t copy_enu_timer_number );

/*
* Description :set a certain value on the timer counting register 
* @param the  timer type and the initial value to be set
* @return status of the function
*  TIMER_OK :the function done successfully
*  TIMER_NOT_OK :the function has issues performing the function
*/
timer_enu_return_state_t TIMERx_setValue(const timer_enu_timer_number_t copy_enu_timer_number ,const uint16_t copy_u16_timer_init_value);

/*
* Description :this function sets the offset of the compare unit 
* @param timer type and the top value to be compared with the TCNCx
* @return status of the function
*  TIMER_OK :the function done successfully
*  TIMER_NOT_OK :the function has issues performing the function
*/
timer_enu_return_state_t TIMERx_CTC_SetCompare(const timer_enu_timer_number_t copy_enu_timer_number ,const uint16_t copy_u16_compare_value);

/*
* Description :Function to make the timer to start again from beginning(reset)
* @param the  timer type and the initial value to be set
* @return status of the function
*  TIMER_OK :the function done successfully
*  TIMER_NOT_OK :the function has issues performing the function
*/
timer_enu_return_state_t TIMERx_reset(const timer_enu_timer_number_t copy_enu_timer_number);

/*
* Description :Function to Halt the timer (stop)
* @param the  timer type and the initial value to be set
* @return status of the function
*  TIMER_OK :the function done successfully
*  TIMER_NOT_OK :the function has issues performing the function
*/
timer_enu_return_state_t TIMERx_stop(const timer_enu_timer_number_t copy_enu_timer_number);

#endif /* TIMER_H_ */
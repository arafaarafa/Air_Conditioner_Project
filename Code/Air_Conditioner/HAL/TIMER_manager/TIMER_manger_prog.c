/**
 * @file TIMER_manger_prog.c
 * @brief Timer Manager Implementation Source File
 *
 * This source file implements functions for managing timers using the Timer Manager module.
 * It includes functions for initializing a timer, starting, stopping, and setting its value.
 *
 * @note This file assumes that "TIMER_manger_interface.h" is included to provide necessary declarations.
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */

#include "TIMER_manger_interface.h"

static timer_str_config_t g_str_Timer; /**< Global instance of the timer configuration structure. */



timerm_enu_return_state_t TIMER_MANGER_init(const timerm_str_config_t *stPtr_a_TimerConfig)
{
	timerm_enu_return_state_t l_ret = TIMERM_E_OK;
	if( (stPtr_a_TimerConfig->enu_timer_no >= INVALID_TIMER_TYPE) )
	{
		l_ret = TIMERM_E_NOK;
	}
	else
	{
		/*initiate the timer */
		
		g_str_Timer.enu_timer_no				=		stPtr_a_TimerConfig->enu_timer_no;
		g_str_Timer.enu_timer_mode				=		stPtr_a_TimerConfig->enu_timer_mode;
		g_str_Timer.u16_timer_InitialValue	    =		stPtr_a_TimerConfig->u16_timer_initial_value;
		g_str_Timer.u16_timer_compare_MatchValue=		stPtr_a_TimerConfig->u16_timer_compare_match_value;
		
		l_ret = TIMERx_init(&g_str_Timer);
		/*set call-back function  */
		l_ret |= TIMERx_setCallBack(stPtr_a_TimerConfig->ptr_call_back_func , stPtr_a_TimerConfig->enu_timer_no);
	}
	return l_ret;
}

timerm_enu_return_state_t TIMER_MANGER_start(const timer_enu_clock_t copy_enu_timer_clock, const timer_enu_timer_number_t copy_enu_timer_num)
{
	timerm_enu_return_state_t l_ret = TIMERM_E_OK;
	if( (copy_enu_timer_clock >= INVALID_TIMER_CLK)||(copy_enu_timer_num >= INVALID_TIMER_TYPE) )
	{
		l_ret = TIMERM_E_NOK;
	}
	else
	{
		/*Configure the TIMER Pres-scaler value for Timer-x clock*/
		l_ret = TIMERx_start(copy_enu_timer_clock,copy_enu_timer_num);
	}
	return l_ret;
}

timerm_enu_return_state_t TIMER_MANGER_stop(const timer_enu_timer_number_t copy_enu_timer_num)
{
	
	timerm_enu_return_state_t l_ret = TIMERM_E_OK;
	if(copy_enu_timer_num >= INVALID_TIMER_TYPE)
	{
		l_ret = TIMERM_E_NOK;
	}
	else
	{
		/*stop the clock for the specific timer*/
		l_ret = TIMERx_stop(copy_enu_timer_num);
	}
	return l_ret;
}

timerm_enu_return_state_t TIMER_MANGER_setValue(const timer_enu_timer_number_t copy_enu_timer_num , uint16_t u16_a_InitialValue)
{
	timerm_enu_return_state_t l_ret = TIMERM_E_OK;
	if(copy_enu_timer_num >= INVALID_TIMER_TYPE)
	{
		l_ret = TIMERM_E_NOK;
	}
	else
	{
		/*stop the clock for the specific timer*/
		l_ret =  TIMERx_setValue(copy_enu_timer_num , u16_a_InitialValue);
	}
	return l_ret;
}
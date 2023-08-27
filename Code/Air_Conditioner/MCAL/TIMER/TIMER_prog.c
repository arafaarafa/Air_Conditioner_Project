/*
 * TIMER_PROG.c
 *
 * Created: 21/8/2023 3:38:03 PM
 *  Author:  Arafa Arafa
 */ 
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "../AVR_ARCH/ISR_interface.h"

/* Global pointers to function to hold the address of the call back function in the upper layers */
static void (*g_Timer0_callBackPtr)(void) = NULL;
static void (*g_Timer1_callBackPtr)(void) = NULL;
static void (*g_Timer2_callBackPtr)(void) = NULL;

/*helper static functions prototypes*/
static  timer_enu_return_state_t TIMERx_selectClk(const  timer_enu_timer_number_t copy_enu_timer_number,const timer_enu_clock_t copy_enu_timer_clk);
static  timer_enu_return_state_t TIMERx_setTimerMode(const timer_str_config_t * ptr_str_timer_Config);

/***********************Interrupt Service Routines for TIMER_0 *************************/

ISR(TIMER1_OVF)
{
	if(g_Timer1_callBackPtr != NULL)
	{
		// The TIMER_0 overflow  occurred (must be cleared in software) 
		CLEAR_BIT(TIFR,TOV1);
		// Call the Call Back function in the upper layer after the timer overflow
		(*g_Timer1_callBackPtr)();
	}
}
ISR(TIMER0_OVF)
{
	if(g_Timer0_callBackPtr != NULL)
	{
		// The TIMER_0 overflow  occurred (must be cleared in software) 
		 CLEAR_BIT(TIFR,TOV0);
		//Call the Call Back function in the upper layer after the timer overflow
		(*g_Timer0_callBackPtr)();
	}
}

timer_enu_return_state_t TIMERx_setCallBack(  ptr_to_v_fun_in_void_t ptr_v_fun_in_v, const  timer_enu_timer_number_t copy_enu_timer_number )
{
	 timer_enu_return_state_t  enu_return_state =  TIMER_OK;
	if( (copy_enu_timer_number >= INVALID_TIMER_TYPE) || (NULL==ptr_v_fun_in_v) )
	{
		 enu_return_state =  TIMER_NOT_OK;
	}
	else
	{
		switch(copy_enu_timer_number)
		{
			case TIMER_0:
				/* load the address of the Call back function from upper layer in the global pointer to function */
				g_Timer0_callBackPtr = ptr_v_fun_in_v;
				break;
			case TIMER_1:
				/* load the address of the Call back function from upper layer in the global pointer to function */
				g_Timer1_callBackPtr = ptr_v_fun_in_v;
				break;
			case TIMER_2:
				/* load the address of the Call back function from upper layer in the global pointer to function */
				g_Timer2_callBackPtr = ptr_v_fun_in_v;
				break;
			default:
				 enu_return_state =  TIMER_NOT_OK;
				break;
		}
	}
	return  enu_return_state;
}


timer_enu_return_state_t TIMERx_init(const timer_str_config_t * ptr_str_timer_Config)
{
	 timer_enu_return_state_t  enu_return_state =  TIMER_OK;
	if(( ptr_str_timer_Config == NULL) || ( ptr_str_timer_Config->enu_timer_no >= INVALID_TIMER_TYPE) 
	|| ( ptr_str_timer_Config->enu_timer_mode >= INVALID_TIMER_MODE) ||
	( ptr_str_timer_Config->enu_output_compare_mode >=CTC_INVALID_TIMER_OUTPUT_COMPARE_MODE ) || ( ptr_str_timer_Config->enu_fast_pwm_mode >= FAST_INVALID_TIMER_FAST_PWM_MODE))
	{
		 enu_return_state =  TIMER_NOT_OK;
	}
	else
	{
		switch( ptr_str_timer_Config->enu_timer_no)
		{
			case TIMER_0:
				/*Clear registers of TIMER_0 before processing any of them*/
				CLEAR_REG(TCNT0);
				CLEAR_REG(TCCR0);
				CLEAR_REG(OCR0);
				/*Configure initial value in TCNT0 for TIMER_0 to start count from it*/
				TCNT0 =  ptr_str_timer_Config->u16_timer_InitialValue & U8_BIT_REG_MASK;
				/*Configure the TIMER mode value and enable the interrupt for this mode*/
				 enu_return_state |= TIMERx_setTimerMode( ptr_str_timer_Config);
				break;
			
			case TIMER_1:
				/*Clear registers of TIMER_1 before processing any of them*/
				CLEAR_REG(TCNT1L);
				CLEAR_REG(TCNT1H);
				CLEAR_REG(TCCR1A);
				CLEAR_REG(TCCR1B);
				CLEAR_REG(OCR1AH);
				CLEAR_REG(OCR1AL);
				/*Configure initial value in TCNT1(high&low) for TIMER_0 to start count from it*/
				TCNT1 =  ptr_str_timer_Config->u16_timer_InitialValue;
				/*TCNT1L =( ptr_str_timer_Config->u16_timer_InitialValue) & U8_BIT_REG_MASK;
				TCNT1H = ( ptr_str_timer_Config->u16_timer_InitialValue >> 8) & U8_BIT_REG_MASK;*/
				/*Configure the TIMER mode value and enable the interrupt for this mode*/
				 enu_return_state |= TIMERx_setTimerMode( ptr_str_timer_Config);
				break;
			
			case TIMER_2:
				/*Clear registers of TIMER_2 before processing any of them*/
				CLEAR_REG(TCNT2);
				CLEAR_REG(TCCR2);
				CLEAR_REG(OCR2);
				/*Configure initial value in TCNT for TIMER_2 to start count from it*/
				TCNT2 =  ptr_str_timer_Config->u16_timer_InitialValue & U8_BIT_REG_MASK;
				/*Configure the TIMER mode value and enable the interrupt for this mode*/
				 enu_return_state |= TIMERx_setTimerMode( ptr_str_timer_Config);
				break;
			
			default:
				 enu_return_state |=  TIMER_NOT_OK;
				break;
		}
	}
	return  enu_return_state;
}
timer_enu_return_state_t TIMERx_start(const timer_enu_clock_t copy_enu_timer_clk,const  timer_enu_timer_number_t copy_enu_timer_number)
{
	 timer_enu_return_state_t  enu_return_state =  TIMER_OK;
	if((copy_enu_timer_clk >= INVALID_TIMER_CLK)||(copy_enu_timer_number >= INVALID_TIMER_TYPE))
	{
		 enu_return_state =  TIMER_NOT_OK;
	}
	else
	{
		sei();
		/*Configure the TIMER Pres-scaler value for Timer-x clock*/
		 enu_return_state = TIMERx_selectClk(copy_enu_timer_number,copy_enu_timer_clk);
	}
	return  enu_return_state;
}
timer_enu_return_state_t TIMERx_setValue(const  timer_enu_timer_number_t copy_enu_timer_number ,const uint16_t copy_u16_timer_init_value)
{
	 timer_enu_return_state_t  enu_return_state =  TIMER_OK;
	if( (copy_enu_timer_number >= INVALID_TIMER_TYPE) )
	{
		 enu_return_state =  TIMER_NOT_OK;
	}
	else
	{
		switch(copy_enu_timer_number)
		{
			case TIMER_0:
				TCNT0 = (uint8_t) copy_u16_timer_init_value;
				break;
				
			case TIMER_1:
				TCNT1 = copy_u16_timer_init_value;
				/*TCNT1L = (uint8_t)(copy_u16_timer_init_value) & U8_BIT_REG_MASK;
				TCNT1H = (uint8_t)(copy_u16_timer_init_value >> U8_BIT_REG_MASK) & U8_BIT_REG_MASK;	*/	
				break;
				
			case TIMER_2:
				TCNT2 = copy_u16_timer_init_value & U8_BIT_REG_MASK;
				break;
				
			default:
				 enu_return_state |=  TIMER_NOT_OK;
				break;
		}
	}
	return  enu_return_state;
}

timer_enu_return_state_t TIMERx_CTC_SetCompare(const  timer_enu_timer_number_t copy_enu_timer_number ,const uint16_t copy_u16_compare_value)
{
	 timer_enu_return_state_t  enu_return_state =  TIMER_OK;
	if( (copy_enu_timer_number >= INVALID_TIMER_TYPE) )
	{
		 enu_return_state =  TIMER_NOT_OK;
	}
	else
	{
		switch(copy_enu_timer_number)
		{
			case TIMER_0:
				OCR0 =(uint8_t) copy_u16_compare_value & U8_BIT_REG_MASK;
				break;
				
			case TIMER_1:
				OCR1AL = (uint8_t)copy_u16_compare_value ;
				OCR1AH = (uint8_t)(copy_u16_compare_value >> 8);
				break;
				
			case TIMER_2:
				OCR2 =(uint8_t) copy_u16_compare_value & U8_BIT_REG_MASK;
				break;
				
			default:
				 enu_return_state |=  TIMER_NOT_OK;
				break;
		}
	}
	return  enu_return_state;
}


timer_enu_return_state_t TIMERx_reset(const  timer_enu_timer_number_t copy_enu_timer_number)
{
	 timer_enu_return_state_t  enu_return_state =  TIMER_OK;
	if( (copy_enu_timer_number >= INVALID_TIMER_TYPE) )
	{
		 enu_return_state =  TIMER_NOT_OK;
	}
	else
	{
		switch(copy_enu_timer_number)
		{
			case TIMER_0:
				/*Clear registers of TIMER_0 before processing any of them*/
				CLEAR_REG(TCNT0);
				CLEAR_REG(TCCR0);
				CLEAR_REG(OCR0);
				CLEAR_REG(TIMSK);
				CLEAR_REG(TIFR);
				break;
				
			case TIMER_1:
				/*Clear registers of TIMER_1 before processing any of them*/
				CLEAR_REG(TCNT1L);
				CLEAR_REG(TCNT1H);
				CLEAR_REG(TCCR1A);
				CLEAR_REG(TCCR1B);
				CLEAR_REG(OCR1AH);
				CLEAR_REG(OCR1AL);
				CLEAR_REG(TIMSK);
				CLEAR_REG(TIFR);
				break;
				
			case TIMER_2:
				/*Clear registers of TIMER_2 before processing any of them*/
				CLEAR_REG(TCNT2);
				CLEAR_REG(TCCR2);
				CLEAR_REG(OCR2);
				CLEAR_REG(TIMSK);
				CLEAR_REG(TIFR);
				break;
				
			default:
				 enu_return_state |=  TIMER_NOT_OK;
				break;
		}
	}
	return  enu_return_state;
}

timer_enu_return_state_t TIMERx_stop(const  timer_enu_timer_number_t copy_enu_timer_number)
{
	 timer_enu_return_state_t  enu_return_state =  TIMER_OK;
	if( (copy_enu_timer_number >= INVALID_TIMER_TYPE) )
	{
		 enu_return_state =  TIMER_NOT_OK;
	}
	else
	{
		switch(copy_enu_timer_number)
		{
			case TIMER_0:
				/*use no clock to halt TIMER_0*/
				CLEAR_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
				break;
				
			case TIMER_1:
				/*use no clock to halt TIMER_1*/
				CLEAR_BIT(TCCR1B,CS10);
				CLEAR_BIT(TCCR1B,CS11);
				CLEAR_BIT(TCCR1B,CS12);
				break;
				
			case TIMER_2:
				/*use no clock to halt TIMER_2*/
				CLEAR_BIT(TCCR2,CS20);
				CLEAR_BIT(TCCR2,CS21);
				CLEAR_BIT(TCCR2,CS22);
				break;
				
			default:
				 enu_return_state |=  TIMER_NOT_OK;
				break;
		}
	}
	return  enu_return_state;
}

static timer_enu_return_state_t TIMERx_selectClk(const  timer_enu_timer_number_t copy_enu_timer_number,const timer_enu_clock_t copy_enu_timer_clk)
{
	 timer_enu_return_state_t  enu_return_state =  TIMER_OK;
	if( (copy_enu_timer_number >= INVALID_TIMER_TYPE) || (copy_enu_timer_clk >= INVALID_TIMER_CLK) )
	{
		 enu_return_state =  TIMER_NOT_OK;
	}
	else
	{
		switch(copy_enu_timer_number)
		{
			case TIMER_0:
				switch(copy_enu_timer_clk)
				{
					case NO_CLOCK:
						CLEAR_BIT(TCCR0,CS00);
						CLEAR_BIT(TCCR0,CS01);
						CLEAR_BIT(TCCR0,CS02);
						break;
					case F_CPU_CLOCK:
						SET_BIT(TCCR0,CS00);
						CLEAR_BIT(TCCR0,CS01);
						CLEAR_BIT(TCCR0,CS02);
						break;
					case F_CPU_8:
						CLEAR_BIT(TCCR0,CS00);
						SET_BIT(TCCR0,CS01);
						CLEAR_BIT(TCCR0,CS02);
						break;
					case F_CPU_64:
						SET_BIT(TCCR0,CS00);
						SET_BIT(TCCR0,CS01);
						CLEAR_BIT(TCCR0,CS02);
						break;
					case F_CPU_256:
						CLEAR_BIT(TCCR0,CS00);
						CLEAR_BIT(TCCR0,CS01);
						SET_BIT(TCCR0,CS02);
						break;
					case F_CPU_1024:
						SET_BIT(TCCR0,CS00);
						CLEAR_BIT(TCCR0,CS01);
						SET_BIT(TCCR0,CS02);	
						break;
					case TIMER_EXTERNAL_CLK_FALLING_EDGE:
						CLEAR_BIT(TCCR0,CS00);
						SET_BIT(TCCR0,CS01);
						SET_BIT(TCCR0,CS02);
						break;
					case TIMER_EXTERNAL_CLK_RISING_EDGE:
						SET_BIT(TCCR0,CS00);
						SET_BIT(TCCR0,CS01);
						SET_BIT(TCCR0,CS02);
						break;
					default:
						 enu_return_state =  TIMER_NOT_OK;
						break;
				}
				break;
				
			case TIMER_1:
				switch(copy_enu_timer_clk)
				{
					case NO_CLOCK:
						CLEAR_BIT(TCCR1B,CS10);
						CLEAR_BIT(TCCR1B,CS11);
						CLEAR_BIT(TCCR1B,CS12);
						break;
					case F_CPU_CLOCK:
						SET_BIT(TCCR1B,CS10);
						CLEAR_BIT(TCCR1B,CS11);
						CLEAR_BIT(TCCR1B,CS12);
						break;
					case F_CPU_8:
						CLEAR_BIT(TCCR1B,CS10);
						SET_BIT(TCCR1B,CS11);
						CLEAR_BIT(TCCR1B,CS12);
						break;
					case F_CPU_64:
						SET_BIT(TCCR1B,CS10);
						SET_BIT(TCCR1B,CS11);
						CLEAR_BIT(TCCR1B,CS12);
						break;
					case F_CPU_256:
						CLEAR_BIT(TCCR1B,CS10);
						CLEAR_BIT(TCCR1B,CS11);
						SET_BIT(TCCR1B,CS12);
						break;
					case F_CPU_1024:
						SET_BIT(TCCR1B,CS10);
						CLEAR_BIT(TCCR1B,CS11);
						SET_BIT(TCCR1B,CS12);	
						break;
					case TIMER_EXTERNAL_CLK_FALLING_EDGE:
						CLEAR_BIT(TCCR1B,CS10);
						SET_BIT(TCCR1B,CS11);
						SET_BIT(TCCR1B,CS12);
						break;
					case TIMER_EXTERNAL_CLK_RISING_EDGE:
						SET_BIT(TCCR1B,CS10);
						SET_BIT(TCCR1B,CS11);
						SET_BIT(TCCR1B,CS12);
						break;
					default:
						 enu_return_state =  TIMER_NOT_OK;
						break;
				}			
				break;
				
			case TIMER_2:
				switch(copy_enu_timer_clk)
				{
					case NO_CLOCK:
						CLEAR_BIT(TCCR2,CS20);
						CLEAR_BIT(TCCR2,CS21);
						CLEAR_BIT(TCCR2,CS22);
						break;
					case F_CPU_CLOCK:
						SET_BIT(TCCR2,CS20);
						CLEAR_BIT(TCCR2,CS21);
						CLEAR_BIT(TCCR2,CS22);
						break;
					case F_CPU_8:
						CLEAR_BIT(TCCR2,CS20);
						SET_BIT(TCCR2,CS21);
						CLEAR_BIT(TCCR2,CS22);
						break;
					case F_CPU_32:
						SET_BIT(TCCR2,CS20);
						SET_BIT(TCCR2,CS21);
						CLEAR_BIT(TCCR2,CS22);
						break;
					case F_CPU_64:
						CLEAR_BIT(TCCR2,CS20);
						CLEAR_BIT(TCCR2,CS21);
						SET_BIT(TCCR2,CS22);
						break;
					case F_CPU_128:
						SET_BIT(TCCR2,CS20);
						CLEAR_BIT(TCCR2,CS21);
						SET_BIT(TCCR2,CS22);
						break;
					case F_CPU_256:
						CLEAR_BIT(TCCR2,CS20);
						SET_BIT(TCCR2,CS21);
						SET_BIT(TCCR2,CS22);
						break;
					case F_CPU_1024:
						SET_BIT(TCCR2,CS20);
						SET_BIT(TCCR2,CS21);
						SET_BIT(TCCR2,CS22);	
						break;
					default:
						 enu_return_state =  TIMER_NOT_OK;
						break;
				}
				break;
				
			default:
				 enu_return_state |=  TIMER_NOT_OK;
				break;
		}
	}
	return  enu_return_state;
}


static timer_enu_return_state_t TIMERx_setTimerMode(const timer_str_config_t * ptr_str_timer_Config)
{
	 timer_enu_return_state_t  enu_return_state =  TIMER_OK;
	if( ( ptr_str_timer_Config == NULL) || ( ptr_str_timer_Config->enu_timer_no >= INVALID_TIMER_TYPE) || ( ptr_str_timer_Config->enu_timer_mode >= INVALID_TIMER_MODE) ||
	    ( ptr_str_timer_Config->enu_output_compare_mode >=CTC_INVALID_TIMER_OUTPUT_COMPARE_MODE ) )
	{
		 enu_return_state =  TIMER_NOT_OK;
	}
	else
	{
		switch( ptr_str_timer_Config->enu_timer_no)
		{
			case TIMER_0:
				switch( ptr_str_timer_Config->enu_timer_mode)
				{
					case TIMER_NORMAL_MODE:
						/*Make FOC0 to be Active as it is overflow mode(for non-PWM mode)*/
						SET_BIT(TCCR0,FOC0);
						/*Normal Overflow mode*/
						CLEAR_BIT(TCCR0,WGM00);
						CLEAR_BIT(TCCR0,WGM01);
						/*Normal port operation, OC0 disconnected*/
						CLEAR_BIT(TCCR0,COM00);
						CLEAR_BIT(TCCR0,COM01);
						/* Enable TIMER_0 overflow interrupt*/
						//TIMSK |= 1<< TOIE0;
						SET_BIT(TIMSK,TOIE0);
						break;
					case TIMER_PHASE_CORRECT_PWM_MODE:
						/*PWM Phase Correct*/
						SET_BIT(TCCR0,WGM00);
						CLEAR_BIT(TCCR0,WGM01);
						/*Compare Output Mode, Phase Correct PWM Mode*/
						if( ptr_str_timer_Config->enu_phase_correct_pwm_mode == PC_OUTPUT_COMPARE_MODE_DISCONNECTED){
							CLEAR_BIT(TCCR0,COM00);
							CLEAR_BIT(TCCR0,COM01);
						}
						else if( ptr_str_timer_Config->enu_phase_correct_pwm_mode == PC_OUTPUT_COMPARE_MODE_NON_INVERTED){
							CLEAR_BIT(TCCR0,COM00);
							SET_BIT(TCCR0,COM01);
						}
						else if( ptr_str_timer_Config->enu_phase_correct_pwm_mode == PC_OUTPUT_COMPARE_MODE_INVERTED){
							SET_BIT(TCCR0,COM00);
							SET_BIT(TCCR0,COM01);
						}
						else{
							enu_return_state =  TIMER_NOT_OK;
						}
						
						 /*The Output Compare Register contains an 8-bit value that is continuously compared with the  counter value (TCNT0) */
						 OCR0 =(uint8_t)  ptr_str_timer_Config->u16_timer_compare_MatchValue & U8_BIT_REG_MASK;
						break;
						
					case TIMER_FAST_PWM_MODE:
						/*Fast PWM*/
						SET_BIT(TCCR0,WGM00);
						SET_BIT(TCCR0,WGM01);
						/*Compare Output Mode, Fast PWM Mode*/

						if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_DISCONNECTED){
							CLEAR_BIT(TCCR0,COM00);
							CLEAR_BIT(TCCR0,COM01);
						}
						else if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_NON_INVERTED){
							CLEAR_BIT(TCCR0,COM00);
							SET_BIT(TCCR0,COM01);
						}
						else if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_INVERTED){
							SET_BIT(TCCR0,COM00);
							SET_BIT(TCCR0,COM01);
						}
						else{
							enu_return_state =  TIMER_NOT_OK;
						}
						
						 /*The Output Compare Register contains an 8-bit value that is continuously compared with the  counter value (TCNT0) */
						 OCR0 =  ptr_str_timer_Config->u16_timer_compare_MatchValue & U8_BIT_REG_MASK;
						break;
						
					case TIMER_CTC_MODE:
						/*Make FOC0 to be Active as it is CTC mode(for non-PWM mode)*/
						SET_BIT(TCCR0,FOC0);
						/*CTC Mode, non-PWM Mode*/
						CLEAR_BIT(TCCR0,WGM00);
						SET_BIT(TCCR0,WGM01);
						/*Compare Output Mode, non-PWM Mode*/
						switch( ptr_str_timer_Config->enu_output_compare_mode)
						{
							case CTC_OUTPUT_COMPARE_MODE_DISCONNECTED:
								/* Normal port operation, OC0 disconnected.*/
								CLEAR_BIT(TCCR0,COM00);
								CLEAR_BIT(TCCR0,COM01);
								break;
							case CTC_OUTPUT_COMPARE_MODE_TOGGLE:
								/* Toggle OC0 on compare match*/
								SET_BIT(TCCR0,COM00);
								CLEAR_BIT(TCCR0,COM01);
								break;
							case CTC_OUTPUT_COMPARE_MODE_CLEAR:
								/*Clear OC0 on compare match*/
								CLEAR_BIT(TCCR0,COM00);
								SET_BIT(TCCR0,COM01);
								break;
							case CTC_OUTPUT_COMPARE_SET:
							/*Set OC0 on compare match*/
								SET_BIT(TCCR0,COM00);
								SET_BIT(TCCR0,COM01);
								break;
							default: 
								 enu_return_state |=  TIMER_NOT_OK;
								break;
						}
					    /*The Output Compare Register contains an 8-bit value that is continuously compared with the  counter value (TCNT0) */
						OCR0 =  ptr_str_timer_Config->u16_timer_compare_MatchValue & U8_BIT_REG_MASK;	
						/* Enable TIMER_0 CTC mode interrupt*/
						SET_BIT(TIMSK,OCIE0);
						break;
					default:
						 enu_return_state =  TIMER_NOT_OK;
						break;
				}
				break;
				
			case TIMER_1:
				switch( ptr_str_timer_Config->enu_timer_mode)
				{
					case TIMER_NORMAL_MODE:
						/*Make FOC1A,FOC1B to be Active as it is overflow mode(for non-PWM mode)*/
						SET_BIT(TCCR1A,FOC1A);
						SET_BIT(TCCR1A,FOC1B);
						/*Normal Overflow mode*/
						CLEAR_BIT(TCCR1A,WGM10);
						CLEAR_BIT(TCCR1A,WGM11);
						CLEAR_BIT(TCCR1B,WGM12);
						CLEAR_BIT(TCCR1B,WGM13);
						/*Normal port operation, OC1A/OC1B disconnected.*/
						CLEAR_BIT(TCCR1A,COM1A0);
						CLEAR_BIT(TCCR1A,COM1A1);
						CLEAR_BIT(TCCR1A,COM1B0);
						CLEAR_BIT(TCCR1A,COM1B1);
						/* Enable TIMER_0 overflow interrupt*/
						//TIMSK |= 1<<  TOIE1;
						SET_BIT(TIMSK,TOIE1);
						break;
					case TIMER_PHASE_CORRECT_PWM_MODE:
						/*PWM Phase Correct 8-bit,top= 0x00FF ,Update of OCR1A at TOP,TOV1 Flag Set on BOTTOM*/
						SET_BIT(TCCR1A,WGM10);
						CLEAR_BIT(TCCR1A,WGM11);
						CLEAR_BIT(TCCR1B,WGM12);
						CLEAR_BIT(TCCR1B,WGM13);
						/*Compare Output Mode, Phase Correct PWM Mode*/
						switch( ptr_str_timer_Config->enu_phase_correct_pwm_mode)
						{
							case PC_OUTPUT_COMPARE_MODE_DISCONNECTED:
								/*Normal port operation, OC1A/OC1B disconnected.*/
								CLEAR_BIT(TCCR1A,COM1A0);
								CLEAR_BIT(TCCR1A,COM1A1);
								CLEAR_BIT(TCCR1A,COM1B0);
								CLEAR_BIT(TCCR1A,COM1B1);
								break;
							case PC_OUTPUT_COMPARE_MODE_TOGGLE:
								/* Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
								 * For all other WGM13:0 settings, normal port operation, OC1A/OC1B disconnected
								 */
								SET_BIT(TCCR1A,COM1A0);
								CLEAR_BIT(TCCR1A,COM1A1);
								SET_BIT(TCCR1A,COM1B0);
								CLEAR_BIT(TCCR1A,COM1B1);
								break;
							case PC_OUTPUT_COMPARE_MODE_NON_INVERTED:
								/*Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare
								* match when down counting. (non-inverting mode)
								*/
								CLEAR_BIT(TCCR1A,COM1A0);
								SET_BIT(TCCR1A,COM1A1);
								CLEAR_BIT(TCCR1A,COM1B0);
								SET_BIT(TCCR1A,COM1B1);
								break;
							case PC_OUTPUT_COMPARE_MODE_INVERTED:
								/* Set OC1A/OC1B on compare match when up-counting. Clear OC1A/OC1B on compare
								* match when down counting,(inverting mode)
								*/
								SET_BIT(TCCR1A,COM1A0);
								SET_BIT(TCCR1A,COM1A1);
								SET_BIT(TCCR1A,COM1B0);
								SET_BIT(TCCR1A,COM1B1);
								break;
							default: 
								 enu_return_state |=  TIMER_NOT_OK;
								break;
						}
						/*The Output Compare Register contains an 16-bit value that is continuously compared with the  counter value (TCNT1) */
						OCR1AL = (uint8_t) ptr_str_timer_Config->u16_timer_compare_MatchValue ;
						OCR1AH = (uint8_t)( ptr_str_timer_Config->u16_timer_compare_MatchValue >> 8);
						break;
						
					case TIMER_FAST_PWM_MODE:
						/*Fast PWM 8-bit,top= 0x00FF ,Update of OCR1A at BOTTOM,TOV1 Flag Set on TOP*/
						SET_BIT(TCCR1A,WGM10);
						CLEAR_BIT(TCCR1A,WGM11);
						SET_BIT(TCCR1B,WGM12);
						CLEAR_BIT(TCCR1B,WGM13);
						/*Compare Output Mode, Fast PWM Mode*/
						if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_DISCONNECTED){
							CLEAR_BIT(TCCR1A,COM1A0);
							CLEAR_BIT(TCCR1A,COM1A1);
							CLEAR_BIT(TCCR1A,COM1B0);
							CLEAR_BIT(TCCR1A,COM1B1);
						}
						else if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_TOGGLE){
							SET_BIT(TCCR1A,COM1A0);
							CLEAR_BIT(TCCR1A,COM1A1);
							SET_BIT(TCCR1A,COM1B0);
							CLEAR_BIT(TCCR1A,COM1B1);
						}
						else if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_NON_INVERTED){
							CLEAR_BIT(TCCR1A,COM1A0);
							SET_BIT(TCCR1A,COM1A1);
							CLEAR_BIT(TCCR1A,COM1B0);
							SET_BIT(TCCR1A,COM1B1);
						}
						else if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_INVERTED){
							SET_BIT(TCCR1A,COM1A0);
							SET_BIT(TCCR1A,COM1A1);
							SET_BIT(TCCR1A,COM1B0);
							SET_BIT(TCCR1A,COM1B1);
						}
						else{
							enu_return_state =  TIMER_NOT_OK;
						}
						
						/*The Output Compare Register contains an 16-bit value that is continuously compared with the  counter value (TCNT1) */
						OCR1AL = (uint8_t) ptr_str_timer_Config->u16_timer_compare_MatchValue ;
						OCR1AH = (uint8_t)( ptr_str_timer_Config->u16_timer_compare_MatchValue >> 8);
						break;
						
					case TIMER_CTC_MODE:
						/*Make FOC1A,FOC1B to be Active as it is overflow mode(for non-PWM mode)*/
						SET_BIT(TCCR1A,FOC1A);
						SET_BIT(TCCR1A,FOC1B);
						/*CTC Mode, non-PWM Mode*/
						CLEAR_BIT(TCCR1A,WGM10);
						CLEAR_BIT(TCCR1A,WGM11);
						SET_BIT(TCCR1B,WGM12);
						CLEAR_BIT(TCCR1B,WGM13);
						/*Compare Output Mode, non-PWM Mode*/
						if( ptr_str_timer_Config->enu_output_compare_mode == CTC_OUTPUT_COMPARE_MODE_DISCONNECTED){
							CLEAR_BIT(TCCR1A,COM1A0);
							CLEAR_BIT(TCCR1A,COM1A1);
							CLEAR_BIT(TCCR1A,COM1B0);
							CLEAR_BIT(TCCR1A,COM1B1);
						}else if( ptr_str_timer_Config->enu_output_compare_mode == CTC_OUTPUT_COMPARE_MODE_TOGGLE){
							SET_BIT(TCCR1A,COM1A0);
							CLEAR_BIT(TCCR1A,COM1A1);
							SET_BIT(TCCR1A,COM1B0);
							CLEAR_BIT(TCCR1A,COM1B1);
						}
						else if( ptr_str_timer_Config->enu_output_compare_mode == CTC_OUTPUT_COMPARE_MODE_CLEAR){
							CLEAR_BIT(TCCR1A,COM1A0);
							SET_BIT(TCCR1A,COM1A1);
							CLEAR_BIT(TCCR1A,COM1B0);
							SET_BIT(TCCR1A,COM1B1);
						}
						else if( ptr_str_timer_Config->enu_output_compare_mode == CTC_OUTPUT_COMPARE_SET){
							SET_BIT(TCCR1A,COM1A0);
							SET_BIT(TCCR1A,COM1A1);
							SET_BIT(TCCR1A,COM1B0);
							SET_BIT(TCCR1A,COM1B1);
						}
						else{
							enu_return_state =  TIMER_NOT_OK;
						}
						
					    /*The Output Compare Register contains an 16-bit value that is continuously compared with the  counter value (TCNT1) */
						OCR1AL =  ptr_str_timer_Config->u16_timer_compare_MatchValue ;
						OCR1AH = ( ptr_str_timer_Config->u16_timer_compare_MatchValue >> 8) ;	
						/* Enable TIMER_1 CTC-A mode interrupt*/
						SET_BIT(TIMSK,OCIE1A);
						break;
					default:
						 enu_return_state =  TIMER_NOT_OK;
						break;
				}
				
				break;
				
			case TIMER_2:
				switch( ptr_str_timer_Config->enu_timer_mode)
				{
					case TIMER_NORMAL_MODE:
						/*Make FOC2 to be Active as it is overflow mode(for non-PWM mode)*/
						SET_BIT(TCCR2,FOC2);
						/*Normal Overflow mode*/
						CLEAR_BIT(TCCR2,WGM20);
						CLEAR_BIT(TCCR2,WGM21);
						/*Normal port operation, OC2 disconnected*/
						CLEAR_BIT(TCCR2,COM20);
						CLEAR_BIT(TCCR2,COM21);
						/* Enable TIMER_2 overflow interrupt*/
						SET_BIT(TIMSK,TOIE2);
						break;
					case TIMER_PHASE_CORRECT_PWM_MODE:
						/*PWM Phase Correct*/
						SET_BIT(TCCR2,WGM20);
						CLEAR_BIT(TCCR2,WGM21);
						/*Compare Output Mode, Phase Correct PWM Mode*/
						if( ptr_str_timer_Config->enu_phase_correct_pwm_mode == PC_OUTPUT_COMPARE_MODE_DISCONNECTED){
							CLEAR_BIT(TCCR2,COM20);
							CLEAR_BIT(TCCR2,COM21);

						}else if(ptr_str_timer_Config->enu_phase_correct_pwm_mode == PC_OUTPUT_COMPARE_MODE_NON_INVERTED){
							CLEAR_BIT(TCCR2,COM20);
							SET_BIT(TCCR2,COM21);
						}
						else if(ptr_str_timer_Config->enu_phase_correct_pwm_mode == PC_OUTPUT_COMPARE_MODE_INVERTED){
							SET_BIT(TCCR2,COM20);
							SET_BIT(TCCR2,COM21);
						}
						else{
							enu_return_state =  TIMER_NOT_OK;
						}
						
						/*The Output Compare Register contains an 8-bit value that is continuously compared with the  counter value (TCNT2) */
						OCR2 = (uint8_t) ptr_str_timer_Config->u16_timer_compare_MatchValue & U8_BIT_REG_MASK;
						break;
						
					case TIMER_FAST_PWM_MODE:
						
						/*Fast PWM*/
						SET_BIT(TCCR2,WGM20);
						SET_BIT(TCCR2,WGM21);
						/*Compare Output Mode, Fast PWM Mode*/
						if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_DISCONNECTED){
							CLEAR_BIT(TCCR2,COM20);
							CLEAR_BIT(TCCR2,COM21);
						}
						else if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_NON_INVERTED){
							CLEAR_BIT(TCCR2,COM20);
							SET_BIT(TCCR2,COM21);
						}
						else if(ptr_str_timer_Config->enu_fast_pwm_mode == FAST_OUTPUT_COMPARE_MODE_INVERTED){
							SET_BIT(TCCR2,COM20);
							SET_BIT(TCCR2,COM21);
						}
						else{
							enu_return_state |=  TIMER_NOT_OK;
						}
						
						 /*The Output Compare Register contains an 8-bit value that is continuously compared with the  counter value (TCNT2) */
						 OCR2 =(uint8_t)  ptr_str_timer_Config->u16_timer_compare_MatchValue & U8_BIT_REG_MASK;
						break;
						
					case TIMER_CTC_MODE:
						/*Make FOC2 to be Active as it is CTC mode(for non-PWM mode)*/
						SET_BIT(TCCR2,FOC2);
						/*CTC Mode, non-PWM Mode*/
						CLEAR_BIT(TCCR2,WGM20);
						SET_BIT(TCCR2,WGM21);
						/*Compare Output Mode, non-PWM Mode*/
						if(ptr_str_timer_Config->enu_output_compare_mode == CTC_OUTPUT_COMPARE_MODE_DISCONNECTED){

							CLEAR_BIT(TCCR2,COM20);
							CLEAR_BIT(TCCR2,COM21);
						}else if(ptr_str_timer_Config->enu_output_compare_mode == CTC_OUTPUT_COMPARE_MODE_TOGGLE){
							SET_BIT(TCCR2,COM20);
							CLEAR_BIT(TCCR2,COM21);
						}
						else if(ptr_str_timer_Config->enu_output_compare_mode == CTC_OUTPUT_COMPARE_MODE_CLEAR){
							CLEAR_BIT(TCCR2,COM20);
							SET_BIT(TCCR2,COM21);
						}
						else if(ptr_str_timer_Config->enu_output_compare_mode == CTC_OUTPUT_COMPARE_SET){
							SET_BIT(TCCR2,COM20);
								SET_BIT(TCCR2,COM21);
						}
						else{
							enu_return_state |=  TIMER_NOT_OK;
						}
					     /*The Output Compare Register contains an 8-bit value that is continuously compared with the  counter value (TCNT2) */
					     OCR2 =(uint8_t)  ptr_str_timer_Config->u16_timer_compare_MatchValue & U8_BIT_REG_MASK;
						/* Enable TIMER_0 CTC mode interrupt*/
						SET_BIT(TIMSK,OCIE2);
						break;
					default:
						 enu_return_state =  TIMER_NOT_OK;
						break;
				}
				
				break;
				
			default:
				 enu_return_state =  TIMER_NOT_OK;
				break;
		}
	}
	
	return  enu_return_state;
}


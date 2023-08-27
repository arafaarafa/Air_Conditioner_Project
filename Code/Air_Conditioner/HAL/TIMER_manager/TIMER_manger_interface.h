/**
 * @file TIMER_manager_interface.h
 * @brief Timer Manager Interface Header File
 *
 * This header file provides declarations for the Timer Manager module's interface functions
 * and related data types. It includes macros, enums, and function prototypes for initializing,
 * starting, stopping, and setting timer values using the Timer Manager module.
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */


#ifndef TIMER_MANGER_INTERFACE_H_
#define TIMER_MANGER_INTERFACE_H_

#include "../../MCAL/TIMER/TIMER_interface.h"


/** @defgroup TimerManager_Configurations Timer Manager Configuration Macros */
/** @{ */

#define INTIALIZE_TIMER_WITH_ZERO   (0) /**< Initial value for timer set to zero. */
#define OVERFLOW_COUNT_FOR_ONE_SEC  (30U) /**< Overflow count for one second. */
#define CONFIG_COMPARE_VALUE        (uint8_t)97 /**< Default compare value. */

/** @} */




/**
 * @brief Enumeration for Timer Manager return states.
 */
typedef enum {
    TIMERM_E_OK,       /**< Operation performed successfully. */
    TIMERM_E_NOK,      /**< Operation performed with issues or errors. */
    TIMERM_NULL_PTR    /**< Null pointer encountered. */
} timerm_enu_return_state_t;


/**
 * @brief Structure to hold the configuration of a timer for Timer Manager module.
 */
typedef struct {
    timer_enu_timer_number_t    enu_timer_no;              /**< Timer number (Timer0, Timer1, Timer2). */
    timer_enu_timer_Mode_t      enu_timer_mode;            /**< Timer mode (OverFlow, Compare, PWM). */
    uint16_t                    u16_timer_initial_value;   /**< Initial value for Timer/Counter Register. */
    uint16_t                    u16_timer_compare_match_value; /**< Compare match value for Output Compare Register. */
    ptr_to_v_fun_in_void_t      ptr_call_back_func;        /**< Pointer to callback function for timer interrupt. */
	timer_enu_clock_t			enu_prescaller;
} timerm_str_config_t;



/**
 * @brief Initialize and configure a timer using the Timer Manager module.
 *
 * This function initializes and configures a timer based on the provided configuration structure.
 *
 * @param stPtr_a_TimerConfig Pointer to the timer configuration structure.
 * @return The return state of the timer initialization.
 *     - #TIMERM_E_OK: Timer initialization successful.
 *     - #TIMERM_E_NOK: Timer initialization failed.
 */
timerm_enu_return_state_t TIMER_MANGER_init(const timerm_str_config_t *ptr_str_timer_manger_config);

/**
 * @brief Start a timer using the Timer Manager module.
 *
 * This function starts a specified timer with the provided clock and timer number.
 *
 * @param copy_enu_timer_clock The timer's clock configuration.
 * @param copy_enu_timer_num The timer number to start.
 * @return The return state of starting the timer.
 *     - #TIMERM_E_OK: Timer started successfully.
 *     - #TIMERM_E_NOK: Timer start failed.
 */
timerm_enu_return_state_t TIMER_MANGER_start(const timer_enu_clock_t copy_enu_timer_clock, const timer_enu_timer_number_t copy_enu_timer_num);


/**
 * @brief Stop a timer using the Timer Manager module.
 *
 * This function stops a specified timer.
 *
 * @param copy_enu_timer_num The timer number to stop.
 * @return The return state of stopping the timer.
 *     - #TIMERM_E_OK: Timer stopped successfully.
 *     - #TIMERM_E_NOK: Timer stop failed.
 */
timerm_enu_return_state_t TIMER_MANGER_stop(const timer_enu_timer_number_t copy_enu_timer_num);


/**
 * @brief Set the initial value of a timer using the Timer Manager module.
 *
 * This function sets the initial value of a specified timer.
 *
 * @param copy_enu_timer_num The timer number to set the value for.
 * @param u16_a_InitialValue The initial value to set for the timer.
 * @return The return state of setting the timer's value.
 *     - #TIMERM_E_OK: Timer value set successfully.
 *     - #TIMERM_E_NOK: Timer value set failed.
 */
timerm_enu_return_state_t TIMER_MANGER_setValue(const timer_enu_timer_number_t copy_enu_timer_num , uint16_t copy_u16_InitialValue);

#endif /* TIMER_MANGER_H_ */
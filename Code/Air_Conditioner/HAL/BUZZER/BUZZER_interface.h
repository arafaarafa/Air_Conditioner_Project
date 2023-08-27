/**
 * @file buzzer.h
 * @brief Buzzer module interface and configuration.
 *
 * This file defines the interface for the buzzer module, including enumerations for buzzer initialization state
 * and return states, a structure for buzzer configuration, and function prototypes for initialization, starting, and stopping the buzzer.
 *
 * @date 2023-08-21
 * @author Arafa
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/DIO/DIO_interface.h"

/**
 * @brief Enumeration for buzzer initialization states.
 *
 * This enumeration defines the possible states of the buzzer module during initialization: INIT and NOT_INIT.
 */
typedef enum {
    BUZZER_INIT,        /**< Buzzer is initialized. */
    BUZZER_NOT_INIT     /**< Buzzer is not initialized. */
} buzzer_enu_state_init_t;

/**
 * @brief Structure to hold buzzer configuration.
 *
 * This structure defines the configuration parameters for a buzzer, including its port and pin.
 */
typedef struct {
    dio_enu_port_t enu_port; /**< Port of the buzzer. */
    dio_enu_pin_t enu_pin;   /**< Pin of the buzzer. */
} buzzer_str_config_t;

/**
 * @brief Enumeration for buzzer module return states.
 *
 * This enumeration defines the possible return states of buzzer module functions:
 * BUZZER_E_OK (operation successful), BUZZER_E_NOT_OK (operation not successful), and BUZZER_NULL_PTR (NULL pointer provided).
 */
typedef enum {
    BUZZER_E_OK,        /**< Operation successful. */
    BUZZER_E_NOT_OK,    /**< Operation not successful. */
    BUZZER_NULL_PTR     /**< NULL pointer provided. */
} buzzer_enu_return_state_t;

/**
 * @brief Initialize the buzzer.
 *
 * This function initializes the buzzer based on the provided configuration.
 *
 * @param[in] ptr_str_buzzer_config Pointer to the buzzer configuration structure.
 * @return Operation status: BUZZER_E_OK if successful, BUZZER_E_NOT_OK if initialization failed, BUZZER_NULL_PTR if NULL pointer provided.
 */
buzzer_enu_return_state_t BUZZER_init (buzzer_str_config_t* ptr_str_buzzer_config);

/**
 * @brief Start the buzzer.
 *
 * This function starts the buzzer by setting the associated pin to a high level.
 *
 * @return Operation status: BUZZER_E_OK if successful, BUZZER_E_NOT_OK if not initialized.
 */
buzzer_enu_return_state_t BUZZER_start(void);

/**
 * @brief Stop the buzzer.
 *
 * This function stops the buzzer by setting the associated pin to a low level.
 *
 * @return Operation status: BUZZER_E_OK if successful, BUZZER_E_NOT_OK if not initialized.
 */
buzzer_enu_return_state_t BUZZER_stop(void);
#endif /* BUZZER_H_ */
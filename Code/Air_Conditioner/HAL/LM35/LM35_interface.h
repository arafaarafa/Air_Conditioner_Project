/**
 * @file LM35_interface.h
 * @brief LM35 Temperature Sensor module interface.
 *
 * This file contains the interface and data structures for the LM35 temperature sensor module.
 *
 * @date 4/21/2023
 * @author Arafa Arafa
 */ 



#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

#include "../../MCAL/ADC/ADC_interface.h"
#define	LM35_VOLT_PER_DEGREE 0.01

/**
 * @brief Enumeration for LM35 module return states.
 */
typedef enum{
    LM35_OK,            /**< Operation successful. */
    LM35_NOK,           /**< Operation unsuccessful. */
    LM35_INVALID_PORT,  /**< Invalid port. */
    LM35_NULL_PTR       /**< Null pointer encountered. */
} lm35_enu_return_state_t;


/**
 * @brief Structure for LM35 sensor channel.
 */
typedef struct{
    adc_str_channel_config_t str_lm35_channel; /**< LM35 sensor ADC channel configuration. */
} lm35_str_channel_t;


/**
 * @brief Structure for LM35 sensor configuration.
 */
typedef struct{
    adc_str_config_t str_lm35_adc_config; /**< LM35 sensor ADC configuration. */
} lm35_str_config_t;
	


/**
 * @brief Initialize the LM35 temperature sensor.
 *
 * Initializes the LM35 temperature sensor by configuring its associated ADC channel.
 *
 * @param[in] lm35_obj Pointer to the LM35 channel object.
 * @param[in] lm35_config Pointer to the LM35 configuration.
 * @return Status of the initialization operation.
 */
lm35_enu_return_state_t LM35_init(lm35_str_channel_t *lm35_obj, lm35_str_config_t *lm35_config);

/**
 * @brief Read temperature from LM35 sensor.
 *
 * Reads the temperature from the LM35 sensor using the configured ADC channel and returns it in degrees Celsius.
 *
 * @param[in] lm35_obj Pointer to the LM35 channel object.
 * @param[in] lm35_config Pointer to the LM35 configuration.
 * @param[out] temp Pointer to store the temperature value in degrees Celsius.
 * @return Status of the temperature reading operation.
 */
lm35_enu_return_state_t LM35_read_temp(lm35_str_channel_t *lm35_obj, lm35_str_config_t *lm35_config, double *temp);

/**
 * @brief Read temperature asynchronously using callback.
 *
 * Reads the temperature from the LM35 sensor asynchronously using callback functions.
 * The ADC reading is converted to temperature using a provided conversion function.
 *
 * @param[in] lm35_obj Pointer to the LM35 channel object.
 * @param[in] lm35_config Pointer to the LM35 configuration.
 * @param[out] temp Pointer to store the temperature value in degrees Celsius.
 * @param[in] callback Callback function to initiate ADC conversion.
 * @return Status of the asynchronous temperature reading operation.
 */
lm35_enu_return_state_t LM35_read_temp_INT(lm35_str_channel_t *lm35_obj, lm35_str_config_t *lm35_config, double *temp, void(*callback)(adc_str_config_t **ptr_ptr_str_adc_config, double **ptr_ptr_do_data));

#endif /* LM35_H_ */
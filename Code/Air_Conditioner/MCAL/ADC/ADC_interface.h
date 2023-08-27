/**
 * @file ADC_interface.h
 * @brief ADC module interface.
 *
 * This file contains the interface and data structures for the ADC module.
 *
 * @date 8/22/2023
 * @author Arafa Arafa
 */ 

 #ifndef ADC_INTERFACE_H_
 #define ADC_INTERFACE_H_

#include "ADC_config.h"
#include "../DIO/DIO_interface.h"
#ifndef ADC_BIT_RESOLUTION
#error ADC bit resolution size
#endif

#ifndef ADC_EXTERNAL_VREF_VOLT
#error ADC external vref
#endif

/**
 * @brief Enumeration for ADC data adjustment selection.
 */
typedef enum{
    ADC_DATA_ADJUST_RIGHT=0, /**< Right-adjusted ADC data. */
    ADC_DATA_ADJUST_LEFT    /**< Left-adjusted ADC data. */
} adc_enu_DATA_L_R_t;
/**
 * @brief Enumeration for ADC prescaler selection.
 */

typedef enum{
	ADC_PRESCALER_2=0,
	ADC_PRESCALER_4=2,
	ADC_PRESCALER_8,
	ADC_PRESCALER_16,
	ADC_PRESCALER_32,
	ADC_PRESCALER_64,
	ADC_PRESCALER_128
}adc_enu_prescaler_t;


/**
 * @brief Enumeration for ADC voltage reference selection.
 */
typedef enum{
    ADC_INTERNAL_VREF_OFF=0,   /**< Internal voltage reference off. */
    ADC_EXTERNAL_VREF,         /**< External voltage reference. */
    ADC_INTERNAL_VREF=3        /**< Internal voltage reference. */
}adc_enu_vref_t;	


/**
 * @brief Enumeration for ADC interrupt selection.
 */
typedef enum{
    ADC_INTERRUPT_DISABLE=0, /**< ADC interrupt disabled. */
    ADC_INTERRUPT_ENABLE     /**< ADC interrupt enabled. */
} adc_enu_interrupt_t;

/**
 * @brief Enumeration for ADC module return states.
 */
typedef enum{
    ADC_OK,                /**< Operation successful. */
    ADC_INVALID_PIN,       /**< Invalid pin. */
    ADC_INVALID_PORT,      /**< Invalid port. */
    ADC_NULL_PTR           /**< Null pointer encountered. */
} adc_enu_return_state_t;

/**
 * @brief Structure for ADC configuration.
 */
typedef struct{
    adc_enu_prescaler_t adc_enu_prescaler;   /**< ADC prescaler configuration. */
    adc_enu_vref_t adc_enu_vref;             /**< ADC voltage reference configuration. */
    adc_enu_interrupt_t adc_enu_interrupt;   /**< ADC interrupt configuration. */
    adc_enu_DATA_L_R_t adc_enu_DATA_L_R;     /**< ADC data adjustment configuration. */
} adc_str_config_t;


/**
 * @brief Structure for ADC channel configuration.
 */
typedef struct{
    dio_enu_port_t enu_channel_port;    /**< Port of the ADC channel. */
    dio_enu_pin_t enu_channel_pin;      /**< Pin of the ADC channel. */
} adc_str_channel_config_t;




/**
 * @brief Initialize the ADC module.
 *
 * Initializes the ADC module with the specified configuration.
 *
 * @param[in] adc_config Pointer to the ADC configuration.
 * @return Status of the initialization operation.
 */
adc_enu_return_state_t ADC_init(adc_str_config_t *adc_config);

/**
 * @brief Initialize an ADC channel.
 *
 * Initializes an ADC channel with the specified configuration.
 *
 * @param[in] adc_channel_config Pointer to the ADC channel configuration.
 * @return Status of the channel initialization operation.
 */
adc_enu_return_state_t ADC_channel_init(adc_str_channel_config_t *adc_channel_config);


/**
 * @brief Read ADC channel.
 *
 * Reads the value from an ADC channel and converts it to voltage.
 *
 * @param[in] adc_config Pointer to the ADC configuration.
 * @param[in] adc_channel_config Pointer to the ADC channel configuration.
 * @param[out] data Pointer to store the converted voltage.
 * @return Status of the channel reading operation.
 */
adc_enu_return_state_t ADC_channel_read(adc_str_config_t *adc_config, adc_str_channel_config_t *adc_channel_config, double *data);


/**
 * @brief Read ADC channel asynchronously using callback.
 *
 * Reads the value from an ADC channel asynchronously using callback functions.
 *
 * @param[in] adc_config Pointer to the ADC configuration.
 * @param[in] adc_channel_config Pointer to the ADC channel configuration.
 * @param[in] callback Callback function to initiate ADC conversion.
 * @param[in] adc_end_ISR_func Callback function to handle ADC conversion completion.
 * @return Status of the asynchronous channel reading operation.
 */
adc_enu_return_state_t ADC_channel_read_INT(adc_str_config_t *adc_config, adc_str_channel_config_t *adc_channel_config, void(*callback)(adc_str_config_t **adc_config, double **data), void(*adc_end_ISR)(void *data));



 #endif  /* ADC_INTERFACE_H_ */
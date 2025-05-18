/**
 * @file    thermocouple_sensor.h
 * @author  Amirhossein Askari
 * @version v1.0.0
 * @date    2025-03-24
 * @email   theamiraskarii@gmail.com
 * @see     https://github.com/AmirhoseinAskari
 * @brief   Header file for thermocouple temperature-voltage conversions.
 * 
 * @details
 * Implements functions for converting temperature to voltage and vice versa
 * for thermocouple types R, S, B, J, K, E, N, and T. The conversions use polynomial
 * approximations to ensure accurate results..
 * 
 * @note
 * Ensure the correct thermocouple type is provided as input to the conversion functions.
 *  
 * @warning
 * Always verify that temperature and voltage inputs are within supported ranges
 * to ensure accurate and safe conversions
 */


#ifndef _THERMOCOUPLE_SENSOR_H
#define _THERMOCOUPLE_SENSOR_H


/* ------------------------------------- Includes ------------------------------------- */

#include <stddef.h>    ///< Defines size_t and NULL
#include <stdint.h>    ///< Fixed-width integer types
#include <math.h>      ///< Standard math library


/* -------------------------------------- Defines ------------------------------------- */

/** @brief Return value indicating that the conversion has failed */
#define  TC_CONVERSION_FAILED  -1.0e6   ///< Conversion failure return value


/* --------------------------------------- Types -------------------------------------- */

/** @brief Enumeration of supported thermocouple types */
typedef enum
{
    TC_TYPE_R = 0U,
    TC_TYPE_S,
    TC_TYPE_B,
    TC_TYPE_J,
    TC_TYPE_T,
    TC_TYPE_E,
    TC_TYPE_K,
    TC_TYPE_N,
} ThermocoupleType;

/** @brief Structure for storing polynomial coefficients */
typedef struct
{
    const double *pCoefficients;    /**< Pointer to array of coefficients */
    uint8_t length;                 /**< Number of coefficients */
} PolyCoeff;

/** @brief Structure representing a temperature or voltage range with its polynomial */
typedef struct
{
    double min;        /**< Minimum value of range */
    double max;        /**< Maximum value of range */
    PolyCoeff poly;    /**< Polynomial coefficients for this range */
} RangePoly;


/* ------------------------------------- Prototype ------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

        
/**
 * @brief  Calculates temperature from thermocouple voltage.
 *
 * @details
 * Converts a voltage reading (in millivolts) from a specified thermocouple type
 * into a temperature value (in degrees Celsius) using type-specific polynomial approximations.
 *
 * @param[in]  type     Thermocouple type (e.g., @c TC_TYPE_K, @c TC_TYPE_J) as defined in the @c ThermocoupleType enum.
 * @param[in]  voltage  Measured voltage from the thermocouple in millivolts (mV).
 * 
 * @return Calculated temperature in degrees Celsius.
 *         Returns @c TC_CONVERSION_FAILED if the voltage is out of range or if the thermocouple type is invalid.
 *
 * @note     The function uses polynomial approximations specific to each thermocouple type.
 * @warning  Ensure the @p type is valid and the input voltage is within the supported range.
 */
double TC_CalculateTemperature(ThermocoupleType type, double voltage);

/**
 * @brief  Calculates thermocouple voltage from temperature.
 *
 * @details
 * Converts a temperature value (in degrees Celsius) for a specified thermocouple type
 * into the corresponding voltage (in millivolts) using type-specific polynomial approximations.
 *
 * @param[in]  type         Thermocouple type (e.g., @c TC_TYPE_K, @c TC_TYPE_J) as defined in the @c ThermocoupleType enum.
 * @param[in]  temperature  Temperature in degrees Celsius (°C).
 * 
 * @return Calculated voltage in millivolts (mV).  
 *         Returns @c TC_CONVERSION_FAILED if the temperature is out of range or the thermocouple type is invalid.
 *
 * @note     The function uses polynomial approximations specific to each thermocouple type.
 * @warning  Ensure the @p type is valid and the input temperature is within the supported range.
 */
double TC_CalculateVoltage(ThermocoupleType type, double temperature);


#ifdef __cplusplus
}
#endif


#endif /* thermocouple_sensor.h */

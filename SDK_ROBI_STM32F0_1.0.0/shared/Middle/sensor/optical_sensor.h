/*******************************************************************************
 *
 * Copyright (c) 2019
 * Lumi, JSC.
 * All Rights Reserved
 *
 *
 * Description: Include file for application
 *
 * Author: HoangNH
 *
 * Last Changed By:  $Author: HoangNH $
 * Revision:         $Revision: 1.1 $
 * Last Changed:     $Date: 2/8/2023 $
 *
 ******************************************************************************/
#ifndef _OPTICAL_SENSOR_H_
#define _OPTICAL_SENSOR_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdint.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define IR_SENSOR_MAX	 			7
#define AVERAGE_ADC					200

typedef enum {
	ADC_READ_MODE_DMA,
	ADC_READ_MODE_POLLING
} ADC_READ_MODE;

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
extern uint16_t AdcValuesThreshold[IR_SENSOR_MAX];
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/**
 * @func   OpticalSensor_Init
 * @brief  Initializes module Reflective Optical Sensor
 * @param  None
 * @retval None
 */
void
OpticalSensor_Init(
    ADC_READ_MODE adc_read_mode
);

/**
 * @func   OpticalSensor_MeasureUseDMAMode
 * @brief  Measure value ADC in mode DMA
 * @param  None
 * @retval Value of ADC
 */
uint16_t
OpticalSensor_MeasureUseDMAMode(uint8_t irSensID);

/**
 * @func   OpticalSensor_MeasureUsePollingMode
 * @brief  Measure value ADC in mode polling
 * @param  None
 * @retval Value of ADC
 */
uint16_t
OpticalSensor_MeasureUsePollingMode(uint8_t irSensID);

/**
 * @func   OpticalSensor_SendPacketRespond
 * @brief  Respond frame value light
 * @param  value: value of light
 * @retval None
 */
void
OpticalSensor_SendPacketRespond(
	uint16_t value
);

/**
 * @func   SamplingWhite
 * @brief  Sampling White line
 * @param  None
 * @retval None
 */
void SamplingWhite(void);

/**
 * @func   SamplingBlack
 * @brief  Sampling Black Line
 * @param  None
 * @retval None
 */
void SamplingBlack(void);

/**
 * @func   Calculate_AdcThreshold
 * @brief  Calculate Threshold for per IR sensor
 * @param  None
 * @retval Threshold of per Adc Values
 */
void Calculate_AdcThreshold(void);

#endif

/* END FILE */

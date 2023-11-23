/*******************************************************************************
 *
 * Copyright (c) 2020
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
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "optical_sensor.h"
#include "serial.h"
#include "motor.h"
#include "stm32f0xx_adc.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define IRSENSOR_NUM_SAMPLING	200
#define ADC1_DR_Address    		0x40012440
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static __IO uint16_t RegularConvData_Tab[IR_SENSOR_MAX];

uint16_t AdcValues_White[IR_SENSOR_MAX];
uint16_t AdcValues_Black[IR_SENSOR_MAX];
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/**
 * @func   OpticalSensor_Init
 * @brief  Initializes module light sensor
 * @param  None
 * @retval None
 */
void
OpticalSensor_Init(
	ADC_READ_MODE adc_read_mode
) {
	ADC_InitTypeDef 	ADC_InitStructure;
	GPIO_InitTypeDef 	GPIO_InitStructure;
	DMA_InitTypeDef 	DMA_InitStructure;

	/* Enable peripheral clocks ***********************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |
								  GPIO_Pin_2 | GPIO_Pin_3 |
								  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* ADC De-initialization ***************************************************/
	ADC_DeInit(ADC1);

	/* Initialize ADC structure */
	ADC_StructInit(&ADC_InitStructure);

	/* Configure the ADC1 in continuous mode with a resolution equal to 12 bits  */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */
	ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_1, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_2, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_3, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_8, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_9, ADC_SampleTime_239_5Cycles);

	/* ADC Calibration */
	ADC_GetCalibrationFactor(ADC1);

	/* Enable the ADC peripheral */
	ADC_Cmd(ADC1, ENABLE);

	/* Wait the ADRDY flag */
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));

	/* ADC1 regular Software Start Conv */
	ADC_StartOfConversion(ADC1);

	if (adc_read_mode == ADC_READ_MODE_DMA)
	{
		/* ADC DMA request in circular mode */
		ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);

		/* Enable ADC_DMA */
		ADC_DMACmd(ADC1, ENABLE);

		/* DMA2_Stream0 channel0 configuration ********************************/
		DMA_DeInit(DMA1_Channel1);
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_BufferSize = 7;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_Init(DMA1_Channel1, &DMA_InitStructure);
		/* DMA1 Channel1 enable */
		DMA_Cmd(DMA1_Channel1, ENABLE);
	}
}

/**
 * @func   OpticalSensor_MeasureUseDMAMode
 * @brief  Measure value ADC in mode DMA
 * @param  None
 * @retval Value of ADC
 */
uint16_t
OpticalSensor_MeasureUseDMAMode(uint8_t irSensID)
{
	if (irSensID >= (sizeof(RegularConvData_Tab) / sizeof(RegularConvData_Tab[0])))
		return 0;

	return RegularConvData_Tab[irSensID];
}

/**
 * @func   OpticalSensor_MeasureUsePollingMode
 * @brief  Measure value ADC in mode polling
 * @param  None
 * @retval Value of ADC
 */
uint16_t
OpticalSensor_MeasureUsePollingMode(uint8_t irSensID)
{
	uint16_t result = 0;

	switch (irSensID) {
		case 0:
			ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_239_5Cycles);
			break;

		case 1:
			ADC_ChannelConfig(ADC1, ADC_Channel_1, ADC_SampleTime_239_5Cycles);
			break;

		case 2:
			ADC_ChannelConfig(ADC1, ADC_Channel_2, ADC_SampleTime_239_5Cycles);
			break;

		case 3:
			ADC_ChannelConfig(ADC1, ADC_Channel_3, ADC_SampleTime_239_5Cycles);
			break;

		case 4:
			ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_239_5Cycles);
			break;

		case 5:
			ADC_ChannelConfig(ADC1, ADC_Channel_8, ADC_SampleTime_239_5Cycles);
			break;

		case 6:
			ADC_ChannelConfig(ADC1, ADC_Channel_9, ADC_SampleTime_239_5Cycles);
			break;

		default:
			return 0;
			break;
	}

	// Wait for ADC conversion complete
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

	// Read value
	result = ADC_GetConversionValue(ADC1);

	return result;
}

/**
 * @func   OpticalSensor_SendPacketRespond
 * @brief  Respond frame value of optical sensor
 * @param  value: value of light
 * @retval None
 */
void
OpticalSensor_SendPacketRespond(
	uint16_t value
) {
	uint8_t byPayload[CMD_SIZE_OF_PAYLOAD_LIGHTSEN];

	byPayload[0] = (value >> 8) & 0xFFU;
	byPayload[1] = value & 0xFFU;

	/* Send message uart button press 1 time */
	Serial_SendPacket(CMD_OPT_NOT_USE,
					  CMD_ID_LIGHT_SENSOR,
					  CMD_TYPE_RES,
					  byPayload,
					  sizeof(byPayload));
}

/**
 * @func   SamplingWhite
 * @brief  Sampling White line
 * @param  None
 * @retval None
 */
void SamplingWhite(void)
{
	uint32_t sample[IR_SENSOR_MAX] = {0};

	for(uint8_t i = 0; i < IR_SENSOR_MAX; i++)
	{
		for(uint8_t j = 0; j < IRSENSOR_NUM_SAMPLING; j++)
		{
			sample[i] += OpticalSensor_MeasureUseDMAMode(i);

		}

		AdcValues_White[i] = sample[i] / IRSENSOR_NUM_SAMPLING;
	}
}

/**
 * @func   SamplingBlack
 * @brief  Sampling Black Line
 * @param  None
 * @retval None
 */
void SamplingBlack(void)
{
	uint32_t sample[IR_SENSOR_MAX] = {0};

	for(uint8_t i = 0; i < IR_SENSOR_MAX; i++)
	{
		for(uint8_t j = 0; j < IRSENSOR_NUM_SAMPLING; j++)
		{
			sample[i] += OpticalSensor_MeasureUseDMAMode(i);

		}

		AdcValues_Black[i] = sample[i] / IRSENSOR_NUM_SAMPLING;
	}
}

/**
 * @func   Calculate_AdcThreshold
 * @brief
 * @param  None
 * @retval Threshold of per Adc Values
 */
void Calculate_AdcThreshold(void)
{
	for(uint8_t i = 0; i < IR_SENSOR_MAX; i++) {
		AdcValuesThreshold[i] = ((AdcValues_White[i] + AdcValues_Black[i]) / 2);
	}
}

/* END FILE */

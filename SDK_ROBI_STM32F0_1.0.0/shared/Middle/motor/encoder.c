/*******************************************************************************
 *
 * Copyright (c) 2023
 * Lumi, JSC.
 * All Rights Reserved
 *
 * Description: Include file for application
 *
 * Author: ThaiHM
 *
 * Last Changed By:  $Author: ThaiHM $
 * Revision:         $Revision: $
 * Last Changed:     $Date: 01/08/2023 $
 *
*******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "encoder.h"
#include "timer.h"
#include "motor.h"

#include "stm32f0xx_exti.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_syscfg.h"
#include "stm32f0xx_tim.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/*! @brief Encoder parameters */
#define ENCODER_PULSE_ROUND		210   		// pulse
#define SAMPLE_TIME				1

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
/*! @brief Encoder values */
char State[16] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
char EncoderL_Val = 0;
char EncoderR_Val = 0;

volatile uint32_t encoderL_temp;
volatile uint32_t encoderR_temp;

volatile uint32_t SpeedL_1ms;
volatile uint32_t SpeedR_1ms;
static uint16_t count = 0;
bool stateEncoder = false;

static SSwTimer idTimerScanSpeed = NO_TIMER;
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
static void EncoderL_GPIO_Config(void);
static void EncoderR_GPIO_Config(void);
int16_t binaryToDecimal(int16_t binaryNumber);
static void ScanTimer(void);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/**
 * @func   Encoder_Init
 * @brief  Initializes encoder to read speed of motor
 * @param  None
 * @retval None
 */
void
Encoder_Init(void)
{
	EncoderL_GPIO_Config();
	EncoderR_GPIO_Config();
	ScanTimer();
}

/**
 * @func   Encoder1GPIO_Config
 * @brief  Configure GPIO for encoder left
 * @param  None
 * @retval None
 */
static
void EncoderL_GPIO_Config(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	EXTI_InitTypeDef			EXTI_InitStructure;
	NVIC_InitTypeDef			NVIC_InitStructure;

	/* Enable clock GPIOB */
	RCC_AHBPeriphClockCmd(Encoder_RCC_GPIO, ENABLE);

	/* Initializes GPIO Use Input */
	GPIO_InitStructure.GPIO_Pin = EncoderL1_GPIO_PIN | EncoderL2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(Encoder_GPIO_PORT, &GPIO_InitStructure);

	/* Enable Clock Syscfg, Connect EXTI Line6 to PB6 pin */
	RCC_APB2PeriphClockCmd(Encoder_SYSCFG_CLOCK, ENABLE);
	SYSCFG_EXTILineConfig(Encoder_EXTI_PORT, EncoderL1_EXTI_PinSource);

	/* Configure EXTI Line6 */
	EXTI_InitStructure.EXTI_Line =  EncoderL1_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Configure NVIC for Encoder left Interface Update Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_Init(&NVIC_InitStructure);
}

/**
 * @func   Encoder2GPIO_Config
 * @brief  Configure GPIO for encoder right
 * @param  None
 * @retval None
 */
static
void EncoderR_GPIO_Config(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	EXTI_InitTypeDef			EXTI_InitStructure;
	NVIC_InitTypeDef			NVIC_InitStructure;

	/* Enable clock GPIOB */
	RCC_AHBPeriphClockCmd(Encoder_RCC_GPIO, ENABLE);

	/* Initializes GPIO Use Input */
	GPIO_InitStructure.GPIO_Pin = EncoderR1_GPIO_PIN | EncoderR2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(Encoder_GPIO_PORT, &GPIO_InitStructure);

	/* Enable Clock Syscfg, Connect EXTI Line4 to PB4 pin */
	RCC_APB2PeriphClockCmd(Encoder_SYSCFG_CLOCK, ENABLE);
	SYSCFG_EXTILineConfig(Encoder_EXTI_PORT, EncoderR1_EXTI_PinSource);

	/* Configure EXTI Line4 */
	EXTI_InitStructure.EXTI_Line = EncoderR1_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Configure NVIC for Encoder right Interface Update Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_Init(&NVIC_InitStructure);
}

/**
 * @func   binaryToDecimal
 * @brief  Convert Binary To Decimal
 * @param  Binary Number
 * @retval Decimal Number
 */
int16_t binaryToDecimal(int16_t binaryNumber)
{
    int16_t decimalNumber = 0, i = 0, remainder;

    while (binaryNumber != 0) {
        remainder = binaryNumber % 10;
        binaryNumber /= 10;
        decimalNumber += remainder * pow(2, i);
        ++i;
    }

    return decimalNumber;
}

/**
 * @func   EXTI4_15_IRQHandler
 * @brief  Handler interrupt of encoder for count pulse
 * @param  None
 * @retval None
 */
void EXTI4_15_IRQHandler(void)
{
	/* Count Pulse Encoder Left */
	char EncoderL_pinA = GPIO_ReadInputDataBit(Encoder_GPIO_PORT, EncoderL1_GPIO_PIN);
	char EncoderL_pinB = GPIO_ReadInputDataBit(Encoder_GPIO_PORT, EncoderL2_GPIO_PIN);

	/* Handler EXTI_Line7 to PB7 */
	if(EXTI_GetFlagStatus(EncoderL1_EXTI_Line) == SET) {
		/* Pulse Noise Filtering */
		EncoderL_Val   = EncoderL_Val << 2;
		EncoderL_Val   = (( EncoderL_pinA | EncoderL_pinB) | EncoderL_Val ) & 0x0f;
		encoderL_temp += State[binaryToDecimal(EncoderL_Val)];

		EXTI_ClearITPendingBit(EncoderL1_EXTI_Line);
	}

	/* Count Pulse Encoder Right */
	char EncoderR_pinA = GPIO_ReadInputDataBit(Encoder_GPIO_PORT, EncoderR1_GPIO_PIN);
	char EncoderR_pinB = GPIO_ReadInputDataBit(Encoder_GPIO_PORT, EncoderR2_GPIO_PIN);

	/* Handler EXTI_Line5 to PB5 */
	if(EXTI_GetFlagStatus(EncoderR1_EXTI_Line) == SET) {
		/* Pulse Noise Filtering */
		EncoderR_Val   = EncoderR_Val << 2;
		EncoderR_Val   = (( EncoderR_pinA | EncoderR_pinB) | EncoderR_Val ) & 0x0f;
		encoderR_temp += State[binaryToDecimal(EncoderR_Val)];

		EXTI_ClearITPendingBit(EncoderR1_EXTI_Line);
	}
}

/**
 * @func   CalculateSpeed
 * @brief  Calculate speed encoder
 * @param  None
 * @retval None
 */
static
void CalculateSpeed(void *arg)
{
	/* Calculate speed encoder in 1ms */
	if (stateEncoder == false) {
		SpeedL_1ms += (uint32_t)((encoderL_temp * 1000) / ENCODER_PULSE_ROUND);	// v/s
		SpeedR_1ms += (uint32_t)((encoderR_temp * 1000) / ENCODER_PULSE_ROUND);	// v/s
		count++;

		/* Calculate speed encoder in 4ms */
		if(count >= 5) {
			stateEncoder = true;
			encoderL_speed = (uint32_t)(SpeedL_1ms / count);	// v/s
			encoderR_speed = (uint32_t)(SpeedR_1ms / count);	// v/s

			/* Reset Count Pulse, Speed, Count */
			encoderL_temp = 0;
			encoderR_temp = 0;
			SpeedL_1ms = 0;
			SpeedR_1ms = 0;
			count = 0;
		}
	}
}

/**
 * @func   ScanTimer
 * @brief  Scan timer for calculate speed
 * @param  None
 * @retval None
 */
static
void ScanTimer(void)
{
	if(idTimerScanSpeed != NO_TIMER) {
		TimerStop(idTimerScanSpeed);
		idTimerScanSpeed = NO_TIMER;
	}

	idTimerScanSpeed = TimerStart("CalculateSpeed", 	\
								  SAMPLE_TIME, 			\
								  TIMER_REPEAT_FOREVER, \
							 	  CalculateSpeed,       \
								  NULL);
}

/* END_FILE */

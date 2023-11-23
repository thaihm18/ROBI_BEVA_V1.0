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
#ifndef _ENCODER_H_
#define _ENCODER_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/*! @brief Encoder Pins */
#define Encoder_GPIO_PORT				GPIOB
#define Encoder_RCC_GPIO         		RCC_AHBPeriph_GPIOB
#define Encoder_EXTI_PORT				EXTI_PortSourceGPIOB
#define Encoder_SYSCFG_CLOCK			RCC_APB2Periph_SYSCFG

#define EncoderR1_GPIO_PIN				GPIO_Pin_5
#define EncoderR1_EXTI_PinSource		EXTI_PinSource5
#define EncoderR1_EXTI_Line				EXTI_Line5

#define EncoderR2_GPIO_PIN				GPIO_Pin_4
#define EncoderR2_EXTI_PinSource		EXTI_PinSource4
#define EncoderR2_EXTI_Line				EXTI_Line4

#define EncoderL1_GPIO_PIN				GPIO_Pin_7
#define EncoderL1_EXTI_PinSource		EXTI_PinSource7
#define EncoderL1_EXTI_Line				EXTI_Line7

#define EncoderL2_GPIO_PIN				GPIO_Pin_6
#define EncoderL2_EXTI_PinSource		EXTI_PinSource6
#define EncoderL2_EXTI_Line				EXTI_Line6

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
extern volatile uint32_t encoderL_speed;
extern volatile uint32_t encoderR_speed;
extern bool stateEncoder;
extern int16_t dutyCycle_L;
extern int16_t dutyCycle_R;
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
Encoder_Init(void);

#endif

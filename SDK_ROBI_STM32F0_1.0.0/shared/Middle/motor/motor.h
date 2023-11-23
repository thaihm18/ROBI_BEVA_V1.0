/*******************************************************************************
 *
 * Copyright (c) 2023
 * Lumi, JSC.
 * All Rights Reserved
 *
 * Description: Include file for application
 *
 * Author: HoangNH
 *
 * Last Changed By:  $Author: HoangNH $
 * Revision:         $Revision: $
 * Last Changed:     $Date: 01/08/2023 $
 *
*******************************************************************************/
#ifndef _MOTOR_H_
#define _MOTOR_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdint.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/*! @brief Motor Right Pins */
#define MotorR1_RCC_GPIO         		RCC_AHBPeriph_GPIOB
#define MotorR1_RCC_TIM          		RCC_APB2Periph_TIM15
#define MotorR1_GPIO_PORT               GPIOB
#define MotorR1_GPIO_PIN				GPIO_Pin_15
#define MotorR1_GPIO_AF          		GPIO_AF_1
#define MotorR1_PinSource				GPIO_PinSource15
#define MotorR1_TIM						TIM15

#define MotorR2_RCC_GPIO         		RCC_AHBPeriph_GPIOA
#define MotorR2_RCC_TIM         	 	RCC_APB2Periph_TIM1
#define MotorR2_GPIO_PORT				GPIOA
#define MotorR2_GPIO_PIN				GPIO_Pin_8
#define MotorR2_PinSource				GPIO_PinSource8
#define MotorR2_GPIO_AF          		GPIO_AF_2
#define MotorR2_TIM						TIM1

/*! @brief Motor Left Pins */
#define MotorL_RCC_GPIO         		RCC_AHBPeriph_GPIOB
#define MotorL_GPIO_PORT				GPIOB
#define MotorL_GPIO_AF          		GPIO_AF_2

#define MotorL1_RCC_TIM          		RCC_APB2Periph_TIM16

#define MotorL1_GPIO_PIN				GPIO_Pin_8
#define MotorL1_PinSource				GPIO_PinSource8
#define MotorL1_TIM						TIM16


#define MotorL2_RCC_TIM          		RCC_APB2Periph_TIM17
#define MotorL2_GPIO_PIN				GPIO_Pin_9
#define MotorL2_PinSource				GPIO_PinSource9
#define MotorL2_TIM						TIM17

/*! @brief Motor ID */
typedef enum _MOTOR_ID_ {
	MOTOR_ID_L,
	MOTOR_ID_R,
	MOTOR_ID_MAX
} motor_id_e;

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/**
 * @func   MotorControl_Init
 * @brief  Initializes module motor
 * @param  None
 * @retval None
 */
void MotorControl_Init(void);

/**
 * @func   MotorControl_ForwardRotating
 * @brief  Setup forward rotation motor x
 * @param  id:
 *         dutycycle:
 * @retval None
 */
void MotorControl_ForwardRotating(motor_id_e id, uint32_t compare);

/**
 * @func   Motor1Control_ReverseRotating
 * @brief  Setup reverse rotation motor x
 * @param  id:
 *         dutycycle:
 * @retval None
 */
void MotorControl_ReverseRotating(motor_id_e id, uint32_t compare);

#endif

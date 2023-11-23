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
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "motor.h"
#include "encoder.h"

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_tim.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define MOTOR_PWM_FREQUENCY     1000 // 1 kHz

#define MOTOR_TIM_PRESCALE      48
#define MOTOR_TIMER_RCC_FREQ    48000000
#define MOTOR_TIM_PERIOD        (MOTOR_TIMER_RCC_FREQ / (MOTOR_TIM_PRESCALE * MOTOR_PWM_FREQUENCY))

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
static void ML_GPIO_Config(void);
static void MR_GPIO_Config(void);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/**
 * @func   MotorControl_Init
 * @brief  Initializes module motor
 * @param  None
 * @retval None
 */
void
MotorControl_Init(void)
{
	// Initialize pins GPIO motor
	ML_GPIO_Config();
	MR_GPIO_Config();
}

/**
 * @func   MR_GPIO_Config
 * @brief  Configure GPIO for motor right
 * @param  None
 * @retval None
 */
static
void MR_GPIO_Config(void) {
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef 			TIM_OCInitStructure;

	/* Enable clock GPIOB, GPIOA */
	RCC_AHBPeriphClockCmd(MotorR1_RCC_GPIO | MotorR2_RCC_GPIO, ENABLE);

	/* Initializes GPIO Use Output Compare */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* GPIOB Configuration as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = MotorR1_GPIO_PIN;
	GPIO_Init(MotorR1_GPIO_PORT, &GPIO_InitStructure);

	/* GPIOA Configuration as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = MotorR2_GPIO_PIN;
	GPIO_Init(MotorR2_GPIO_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(MotorR1_GPIO_PORT, MotorR1_PinSource, MotorR1_GPIO_AF);
	GPIO_PinAFConfig(MotorR2_GPIO_PORT, MotorR2_PinSource, MotorR2_GPIO_AF);

	/* Enable TIM1, TIM15 clock */
	RCC_APB2PeriphClockCmd(MotorR1_RCC_TIM, ENABLE);
	RCC_APB2PeriphClockCmd(MotorR2_RCC_TIM, ENABLE);

	/* Initializes Use Timer Base */
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Prescaler = MOTOR_TIM_PRESCALE - 1;
	TIM_TimeBaseInitStructure.TIM_Period = MOTOR_TIM_PERIOD - 1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(MotorR1_TIM, &TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(MotorR2_TIM, &TIM_TimeBaseInitStructure);

	//Timer OC Configure
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_Pulse = 0;

	TIM_OC2Init(MotorR1_TIM, &TIM_OCInitStructure);
	TIM_OC1Init(MotorR2_TIM, &TIM_OCInitStructure);

	TIM_Cmd(MotorR1_TIM, ENABLE);
	TIM_Cmd(MotorR2_TIM, ENABLE);

	TIM_CtrlPWMOutputs(MotorR1_TIM, ENABLE);
	TIM_CtrlPWMOutputs(MotorR2_TIM, ENABLE);
}

/**
 * @func   ML_GPIO_Config
 * @brief  Configure GPIO for motor left
 * @param  None
 * @retval None
 */
static void ML_GPIO_Config(void) {
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef			TIM_OCInitStructure;

	/* Enable clock GPIOB */
	RCC_AHBPeriphClockCmd(MotorL_RCC_GPIO, ENABLE);

	/* Initializes GPIO Use Output Compare */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* GPIOB Configuration as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = MotorL1_GPIO_PIN | MotorL2_GPIO_PIN;
	GPIO_Init(MotorL_GPIO_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(MotorL_GPIO_PORT, MotorL1_PinSource, MotorL_GPIO_AF);
	GPIO_PinAFConfig(MotorL_GPIO_PORT, MotorL2_PinSource, MotorL_GPIO_AF);

	/* Enable TIM16, TIM17 clock */
	RCC_APB2PeriphClockCmd(MotorL1_RCC_TIM, ENABLE);
	RCC_APB2PeriphClockCmd(MotorL2_RCC_TIM, ENABLE);

	/* Initializes Use Timer Base */
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Prescaler = MOTOR_TIM_PRESCALE - 1;
	TIM_TimeBaseInitStructure.TIM_Period = MOTOR_TIM_PERIOD - 1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(MotorL1_TIM, &TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(MotorL2_TIM, &TIM_TimeBaseInitStructure);

	//Timer OC Configure
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_Pulse = 0;

	TIM_OC1Init(MotorL1_TIM, &TIM_OCInitStructure);
	TIM_OC1Init(MotorL2_TIM, &TIM_OCInitStructure);

	TIM_Cmd(MotorL1_TIM, ENABLE);
	TIM_Cmd(MotorL2_TIM, ENABLE);

	TIM_CtrlPWMOutputs(MotorL1_TIM, ENABLE);
	TIM_CtrlPWMOutputs(MotorL2_TIM, ENABLE);
}

/**
 * @func   MotorControl_ForwardRotating
 * @brief  Setup forward rotation motor x
 * @param  id:
 *         dutycycle:
 * @retval None
 */
void MotorControl_ForwardRotating(motor_id_e id, uint32_t dutycycle)
{
	uint32_t compare;

	switch (id) {
		case MOTOR_ID_L:
			compare = (dutycycle * MOTOR_TIM_PERIOD) / 100;
			TIM_SetCounter(MotorL1_TIM, 0);
			TIM_SetCounter(MotorL2_TIM, 0);
			TIM_SetCompare1(MotorL1_TIM, compare);
			TIM_SetCompare1(MotorL2_TIM, 0);
			break;

		case MOTOR_ID_R:
			compare = (dutycycle * MOTOR_TIM_PERIOD) / 100;
			TIM_SetCounter(MotorR1_TIM, 0);
			TIM_SetCounter(MotorR2_TIM, 0);
			TIM_SetCompare1(MotorR2_TIM, compare);
			TIM_SetCompare2(MotorR1_TIM, 0);
			break;

		default:
			break;
	}
}

/**
 * @func   Motor1Control_ReverseRotating
 * @brief  Setup reverse rotation motor x
 * @param  id:
 *         dutycycle:
 * @retval None
 */
void MotorControl_ReverseRotating(motor_id_e id, uint32_t dutycycle)
{
	uint32_t compare;

	switch (id) {
		case MOTOR_ID_L:
			compare = (dutycycle * MOTOR_TIM_PERIOD) / 100;
			TIM_SetCounter(MotorL1_TIM, 0);
			TIM_SetCounter(MotorL2_TIM, 0);
			TIM_SetCompare1(MotorL2_TIM, compare);
			TIM_SetCompare1(MotorL1_TIM, 0);
			break;

		case MOTOR_ID_R:
			compare = (dutycycle * MOTOR_TIM_PERIOD) / 100;
			TIM_SetCounter(MotorR1_TIM, 0);
			TIM_SetCounter(MotorR2_TIM, 0);
			TIM_SetCompare2(MotorR1_TIM, compare);
			TIM_SetCompare1(MotorR2_TIM, 0);
			break;

		default:
			break;
	}
}

/* END_FILE */

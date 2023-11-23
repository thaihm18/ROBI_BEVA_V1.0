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
 * Last Changed:     $Date: 22/11/2023 $
 *
*******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "pid.h"
#include "motor.h"
#include "optical_sensor.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/*@brief ADC Threshold values */
uint16_t AdcValuesThreshold[IR_SENSOR_MAX];

/*@brief PID values */
int P, I, D;
int previousError, error;
float PIDvalue = 0;
float Kp = 0.0;
float Ki = 0.0;
float Kd = 0.0;
int lfspeed = 20;
int lsp, rsp;
uint8_t count = 0;

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/**
 * @func   LineFollow
 * @brief
 * @param  None
 * @retval None
 */
void LineFollow(void)
{
	/* IR sensor is in the leftmost position */
    if (OpticalSensor_MeasureUseDMAMode(0) > AdcValuesThreshold[0] &&
		OpticalSensor_MeasureUseDMAMode(6) < AdcValuesThreshold[6])
    {
    	/* Turn left */
		MotorControl_ForwardRotating(MOTOR_ID_R, 25);
		MotorControl_ReverseRotating(MOTOR_ID_L, 25);

    }

    /* IR sensor is in the rightmost position */
    else if (OpticalSensor_MeasureUseDMAMode(0) < AdcValuesThreshold[0] &&
    		 OpticalSensor_MeasureUseDMAMode(6) > AdcValuesThreshold[6])
    {
    	/* Turn right */
		MotorControl_ReverseRotating(MOTOR_ID_R, 25);
		MotorControl_ForwardRotating(MOTOR_ID_L, 25);
    }

    /* IR sensor is in the center position */
    else if (OpticalSensor_MeasureUseDMAMode(3) > AdcValuesThreshold[3])
    {
    	/* Calculate Kp, Ki, Kd used to Follow Line */
		Kp = 0.00001 * (1000 - OpticalSensor_MeasureUseDMAMode(3));
		Kd = 50 * Kp;
//      Ki = 0.0000001;
		PID_Control();
    }
}

/**
 * @func   PID_Control
 * @brief
 * @param  None
 * @retval None
 */
void PID_Control(void)
{
	/* Calculate error */
	int error = (OpticalSensor_MeasureUseDMAMode(1) - OpticalSensor_MeasureUseDMAMode(5));

	P =  error;
	I += error;
	D =  error - previousError;

	PIDvalue = ((Kp * P) + (Ki * I) + (Kd * D));
	previousError = error;

	lsp = lfspeed - PIDvalue;
	rsp = lfspeed + PIDvalue;

	if (lsp > 100) 	lsp = 100;

	if (lsp < 0) 	lsp = 0;

	if (rsp > 100) 	rsp = 100;

	if (rsp < 0) 	rsp = 0;

	MotorControl_ForwardRotating(MOTOR_ID_R, rsp);
	MotorControl_ForwardRotating(MOTOR_ID_L, lsp);
}

/**
 * @func   Check_InLine
 * @brief  Check IR sensor In Line or Out Line
 * @param  None
 * @retval Number IR sensor In Line and Out Line
 */
uint8_t Check_InLine(void)
{
	for(uint8_t i = 0; i < IR_SENSOR_MAX; i++){
		if(OpticalSensor_MeasureUseDMAMode(i) > AdcValuesThreshold[i]) {
			count++;
		}
		else {
			count--;
		}
	}

	if (count == 6 || count == -6){
		count = 0;
		return 1;
	}
	else {
		count = 0;
		return 0;
	}
}

/**
 * @func   Motor_Control
 * @brief
 * @param  None
 * @retval None
 */
void MotorControl_PID(void)
{
	if (Check_InLine()){
		if (previousError > 0) {
			MotorControl_ForwardRotating(MOTOR_ID_R, 40);
			MotorControl_ForwardRotating(MOTOR_ID_L, 0);
		}

		else if (previousError < 0) {
			MotorControl_ForwardRotating(MOTOR_ID_R, 0);
			MotorControl_ForwardRotating(MOTOR_ID_L, 40);
		}
	}

	else {
		LineFollow();
	}
}

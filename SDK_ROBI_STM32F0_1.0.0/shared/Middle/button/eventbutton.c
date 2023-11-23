/*******************************************************************************
 *
 * Copyright (c) 2020
 * Lumi, JSC.
 * All Rights Reserved
 *
 * Description:
 *
 * Author: HoangNH
 *
 * Last Changed By:  $Author: HoangNH $
 * Revision:         $Revision: 1.1 $
 * Last Changed:     $Date: 10/07/20 $
 *
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "button.h"
#include "eventbutton.h"
#include "eventman.h"
#include "serial.h"
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
static void ButtonProcessEventEdge(uint8_t btnID, uint16_t edge);
static void ButtonProcessEventPress(uint8_t btnID, uint16_t times);
static void ButtonProcessEventHold(uint8_t btnID, uint16_t time);
static void ButtonProcessEventRelease(uint8_t btnID, uint16_t time);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/**
 * @func   EventButton_Init
 * @brief  Initialize events of button
 * @param  pFuncAppProcEvent: funtion callback
 * @retval None
 */
void
EventButton_Init(void) {
    /* Init callback functions */
	Button_RegisterEventCallback(BUTTON_EVENT_EDGE, ButtonProcessEventEdge);
	Button_RegisterEventCallback(BUTTON_EVENT_PRESS, ButtonProcessEventPress);
	Button_RegisterEventCallback(BUTTON_EVENT_HOLD, ButtonProcessEventHold);
	Button_RegisterEventCallback(BUTTON_EVENT_RELEASE, ButtonProcessEventRelease);

    Button_Init();
}

/**
 * @func   ButtonProcessEventEdge
 * @brief  Event edge pulse
 * @param  btnID
 * @param  edge
 * @retval None
 */
static void 
ButtonProcessEventEdge(
    uint8_t btnID,
    uint16_t edge
) {
	uint8_t event;

    if (edge == BUTTON_EDGE_RISING)
    {
    	event = EVENT_OF_BUTTON_BACK_PRESS_EDGE_RISING + btnID;
    }
    else /* (edge == BUTTON_EDGE_FAILING) */
    {
    	event = EVENT_OF_BUTTON_BACK_PRESS_EDGE_FALLING + btnID;
    }

    EventSchedulerAdd(event);
}

/**
 * @func   InputProcessEventPress
 * @brief  Event logic level
 * @param  btnID
 * @param  time
 * @retval None
 */
static void 
ButtonProcessEventPress(
    uint8_t btnID,
    uint16_t times
) {
	uint8_t event;

	if (times == 1)
	{
		event = EVENT_OF_BUTTON_BACK_PRESS_LOGIC + btnID;
	}
	else if (times == 2)
	{
		event = EVENT_OF_BUTTON_BACK_PRESS_2_TIMES + btnID;
	}
	else if (times == 3)
	{
		event = EVENT_OF_BUTTON_BACK_PRESS_3_TIMES + btnID;
	}
	else if (times == 4)
	{
		event = EVENT_OF_BUTTON_BACK_PRESS_4_TIMES + btnID;
	}
	else if (times == 5)
	{
		event = EVENT_OF_BUTTON_BACK_PRESS_5_TIMES + btnID;
	}
	else return;

    EventSchedulerAdd(event);
}

/**
 * @func   InputProcessEventHold
 * @brief  Event hold
 * @param  butt
 * @param  time
 * @retval None
 */
static void 
ButtonProcessEventHold(
    uint8_t btnID,
    uint16_t time
) {
	uint8_t event;

	if (time == TIMECNT_HOLD10S)
	{
		event = EVENT_OF_BUTTON_BACK_HOLD_10S + btnID;
	}
	else if (time == TIMECNT_HOLD5S)
	{
		event = EVENT_OF_BUTTON_BACK_HOLD_5S + btnID;
	}
	else if (time == TIMECNT_HOLD3S)
	{
		event = EVENT_OF_BUTTON_BACK_HOLD_3S + btnID;
	}
	else if (time == TIMECNT_HOLD1S)
	{
		event = EVENT_OF_BUTTON_BACK_HOLD_1S + btnID;
	}
	else return;

	EventSchedulerAdd(event);
}

/**
 * @func   InputProcessEventRelease
 * @brief  Event release
 * @param  butt
 * @param  time
 * @retval None
 */
static void 
ButtonProcessEventRelease(
    uint8_t btnID,
    uint16_t time
) {
	uint8_t event;

	if (time >= TIMECNT_HOLD10S)
	{
		event = EVENT_OF_BUTTON_BACK_RELEASED_10S + btnID;
	}
	else if (time >= TIMECNT_HOLD5S)
	{
		event = EVENT_OF_BUTTON_BACK_RELEASED_5S + btnID;
	}
	else if (time >= TIMECNT_HOLD3S)
	{
		event = EVENT_OF_BUTTON_BACK_RELEASED_3S + btnID;
	}
	else if (time >= TIMECNT_HOLD1S)
	{
		event = EVENT_OF_BUTTON_BACK_RELEASED_1S + btnID;
	}
	else return;

	EventSchedulerAdd(event);
}

/**
 * @func   Button_SendPacketRespond
 * @brief  Respond frame state of button
 * @param  button_id: id of button
 *         button_state: state of button
 * @retval None
 */
void
Button_SendPacketRespond(
	uint8_t button_id,
	uint8_t button_state
) {
	uint8_t byPayload[CMD_SIZE_OF_PAYLOAD_BUTTON];

	byPayload[0] = button_id + 1;
	byPayload[1] = button_state;

	/* Send message uart button */
	Serial_SendPacket(CMD_OPT_NOT_USE,
					  CMD_ID_BUTTON,
					  CMD_TYPE_RES,
					  byPayload,
					  sizeof(byPayload));
}

/* END FILE */

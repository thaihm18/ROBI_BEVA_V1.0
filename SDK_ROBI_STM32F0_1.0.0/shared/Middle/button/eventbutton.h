/*******************************************************************************
 *
 * Copyright (c) 2020
 * Lumi, JSC.
 * All Rights Reserved
 *
 * Description: Include file for application
 *
 * Author: HoangNH
 *
 * Last Changed By:  $Author: HoangNH $
 * Revision:         $Revision: 1.1 $
 * Last Changed:     $Date: 10/07/20 $
 *
 ******************************************************************************/
#ifndef _EVENT_BUTTON_H_
#define _EVENT_BUTTON_H_ 
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdint.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/*! @brief Defines events for the application */
typedef enum {
	EVENT_OF_BUTTON_BACK_PRESS_EDGE_RISING,
	EVENT_OF_BUTTON_ENTER_PRESS_EDGE_RISING,
	EVENT_OF_BUTTON_NEXT_PRESS_EDGE_RISING,

	EVENT_OF_BUTTON_BACK_PRESS_EDGE_FALLING,
	EVENT_OF_BUTTON_ENTER_PRESS_EDGE_FALLING,
	EVENT_OF_BUTTON_NEXT_PRESS_EDGE_FALLING,

    EVENT_OF_BUTTON_BACK_PRESS_LOGIC,
    EVENT_OF_BUTTON_ENTER_PRESS_LOGIC,
    EVENT_OF_BUTTON_NEXT_PRESS_LOGIC,

    EVENT_OF_BUTTON_BACK_PRESS_2_TIMES,
    EVENT_OF_BUTTON_ENTER_PRESS_2_TIMES,
    EVENT_OF_BUTTON_NEXT_PRESS_2_TIMES,

	EVENT_OF_BUTTON_BACK_PRESS_3_TIMES,
	EVENT_OF_BUTTON_ENTER_PRESS_3_TIMES,
	EVENT_OF_BUTTON_NEXT_PRESS_3_TIMES,

	EVENT_OF_BUTTON_BACK_PRESS_4_TIMES,
	EVENT_OF_BUTTON_ENTER_PRESS_4_TIMES,
	EVENT_OF_BUTTON_NEXT_PRESS_4_TIMES,

    EVENT_OF_BUTTON_BACK_PRESS_5_TIMES,
    EVENT_OF_BUTTON_ENTER_PRESS_5_TIMES,
    EVENT_OF_BUTTON_NEXT_PRESS_5_TIMES,

    EVENT_OF_BUTTON_BACK_HOLD_1S,
	EVENT_OF_BUTTON_ENTER_HOLD_1S,
	EVENT_OF_BUTTON_NEXT_HOLD_1S,

    EVENT_OF_BUTTON_BACK_HOLD_3S,
	EVENT_OF_BUTTON_ENTER_HOLD_3S,
	EVENT_OF_BUTTON_NEXT_HOLD_3S,

    EVENT_OF_BUTTON_BACK_HOLD_5S,
	EVENT_OF_BUTTON_ENTER_HOLD_5S,
	EVENT_OF_BUTTON_NEXT_HOLD_5S,

    EVENT_OF_BUTTON_BACK_HOLD_10S,
	EVENT_OF_BUTTON_ENTER_HOLD_10S,
	EVENT_OF_BUTTON_NEXT_HOLD_10S,

    EVENT_OF_BUTTON_BACK_RELEASED_1S,
    EVENT_OF_BUTTON_ENTER_RELEASED_1S,
    EVENT_OF_BUTTON_NEXT_RELEASED_1S,

    EVENT_OF_BUTTON_BACK_RELEASED_3S,
    EVENT_OF_BUTTON_ENTER_RELEASED_3S,
    EVENT_OF_BUTTON_NEXT_RELEASED_3S,

    EVENT_OF_BUTTON_BACK_RELEASED_5S,
    EVENT_OF_BUTTON_ENTER_RELEASED_5S,
    EVENT_OF_BUTTON_NEXT_RELEASED_5S,

    EVENT_OF_BUTTON_BACK_RELEASED_10S,
    EVENT_OF_BUTTON_ENTER_RELEASED_10S,
    EVENT_OF_BUTTON_NEXT_RELEASED_10S,
} event_button_t, *event_button_p;

/*! @brief Button state */
#define BUTTON_PRESSED_1_TIME       0x01u
#define BUTTON_PRESSED_2_TIMES      0x02u
#define BUTTON_PRESSED_3_TIMES      0x03u
#define BUTTON_PRESSED_4_TIMES      0x04u
#define BUTTON_PRESSED_5_TIMES      0x05u
#define BUTTON_IS_RELEASED          0x10u
#define BUTTON_IS_HELD_DOWN         0x11u
#define BUTTON_IS_HOLD_3s           0x12u
#define BUTTON_IS_HOLD_5s           0x13u
#define BUTTON_IS_HOLD_7s           0x14u
#define BUTTON_IS_HOLD_10s          0x15u
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
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
 * @func   EventButton_Init
 * @brief  Initializes events of button
 * @param  None
 * @retval None
 */
void
EventButton_Init(void);

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
);

#endif

/* END FILE */

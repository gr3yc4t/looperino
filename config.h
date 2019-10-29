/**
 * @author gr3yc4t@protonmail.com
 * 
 * @brief Contains configuration of pins and other things
 * 
 * 
 */


#ifndef CONFIG_H_GUARD
#define CONFIG_H_GUARD


//----------------- COMPILATOR -------------------
#define DEBUG
#define BLUETOOTH 0     //No bluetooth support
#define INPUTS 0        //No input is enabled, like loop number or tap tempo


//---------------------------------------------------
//------------ BUTTONS  -----------------------------
//---------------------------------------------------

#define REC_BTN 31
#define STOP_BTN 30
#define UNDO_BTN 6
#define NEXT_BTN 40
#define EDIT_BTN 34
#define SOLO_BTN 7



#define BLUETOOTH_SWITCH 1

//--------------------- LED ------------------------

#define REC_LED 4
#define OVERDUB_LED 10
#define TEMPO_LED 12
#define HOLD_LED 2



#define HOLD_BTN  22
#define TAP_TEMPO_BTN 12
#define LOOP_NUM_INPUT 24


//--------------- OTHER --------------------------

#define MAX_LOOP 32

#define HOLD_TIME 2000

#define INITIAL_LOOP_NUMBER 6

#endif
/**
 * @brief Manages button initialization 
 * @author gr3yc4t@protonmail.com
 */

#ifndef BUTTONS_H_GUARD
#define BUTTONS_H_GUARD


#include "config.h"     //For retrieving button's pins
#include "hold.h"       //For initializing BUTTONS_H_GUARD



BounceHeld recBounce = BounceHeld(750); // Instantiate a Bounce object
BounceHeld stopBounce = BounceHeld(1000); // Held for 1 sec
BounceHeld nextBounce = BounceHeld(800); // Instantiate a Bounce object
BounceHeld editBounce = BounceHeld(800); // Instantiate a Bounce object
BounceHeld undoBounce = BounceHeld(2000); // Held for 2 sec
BounceHeld soloBounce = BounceHeld(1500); // Instantiate a Bounce object

BounceHeld holdBounce = BounceHeld(1500); // Instantiate a Bounce object
Bounce loopInputBounce = Bounce(); // Instantiate a Bounce object
Bounce tapTempoBounce = Bounce();


void setPinMode();
void enableBounce();
void updateButtons();


/**
 * @brief Initialize both pins and Bounce 
 * Initialize pins in "config.h" as INPUT and create the Bounce object
 */
void initializeButtons(){

    setPinMode();   

    enableBounce();

}

/**
 *  @brief Setup the pin mode of station's components
 */

void setPinMode(){
    //------------------------------------------------------
    pinMode(REC_BTN, INPUT);
    digitalWrite(REC_BTN, LOW);
    pinMode(STOP_BTN, INPUT);
    digitalWrite(STOP_BTN, LOW);
    pinMode(NEXT_BTN, INPUT);
    digitalWrite(NEXT_BTN, LOW);
    pinMode(SOLO_BTN, INPUT);
    digitalWrite(SOLO_BTN, LOW);
    pinMode(UNDO_BTN, INPUT);
    digitalWrite(UNDO_BTN, LOW);
    //-----------------------------------------------------

    pinMode(EDIT_BTN, INPUT);
    digitalWrite(EDIT_BTN, LOW);

    #if INPUTS
    pinMode(HOLD_BTN, INPUT);
    digitalWrite(HOLD_BTN, LOW);
    pinMode(LOOP_NUM_INPUT, INPUT);
    digitalWrite(LOOP_NUM_INPUT, LOW);
    pinMode(TAP_TEMPO_BTN, INPUT);
    digitalWrite(TAP_TEMPO_BTN, LOW);
    #endif
}

/**
 * @brief Setup the anti-bounce paraments
 */
void enableBounce(){

    recBounce.attach(REC_BTN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
    stopBounce.attach(STOP_BTN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
    nextBounce.attach(NEXT_BTN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
    soloBounce.attach(SOLO_BTN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
    undoBounce.attach(UNDO_BTN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
    
    
    editBounce.attach(EDIT_BTN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode


    recBounce.interval(10); // 10 milliseconds
    stopBounce.interval(15); // Use a debounce interval of 25 milliseconds
    nextBounce.interval(25); // Use a debounce interval of 25 milliseconds
    editBounce.interval(25); // Use a debounce interval of 25 milliseconds
    undoBounce.interval(50); // Use a debounce interval of 25 milliseconds
    soloBounce.interval(25); // Use a debounce interval of 25 milliseconds

    #if INPUTS
    holdBounce.attach(HOLD_BTN, INPUT_PULLUP);
    loopInputBounce.attach(LOOP_NUM_INPUT, INPUT_PULLUP);
    tapTempoBounce.attach(TAP_TEMPO_BTN, INPUT_PULLUP);

    holdBounce.interval(30);
    loopInputBounce.interval(10);
    tapTempoBounce.interval(10);
    #endif
}

/**
 * @brief Updates buttons status. 
 * This fuction must be called every loop in order to detect button pression/hold.
 */
void updateButtons(){
    recBounce.update();
    stopBounce.update();
    nextBounce.update();
    soloBounce.update();
    undoBounce.update();
    editBounce.update();

    #if INPUTS
    holdBounce.update();
    #endif
}

#endif
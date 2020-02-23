



/**
 * MIDI Looper main file
 * 
 * @author gr3yc4t@protonmail.com
 * 
 */

#include <Bounce2.h>
#include <jled.h>


#define BOUNCE_WITH_PROMPT_DETECTION

//----------------- COMPILATOR -------------------
//#define DEBUG
#define BLUETOOTH 0     //No bluetooth support
#define INPUTS 0        //No input is enabled, like loop number or tap tempo
#define DISPLAY_OLED 1


//Load Configs
#include "config.h"

#include "buttons.h"
#include "debug.h"
#include "looper.h"
#include "hold.h"


#if INPUTS
#include "input.h"
#endif

#if BLUETOOTH
#include "bluetooth.h"
#endif

#if DISPLAY_OLED
#include "display.h"
#endif


uint8_t active_loop;
uint8_t selected_loop[MAX_LOOP];
uint8_t selected_loop_count;


int active_rec; //1 if REC is running


BounceHeld recBounce = BounceHeld(750); // Instantiate a Bounce object

BounceHeld stopBounce = BounceHeld(1000); // Held for 1 sec
BounceHeld nextBounce = BounceHeld(800); // Instantiate a Bounce object
BounceHeld editBounce = BounceHeld(800); // Instantiate a Bounce object
BounceHeld undoBounce = BounceHeld(2000); // Held for 2 sec
BounceHeld soloBounce = BounceHeld(1500); // Instantiate a Bounce object

#if INPUTS
BounceHeld holdBounce = BounceHeld(1500); // Instantiate a Bounce object
Bounce loopInputBounce = Bounce(); // Instantiate a Bounce object
Bounce tapTempoBounce = Bounce();
#endif


auto recLed = JLed(REC_LED).Blink(200, 200).Forever();
auto overdubLed = JLed(OVERDUB_LED).Blink(400, 200).Forever();


Looper looper = Looper(1, INITIAL_LOOP_NUMBER); //Start the loop object

#if INPUTS
LooperInput numInput = LooperInput();
TapTempo tapTempo = TapTempo(TAP_TEMPO_BTN, TEMPO_LED);
#endif

#if DISPLAY_OLED

Display oled = Display(&looper);

#endif




bool input_switch;


////////////////////////////////////
/////// BUG 1  ////////////////////
///////////////////////////////////
/*
 * When the HBounce "held" state finishes the program receive another "fell()" event and therefore it sends the
 * MIDI event. 
 * This is solved with a flag which check if in the last loop the button was pressed
 */ 
bool rec_held_flag;
bool stop_held_flag;
bool undo_held_flag;
bool edit_held_flag;
bool next_held_flag;
bool solo_held_flag;



bool debug_led = LOW;





void setPinModeRoutine();
void enableBounce();
void updateButtons();









void setup() {

  Serial.begin(115200); 
  

  initializeButtons();

    
  pinMode(REC_LED, OUTPUT);
  digitalWrite(REC_LED, LOW);

  #if INPUTS
  {
    pinMode(HOLD_LED, OUTPUT);
    digitalWrite(HOLD_LED, LOW);
    pinMode(TEMPO_LED, OUTPUT);
    digitalWrite(TEMPO_LED, LOW);
  }
  #endif

  active_rec = LOW; //Stop REC at the beginning

  rec_held_flag = false;
  stop_held_flag = false;
  undo_held_flag = false;
  edit_held_flag = false;
  next_held_flag = false;
  solo_held_flag = false;


  #if BLUETOOTH
    Bluetooth(BLUETOOTH_SWITCH);
  #endif

  #if DISPLAY_OLED
    Serial.println("Activating the display");
    oled.initialize();
    oled.showLogo();
    oled.printLooperStatus(true);
  #endif

  input_switch = false;
    
}

void loop() {

  #if BLUETOOTH
  {
    bluetooth_enabled = digitalRead(BLUETOOTH_SWITCH);

    if(bluetooth_enabled)){
      
    }
  }
  #endif

  #if DISPLAY_OLED
    oled.printLooperStatus();
  #endif


  //Update buttons status
  updateButtons();  


  #if INPUTS
  if(holdBounce.held()){

    digitalWrite(HOLD_LED, HIGH);


    if(input_switch){
      //Loop Number Input

      debug("Loop Input Mode");
      
      loopInputBounce.update();
  
      if(loopInputBounce.fell()){
        digitalWrite(HOLD_LED, LOW);
        delay(10);
        debug("Inserted Loop");
        numInput.addLoop();
      }
            
    }else{
      //Tap Tempo Function
      //debug("Recording TAP TEMPO");
      tapTempoBounce.update();
      
      if(tapTempoBounce.fell()){
        debug("TAP");
        tapTempo.recTapTempo(true);
      }else{
        tapTempo.recTapTempo(false);
      }
    }


        
  }else if(holdBounce.fell()){


    if(input_switch){
      uint8_t loops_number = numInput.getLoops();
      looper.changeLoopsCount(loops_number);
      numInput.reset();
    }else{
      ; //Do nothing
    }
    digitalWrite(HOLD_LED, LOW);
   
  }
  #endif





  if (!looper.isRecording()){
    /////////////////////////
    //No REC present
    /////////////////////////

    if( recBounce.held() ){
      looper.sync();
      rec_held_flag = true;
    }
    
    if( recBounce.fell() ){  //Start recording/Stop Overdub

      if (rec_held_flag){
        rec_held_flag = false;  //To fix a bug
      }else{
      
        debug("REC BUTTON FELL");
        
        if (looper.isOverdubbing()){
          debug("Stop Overdubbing");
          looper.stopOverdub(); //Stop Overdubbing
        }else if (!looper.isOverdubbing() && !looper.isEmpty()) {
          debug("Start Overdubbing");
          looper.startOverdub();
        }else{
          debug("Start REC");
          looper.startRecording();  //Start Recording
        }
        
      }
    }


    if( stopBounce.held()){
      
      if(looper.isOverdubbing()){
        debug("Stop Overdub");
        looper.stopOverdub();
        delay(500);
        looper.undoAll();
      }else if (!looper.isEmpty()){
        //Execute "Once"
        debug("Execute Once");
        looper.once();        
      }
      

      stop_held_flag = true;
    }else if(/*stopBounce.wasHeld() &&*/ stopBounce.fell() && !looper.isEmpty()){

      if(stop_held_flag){
        stop_held_flag = false;
      }else{
        debug("Mute");
        looper.mute();
      }
    }
  }else{
    /////////////////////////
    //REC present
    /////////////////////////
    if( stopBounce.held() ){
      //TODO ADD a Global LED blinking
      debug("Undo ALL");
      looper.undoAll();
    }
    
    if (recBounce.fell()){  //Register Loop
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on 
      debug("Stopping REC");
      looper.stopRecording();
    }
    
  }


  //////////////////////////////////////////////
  ////////// UNDO 
  //////////////////////////////////////////////


  if (undoBounce.held()){
    if ( !undo_held_flag){
      looper.redo();
      debug("REDO");
    }
    undo_held_flag = true;
  }else if (undoBounce.fell()){

    if(undo_held_flag){
      undo_held_flag = false;
      debug("UNDO");
    }else{
      looper.undo();
    }
  }

  /////////////////////////////////////////////
  /////////// SOLO
  /////////////////////////////////////////////

  if (soloBounce.held()){
    if ( !solo_held_flag){
      looper.stopAll();
    }
    solo_held_flag = true;
  }else if (soloBounce.fell()){

    if(solo_held_flag){
      solo_held_flag = false;
    }else{
      looper.solo();
    }
  }
  

  ////////////////////////////////////////
  //////////////// EDIT
  ////////////////////////////////////////
  /*
    if( editBounce.held() ){
      looper.replace();
      edit_held_flag = true;
    } else if( editBounce.fell() ){
      if(edit_held_flag){
        edit_held_flag = false;
      }else{
        looper.trigger();
      }
    }
  */



   ///////////////////////////////////////////////////////////////
   //////////////// LOOP SELECTION  //////////////////////////////
   ///////////////////////////////////////////////////////////////
   if(!looper.isRecording() && !looper.isOverdubbing()){
  
      if( nextBounce.held() ){
        looper.multiply();
        next_held_flag = true;
      } else if( nextBounce.fell() ){
         if(next_held_flag){
           next_held_flag = false;
          }else{
            looper.selectNextLoop();
          }
      }

  
   }
  
  ///////////////////////////////////////////////////////////////

  //                  LED BLINKING PROCEDURES

  ////////////////////////////////////////////////////////////////////

   if ( looper.isRecording() ) {  // Call code if button transitions from HIGH to LOW
     recLed.Update(); //Update REC Led Blinking
   }else{
     if (!recLed.IsRunning()){
      recLed.Stop();    //Stop REC Led Blinking
      digitalWrite(REC_LED, LOW);
     }
   }
  /*
   if ( looper.isOverdubbing() ) {  // Call code if button transitions from HIGH to LOW
     overdubLed.Update(); //Update REC Led Blinking
   }else{
     if (!overdubLed.IsRunning()){
      overdubLed.Stop();    //Stop REC Led Blinking
      digitalWrite(OVERDUB_LED, LOW);
     }
   }
  */

  #if INPUTS
  looper.tempoBlinkLed(TEMPO_LED);
  #endif


}

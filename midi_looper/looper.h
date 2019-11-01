#ifndef LOOPER_H_GUARD
#define LOOPER_H_GUARD


#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_RingBuffer.h>
#include <midi_Settings.h>
#include <MIDI.h>


MIDI_CREATE_DEFAULT_INSTANCE();


//#define DEBUG
#include "debug.h"

#include "loop.h"

// Created and binds the MIDI interface to the default hardware Serial port



#define MAX_LOOP 16



class Looper{

  private: 
    //@todo Use enum instead of list of consts
    
    const uint8_t start_rec_cmd = 10;   //Record
    const uint8_t stop_rec_cmd = 11;    //Record
    const uint8_t overdub_cmd = 10;     //Overdub
    const uint8_t clear_loop_cmd = 13;  //Clear Loop?
    const uint8_t next_loop_cmd = 14;   //Next Loop
    const uint8_t prev_loop_cmd = 15;   //Prev Loop
    const uint8_t stop_all_cmd = 16;    //Stop All (TODO)
    const uint8_t solo_cmd = 17;        //Solo
    const uint8_t mul_cmd = 18;         //Multiply
    const uint8_t tap_tempo_cmd = 19;   //Tap Tempo (To finish)
    const uint8_t once_cmd = 20;        //Once
    const uint8_t mute_cmd = 21;        //Mute
    const uint8_t replace_cmd = 22;     //Replace
    const uint8_t undo_all_cmd = 23;    //Undo All
    const uint8_t undo_cmd = 24;        //Redo
    const uint8_t redo_cmd = 25;        //Undo
    const uint8_t substitute_cmd = 26;  //Substitute
    const uint8_t reverse_cmd = 27;     //Reverse
    const uint8_t insert_cmd = 28;      //Insert
    const uint8_t sync_cmd = 29;        //Sync
    const uint8_t trigger_cmd = 30;     //Trigger
    /*
    
    enum looper_cmd{
      start_rec_cmd =   10,   //Record
      stop_rec_cmd =    11,   //Record
      overdub_cmd =     12,   //Overdub
      clear_loop_cmd =  13,   //Clear Loop?
      next_loop_cmd =   14,   //Next Loop
      prev_loop_cmd =   15,   //Prev Loop
      stop_all_cmd =    16,   //Stop All (TODO)
      solo_cmd =        17,   //Solo
      mul_cmd =         18,   //Multiply
      tap_tempo_cmd =   19,   //Tap Tempo (To finish)
      once_cmd =        20,   //Once
      mute_cmd =        21,   //Mute
      replace_cmd =     22,   //Replace
      undo_all_cmd =    23,   //Undo All
      undo_cmd =        24,   //Redo
      redo_cmd =        25,   //Undo
      substitute_cmd =  26,   //Substitute
      reverse_cmd =     27,   //Reverse
      insert_cmd =      28,   //Insert
      sync_cmd =        29,   //Sync
      trigger_cmd =     30    //Trigger
    };
    */


    const uint8_t loop_initial_code = 50;



    const uint8_t set_loop_num_input = 100;

  
    uint8_t channel;   //MIDI Channel to use
    uint16_t elasped_time;    //Don't remember why is there




    uint8_t total_loop;  //The number of present loop
    Loop loops[MAX_LOOP]; //Array of Loop objects

    uint8_t selected_loop;
    Loop *CurrentLoop;  //Pointer to the current loop in "loops" array



    void updateCurrentLoop(){
      debug(selected_loop);
      CurrentLoop = &loops[selected_loop];
    }



  public:
  
    Looper(uint8_t _channel, uint8_t _initialLoopsNumber){

      //MIDI.begin(MIDI_CHANNEL_OMNI);

      this->channel = _channel;
      selected_loop = 0;
      
      if (_initialLoopsNumber < MAX_LOOP){
        total_loop = _initialLoopsNumber;
      }else{
        total_loop = 1;
      }
      
      CurrentLoop = &loops[0];


      debug(CurrentLoop->isRecording());
    }


    void changeLoopsCount(uint8_t _loopNumber){
      if (_loopNumber > MAX_LOOP){
        debug("Max Loop Reached"); 
      }
      total_loop = _loopNumber;
      
      debug("Resetting Loops statuts");
      for(int i=0; i<total_loop; i++){
        loops[i].clear_loop();
      }

    }




    bool isRecording(){
      return CurrentLoop->isRecording();
    }

    void setRecordingState(){
      CurrentLoop->startRecording();  
    }
    bool isOverdubbing(){
      return CurrentLoop->isOverdubbing();
    }

    void setOverdubbingState(){
      CurrentLoop->startOverdubbing();  
    }

    bool isSolo(){
      return CurrentLoop->isSolo();
    }


    bool isEmpty(){
      return CurrentLoop->isEmpty();
    }

    bool isSynced(){
      return CurrentLoop->isSynced();
    }


    ////////////////////////////////////////////////
    //// Loop Selection
    ////////////////////////////////////////////////
    
    void selectNextLoop(){
      MIDI.sendControlChange(next_loop_cmd, 1, this->channel);
      selected_loop = (selected_loop+1) % total_loop;
      updateCurrentLoop();
    }
    

    void selectPrevLoop(){
      //MIDI.sendControlChange(prev_loop_cmd, 1, this->channel);
      selected_loop = (selected_loop-1) % total_loop;
      if(selected_loop > total_loop-1){
        selected_loop = total_loop-1;
      }
      updateCurrentLoop();
      debug(selected_loop);
    }



    //// Loop Control
  
    void startRecording(){
      if(CurrentLoop->isOverdubbing()){   //If there is overdubbing then stop overdub
        this->stopOverdub();
      }else{
        MIDI.sendControlChange(start_rec_cmd, 1, this->channel);
        if (!CurrentLoop->isRecording()){   //If nothing is recording start REC
          CurrentLoop->startRecording();}
        else{
          CurrentLoop->stopRecording();
        }        
      }
    }

    void stopRecording(){
      MIDI.sendControlChange(start_rec_cmd, 1, this->channel);
      CurrentLoop->stopRecording();
    }

  
    void startOverdub(){
      if (!CurrentLoop->isOverdubbing()){
        debug("Looper - Overdub Started");
        MIDI.sendControlChange(overdub_cmd, 1, this->channel);
        CurrentLoop->startOverdubbing();
      }
    }

  
    void stopOverdub(){
      if (CurrentLoop->isOverdubbing()){
        MIDI.sendControlChange(overdub_cmd, 1, this->channel);
        debug("Looper - Overdub Stopped");
        CurrentLoop->stopOverdubbing();
      }
    }

    void clearLoop(){
      MIDI.sendControlChange(clear_loop_cmd, 1, this->channel);
      CurrentLoop->clear_loop();
    }

    void solo(){
      if (!CurrentLoop->isSolo()){
        debug("START SOLO");
        CurrentLoop->startSolo();
      }else{
        debug("STOP SOLO");
        CurrentLoop->stopSolo();
      }
      MIDI.sendControlChange(solo_cmd, 1, this->channel);
    }

    void multiply(){
      debug("MULTIPLY");
      MIDI.sendControlChange(mul_cmd, 1, this->channel);
    }

    void once(){
      debug("ONCE");
      MIDI.sendControlChange(once_cmd, 1, this->channel);      
    }

    void mute(){
      debug("MUTE");
      MIDI.sendControlChange(mute_cmd, 1, this->channel);           
    }

    void replace(){
      debug("REPLACE");
      MIDI.sendControlChange(replace_cmd, 1, this->channel);           
    }


    void undoAll(){
      debug("UNDO ALL");
      MIDI.sendControlChange(undo_all_cmd, 1, this->channel);           
      CurrentLoop->stopRecording();
      CurrentLoop->stopOverdubbing();
      CurrentLoop->clear_loop();
    }


    void undo(){
      debug("UNDO");
      MIDI.sendControlChange(undo_cmd, 1, this->channel);           
    }

    void redo(){
      debug("REDO");
      MIDI.sendControlChange(redo_cmd, 1, this->channel);           
    }    


    void stopAll(){
      debug("STOP ALL");
      MIDI.sendControlChange(stop_all_cmd, 1, this->channel);            
    }


    void sync(){
      CurrentLoop->sync();
      MIDI.sendControlChange(sync_cmd, 1, this->channel);            
    }

    void trigger(){
      MIDI.sendControlChange(trigger_cmd, 1, this->channel);            
    }



    void changeLoopVolume(uint8_t loopNumber, uint8_t volumeValue){
      //Check if the received loop excedes the current loop number
      if(loopNumber > total_loop){
        return;
      }

      //Check for invalid volume value
      if(volumeValue > 100){
        return;
      }
      
      uint8_t loopMidiCode = loop_initial_code + loopNumber;    //The number saved into SooperLooper

      MIDI.sendControlChange(loopMidiCode, volumeValue, this->channel); 
      
    }
    
  
};




#endif

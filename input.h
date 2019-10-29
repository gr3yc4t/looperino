#include <MIDI.h>
// Suspended for now
//#include <ArduinoTapTempo.h>

#define DEBUG

#include "debug.h"

//Tap Tempo Development suspended

/*
class TapTempo{

    private:
    
      ArduinoTapTempo tapTempo;
      uint8_t tapButton;
      bool recorded;

      const uint8_t tap_tempo_cmd = 50;

      uint8_t ledTempo;
  
      void sendTapTempo(){
        //debug("TAP");
        Serial.println(tapTempo.getBPM());
        //MIDI.sendControlChange(tap_tempo_cmd, 1 , 1);
      }

      
    
    public:

      TapTempo(uint8_t _tapButton, uint8_t _ledTempo){
        tapButton = _tapButton;
        ledTempo = _ledTempo;
        recorded = false;
        
        tapTempo.setMaxBPM(220.);
        tapTempo.setMinBPM(60.);      
      }
  
  
      void tempoUpdate(bool _fell){
        
        _fell = !_fell;
        
        tapTempo.update(_fell);   

        if (_fell){
          this->sendTapTempo();
          digitalWrite(ledTempo, HIGH);
        }else{
          digitalWrite(ledTempo, LOW);
        }
      }
  

  
      void recTapTempo(bool _fell){
        this->tempoUpdate(_fell);
        this->recorded = true;
      }

    ///////////////////////////////////////////////////////
    //////// TEMPO
    ///////////////////////////////////////////////////////
    
    void tempoBlinkLed(){

      if(!this->recorded){
        digitalWrite(ledTempo, LOW);
        return;
      }


      //tapTempo.update();
      
      if(this->isOnBeat()){
        digitalWrite(ledTempo, HIGH);
      }else{
        digitalWrite(ledTempo, LOW);
      }
    }

    bool isOnBeat(){
      return tapTempo.onBeat();
    }
    
};


*/




class LooperInput{


    private:

    uint16_t loopNumber;
    

    public:

    LooperInput(void){
      loopNumber = 1;
    }



    void addLoop(){
      loopNumber++;
    }

    
    uint16_t getLoops(){
      //debug(loopNumber);
      return loopNumber;
    }


    void reset(){
      loopNumber = 1;
    }
/*

    ////////////////////////////////////////////////
    //////////// INPUTS 
    ////////////////////////////////////////////////

    void handleProgramChange(uint8_t data1, uint8_t data2){
      //Set number of loop
      if(data1 == set_loop_num_input){  
        if (data2 <= MAX_LOOP){
          this->total_loop = data2;
        }
      }
    }



    void parseInput(){
      if (MIDI.read())                // Is there a MIDI message incoming ?
      {

          uint8_t recv_channel = MIDI.getChannel();

          if (recv_channel != 3){
            return;         //Only allow INPUTS on Channel 3
          }

        
          switch(MIDI.getType())      // Get the type of the message we caught
          {
              case midi::ProgramChange:       
                  handleProgramChange(MIDI.getData1(), MIDI.getData2());     
                  break;
              default:
                  break;
          }
      }
    }


*/

  
};

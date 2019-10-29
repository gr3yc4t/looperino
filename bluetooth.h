#include "debug.h"
#include "looper.h"

#define INITIAL_VOLUME_CMD 50
#define FINAL_VOLUME_CMD 70


/**
 * This class is responsible for reading and parsing bluetooth messagges that, 
 * after processing, manage the looper.
 *  
 */
class Bluetooth{


  private:
    uint8_t enablePin;  //Pin responsible for enabling bluetooth communication 
    Looper *looper;     //Pointer to the main looper instance
  

    /**
     * @param cmd The received command, used to determine the selected loopNumber
     * 
     * @brief This function read the next available byte and checks if is a valid volume value
     * If not, the function return and nothing on the buffer is touched (except for the volume command)
     * Otherwise it remove the volume value from the buffer and call the Looper object to process the MIDI
     * command
     * 
     */
    void parseVolumeCommand(uint8_t cmd){
      uint8_t volume_value;
      uint8_t loop_value;
      
      loop_value= cmd - INITIAL_VOLUME_CMD;

      //Check if the next value on the buffer is a coherent value
      volume_value = Serial3.peek();

      if(volume_value > 100){
        //Invalid volume value, return without removing the byte from the incoming buffer
        return; 
      }

      volume_value = Serial3.read();  //Remove the value from the buffer


      this->looper->changeLoopVolume(loop_value, volume_value); //Call the looper object
      
    }
      



  public:

    /**
     * @param _enablePin  Pin attached to the "Bluetooth Enabler" switch
     * @param _looper     Pointer to the Looper Object
     * 
     * The pointer to the Looper object is necessary since when command are received this class
     * directly call the appropriate function.
     */
     
    Bluetooth(uint8_t _enablePin, Looper* _looper){
      this->enablePin = _enablePin;
      Serial3.begin(9600);
      pinMode(enablePin, INPUT);


      if(_looper != NULL){
        this->looper = _looper;
      }

    }


    /**
     * Update the status of the looper by processing incoming data present in the 
     * bluetooth serial buffer
     */

    void update(){
      uint8_t command;
      uint8_t availableBytes;

      while( (availableBytes = Serial3.available()) > 0){
      
        command = Serial3.read();

        //Check If is a volume command
        if(command >= INITIAL_VOLUME_CMD && command <= FINAL_VOLUME_CMD){
          parseVolumeCommand(command);
        }
         
      }
    }





  
};

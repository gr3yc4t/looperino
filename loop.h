#ifndef LOOP_H_GUARD
#define LOOP_H_GUARD


#include "debug.h"

#define DEBUG



class Loop{

  private:
    uint8_t recording;
    uint8_t overdubbing;
    uint8_t once;
    uint8_t solo;
    uint8_t is_empty;
    uint8_t is_synced;


    uint8_t volume;


    void fill(){
      is_empty = 0;
    }



  public:

    Loop(){
      recording = 0;
      overdubbing = 0;
      once = 0;
      solo = 0;
      is_empty = 1;
      is_synced = 0;

      volume = 70;
    }


    void clear_loop(){
      this->is_empty = 1;
      this->recording = 0;
      this->overdubbing = 0;
      this->once = 0;
      this->solo = 0;
      this->is_synced = 0;
    }

    bool isEmpty(){
      if(is_empty == 1){
        return true;
      }
      return false;
    }

    bool isRecording(){
      if (recording == 1){
        return true;
      }
      return false;
    }

    bool isOverdubbing(){
      if (overdubbing == 1){
        return true;
      }
      return false;
    }


    bool isOnce(){
      if (once == 1){
        return true;
      }
      return false;
    }


    bool isSolo(){
      if (solo == 1){
        return true;
      }
      return false;
    }


    bool isSynced(){
      if(is_synced == 1)
        return true;
      return false;
    }



    void sync(){
      is_synced = 1;
    }


    void startRecording(){
      debug("Start Recording");
      recording = 1;
    }

    void stopRecording(){
      recording = 0;
      this->fill();
      debug("Stop Recording");
    }


    void startOverdubbing(){
      overdubbing = 1;
    }

    void stopOverdubbing(){
      overdubbing = 0;
    }


    void startSolo(){
      solo = 1;
    }

    void stopSolo(){
      overdubbing = 0;
    }

    
  
};




#endif

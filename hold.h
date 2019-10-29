#ifndef HOLD_H_GUARD
#define HOLD_H_GUARD

#include <Bounce2.h>



class BounceHeld: public Bounce{

  private:

    int btn_state;
    unsigned long int counter;
    uint16_t held_time;

    int lastState;
    bool was_held;

  public:

  
    BounceHeld(uint16_t _held_time){
      btn_state = 0;
      held_time= _held_time;
      was_held = true;
      lastState = LOW;
      counter=0;
    }

    bool held(){

        this->fell();
        int curr_btn_state = this->read();
        if (curr_btn_state == HIGH && ((this->duration()) > 1500)){
          lastState = HIGH;
          return true;
        }else if(lastState == HIGH){
          was_held = true;
        }
        return false;
    }


    //TODO Change true/false for clarity
    bool wasHeld(){

      if (was_held == true){
        was_held = false;
        return true;
      }

      //if (lastState == LOW)
      //  return true;
      //debug("Not HELD");
      return false;
    }

  
};


#endif
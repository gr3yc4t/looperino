/**
 * 
 * Class responsible for managing the effect button and the effect knob
 * Each button/knob must be instantiated with the related object by specifying the pin to which
 * is attached. Inside the loop there must be an "update()" function which updates the button/knob value/state
 * 
 * 
 */

#ifndef EFFECT_H_GUARD
#define EFFECT_H_GUARD


#include <MIDI.h>
#include <Bounce2.h>
#include "hold.h"

class Effects{



}



//Inherit from BouceHeld
class EffectButton : public BounceHeld{

  public:
    EffectButton(uint8_t cmd, uint8_t value);
  
}


//Must write entirely
class EffectKnob{


  
}

#endif

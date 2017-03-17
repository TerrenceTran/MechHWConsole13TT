//AMIB2

#include "states.h"

//#define BALL_PS_SWISHYBOATS_START 8
#define BALL_PS_SWISHYBOATS_END 55

namespace BALLCHECK {
  void setup() {
    //pinMode(BALL_PS_SWISHYBOATS_START, INPUT_PULLUP);
    pinMode(BALL_PS_SWISHYBOATS_END, INPUT_PULLUP);
  }
  
  void loop() {
    
  }
  
  void enter() {
    master::events::amib2Ready();
  }
  
  void exit() {
    master::events::amib2NotReady();
  }
  
  void events::checkSensors() {
    
    if(!digitalRead(BALL_PS_SWISHYBOATS_END))
      ballSense3.value = true;
    else
      ballSense3.value = false;
    
    //manager.updateValue(master::ballSense2, ballSense2.value);
    manager.updateValue(master::ballSense3, ballSense3.value);
  }
}
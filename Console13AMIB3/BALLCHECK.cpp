//For modifying:
//-Simply add or remove certain portions of code
//  depending on the amount of sensors on this board

#include "states.h"

#define BALL_PS_SPINNYLIFTER2_END A5

namespace BALLCHECK {
  void setup() {
    pinMode(BALL_PS_SPINNYLIFTER2_END, INPUT_PULLUP);
  }
  
  void loop() {
    
  }
  
  void enter() {
    master::events::amib3Ready();
  }
  
  void exit() {
    master::events::amib3NotReady();
  }
  
  void events::checkSensors() {
    if(!digitalRead(BALL_PS_SPINNYLIFTER2_END))
      ballSense4.value = true;
    else
      ballSense4.value = false;

    manager.updateValue(master::ballSense4, ballSense4.value);
  }
}
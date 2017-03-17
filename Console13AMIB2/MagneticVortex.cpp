//AMIB2

#include "states.h"

namespace MAGNETICVORTEX {

  //const byte START_SENSOR_PIN  = 23;

// NOTE: all of {setup, enter, loop, exit} are optional

void setup() {
  // do setup!
  // things like pinMode, configure steppers, etc.
  
  //pinMode(START_SENSOR_PIN, INPUT_PULLUP);
}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc.
  
}

//void events::startSensor(){
  //while(digitalRead(START_SENSOR_PIN)) {
    //amib3::events::lowPiston();
  //}
  
  //amib3::events::highPiston();
//}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

// now you have to implement the various events


}

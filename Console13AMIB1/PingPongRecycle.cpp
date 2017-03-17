
#include "states.h"

namespace PINGPONGRECYCLE {

// NOTE: all of {setup, enter, loop, exit} are optional

void setup() {
  // do setup!
  // things like pinMode, configure steppers, etc.
}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc.
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

// now you have to implement the various events


}

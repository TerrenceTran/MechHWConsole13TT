
#include "states.h"

namespace BERNOULLIFAN {

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

void events::homeFan(void) {
  amib3::events::homeFan();
}

void events::demo(void) {
	amib3::events::demo();
}

void events::liftBall(void) {
  amib3::events::liftBall();
}

// now you have to implement the various events
}

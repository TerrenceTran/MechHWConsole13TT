
#include "states.h"

namespace SPINNYLIFTER2 {

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
  MANAGER_PASS_ON(amib3, spinnyOffset1);
  
  manager.updateFromSlave(2);
  manager.updateFromSlave(3);
}

void events::demo(void) {
  amib3::events::demo();
}

void events::cycleBall(void) {
  amib3::events::cycleBall();
}

void events::cycleEntranceStop(void) {
  amib2::events::cycleEntranceStop();
}

void events::cycleExitStop(void) {
  amib3::events::cycleExitStop();
}

void events::stopMovement(void) {
  amib3::events::stopMovement();
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

}

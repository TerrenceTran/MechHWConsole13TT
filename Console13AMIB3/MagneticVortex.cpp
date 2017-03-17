//Magnetic Vortex AMIB3

#include "states.h"

namespace MAGNETICVORTEX {
  
const byte PISTON_LIFTER_PORT = 9;

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

//lowers and raises the piston on a delay, not used with ballchecking
void events::pistonStop() {
  digitalWrite(PISTON_LIFTER_PORT, HIGH);
  delay(1500);
  digitalWrite(PISTON_LIFTER_PORT, LOW);
}

//Calls the event startSensor on the master AMIB, which waits to lift the piston until it reads the sensor in the ball lifter
void events::startSensor() {
  master::events::startSensor();
}

//same as pistonStop, not used in ballchecking
void events::cycleBall() {
  digitalWrite(PISTON_LIFTER_PORT, HIGH);
  delay(1500);
  digitalWrite(PISTON_LIFTER_PORT, LOW);
}

//lowers the piston
void events::lowPiston() {
  digitalWrite(PISTON_LIFTER_PORT, HIGH);
}

//raises the piston
void events::highPiston() {
  digitalWrite(PISTON_LIFTER_PORT, LOW);
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

}

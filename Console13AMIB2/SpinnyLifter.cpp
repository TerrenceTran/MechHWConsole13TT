//SpinnyLifter.cpp AMIB2

#include "states.h"
#include <Manager.h>

namespace SPINNYLIFTER {

const byte PISTON_LIFTER_PORT = 9;
//const byte BOAT_ENTRANCE_PS = 8;

void setup() {
  Serial.begin(9600);
  pinMode(PISTON_LIFTER_PORT, OUTPUT);
  //pinMode(BOAT_ENTRANCE_PS, INPUT_PULLUP);
  
  Serial.println("SPINNYLIFTER::setup()");
}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
  //manager.updateValue(master::topSensor, (unsigned int) 0); //no ball
}

void loop() {
 // MANAGER_PASS_ON(master, topSensor);

  //called in a loop continuously while in this state
  //monitor sensors, etc.

  //if (digitalRead(BOAT_ENTRANCE_PS) == LOW){
    //master::topSensor.change = true;
    //manager.updateValue(master::topSensor, (unsigned int) 1); //1 means there's a ball
    
  //}
  
}

void events::liftBall() {
  digitalWrite(PISTON_LIFTER_PORT, HIGH);
  delay(1500);
  digitalWrite(PISTON_LIFTER_PORT, LOW);
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

// now you have to implement the various events

}

#include "states.h"

namespace SPINNYLIFTER2 {

const byte BOAT_EXIT_PS = A1;
const byte BOAT_EXIT_STOP = 4; 

void setup() {
  pinMode(BOAT_EXIT_PS, INPUT_PULLUP); // for the boat exit sensor 
  pinMode(BOAT_EXIT_STOP, OUTPUT);
}

void enter() {
  
}

void loop() {

}

void events::cycleEntranceStop() {
  digitalWrite(BOAT_EXIT_STOP, HIGH);
  delay(1500);
  digitalWrite(BOAT_EXIT_STOP, LOW);
}

void exit() {
  
}

}

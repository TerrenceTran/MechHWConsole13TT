#include <Arduino.h>
#include <Wire.h>
#include <MultiInterfaceBoard.h>
#include <SpeedyStepper.h>
#include <FlexyStepper.h>

#include "states.h"
#include <Manager.h>

void setup() {
  setupMultiInterfaceBoard();
  manager.debugSetup(STATE_IDLE);
}

void loop() {
  manager.loop();
}

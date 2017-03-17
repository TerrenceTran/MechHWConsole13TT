
#include <Arduino.h>
#include <Wire.h>
#include <MultiInterfaceBoard.h>
#include <SpeedyStepper.h>
#include <FlexyStepper.h>

#include "states.h"
#include <Manager.h>
#include "common.h"

const byte ARCADE_LED_DIMMER = 10;

void setup() {
  setupMultiInterfaceBoard();
  manager.debugSetup(STATE_IDLE);
  pinMode(ARCADE_LED_DIMMER, OUTPUT);
  turnOnLeds();
  
}

void loop() {
  manager.loop();
}

void turnOnLeds() {
  digitalWrite(ARCADE_LED_DIMMER, HIGH);
}

void turnOffLeds() {
  digitalWrite(ARCADE_LED_DIMMER, LOW);
}

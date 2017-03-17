//AMIB3 SpinnyLifter2

#include "states.h"

#include <FlexyStepper.h>
#include <Encoder.h>


namespace SPINNYLIFTER2 {

FlexyStepper spinnyStepper;
const byte SPINNY_1_STEPPER_PORT = 6;

//boolean ballHasSeenLifter1PS = false;
const byte STEPS_PER_R = 100;
const float HOMING_SPEED_IN_RPS = .15;
//const float SPEED_IN_RPS = 1;
const float MAX_DIST_IN_R = 10;

float targetPosition = 0.0;

const float SPINNY_STEPS_PER_REV = 800*295.0/20.0;
const float SPINNY_SPEED_IN_RPS = .15;
const float SPINNY_ACCEL_IN_RPSPS = .5;

//const byte SPINNY_1_START_PS = 8;
const byte SPINNY_2_EXIT_PS = A5;
const byte SPINNY_2_ENTRANCE_PS = A1; //this sensor is weak, needs to be replaced 12/16/16
const byte SPINNY_2_EXIT_STOP = 9;
const byte SPINNY_2_HOMING = 56;

//SpeedyStepper *const SPINNY_STEPPERS[] = {&spinnyStepper1};

void setup() {
  Serial.begin(9600);
  spinnyStepper.connectToPort(SPINNY_1_STEPPER_PORT);
  spinnyStepper.setStepsPerRevolution(SPINNY_STEPS_PER_REV);
  spinnyStepper.setSpeedInRevolutionsPerSecond(SPINNY_SPEED_IN_RPS);
  spinnyStepper.setAccelerationInRevolutionsPerSecondPerSecond(SPINNY_ACCEL_IN_RPSPS);
  
  pinMode(SPINNY_2_EXIT_PS, INPUT_PULLUP);
  pinMode(SPINNY_2_ENTRANCE_PS, INPUT_PULLUP);
  pinMode(SPINNY_2_EXIT_STOP, OUTPUT);
  pinMode(SPINNY_2_HOMING, INPUT_PULLUP);
  
  spinnyStepper.moveToHomeInRevolutions(1, HOMING_SPEED_IN_RPS, MAX_DIST_IN_R, SPINNY_2_HOMING);
  spinnyStepper.setCurrentPositionInMillimeters(0.0);
  spinnyStepper.disableStepper();
    
  /*pinMode(SPINNY_1_START_PS, INPUT_PULLUP);
  pinMode(SPINNY_1_HOME_PS, INPUT_PULLUP);*/
}

void enter() {
  spinnyStepper.enableStepper();
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc.
}

void events::demo(void) {
  //spinnyStepper.enableStepper();
  master::events::cycleEntranceStop();
  
  while(digitalRead(SPINNY_2_ENTRANCE_PS)) {
    delay(10);
  }
  
  delay(200);
  spinnyStepper.enableStepper();
  spinnyStepper.setTargetPositionInRevolutions(10000);
  
  while(digitalRead(SPINNY_2_EXIT_PS)) {
    spinnyStepper.processMovement();
  }
  
  //This is the piston at the end, its in the MagneticVortex now
  //delay(1000);
  //master::events::cycleExitStop();
  spinnyStepper.setCurrentPositionInRevolutions(0);
  spinnyStepper.setTargetPositionInRevolutions(0);
  spinnyStepper.disableStepper();
}

void events::cycleBall() {
  spinnyStepper.moveToHomeInRevolutions(-1, HOMING_SPEED_IN_RPS, MAX_DIST_IN_R, SPINNY_2_HOMING);
  spinnyStepper.setCurrentPositionInMillimeters(0.0);
  
  master::events::cycleEntranceStop();
  delay(2500);

  //spinnyStepper.enableStepper(); //The stepper gets enabled in setup now
  
  //loops forever and gets stuck, doesn't know when to stop
  //while(digitalRead(SPINNY_2_ENTRANCE_PS)) 
    //delay(10);
  //
  
  spinnyStepper.setTargetPositionInRevolutions(10000);
  
  long startTime = millis();
  long elapsedTime = 0;
  long timeoutTime = 10000;
  
  //This while loop is experimental, combining first spinnylifter code and reading the sensor
  //while(digitalRead(SPINNY_2_ENTRANCE_PS) && elapsedTime < timeoutTime) {
    //delay(100);
  //}
  
  
  //This while loop is copied over from the first spinnylifter, the original code is below
  while(digitalRead(SPINNY_2_EXIT_PS) && elapsedTime < timeoutTime) {
    spinnyStepper.processMovement();
    elapsedTime = millis() - startTime;
  }
  
  //This is the piston at the end, its in the MagneticVortex now
  //delay(1000);
  //master::events::cycleExitStop();
  spinnyStepper.setCurrentPositionInRevolutions(0);
  spinnyStepper.setTargetPositionInRevolutions(0);
  spinnyStepper.disableStepper();
}

void events::cycleExitStop() {
  //spinnyStepper.enableStepper();
  digitalWrite(SPINNY_2_EXIT_STOP, HIGH);
  delay(1500);
  digitalWrite(SPINNY_2_EXIT_STOP, LOW);
  //spinnyStepper.disableStepper();
}

void events::stopMovement(){
  spinnyStepper.disableStepper();
  spinnyStepper.setCurrentPositionInRevolutions(targetPosition);
}

void exit() {
  //spinnyStepper.setTargetPositionToStop();
  //while(!spinnyStepper.processMovement());
  spinnyStepper.disableStepper();
  spinnyStepper.setCurrentPositionInRevolutions(targetPosition);
}

// now you have to implement the various events



}


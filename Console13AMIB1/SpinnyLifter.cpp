//SpinnyLifter.cpp AMIB1

#include <FlexyStepper.h>
#include <Encoder.h>
#include <Manager.h>
#include "states.h"


namespace SPINNYLIFTER {
 FlexyStepper spinnyStepper1;
const byte SPINNY_1_STEPPER_PORT = 1;
const byte PISTON_LIFTER_PORT = 9;

//boolean ballHasSeenLifter1PS = false;
// NOTE: all of {setup, enter, loop, exit} are optional
const byte STEPS_PER_R = 100;
const float HOMING_SPEED_IN_RPS = .7;
const float SPEED_IN_RPS = .35;
//const float ACCEL_IN_MMPSPS = 25;
const float MAX_DIST_IN_R = 10; //for cycleBall

float targetPosition = 0.0;

const float SPINNY_STEPS_PER_REV = 800*295.0/20.0;
const float SPINNY_SPEED_IN_RPS = .3;
const float SPINNY_ACCEL_IN_RPSPS = .5;

//const byte SPINNY_1_START_PS = 8;
const byte SPINNY_1_LIFTER_PS = 23;
const byte SPINNY_1_ENTRANCE_PS = 24; //entrance, unused
const byte BOAT_ENTRANCE_PS = 8; //MOVED FROM AMIB2 TO AMIB1
const byte SPINNY_1_HOMING = 25; //stepper

//SpeedyStepper *const SPINNY_STEPPERS[] = {&spinnyStepper1};

void setup() {
  Serial3.begin(9600);
  //pinMode(SPINNY_1_START_PS, INPUT_PULLUP);
  pinMode(SPINNY_1_LIFTER_PS, INPUT_PULLUP);
  pinMode(SPINNY_1_ENTRANCE_PS, INPUT_PULLUP);
  pinMode(BOAT_ENTRANCE_PS, INPUT_PULLUP);
  
  spinnyStepper1.connectToPort(SPINNY_1_STEPPER_PORT);
  spinnyStepper1.setStepsPerRevolution(SPINNY_STEPS_PER_REV);
  spinnyStepper1.setSpeedInRevolutionsPerSecond(SPINNY_SPEED_IN_RPS);
  spinnyStepper1.setAccelerationInRevolutionsPerSecondPerSecond(SPINNY_ACCEL_IN_RPSPS);
  
  spinnyStepper1.moveToHomeInRevolutions(-1, HOMING_SPEED_IN_RPS, MAX_DIST_IN_R, SPINNY_1_HOMING);
  spinnyStepper1.setCurrentPositionInMillimeters(0.0);
  spinnyStepper1.disableStepper();
  
  digitalWrite(PISTON_LIFTER_PORT, LOW);
  
  //Serial.println("set up SpinnyLifter");
}

void enter() {
  //ballHasSeenLifter1PS = false;
  digitalWrite(PISTON_LIFTER_PORT, HIGH);
  spinnyStepper1.enableStepper();
}

void loop() {
    manager.updateFromSlave(2);
}

void events::liftBall() {
  amib2::events::liftBall();
}

void events::demo(void) {
  
  Serial.println("got to demo");
  events::liftBall();
  
  //spinnyStepper1.enableStepper();
  spinnyStepper1.setTargetPositionInRevolutions(-10000);
  
  //while(digitalRead(BOAT_ENTRANCE_PS)) {
  while(topSensor.value == 0) {
    spinnyStepper1.processMovement();
  }
  
  //Serial.println("BOAT_ENTRANCE_PS");
  spinnyStepper1.setCurrentPositionInRevolutions(0);
  spinnyStepper1.setTargetPositionInRevolutions(0);
  spinnyStepper1.disableStepper();
  
}

//works in debug after exiting state into IDLE then back in, idk why
void events::cycleBall(void) {
  spinnyStepper1.moveToHomeInRevolutions(-1, HOMING_SPEED_IN_RPS, 1, SPINNY_1_HOMING);
  spinnyStepper1.setCurrentPositionInMillimeters(0.0);
  
  events::liftBall();
  delay(3550);
  
  spinnyStepper1.moveToHomeInRevolutions(-1, SPEED_IN_RPS, MAX_DIST_IN_R, BOAT_ENTRANCE_PS);
  
  //spinnyStepper1.enableStepper();
  /*spinnyStepper1.setTargetPositionInRevolutions(-10000);
  
  long startTime = millis();
  long messageTimeoutTime = 500;
  long mechanismTimeoutTime = 10000;
  long messageTime = millis() + messageTimeoutTime;
  long mechanismTimeout = millis() + mechanismTimeoutTime;
  
  manager.updateFromSlave(2);
  
  //while(topSensor.value == 0 && elapsedTime < timeoutTime) {
  while(!topSensor.value) {
    spinnyStepper1.processMovement();
    
    if(millis() > messageTime){
      manager.updateFromSlave(2);
      messageTime = millis() + messageTimeoutTime;
    }
  }
  */
  
  //spinnyStepper1.setCurrentPositionInRevolutions(0);
  //spinnyStepper1.setTargetPositionInRevolutions(0);
  spinnyStepper1.disableStepper();
}

void exit() {
  //digitalWrite(PISTON_LIFTER_PORT, LOW);
  //spinnyStepper1.setTargetPositionToStop();
  //while(!spinnyStepper1.processMovement());
  spinnyStepper1.disableStepper();
  //spinnyStepper1.setCurrentPositionInRevolutions(targetPosition);
  //ballHasSeenLifter1PS = false;
}

}
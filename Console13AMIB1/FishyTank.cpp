//FishyTank.cpp

#include <FlexyStepper.h>
#include "states.h"
#include <Encoder.h>
#include <limits.h>

namespace FISHYTANK {

const byte FISHY_MOTOR_PORT = 10; //FISHY_STEPPER_PORT = 2 before motor replacement

//const float STEPS_PER_R = 3200/2.5;
//const float HOMING_SPEED_IN_RPS = .1;
//const float SPEED_IN_RPS = 3;
//const float ACCEL_IN_RPSPS = .4;
//const float MAX_DIST_IN_R = 70;
const float MIN_SPEED = 0.1;
const float MAX_SPEED = 3;

void setup() {
  //fishyMotor.connectToPort(FISHY_MOTOR_PORT);
  //fishyMotor.setStepsPerRevolution(STEPS_PER_R);
  //fishyMotor.setAccelerationInRevolutionsPerSecondPerSecond(ACCEL_IN_RPSPS);
  //fishyMotor.setSpeedInRevolutionsPerSecond(0);
  
  pinMode(FISHY_MOTOR_PORT, OUTPUT);

  //fishyMotor.disableStepper();
}

void enter() {
  //fishyMotor.enableStepper();
  //This is the reason why the tank starts spinning right away...
  //Do we want it to start spinning right away and then go straight to changing values? Or have it how it is now?
  //fishyMotor.setSpeedInRevolutionsPerSecond(MIN_SPEED);
  //fishyMotor.setTargetPositionInRevolutions(LONG_MAX);
}

void loop() {
  //if fishyMotorSpeed.changed is true, change the speed
  if (fishyMotorSpeed.changed) {
   analogWrite(FISHY_MOTOR_PORT, (byte) fishyMotorSpeed.value);
   fishyMotorSpeed.changed = false;
  }
   //if (fishyMotorSpeed.value > MAX_SPEED){
      //fishyMotorSpeed.value = MAX_SPEED;
  
    
 // float speedInRPS = mapf((float) fishyMotorSpeed.value, 0, 10000, MIN_SPEED, MAX_SPEED);
   
    //fishyMotor.setSpeedInRevolutionsPerSecond(fishyMotorSpeed.value);
    //fishyMotor.setTargetPositionRelativeInRevolutions(10);
  }
  //fishyMotor.processMovement();

//Spins for 20 revolutions at a speed of two
void events::spinTank(){
  //fishyMotor.setSpeedInRevolutionsPerSecond(2);
  //fishyMotor.moveRelativeInRevolutions(20);
  
   if (fishyMotorSpeed.changed) {
    
    //If the speed is greater than the max, it will be set to the max
    if (fishyMotorSpeed.value > MAX_SPEED){
      fishyMotorSpeed.value = MAX_SPEED;
    }
    
    //If the speed is smaller than the min, it will be set to the min - unless it's 0
    if (fishyMotorSpeed.value < MIN_SPEED && fishyMotorSpeed.value != 0){
      fishyMotorSpeed.value = MIN_SPEED;
    }
    
    analogWrite(FISHY_MOTOR_PORT, fishyMotorSpeed.value); 
    fishyMotorSpeed.changed = false;
  }
  
  analogWrite(FISHY_MOTOR_PORT, 1);
  delay(5000);
  analogWrite(FISHY_MOTOR_PORT, 0);
  
  //digitalWrite(FISHY_MOTOR_PORT, MAX_SPEED);
  //delay(1000);
  //digitalWrite(FISHY_MOTOR_PORT, MIN_SPEED;
}

void exit() {
  analogWrite(FISHY_MOTOR_PORT, 0);
  //fishyMotor.setTargetPositionToStop();
  //while (!fishyMotor.processMovement());
  //fishyMotor.setCurrentPositionInRevolutions(0);
  //fishyMotor.setTargetPositionInRevolutions(0);
  //fishyMotor.disableStepper();
}
}

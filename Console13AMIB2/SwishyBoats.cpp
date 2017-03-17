//SWISHYBOATS.CPP 3 
//Rewritten to test multi-sensor test
//Status - 
//         new - trying to fix cycleBall code without the sensors
//         3/14/17, P.1 8:30am

#include <FlexyStepper.h>
#include "states.h"

// Tests the whole system of 4 LIDAR sensors with the multiplexor

namespace SWISHYBOATS {
  
//This declares the pistons and sensors at the start and end of the boats  
const byte BOAT_ENTRANCE_STOP = 3;
const byte BOAT_EXIT_PS = A1;  
const byte BOAT_EXIT_STOP = 4;

//this sets all of the steppers and ports
FlexyStepper boat1Stepper;
const byte BOAT_1_STEPPER_PORT = 1;
FlexyStepper boat2Stepper;
const byte BOAT_2_STEPPER_PORT = 2;
FlexyStepper boat3Stepper;
const byte BOAT_3_STEPPER_PORT = 3;
FlexyStepper boat4Stepper;
const byte BOAT_4_STEPPER_PORT = 4;

//This sets the speed of the boats
const byte STEPS_PER_MM = 25 * 2;
const float HOMING_SPEED_IN_MMPS = 100;
const float SPEED_IN_MMPS = 10000; //speed for cycleBall 560
const float ACCEL_IN_MMPSPS = 350; //acceleration for cycleBall 365
const float MAX_DIST_IN_MM = 80; // 80

//This sets the limit switches on each boat, two for each.
const byte BOAT_1_LEFT_LS = 23;
const byte BOAT_1_RIGHT_LS = 24;
const byte BOAT_2_LEFT_LS = 25;
const byte BOAT_2_RIGHT_LS = 26;
const byte BOAT_3_LEFT_LS = 27;
const byte BOAT_3_RIGHT_LS = 28;
const byte BOAT_4_LEFT_LS = 29;
const byte BOAT_4_RIGHT_LS = A0;

//sets the left and right limit switches for the array below
const int LEFT = 1;
const int RIGHT = -1;

//calls the boat number arrays
FlexyStepper *const BOATY_STEPPERS[] = {&boat1Stepper, &boat2Stepper, &boat3Stepper, &boat4Stepper};
int boatCount = sizeof(BOATY_STEPPERS)/sizeof(FlexyStepper *);

//calls the boat homing arrays
int homeLimitSwitch[] = {BOAT_1_RIGHT_LS, BOAT_2_RIGHT_LS, BOAT_3_LEFT_LS, BOAT_4_RIGHT_LS};
int homeDirection[] = {-1, -1, 1, -1}; //-1 is right, 1 is left
int leftLimitSwitch[] = {BOAT_1_LEFT_LS, BOAT_2_LEFT_LS, BOAT_3_LEFT_LS, BOAT_4_LEFT_LS};
int rightLimitSwitch[] = {BOAT_1_RIGHT_LS, BOAT_2_RIGHT_LS, BOAT_3_RIGHT_LS, BOAT_4_RIGHT_LS};


//homes the boats (though this isn't an event)
void homeBoats() {
  for (byte i = 0; i < boatCount; i++) {
    FlexyStepper *boatStepper = BOATY_STEPPERS[i];
    boatStepper->enableStepper();
    boatStepper->moveToHomeInMillimeters(homeDirection[i], HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, homeLimitSwitch[i]);
    boatStepper->setCurrentPositionInMillimeters(-31.0);
  if (i == 2)   {
    boatStepper->setCurrentPositionInMillimeters(31.0);
    boatStepper->moveRelativeInMillimeters(-10); //60 gets the boats off of the switches
  }
    else          boatStepper->moveRelativeInMillimeters(10); //60 gets the boats off of the switches
    boatStepper->disableStepper();
  }
}

//////////////////////     Set Up       ///////////////////////////

void setup() {
  
   //connects the ports
  boat1Stepper.connectToPort(BOAT_1_STEPPER_PORT);
  boat2Stepper.connectToPort(BOAT_2_STEPPER_PORT);
  boat3Stepper.connectToPort(BOAT_3_STEPPER_PORT);
  boat4Stepper.connectToPort(BOAT_4_STEPPER_PORT);
  
  //Sets the speed and acceleration of the boats
  for (byte i = 0; i < boatCount; i++) {
      FlexyStepper *boatStepper = BOATY_STEPPERS[i];
      boatStepper->setStepsPerMillimeter(STEPS_PER_MM);
      boatStepper->setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
      boatStepper->setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
      boatStepper->disableStepper();
  }
  
  //sets imput_pullup or output for the limit switches and sensors 
  pinMode(BOAT_ENTRANCE_STOP, OUTPUT);
  pinMode(BOAT_EXIT_STOP, OUTPUT);

  //sets the start sensor and the end sensor 
  digitalWrite(BOAT_ENTRANCE_STOP, LOW);
  digitalWrite(BOAT_EXIT_STOP, LOW);
  
  homeBoats();   
}

//homes the boats when you enter the swishyboats state
void enter() {
  homeBoats();
}


////////////////////////////////////     LOOP      //////////////////////////////////////////
/*
 * Sequentailly scans devices from ports 0-i for their LIDAR readings
 */

void loop() {
}
//////////////////////////  EVENTS - ORIGINALS SAVED IN THE SWISHYBOATS.CPP -2  ///////////////////////

//opens and closes the gate at the top of the boats
void events::cycleEntranceStop() {
  digitalWrite(BOAT_ENTRANCE_STOP, HIGH);
  delay(1500);
  digitalWrite(BOAT_ENTRANCE_STOP, LOW);

}

//opens the exit stop at the end of the boats
void events::cycleExitStop() {
  digitalWrite(BOAT_EXIT_STOP, HIGH);
  delay(1500);
  digitalWrite(BOAT_EXIT_STOP, LOW);
}

//just opens the gate at the top of the boats
void events::entranceStopOn(){
  digitalWrite(BOAT_ENTRANCE_STOP, LOW); 
}

//just closes the gate at the top of the boats
void events::entranceStopOff(){
  digitalWrite(BOAT_ENTRANCE_STOP, HIGH);
}

//Boolean to check the limit switches
bool checkBoatLimitSwitches(int boatIndex) {
  return !digitalRead(leftLimitSwitch[boatIndex]) || !digitalRead(rightLimitSwitch[boatIndex]);
}

//actually moves the boats...called in cycleBall
void cycleBoat(int boatIndex, int count) {

    bool ballDetected = false;
    float distance = 62.0/2;
    int nextBoat = boatIndex +1;
    FlexyStepper *boatStepper = BOATY_STEPPERS[boatIndex];
    boatStepper->enableStepper();
    boatStepper->setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
    
    for (int i = 0; i < 2 * count; i++) {      
      boatStepper->setTargetPositionInMillimeters(distance);
      while (!boatStepper->motionComplete()) {
        // COMMENT OUT FOLLOWING LINE IF SENSORLESS BALL CYCLE IS NEEDED
        //if(checkLIDAR(nextBoat) || !digitalRead(BOAT_EXIT_PS)) break; // stops boat if next boat position's LIDAR sensor is tripped
        boatStepper->processMovement();
      }
      distance = -distance;
    }
    boatStepper->disableStepper();
}

//calls the cycleBoat function with sensors max count. cycleBoat is above
void events::cycleBall() {  
    int MAX_COUNT = 10; 
    
    events::cycleEntranceStop();
    digitalWrite(BOAT_EXIT_STOP, LOW);
    
    delay(350);
    
    cycleBoat(0, MAX_COUNT); //boat 1
    cycleBoat(1, MAX_COUNT); //boat 2
    cycleBoat(2, MAX_COUNT); //boat 3
    cycleBoat(3, MAX_COUNT); //boat 4 //BOAT_EXIT_PS
}

//runs the last boat in a loop for testing
void events::lastBoat() {
  /*
  boat4Stepper.enableStepper();
  
  boat4Stepper.moveToHomeInMillimeters(-1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_4_RIGHT_LS);
  boat4Stepper.moveToPositionInMillimeters(65.0);
  digitalWrite(BOAT_EXIT_STOP, LOW);
    
  int x = HIGH; //the sensor is high, no ball is there
   
  while(digitalRead(BOAT_EXIT_PS)) {
    //x = digitalRead(BOAT_2_SENSOR); //update this
    
    if (x == LOW){ //if there's a ball, move
      boat4Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
      boat4Stepper.moveToPositionInMillimeters(50.0);
      boat4Stepper.moveToPositionInMillimeters(10.0);
      boat4Stepper.moveToPositionInMillimeters(70.0);
      boat4Stepper.moveToPositionInMillimeters(10.0);
      boat4Stepper.moveToPositionInMillimeters(20.0); 
    }
  }
  delay(2000);
  events::cycleExitStop();
*/
}

// TT CODE
void events::test() {

}


void exit() {
}

}
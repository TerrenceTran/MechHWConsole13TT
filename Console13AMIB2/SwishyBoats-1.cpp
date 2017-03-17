#include "states.h"

#include <FlexyStepper.h>
#include <Encoder.h>

#include "states.h"

namespace SWISHYBOATS1 {
/*
FlexyStepper boat1Stepper;
const byte BOAT_1_STEPPER_PORT = 1;
FlexyStepper boat2Stepper;
const byte BOAT_2_STEPPER_PORT = 2;
FlexyStepper boat3Stepper;
const byte BOAT_3_STEPPER_PORT = 3;
FlexyStepper boat4Stepper;
const byte BOAT_4_STEPPER_PORT = 4;
FlexyStepper *const BOATY_STEPPERS[] = {&boat1Stepper, &boat2Stepper, &boat3Stepper, &boat4Stepper};

const byte STEPS_PER_MM = 25 * 2;
const float HOMING_SPEED_IN_MMPS = 10;
const float SPEED_IN_MMPS = 10000;
const float ACCEL_IN_MMPSPS = 350;
const float MAX_DIST_IN_MM = 70;

const byte BOAT_ENTRANCE_PS = 8;
const byte BOAT_ENTRANCE_STOP = 3;
const byte BOAT_EXIT_PS = A1;
const byte BOAT_EXIT_STOP = 4;

const byte BOAT_1_LEFT_LS = 23;
const byte BOAT_1_RIGHT_LS = 24;
const byte BOAT_2_LEFT_LS = 25;
const byte BOAT_2_RIGHT_LS = 26;
const byte BOAT_3_LEFT_LS = 27;
const byte BOAT_3_RIGHT_LS = 28;
const byte BOAT_4_LEFT_LS = 29;
const byte BOAT_4_RIGHT_LS = A0;

const byte BOAT_2_SENSOR = A7;

// NOTE: all of {setup, enter, loop, exit} are optional

void setup() {
  // do setup!
  // things like pinMode, configure steppers, etc.
  Serial.begin(9600);
  
  boat1Stepper.connectToPort(BOAT_1_STEPPER_PORT);
  boat2Stepper.connectToPort(BOAT_2_STEPPER_PORT);
  boat3Stepper.connectToPort(BOAT_3_STEPPER_PORT);
  boat4Stepper.connectToPort(BOAT_4_STEPPER_PORT);

  for (byte i = 0; i < 4; i++) {
    FlexyStepper *stp = BOATY_STEPPERS[i];
    stp->setStepsPerMillimeter(STEPS_PER_MM);
    stp->setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
    stp->setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  }

  pinMode(BOAT_1_LEFT_LS, INPUT_PULLUP);
  pinMode(BOAT_1_RIGHT_LS, INPUT_PULLUP);
  pinMode(BOAT_2_LEFT_LS, INPUT_PULLUP);
  pinMode(BOAT_2_RIGHT_LS, INPUT_PULLUP);
  pinMode(BOAT_3_LEFT_LS, INPUT_PULLUP);
  pinMode(BOAT_3_RIGHT_LS, INPUT_PULLUP);
  pinMode(BOAT_4_LEFT_LS, INPUT_PULLUP);
  pinMode(BOAT_4_RIGHT_LS, INPUT_PULLUP);
  pinMode(BOAT_ENTRANCE_PS, INPUT_PULLUP);
  pinMode(BOAT_EXIT_PS, INPUT_PULLUP);  
  pinMode(BOAT_ENTRANCE_STOP, OUTPUT);
  pinMode(BOAT_EXIT_STOP, OUTPUT);
  
  pinMode(BOAT_2_SENSOR, INPUT_PULLUP);  
  
  digitalWrite(BOAT_ENTRANCE_STOP, LOW);
  digitalWrite(BOAT_EXIT_STOP, LOW);

  FlexyHomingSpec homingSpecs[] = {
    FlexyHomingSpec(&boat1Stepper, -1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_1_LEFT_LS),
    FlexyHomingSpec(&boat2Stepper, -1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_2_LEFT_LS),
    FlexyHomingSpec(&boat3Stepper, -1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_3_LEFT_LS),
    FlexyHomingSpec(&boat4Stepper, -1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_4_LEFT_LS)
  };
  // FlexyStepper::homeMultipleInMillimeters(sizeof(homingSpecs) / sizeof(FlexyHomingSpec), homingSpecs);

  boat1Stepper.moveToHomeInMillimeters(-1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_1_LEFT_LS);
  boat2Stepper.moveToHomeInMillimeters(-1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_2_LEFT_LS);
  boat3Stepper.moveToHomeInMillimeters(-1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_3_LEFT_LS);
  boat4Stepper.moveToHomeInMillimeters(-1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_4_LEFT_LS);
  Serial.println("finished homing!");
  
  boat1Stepper.setCurrentPositionInMillimeters(0.0);
  boat2Stepper.setCurrentPositionInMillimeters(0.0);
  boat3Stepper.setCurrentPositionInMillimeters(0.0);
  boat4Stepper.setCurrentPositionInMillimeters(0.0);

//  boat1Stepper.setLimitSwitchPins(BOAT_1_LEFT_LS, BOAT_1_RIGHT_LS);
//  boat2Stepper.setLimitSwitchPins(BOAT_2_RIGHT_LS, BOAT_2_LEFT_LS);
//  boat3Stepper.setLimitSwitchPins(BOAT_3_LEFT_LS, BOAT_3_RIGHT_LS);
//  boat4Stepper.setLimitSwitchPins(BOAT_4_RIGHT_LS, BOAT_4_LEFT_LS);

  boat1Stepper.disableStepper();
  boat2Stepper.disableStepper();
  boat3Stepper.disableStepper();
  boat4Stepper.disableStepper();
}

void enter() {
  boat1Stepper.enableStepper();
  boat2Stepper.enableStepper();
  boat3Stepper.enableStepper();
  boat4Stepper.enableStepper();
}

void loop() {
  Serial.print("LEFT 1: ");
  Serial.print(digitalRead(BOAT_2_LEFT_LS));
  Serial.print("  |  ");
  Serial.print("RIGHT 1: ");
  Serial.println(digitalRead(BOAT_2_RIGHT_LS));
  
  if (boat1Pos.changed) {
    Serial.println("Boat 1 Changed");
    if (boat1Pos.value <= 10000) {
      boat1Stepper.setTargetPositionInMillimeters(((float) boat1Pos.value) * (MAX_DIST_IN_MM / 10000.0));
    }
    boat1Pos.changed = false;
  }
  if (boat2Pos.changed) {
     Serial.println("Boat 2 Changed");
    if (boat2Pos.value <= 10000) {
      boat2Stepper.setTargetPositionInMillimeters(((float) boat2Pos.value) * (MAX_DIST_IN_MM / 10000.0));
    }
    boat2Pos.changed = false;
  }
  if (boat3Pos.changed) {
     Serial.println("Boat 3 Changed");
    if (boat3Pos.value <= 10000) {
      boat3Stepper.setTargetPositionInMillimeters(((float) boat3Pos.value) * (MAX_DIST_IN_MM / 10000.0));
    }
    boat3Pos.changed = false;
  }
  if (boat4Pos.changed) {
     Serial.print("Boat 4 Changed");
    if (boat4Pos.value <= 10000) {
      boat4Stepper.setTargetPositionInMillimeters(((float) boat4Pos.value) * (MAX_DIST_IN_MM / 10000.0));
    }
    boat4Pos.changed = false;
  }

  //boat1Stepper.processMovement();
  //boat2Stepper.processMovement();
  //boat3Stepper.processMovement();
  //boat4Stepper.processMovement();
}

bool updateLimitSwitchValues(bool *array) {
  /*if(sizeof(array) != 8)
    return false;
  
  array[0] = !digitalRead(BOAT_1_LEFT_LS);
  array[1] = !digitalRead(BOAT_1_RIGHT_LS);
  array[2] = !digitalRead(BOAT_2_LEFT_LS);
  array[3] = !digitalRead(BOAT_2_RIGHT_LS);
  array[4] = !digitalRead(BOAT_3_LEFT_LS);
  array[5] = !digitalRead(BOAT_3_RIGHT_LS);
  array[6] = !digitalRead(BOAT_4_LEFT_LS);
  array[7] = !digitalRead(BOAT_4_RIGHT_LS);
  
  return true;
}

void events::cycleEntranceStop() {
  digitalWrite(BOAT_ENTRANCE_STOP, HIGH);
  delay(1500);
  digitalWrite(BOAT_ENTRANCE_STOP, LOW);
}

void events::cycleExitStop() {
  digitalWrite(BOAT_EXIT_STOP, HIGH);
  delay(1500);
  digitalWrite(BOAT_EXIT_STOP, LOW);
}

void events::entranceStopOn(){
  digitalWrite(BOAT_ENTRANCE_STOP, LOW);
}

void events::entranceStopOff(){
  digitalWrite(BOAT_ENTRANCE_STOP, HIGH);
}

//demo
void events::demo() {
  int DELAY_TIME = 0;
  float distance = 60.0;
  bool limitSwitchTriggered = false;
  bool limitSwitches[] = {0, 0, 0, 0, 0, 0, 0, 0};
  int count = 0;
  int MAX_COUNT = 10;
  
  events::cycleEntranceStop();
  digitalWrite(BOAT_EXIT_STOP, LOW);
  
  boat1Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  boat1Stepper.moveToPositionInMillimeters(10);
  boat2Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  boat2Stepper.moveToPositionInMillimeters(10);
  boat3Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  boat3Stepper.moveToPositionInMillimeters(10);
  boat4Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  boat4Stepper.moveToPositionInMillimeters(10);
  delay(1000);
  
  while(digitalRead(BOAT_EXIT_PS) && count < MAX_COUNT) {
    boat1Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat2Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat3Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat4Stepper.setTargetPositionRelativeInMillimeters(distance);
    
    while((!boat1Stepper.motionComplete()) && !limitSwitchTriggered) {
        boat1Stepper.processMovement();
        
        updateLimitSwitchValues(limitSwitches);
        for(int i = 0; i < sizeof(limitSwitches); i++) {
          if(limitSwitches[i] == 1) {
            boat1Stepper.disableStepper();
            boat2Stepper.disableStepper();
            boat3Stepper.disableStepper();
            boat4Stepper.disableStepper();
            limitSwitchTriggered = true;
            Serial.println("SWITCH TRIGGERED");
          }
        }
        
        if(!digitalRead(BOAT_EXIT_PS))
          break;
    } 
    
    count++;
    distance = -distance;
    delay(DELAY_TIME);
    //DELAY_TIME += 25;
  }
  count = 0;
  
  while(digitalRead(BOAT_EXIT_PS) && count < MAX_COUNT) {
    boat1Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat2Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat3Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat4Stepper.setTargetPositionRelativeInMillimeters(distance);
    
    while((!boat2Stepper.motionComplete()) && !limitSwitchTriggered) {
        boat2Stepper.processMovement();
        
        updateLimitSwitchValues(limitSwitches);
        for(int i = 0; i < sizeof(limitSwitches); i++) {
          if(limitSwitches[i] == 1) {
            boat1Stepper.disableStepper();
            boat2Stepper.disableStepper();
            boat3Stepper.disableStepper();
            boat4Stepper.disableStepper();
            limitSwitchTriggered = true;
            Serial.println("SWITCH TRIGGERED");
          }
        }
        
        if(!digitalRead(BOAT_EXIT_PS))
          break;
    } 
    
    count++;
    distance = -distance;
    delay(DELAY_TIME);
    //DELAY_TIME += 25;
  }
  
  count = 0;
  
  while(digitalRead(BOAT_EXIT_PS) && count < MAX_COUNT) {
    boat1Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat2Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat3Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat4Stepper.setTargetPositionRelativeInMillimeters(distance);
    
    while((!boat3Stepper.motionComplete()) && !limitSwitchTriggered) {
        boat3Stepper.processMovement();
        
        updateLimitSwitchValues(limitSwitches);
        for(int i = 0; i < sizeof(limitSwitches); i++) {
          if(limitSwitches[i] == 1) {
            boat1Stepper.disableStepper();
            boat2Stepper.disableStepper();
            boat3Stepper.disableStepper();
            boat4Stepper.disableStepper();
            limitSwitchTriggered = true;
            Serial.println("SWITCH TRIGGERED");
          }
        }
        
        if(!digitalRead(BOAT_EXIT_PS))
          break;
    } 
    
    count++;
    distance = -distance;
    delay(DELAY_TIME);
    //DELAY_TIME += 25;
  }
  
  count = 0;
  
  while(digitalRead(BOAT_EXIT_PS) && count < MAX_COUNT) {
    boat1Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat2Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat3Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat4Stepper.setTargetPositionRelativeInMillimeters(distance);
    
    while((!boat4Stepper.motionComplete()) && !limitSwitchTriggered) {
        boat4Stepper.processMovement();
        
        updateLimitSwitchValues(limitSwitches);
        for(int i = 0; i < sizeof(limitSwitches); i++) {
          if(limitSwitches[i] == 1) {
            boat1Stepper.disableStepper();
            boat2Stepper.disableStepper();
            boat3Stepper.disableStepper();
            boat4Stepper.disableStepper();
            limitSwitchTriggered = true;
            Serial.println("SWITCH TRIGGERED");
          }
        }
        
        if(!digitalRead(BOAT_EXIT_PS))
          break;
    } 
    
    count++;
    distance = -distance;
    delay(DELAY_TIME);
    //DELAY_TIME += 25;
  }
  //boat2Stepper.moveToPositionInMillimeters(0.0);
  
  boat1Stepper.moveToPositionInMillimeters(10);
  boat2Stepper.moveToPositionInMillimeters(10);
  boat3Stepper.moveToPositionInMillimeters(10);
  boat4Stepper.moveToPositionInMillimeters(10);
  
  delay(1500);
  if(digitalRead(BOAT_EXIT_PS)) {
    events::demo();
  }
  //events::cycleExitStop();
}

void cycleBoat(FlexyStepper& boat, float distance) {
  
}

//cycleBall
void events::cycleBall(void) {
    int DELAY_TIME = 0;
  float distance = 60.0;
  bool limitSwitchTriggered = false;
  bool limitSwitches[] = {0, 0, 0, 0, 0, 0, 0, 0};
  int count = 0;
  int MAX_COUNT = 10;
  
  events::cycleEntranceStop();
  digitalWrite(BOAT_EXIT_STOP, LOW);
  
  boat1Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  boat1Stepper.moveToPositionInMillimeters(10);
  boat2Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  boat2Stepper.moveToPositionInMillimeters(10);
  boat3Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  boat3Stepper.moveToPositionInMillimeters(10);
  boat4Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  boat4Stepper.moveToPositionInMillimeters(10);
  delay(1000);
  
  while(digitalRead(BOAT_EXIT_PS) && count < MAX_COUNT) {
    boat1Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat2Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat3Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat4Stepper.setTargetPositionRelativeInMillimeters(distance);
    
    while((!boat1Stepper.motionComplete()) && !limitSwitchTriggered) {
        boat1Stepper.processMovement();
        
        updateLimitSwitchValues(limitSwitches);
        for(int i = 0; i < sizeof(limitSwitches); i++) {
          if(limitSwitches[i] == 1) {
            boat1Stepper.disableStepper();
            boat2Stepper.disableStepper();
            boat3Stepper.disableStepper();
            boat4Stepper.disableStepper();
            limitSwitchTriggered = true;
            Serial.println("SWITCH TRIGGERED");
          }
        }
        
        if(!digitalRead(BOAT_EXIT_PS))
          break;
    } 
    
    count++;
    distance = -distance;
    delay(DELAY_TIME);
    //DELAY_TIME += 25;
  }
  count = 0;
  
  //test with the new sensor
  //while(digitalRead(BOAT_2_SENSOR) == HIGH){
    //delay(10);
  //}
  
  while(digitalRead(BOAT_EXIT_PS) && count < MAX_COUNT) {
    boat1Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat2Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat3Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat4Stepper.setTargetPositionRelativeInMillimeters(distance);
    
    while((!boat2Stepper.motionComplete()) && !limitSwitchTriggered) {
        boat2Stepper.processMovement();
        
        updateLimitSwitchValues(limitSwitches);
        for(int i = 0; i < sizeof(limitSwitches); i++) {
          if(limitSwitches[i] == 1) {
            boat1Stepper.disableStepper();
            boat2Stepper.disableStepper();
            boat3Stepper.disableStepper();
            boat4Stepper.disableStepper();
            limitSwitchTriggered = true;
            Serial.println("SWITCH TRIGGERED");
          }
        }
        
        if(!digitalRead(BOAT_EXIT_PS))
          break;
    } 
    
    count++;
    distance = -distance;
    delay(DELAY_TIME);
    //DELAY_TIME += 25;
  }
  
  count = 0;
  
  while(digitalRead(BOAT_EXIT_PS) && count < MAX_COUNT) {
    boat1Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat2Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat3Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat4Stepper.setTargetPositionRelativeInMillimeters(distance);
    
    while((!boat3Stepper.motionComplete()) && !limitSwitchTriggered) {
        boat3Stepper.processMovement();
        
        updateLimitSwitchValues(limitSwitches);
        for(int i = 0; i < sizeof(limitSwitches); i++) {
          if(limitSwitches[i] == 1) {
            boat1Stepper.disableStepper();
            boat2Stepper.disableStepper();
            boat3Stepper.disableStepper();
            boat4Stepper.disableStepper();
            limitSwitchTriggered = true;
            Serial.println("SWITCH TRIGGERED");
          }
        }
        
        if(!digitalRead(BOAT_EXIT_PS))
          break;
    } 
    
    count++;
    distance = -distance;
    delay(DELAY_TIME);
    //DELAY_TIME += 25;
  }
  
  count = 0;
  
  while(digitalRead(BOAT_EXIT_PS) && count < MAX_COUNT) {
    boat1Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat2Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat3Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat4Stepper.setTargetPositionRelativeInMillimeters(distance);
    
    while((!boat4Stepper.motionComplete()) && !limitSwitchTriggered) {
        boat4Stepper.processMovement();
        
        updateLimitSwitchValues(limitSwitches);
        for(int i = 0; i < sizeof(limitSwitches); i++) {
          if(limitSwitches[i] == 1) {
            boat1Stepper.disableStepper();
            boat2Stepper.disableStepper();
            boat3Stepper.disableStepper();
            boat4Stepper.disableStepper();
            limitSwitchTriggered = true;
            Serial.println("SWITCH TRIGGERED");
          }
        }
        
        if(!digitalRead(BOAT_EXIT_PS))
          break;
    } 
    
    count++;
    distance = -distance;
    delay(DELAY_TIME);
    //DELAY_TIME += 25;
  }
  //boat2Stepper.moveToPositionInMillimeters(0.0);
  
  boat1Stepper.moveToPositionInMillimeters(10);
  boat2Stepper.moveToPositionInMillimeters(10);
  boat3Stepper.moveToPositionInMillimeters(10);
  boat4Stepper.moveToPositionInMillimeters(10);
  //events::cycleExitStop();
}

//first boat
void events::firstBoat(){
  //int DELAY_TIME = 0;
  float distance = 60.0;
  bool limitSwitchTriggered = false;
  bool limitSwitches[] = {0, 0, 0, 0, 0, 0, 0, 0};
  int count = 0;
  int MAX_COUNT = 10;
  
  events::cycleEntranceStop();
  digitalWrite(BOAT_EXIT_STOP, LOW);
  
  boat1Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  boat1Stepper.moveToPositionInMillimeters(10);
  delay(1000);
  
  while(digitalRead(BOAT_EXIT_PS) && count < MAX_COUNT) {
    boat1Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat2Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat3Stepper.setTargetPositionRelativeInMillimeters(distance);
    boat4Stepper.setTargetPositionRelativeInMillimeters(distance);
    
    while((!boat1Stepper.motionComplete()) && !limitSwitchTriggered) {
        boat1Stepper.processMovement();
        
        updateLimitSwitchValues(limitSwitches);
        for(int i = 0; i < sizeof(limitSwitches); i++) {
          if(limitSwitches[i] == 1) {
            boat1Stepper.disableStepper();
            boat2Stepper.disableStepper();
            boat3Stepper.disableStepper();
            boat4Stepper.disableStepper();
            limitSwitchTriggered = true;
            Serial.println("SWITCH TRIGGERED");
          }
        }
        
        if(!digitalRead(BOAT_EXIT_PS))
          break;
    } 
    
    count++;
    distance = -distance;
    //delay(DELAY_TIME);
    //DELAY_TIME += 25;
  }
  count = 0;
  
}

//runs the last boat in a loop for testing
void events::lastBoat(){
  
  boat4Stepper.moveToHomeInMillimeters(-1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_4_LEFT_LS);
  digitalWrite(BOAT_EXIT_STOP, LOW);
  //events::cycleExitStop();
    
  int x = HIGH; //the sensor is high, no ball is there
   
  while(digitalRead(BOAT_EXIT_PS)) {
    x = digitalRead(BOAT_2_SENSOR);
    
    if (x == LOW){ //if there's a ball, move
      boat4Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
      boat4Stepper.moveToPositionInMillimeters(10.0);
      boat4Stepper.moveToPositionInMillimeters(70.0);
      boat4Stepper.moveToPositionInMillimeters(10.0);
      boat4Stepper.moveToPositionInMillimeters(20.0); 
    }
  }
  delay(2000);
  events::cycleExitStop();
}

void events::stopBoats(){
  boat1Stepper.disableStepper();
  boat2Stepper.disableStepper();
  boat3Stepper.disableStepper();
  boat4Stepper.disableStepper();
}

void exit() {
  boat1Stepper.disableStepper();
  boat2Stepper.disableStepper();
  boat3Stepper.disableStepper();
  boat4Stepper.disableStepper();
}

*/

}

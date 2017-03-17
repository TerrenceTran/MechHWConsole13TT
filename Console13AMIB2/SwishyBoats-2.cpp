//Real updated SwishyBoats
//MAX DISTANCE IS 80 MM, 65 IS SAFE

//#include <FlexyStepper.h>
//#include <Encoder.h>

//#include "states.h"

//currently works, tests only one LIDAR sensor
//////////Single_LIDAR_test//////////
// Single driver for vl6180x LIDAR sensor. Only 1 sensor can be hooked up directly to the I2C bus
/*
#include <Wire.h>
#include "Adafruit_VL6180X.h"

Adafruit_VL6180X vl = Adafruit_VL6180X();
//////////Single_LIDAR_test end//////////
*/
//doesn't work, supposed to use all of the sensors at once
//////////Multi_sensor_test//////////

// Tests the whole system of 4 LIDAR sensors with the multiplexor
//#include <Wire.h>
//#include <Adafruit_VL6180X.h> 
//extern "C" {
//#include "utility/twi.h" 
//}

//#define Multiplex 0x70
//#define IRSensor 0x29 // line not used, because address is default address declared in library

//Adafruit_VL6180X sensor = Adafruit_VL6180X(); 

//const int LED_PIN = 10; //added from single this and below, everything else is same
//const uint8_t port = 0; //choose port from 0-3 //////////////////////////

//////////Multi_sensor_test end//////////

namespace SWISHYBOATS2 {
/*
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
const float SPEED_IN_MMPS = 560; //speed for cycleBall here
const float ACCEL_IN_MMPSPS = 365; //acceleration for cycleBall here
const float MAX_DIST_IN_MM = 80;

//This declares the pistons and sensors at the start and end of the boats
//const byte BOAT_ENTRANCE_PS = 8; //NOW ON AMIB1
const byte BOAT_ENTRANCE_STOP = 3;
const byte BOAT_EXIT_PS = A1; //sensor has been replaced 1/3/17
const byte BOAT_EXIT_STOP = 4;

//This sets the limit switches on each boat, two for each.
const byte BOAT_1_LEFT_LS = 23;
const byte BOAT_1_RIGHT_LS = 24;
const byte BOAT_2_LEFT_LS = 25;
const byte BOAT_2_RIGHT_LS = 26;
const byte BOAT_3_LEFT_LS = 27;
const byte BOAT_3_RIGHT_LS = 28;
const byte BOAT_4_LEFT_LS = 29;
const byte BOAT_4_RIGHT_LS = A0;

//This sets the new sensors on boats 2, 3, and 4
const byte BOAT_2_SENSOR = A5; //change when put in A7
const byte BOAT_3_SENSOR = A5; //change when put in A6
const byte BOAT_4_SENSOR = A5;

//sets the left and right limit switches for the array below
const int LEFT = 1;
const int RIGHT = -1;

//calls all of the arrays, most using the swishyboats' limit switches
FlexyStepper *const BOATY_STEPPERS[] = {&boat1Stepper, &boat2Stepper, &boat3Stepper, &boat4Stepper};
int leftLimitSwitch[] = {BOAT_1_LEFT_LS, BOAT_2_LEFT_LS, BOAT_3_LEFT_LS, BOAT_4_LEFT_LS};
int rightLimitSwitch[] = {BOAT_1_RIGHT_LS, BOAT_2_RIGHT_LS, BOAT_3_RIGHT_LS, BOAT_4_RIGHT_LS};
int homeLimitSwitch[] = {BOAT_1_RIGHT_LS, BOAT_2_RIGHT_LS, BOAT_3_LEFT_LS, BOAT_4_RIGHT_LS}; //LS ARE BACKWARDS - fixed 1/11/16
int homeDirection[] = {-1, -1, 1, -1}; //-1 is right, 1 is left
int boatCount = sizeof(BOATY_STEPPERS)/sizeof(FlexyStepper *);
void homeBoats(); //calls the boat homing function

//////////Multi_sensor_test//////////
uint8_t status = 0;

void TCASelect(uint8_t i) {
  //if (i > 3) return; // if invalid input

  Wire.beginTransmission(Multiplex);
  Wire.write(1 << i);
  Wire.endTransmission();

  Serial.print("Selecting Port: ");
  Serial.println(i);
}

//////////Multi_sensor_test end//////////
/*
void () {
  
  if (sensor.changed) {
    stopboat;
    movenextboat;
  } 
}

void setup() {

  //starts the serial port
  Serial.begin(9600);
  
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
  pinMode(BOAT_1_LEFT_LS, INPUT_PULLUP);
  pinMode(BOAT_1_RIGHT_LS, INPUT_PULLUP);
  pinMode(BOAT_2_LEFT_LS, INPUT_PULLUP);
  pinMode(BOAT_2_RIGHT_LS, INPUT_PULLUP);
  pinMode(BOAT_3_LEFT_LS, INPUT_PULLUP);
  pinMode(BOAT_3_RIGHT_LS, INPUT_PULLUP);
  pinMode(BOAT_4_LEFT_LS, INPUT_PULLUP);
  pinMode(BOAT_4_RIGHT_LS, INPUT_PULLUP);
  //pinMode(BOAT_ENTRANCE_PS, INPUT_PULLUP);
  pinMode(BOAT_EXIT_PS, INPUT_PULLUP);  
  pinMode(BOAT_ENTRANCE_STOP, OUTPUT);
  pinMode(BOAT_EXIT_STOP, OUTPUT);
  pinMode(BOAT_2_SENSOR, INPUT_PULLUP);  
  
  //sets the start sensor and the end sensor 
  digitalWrite(BOAT_ENTRANCE_STOP, LOW);
  digitalWrite(BOAT_EXIT_STOP, LOW);
  
  homeBoats(); //actually homes the boats
  
//////////Single_LIDAR_test//////////
  //Serial.begin(115200); //called above already
/*
  // wait for serial port to open on native usb devices
  while (!Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL6180x test!");
  if (! vl.begin()) {
    Serial.println("Failed to find sensor");
    while (1);
  }
  Serial.println("Sensor found!");
  */
//////////Single_LIDAR_test end//////////  

//////////changed to single//////////MR TRAN SWEARING HERE
/*
while (!Serial);
  delay(100);
  Wire.begin();

  TCASelect(port);
  digitalWrite(LED_PIN, HIGH);

  //Serial.begin(115200);
  Serial.println("Starting Setup!");

  // wait for Serial port to open on native usb devices
  /*
  while (!Serial) {
    delay(1);
  }
  

  while (!sensor.begin()) {
    TCASelect(port); ///////////////// THIS WORKED?!?!!?!?/////////////////////////////
    sensor.begin();
    Serial.println("TRYING GDI");
  }

  if (!sensor.begin()) {
    Serial.print("Failed to find sensor ");
    Serial.println(port);
    //while (1); // halts if not found
  }

  Serial.print("Sensor ");
  Serial.print(port);
  Serial.println(" found!");
  
  float lux = sensor.readLux(VL6180X_ALS_GAIN_5);

  Serial.print("Lux: "); Serial.println(lux);

  delay(2000);
  
//////////changed to single end//////////
  
//////////Multi_sensor_test//////////
  while (!Serial);
  delay(100);
  Wire.begin();

  //Serial.begin(115200);
  Serial.println("Starting Setup!");

  for (uint8_t i = 0; i < 4; i++) {
    TCASelect(i);
    
    while (!sensor.begin()) {
      TCASelect(i); 
      sensor.begin();
      Serial.println("TRYING GDI");
      delay(250);
    }
    
    if (! sensor.begin()) {
      Serial.print("Failed to find sensor ");
      Serial.println(i);
      while (1); // Halts until all sensors found ********************************************
    }

    Serial.print("Sensor ");
    Serial.print(i);
    Serial.println(" found!");
  }
  Serial.println("All sensors ready");
  delay(1000);
//////////Multi_sensor_test end//////////

}

void enter() {
  homeBoats(); //just homes the boats when you enter the swishyboats state
}

Value<uint16_t> *const boatPosition[] = {&boat1Pos, &boat2Pos, &boat3Pos, &boat4Pos};

void updateBoatPosition(int boatIndex) { // changing the position of the boats 
    
    Value<uint16_t> *postion = boatPosition[boatIndex];
    
    if (postion->changed) {
        Serial.println("Boat 1 Changed");
        if (postion->value <= 10000) {
            BOATY_STEPPERS[boatIndex]->setTargetPositionInMillimeters(((float) postion->value) * (MAX_DIST_IN_MM/ 10000.0));
        }
        postion->changed = false;
    }
}

void loop() {
  //constantly updates where the boats are positioned
  for (int i = 0; i < boatCount; i++) {
      updateBoatPosition(i);
      //Serial.print("boat ");
      //Serial.print(i + 1);
      //Serial.println(" position updated");
  }
  
//////////Single_LIDAR_test//////////
//float lux = vl.readLux(VL6180X_ALS_GAIN_5);

  //Serial.print("Lux: "); Serial.println(lux);
  /*
  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();

  if (status == VL6180X_ERROR_NONE) {
    Serial.print("Range: "); Serial.println(range);
  } 
//////////Single_LIDAR_test end//////////  
  
//////////Multi_sensor_test//////////
  for (int i = 0; i < 4; i++) {

    TCASelect(i);
    Serial.println("TCASelect");
    
    while (!sensor.begin()) {
      Serial.print("connecting...");
    }
    //Serial.println("sanity check");
    
    uint8_t range = sensor.readRange(); //WHAT
    Serial.println("read range");
    status = sensor.readRangeStatus();
    Serial.print("Status: ");
    Serial.println(status);

    if (status == VL6180X_ERROR_NONE) {
      Serial.println("Range: " + range); 
    }
    else {
      //Serial.println("nothing");
    }
  }
    
//////////Multi_sensor_test end//////////changed to Single_sensor_test
//TCASelect(port);
/*
  float lux = sensor.readLux(VL6180X_ALS_GAIN_5);

  Serial.print("Lux: "); Serial.println(lux);

  uint8_t range = sensor.readRange();
  uint8_t status = sensor.readRangeStatus();

  if (status == VL6180X_ERROR_NONE) {
    Serial.print("Range: "); Serial.println(range);
  } 
//////////Multi_sensor_test////////// also used in single    
    // Some error occurred, print it out!

    if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5)) {
      Serial.println("System error");
    }
    else if (status == VL6180X_ERROR_ECEFAIL) {
      Serial.println("ECE failure"); //whaaaaaat its stuck here
      //Serial.println(status);
      //Serial.println(VL6180X_ERROR_ECEFAIL);
    }
    else if (status == VL6180X_ERROR_NOCONVERGE) { 
      Serial.println("No convergence"); //and here
    }
    else if (status == VL6180X_ERROR_RANGEIGNORE) {
      Serial.println("Ignoring range");
    }
    else if (status == VL6180X_ERROR_SNR) {
      Serial.println("Signal/Noise error");
    }
    else if (status == VL6180X_ERROR_RAWUFLOW) {
      Serial.println("Raw reading underflow");
    }
    else if (status == VL6180X_ERROR_RAWOFLOW) {
      Serial.println("Raw reading overflow");
    }
    else if (status == VL6180X_ERROR_RANGEUFLOW) {
      Serial.println("Range reading underflow");
    }
    else if (status == VL6180X_ERROR_RANGEOFLOW) {
      Serial.println("Range reading overflow");
    }
    else {
      //Serial.println("No errors found");
    }
    delay(500);
}
//////////Multi_sensor_test end//////////  

///////////////////////////////////////////////////////////////////EVENTS////////////////////////////////////////////////////////////////////////////////

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

//homes the boats (though this isn't an event)
void homeBoats() {
  for (byte i = 0; i < boatCount; i++) {
    FlexyStepper *boatStepper = BOATY_STEPPERS[i];
    boatStepper->enableStepper();
    boatStepper->moveToHomeInMillimeters(homeDirection[i], HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, homeLimitSwitch[i]);
    boatStepper->setCurrentPositionInMillimeters(0.0);
    if(i == 2) {
      boatStepper->setCurrentPositionInMillimeters(65.0);
    }
    boatStepper->disableStepper();
  }
}

//actually moves the boats...called in cycleBall
void cycleBoat(int boatIndex, float direction, int sensor, int count) {
    bool ballDetected = false;
    FlexyStepper *boatStepper = BOATY_STEPPERS[boatIndex];
    
    float distance = 62.0 / 2; //deleted * direction
    //distance = distance / count; // TT CHANGED THIS
    
    boatStepper->enableStepper();
    boatStepper->setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
    boatStepper->moveToPositionInMillimeters(60); //gets the boats off of the switches
    
    for (int i = 0; i < 2 * count; i++) {
      
      //Position isn't relative anymore
      /*for (int rep = 0; rep < 2; rep++) { //something that moves the boats a lot then a little
        
        if (rep == 0 || rep == 2) { 
          boatStepper->setTargetPositionRelativeInMillimeters(distance);
        } 
        else if (rep == 1) {
          boatStepper->setTargetPositionRelativeInMillimeters(distance / 5);
        }
      }
      
      
      //swishes the boats long and short
      if (i%4 == 0 || i%4 == 1){
        boatStepper->setTargetPositionInMillimeters(distance + 32); //63, 1 
        delay(47); //50 to launch the ball, DON'T CHANGE THIS
      }
      else if (i%4 == 2) {
        boatStepper->setTargetPositionInMillimeters((-distance / 4) + 35); //28.8, 41.2
      }
      
      //checks the sensors
      while (!boatStepper->motionComplete()) {
        if ((sensor != -1) && (ballDetected == false)) {
          ballDetected = !digitalRead(sensor); 
        }
           
        boatStepper->processMovement();
            
        if (checkBoatLimitSwitches(boatIndex)) {
          break;
        }
      }
        
      if (ballDetected) {
        break;
      }
       
      distance = -distance;
    }
    
    boatStepper->disableStepper();
}

//calls the cycleBoat function with sensors max count. cycleBoat is above
void events::cycleBall() {
    int MAX_COUNT = 10; 
    //float distance = 58.0;
    
    events::cycleEntranceStop();
    digitalWrite(BOAT_EXIT_STOP, LOW);
    
    delay(350);
    
    cycleBoat(0, LEFT, BOAT_2_SENSOR, MAX_COUNT); //boat 1
    cycleBoat(1, LEFT, -1, MAX_COUNT); //boat 2, needs sensor
    cycleBoat(2, RIGHT, -1, MAX_COUNT); //boat 3, needs sensor
    cycleBoat(3, LEFT, BOAT_EXIT_PS, MAX_COUNT); //boat 4
}

//DEMO, not used, basically the same thing as cycleBall anyway
void events::demo() {
    int MAX_COUNT = 10;
    float distance = 60.0;
    
    events::cycleEntranceStop();
    digitalWrite(BOAT_EXIT_STOP, LOW);
    
    cycleBoat(0, distance, BOAT_2_SENSOR, MAX_COUNT);
    cycleBoat(1, distance, BOAT_3_SENSOR, MAX_COUNT);
    cycleBoat(2, distance, BOAT_4_SENSOR, MAX_COUNT);
    cycleBoat(3, distance, -1, MAX_COUNT);
  
    delay(1500);
    if(digitalRead(BOAT_EXIT_PS)) {
        events::demo();
    }
}

//doesn't work, ignore this
void events::firstBoat(){
    int MAX_COUNT = 10;
    float distance = 60.0;
    
    events::cycleEntranceStop();
    digitalWrite(BOAT_EXIT_STOP, LOW);
    cycleBoat(0, distance, BOAT_2_SENSOR, MAX_COUNT);
}

//runs the last boat in a loop for testing
void events::lastBoat(){
  boat4Stepper.enableStepper();
  
  boat4Stepper.moveToHomeInMillimeters(-1, HOMING_SPEED_IN_MMPS, MAX_DIST_IN_MM, BOAT_4_RIGHT_LS);
  boat4Stepper.moveToPositionInMillimeters(65.0);
  digitalWrite(BOAT_EXIT_STOP, LOW);
  //events::cycleExitStop();
    
  int x = HIGH; //the sensor is high, no ball is there
   
  while(digitalRead(BOAT_EXIT_PS)) {
    x = digitalRead(BOAT_2_SENSOR);
    
    if (x == LOW){ //if there's a ball, move
      boat4Stepper.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
      boat4Stepper.moveToPositionInMillimeters(50.0);
      //boat4Stepper.moveToPositionInMillimeters(10.0);
      //boat4Stepper.moveToPositionInMillimeters(70.0);
      //boat4Stepper.moveToPositionInMillimeters(10.0);
      //boat4Stepper.moveToPositionInMillimeters(20.0); 
    }
  }
  delay(2000);
  events::cycleExitStop();
}

//breaks the loop, though idk if this still works
void events::stopBoats() {
    for (byte i = 0; i < boatCount; i++) {
        FlexyStepper *boatStepper = BOATY_STEPPERS[i];
        boatStepper->disableStepper();
    }
}

//makes sure the boats are stopped when exiting the state
void exit() {
    events::stopBoats();
}
*/
}

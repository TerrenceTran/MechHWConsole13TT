
#include "states.h"

#include <Wire.h>
#include <Adafruit_VL6180X.h>
extern "C" {
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

#define Multiplex 0x70
#define IRSensor 0x29 // line not used, because address is default address declared in library

Adafruit_VL6180X sensor = Adafruit_VL6180X();

namespace SWISHYBOATS {

/////////////////////////  GLOBAL VARIABLES  //////////////////////////

//This calibrates the LIDAR sensors on the boats
int boat1Sensor = 30;
int boat2Sensor = 30;
int boat3Sensor = 30;
int boat4Sensor = 30;
uint8_t LIDARAverage[] = {boat1Sensor, boat2Sensor, boat3Sensor, boat4Sensor};

//Used in loop, probably breaking
uint8_t range;
uint8_t status;

//Changes Multiplexor from 0-3 for LIDAR sensors
void TCASelect(uint8_t i) {
  if (i > 3) return; // if invalid input

  Wire.beginTransmission(Multiplex);
  Wire.write(1 << i);
  Wire.endTransmission();

  //Serial.print("Selecting Port: ");
  //Serial.println(i);
}

//Moved LIDAR error codes to seperate method for streamlining
void debugLIDAR(int index, uint8_t status) {
    if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5)) {
      Serial.println("System error");
    }
    else if (status == VL6180X_ERROR_ECEFAIL) {
      Serial.println("ECE failure");
    }
    else if (status == VL6180X_ERROR_NOCONVERGE) {
      Serial.println("No convergence");
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
}

//checks the sensors and detects if the ball is there based off of the difference it changed
bool checkLIDAR(uint8_t index) {
  
  bool ballFound = false;
 
  if (index < 4) {
    TCASelect(index); //boatNumber.value
    range = sensor.readRange();
    status = sensor.readRangeStatus();
    
//    Serial.println(range);
//    Serial.println(status);
  
    debugLIDAR(index, status);
    if (status == VL6180X_ERROR_NONE) {
      if(abs(LIDARAverage[index] - range) > 10) {
        ballFound = true;
      }
    }
 //   else {Serial.print("NOPE");}
  }
  
  return ballFound;
}

void setup() {

  //Which sensor is being read and passing value initialization
  boatNumber.value = 0;
  LIDAR1Trig.value = false;
  LIDAR2Trig.value = false;
  LIDAR3Trig.value = false;
  LIDAR4Trig.value = false;
  RemoteValue<bool>* LIDARTrig[] = {&LIDAR1Trig, &LIDAR2Trig, &LIDAR3Trig, &LIDAR4Trig};

  //waits to start until the serial monitor works
  while (!Serial3);
  delay(100);
  Wire.begin();
  
  //sets the serial monitor at 115200 and prints that it's starting
  Serial3.begin(115200);
  Serial3.println("Starting Setup!");
  
  //goes through initializing the 4 sensors
  for (uint8_t i = 0; i < 4; i++) { //1 for now
    TCASelect(i);
    while (! sensor.begin()) {
      Serial3.print("Failed to find sensor ");
      Serial3.println(i);
    }
    //has found the sensor if it gets here, and prints it
    Serial3.print("Sensor ");
    Serial3.print(i);
    Serial3.println(" found!");
  }
  
}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
}

void loop() {
  for (int i = 0; i < 4; i++) {  
    if (checkLIDAR(i) == true) {
        Serial.print(i);
        Serial.println(" ball found");
        MANAGER_PASS_ON(amib2, *LIDARTrig[i]);
    }
  }
}

void events::cycleBall(void) {
  amib2::events::cycleBall();
}

void events::cycleEntranceStop(void) {
  amib2::events::cycleEntranceStop();
}

void events::cycleExitStop(void) {
  amib2::events::cycleExitStop();
}

void events::lastBoat(void){
  amib2::events::lastBoat();
}

void events::entranceStopOn(void){
  amib2::events::entranceStopOn();
}

void events::entranceStopOff(void){
  amib2::events::entranceStopOff();
}

void events::test(void) {
  Serial.print("Checking sensor: ");
  Serial.println(boatNumber.value);
  Serial.print("LIDAR Value: ");
  Serial.println(checkLIDAR(boatNumber.value));
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

// now you have to implement the various events
}

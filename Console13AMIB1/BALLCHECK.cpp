//BALLCHECK AMIB1

#include "states.h"

#define BALL_PS_START 23
#define BALL_PS_SWISHYBOATS_START 8
#define NUM_SENSORS 4

bool prevSensorLocs[NUM_SENSORS];
bool currSensors[NUM_SENSORS];

namespace BALLCHECK { 
  void setup() {
    pinMode(BALL_PS_SWISHYBOATS_START, INPUT_PULLUP);
    pinMode(BALL_PS_START, INPUT_PULLUP);
  }
  
  void loop() {
    manager.updateFromSlave(2);
    manager.updateFromSlave(3);
  }
  
  //lets the tablet know the amibs are in the right state
  void enter() {
    tablet::events::amib1Ready();
  }
  
  void events::amib2Ready() {
    tablet::events::amib2Ready();
  }
  
  void events::amib3Ready() {
    tablet::events::amib3Ready();
  }
  
  void events::amib2NotReady() {
    tablet::events::amib2NotReady();
  }
  
  void events::amib3NotReady() {
    tablet::events::amib3NotReady();
  }
 
  
  void exit() {
    tablet::events::amib1NotReady();
    manager.updateFromSlave(2);
    manager.updateFromSlave(3);
  }
  
  void updateSensors() {
    amib3::events::checkSensors();
    amib2::events::checkSensors();
    delay(20);
    manager.updateFromSlave(2);
    manager.updateFromSlave(3);
    delay(20);

    if(!digitalRead(BALL_PS_START))
      ballSense1.value = true;
    else
      ballSense1.value = false;
    
    if(!digitalRead(BALL_PS_SWISHYBOATS_START))
      ballSense2.value = true;
    else
      ballSense2.value = false;
    

    //Updating current sensor values
    currSensors[0] = ballSense1.value;
    currSensors[1] = ballSense2.value;
    currSensors[2] = ballSense3.value;
    currSensors[3] = ballSense4.value;
  }
  
  void events::checkSensors() { 
    
    updateSensors();
    
    //Your .comm file needs these values in the tablet section
    manager.updateValue(tablet::ballSense1, ballSense1.value);
    manager.updateValue(tablet::ballSense2, ballSense2.value);
    manager.updateValue(tablet::ballSense3, ballSense3.value);
    manager.updateValue(tablet::ballSense4, ballSense4.value);
    
    //Set the previous sensor values
    prevSensorLocs[0] = ballSense1.value;
    prevSensorLocs[1] = ballSense2.value;
    prevSensorLocs[2] = ballSense3.value;
    prevSensorLocs[3] = ballSense4.value;
    
    tablet::events::checkBallDone();
  }
  
  void events::waitForBall() {
    bool checkLoop = true;
    unsigned long thisStartTime = millis();
    unsigned long thisElapsedTime = 0;
    unsigned long thisTimeout = 60000;

    //Check for the ball to move and reach a new sensor
    while(thisElapsedTime < thisTimeout && checkLoop) {
      for(int i = 0; i < NUM_SENSORS; i++) {
        if(currSensors[i] != prevSensorLocs[i] && currSensors[i] == true) 
          checkLoop = false;
      }
      updateSensors();  
      thisElapsedTime = millis() - thisStartTime;
    }
    
    manager.updateValue(tablet::ballSense1, ballSense1.value);
    manager.updateValue(tablet::ballSense2, ballSense2.value);
    manager.updateValue(tablet::ballSense3, ballSense3.value);
    manager.updateValue(tablet::ballSense4, ballSense4.value);
    
    tablet::events::resume();
  }
}
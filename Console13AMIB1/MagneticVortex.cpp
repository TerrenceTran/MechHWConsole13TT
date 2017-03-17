//MagneticVortex.cpp (MASTER)
//

#include <FlexyStepper.h>
#include <Encoder.h>
#include <I2CpwmController.h>

#include "states.h"

extern I2CpwmController pwm;

namespace MAGNETICVORTEX {

//declaring a value that can change the speed of the vortex
  const byte MAGNETIC_VORTEX_DC = 3;

//sets the limits of the speed of the vortex (gets crazy above 50)  
  const float MIN_SPEED = 20;
  const float MAX_SPEED = 50;

//declares the sensor in the lifter at the beginning  
  const byte START_SENSOR_PIN  = 23;  //23


void setup() {

//sets the pins for the value that changes the speed and the sensor in the lifter
  pinMode(MAGNETIC_VORTEX_DC, OUTPUT);
  pinMode(START_SENSOR_PIN, INPUT_PULLUP);

}

void enter() {
  // called when state is entered
  // nothing to see here
}

void loop() {

//constantly checks and changes the speed of the vortex depending on the value  
  if (dialPosition.changed) {
    analogWrite(MAGNETIC_VORTEX_DC, (byte) dialPosition.value);
    dialPosition.changed = false;
  }
}

//unused event now
void events::pistonStop() {
  amib3::events::pistonStop();
}

//cycleBall event in amib3, which lowers and raises the piston
void events::cycleBall() {
  amib3::events::cycleBall();
}

//demos the vortex
void events::demo() {
    //If the speed changes...
  if (DCMotorSpeed.changed) {
    
    //If the speed is greater than the max, it will be set to the max
    if (DCMotorSpeed.value > MAX_SPEED){
      DCMotorSpeed.value = MAX_SPEED;
    }
    
    //If the speed is smaller than the min, it will be set to the min - unless it's 0
    if (DCMotorSpeed.value < MIN_SPEED && DCMotorSpeed.value != 0){
      DCMotorSpeed.value = MIN_SPEED;
    }
    
    analogWrite(MAGNETIC_VORTEX_DC, DCMotorSpeed.value); //bounds of 20-50-ish
    DCMotorSpeed.changed = false;
  }
  
  analogWrite(MAGNETIC_VORTEX_DC, 30);
  delay(5000);
  analogWrite(MAGNETIC_VORTEX_DC, 0);
}

//reads the sensor in the beginning lifter
void events::startSensor(){
  while(digitalRead(START_SENSOR_PIN)) {
    events::lowPiston();
  }
 events::highPiston();
 //delay(1000);
 //events::lowPiston();
 //delay(1000);
}

//lowers the piston from amib3
void events::lowPiston() {
  amib3::events::lowPiston();
}

//raises the piston from amib3
void events::highPiston() {
  amib3::events::highPiston();
}

//once it leaves the state
void exit() {
  analogWrite(MAGNETIC_VORTEX_DC, 0);
}


}

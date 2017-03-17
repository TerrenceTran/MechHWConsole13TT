#include "states.h"
#include <FlexyStepper.h>

namespace BERNOULLIFAN {


//What's this?
//Do we need all of these pins and things? Seems like we have more than we actually use
/*
Turntable Stepper	m		Port 1
Fan Stepper	m		Port 2
Fan Motor PWM	n		D8
Fan Motor Relay	n		A6
BBS 1 Emitter	m		D23
BBS 1 Detector	m		D24
BBS 2 Emitter	m		D25
BBS 2 Detector	m		D26
BBS 3 Emitter	m		D27
BBS 3 Dectector	m		D28
Fan Homing Position Sensor	m		D29
Turntable Homing Position Sensor	m		A0
*/

const int TURNTABLE_STEPPER_PORT = 1;
const int FAN_STEPPER_PORT = 2;
const int FAN_MOTOR_PWM_PORT = 8;
const int FAN_MOTOR_RELAY_PORT = -1; //??? not sure
const int BBS_EMITTER_1 = 23;
const int BBS_DETECTOR_1 = 24;
const int BBS_EMITTER_2 = 25;
const int BBS_DETECTOR_2 = 26;
const int BBS_EMITTER_3 = 27;
const int BBS_DETECTOR_3 = 28;
const int FAN_HOME_PORT = 29;
const int TURNTABLE_HOME_PORT = 54;

//Need to declare: FAN_PWM_POWER, FAN_PWM, BERNOULLIFAN_LIFT_P

void setup() {
  Serial.begin(9600);
  pinMode(BBS_EMITTER_1 , OUTPUT);
  pinMode(BBS_DETECTOR_1, INPUT_PULLUP);
  pinMode(BBS_EMITTER_2 , OUTPUT);
  pinMode(BBS_DETECTOR_2, INPUT_PULLUP);
  pinMode(BBS_EMITTER_3 , OUTPUT);
  pinMode(BBS_DETECTOR_3, INPUT_PULLUP);
}

void enter() {

}

void loop() {
  /*while(true)
  {
    fanStepper.moveRelativeInRevolutions(.25);
    digitalWrite(fanData, HIGH);
    fanStepper.moveRelativeInRevolutions(.2);
    delay(2000);
    fanStepper.moveRelativeInRevolutions(-.4);
    delay(2000);
    fanStepper.moveRelativeInRevolutions(.2);
    delay(2000);
    digitalWrite(fanData, LOW);
    delay(2000);
  }*/
	/*
	if(tableAngle.changed) {
		tableStepper.setTargetPositionInRevolutions(tableAngle.value/360.0);
		tableAngle.changed = false;
	}
	if(fanAngle.changed) {
		//fanStepper.setTargetPositionInRevolutions(fanAngle.value/360.0);
		fanAngle.changed = false;
	} */

  //Serial.println(!digitalRead(FAN_HOMING_PS));

	//tableStepper.processMovement();
	//fanStepper.processMovement();
}

void events::homeFan(void) {
  //fanStepper.enableStepper();
  //fanStepper.moveToHomeInRevolutions(1, 0.025, 0.1, FAN_HOMING_PS);
	//fanStepper.setCurrentPositionInRevolutions(0.0);
}

void events::demo(void) {
  //events::liftBall(); //ANNA FOR UPLOAD
  //delay(1000);  //ANNA FOR UPLOAD

	//turn on fan
  //fanStepper.enableStepper();
  //fanStepper.moveToPositionInRevolutions(0.225);
  delay(1000);

	//digitalWrite(FAN_PWM_POWER, HIGH); //ANNA FOR UPLOAD
	//analogWrite(FAN_PWM, 255); //ANNA FOR UPLOAD
	//delay(5000); //ANNA FOR UPLOAD

	/*tableAngle.value = 60;
	delay(5000);*/

	//fanStepper.moveToPositionInRevolutions(0.05);
	delay(4000);
	//fanStepper.moveToPositionInRevolutions(0.325);
	delay(2000);
	//fanStepper.moveToPositionInRevolutions(0.45);
  delay(2000);
  //fanStepper.moveToPositionInRevolutions(0.225);
  delay(3000);

  //digitalWrite(FAN_PWM_POWER, LOW); //ANNA FOR UPLOAD
  //analogWrite(FAN_PWM, 0); //ANNA FOR UPLOAD
}

void events::liftBall() {
  //digitalWrite(BERNOULLIFAN_LIFT_P, LOW); //ANNA FOR UPLOAD
  //delay(1500); //ANNA FOR UPLOAD
  //digitalWrite(BERNOULLIFAN_LIFT_P, HIGH); //ANNA FOR UPLOAD
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
  //fanStepper.moveToPositionInRevolutions(0.0);
  //fanStepper.disableStepper();
  //digitalWrite(FAN_PWM, LOW); //ANNA FOR UPLOAD
  //digitalWrite(FAN_PWM_POWER, LOW); //ANNA FOR UPLOAD
}

}

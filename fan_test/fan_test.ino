#include <FlexyStepper.h>

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

FlexyStepper turntableStepper;
FlexyStepper fanStepper;

const int TURNTABLE_STEPPER_PORT = 1;
const int TURNTABLE_STEPS_PER_REV = 400*4; // 1/2 microstepping * 200 steps per rev * 4 revs per big revs
const float TURNTABLE_SPEED_REVOLUTIONS = .25;
const float TURNTABLE_ACCEL_REVOLUTIONS = 5; //idk, fast
const float TURNTABLE_HOMING_SPEED = 0.10;
const int TURNTABLE_HOME_PORT = 29;

const int FAN_STEPPER_PORT = 2;
const int FAN_STEPS_PER_REV = 400; // 1/2 microstepping
const float FAN_FULL_MOVEMENT = 7/16.0; //Full movement is 9/16 revolutions
const float FAN_SPEED_REVOLUTIONS = 0.4; // I'm not sure why, but this isn't accurate. This is a full rotation in much less than 100 seconds
const float FAN_ACCEL_REVOLUTIONS = 1; // Relatively fast acceleration.
const float FAN_HOMING_SPEED = 0.2;
const int FAN_HOME_PORT = 54;

const int FAN_MOTOR_PWM_PORT = 8;
const int FAN_MOTOR_RELAY_PORT = -1; //??? not sure
const int BBS_EMITTER_1 = 23;
const int BBS_DETECTOR_1 = 24;
const int BBS_EMITTER_2 = 25;
const int BBS_DETECTOR_2 = 26;
const int BBS_EMITTER_3 = 27;
const int BBS_DETECTOR_3 = 28;

bool triggered1 = false;
bool triggered2 = false;
bool triggered3 = false;
bool fantriggered = false;
bool turntabletriggered = false;

void setup() {
  Serial.begin(9600);
  pinMode(BBS_EMITTER_1 , OUTPUT);
  pinMode(BBS_DETECTOR_1, INPUT_PULLUP);
  pinMode(BBS_EMITTER_2 , OUTPUT);
  pinMode(BBS_DETECTOR_2, INPUT_PULLUP);
  pinMode(BBS_EMITTER_3 , OUTPUT);
  pinMode(BBS_DETECTOR_3, INPUT_PULLUP);

  pinMode(FAN_HOME_PORT, INPUT_PULLUP);
  pinMode(TURNTABLE_HOME_PORT, INPUT_PULLUP);

  turntableStepper.connectToPort(TURNTABLE_STEPPER_PORT);
  turntableStepper.setStepsPerRevolution(TURNTABLE_STEPS_PER_REV);
  turntableStepper.setSpeedInRevolutionsPerSecond(TURNTABLE_SPEED_REVOLUTIONS);
  turntableStepper.setAccelerationInRevolutionsPerSecondPerSecond(TURNTABLE_ACCEL_REVOLUTIONS);

  turntableStepper.moveToHomeInRevolutions(1, TURNTABLE_HOMING_SPEED, .5, TURNTABLE_HOME_PORT); // Try to go the closest way
  turntableStepper.moveToHomeInRevolutions(-1, TURNTABLE_HOMING_SPEED, 1, TURNTABLE_HOME_PORT);
  turntableStepper.setCurrentPositionInRevolutions(0.0);
  
  fanStepper.connectToPort(FAN_STEPPER_PORT);
  fanStepper.setStepsPerRevolution(FAN_STEPS_PER_REV);
  fanStepper.setSpeedInRevolutionsPerSecond(FAN_SPEED_REVOLUTIONS);
  fanStepper.setAccelerationInRevolutionsPerSecondPerSecond(FAN_ACCEL_REVOLUTIONS);

  fanStepper.moveToHomeInRevolutions(-1, FAN_HOMING_SPEED, FAN_FULL_MOVEMENT, FAN_HOME_PORT);
  fanStepper.setCurrentPositionInRevolutions(0.0);
  
  fanStepper.moveToPositionInRevolutions(FAN_FULL_MOVEMENT/2.0);
  turntableStepper.moveToPositionInRevolutions(.25);
  
  turntableStepper.disableStepper();
  fanStepper.disableStepper();
}

void loop() {
  if(!digitalRead(BBS_DETECTOR_1) != triggered1)
  {
    Serial.print("Detector 1 is ");
    Serial.println(!digitalRead(BBS_DETECTOR_1));
    triggered1 = !triggered1;
  }
  if(!digitalRead(BBS_DETECTOR_2) != triggered2)
  {
    Serial.print("Detector 2 is ");
    Serial.println(!digitalRead(BBS_DETECTOR_2));
    triggered2 = !triggered2;
  }
  if(!digitalRead(BBS_DETECTOR_3) != triggered3)
  {
    Serial.print("Detector 3 is ");
    Serial.println(!digitalRead(BBS_DETECTOR_3));
    triggered3 = !triggered3;
  }
  if(!digitalRead(FAN_HOME_PORT) != fantriggered)
  {
    Serial.print("Fan Home is ");
    Serial.println(!digitalRead(FAN_HOME_PORT));
    fantriggered = !fantriggered;
  }
  if(!digitalRead(TURNTABLE_HOME_PORT) != turntabletriggered)
  {
    Serial.print("Turntable home is ");
    Serial.println(!digitalRead(TURNTABLE_HOME_PORT));
    turntabletriggered = !turntabletriggered;
  }
  //turntableStepper.moveToPositionInRevolutions(0.25);
  //fanStepper.moveToPositionInRevolutions(0);
}

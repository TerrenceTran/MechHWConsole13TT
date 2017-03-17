#include "states.h"

static const StateInfo state_infos[10] = {
  {IDLE::setup, IDLE::enter, IDLE::exit, IDLE::loop, IDLE::event},
  {BERNOULLIFAN::setup, BERNOULLIFAN::enter, BERNOULLIFAN::exit, BERNOULLIFAN::loop, BERNOULLIFAN::event},
  {FISHYTANK::setup, FISHYTANK::enter, FISHYTANK::exit, FISHYTANK::loop, FISHYTANK::event},
  {MAGNETICVORTEX::setup, MAGNETICVORTEX::enter, MAGNETICVORTEX::exit, MAGNETICVORTEX::loop, MAGNETICVORTEX::event},
  {SPINNYLIFTER::setup, SPINNYLIFTER::enter, SPINNYLIFTER::exit, SPINNYLIFTER::loop, SPINNYLIFTER::event},
  {SPINNYLIFTER2::setup, SPINNYLIFTER2::enter, SPINNYLIFTER2::exit, SPINNYLIFTER2::loop, SPINNYLIFTER2::event},
  {SPINNYPASSIVEDROP::setup, SPINNYPASSIVEDROP::enter, SPINNYPASSIVEDROP::exit, SPINNYPASSIVEDROP::loop, SPINNYPASSIVEDROP::event},
  {SWISHYBOATS::setup, SWISHYBOATS::enter, SWISHYBOATS::exit, SWISHYBOATS::loop, SWISHYBOATS::event},
  {BALLCHECK::setup, BALLCHECK::enter, BALLCHECK::exit, BALLCHECK::loop, BALLCHECK::event},
  {OFF::setup, OFF::enter, OFF::exit, OFF::loop, OFF::event}
};

static const WireValue wire_values[19] = {
  {1, 0, sizeof(uint16_t), (Value<void*>*) &BERNOULLIFAN::tableAngle},
  {1, 1, sizeof(uint16_t), (Value<void*>*) &BERNOULLIFAN::fanAngle},
  {2, 0, sizeof(uint16_t), (Value<void*>*) &FISHYTANK::fishyMotorSpeed},
  {3, 0, sizeof(uint16_t), (Value<void*>*) &MAGNETICVORTEX::motorSpeed},
  {3, 1, sizeof(uint16_t), (Value<void*>*) &MAGNETICVORTEX::motorDir},
  {3, 2, sizeof(uint16_t), (Value<void*>*) &MAGNETICVORTEX::DCMotorSpeed},
  {3, 3, sizeof(uint8_t), (Value<void*>*) &MAGNETICVORTEX::dialPosition},
  {4, 0, sizeof(int16_t), (Value<void*>*) &SPINNYLIFTER::spinnyOffset1},
  {4, 1, sizeof(uint16_t), (Value<void*>*) &SPINNYLIFTER::topSensor},
  {5, 0, sizeof(uint16_t), (Value<void*>*) &SPINNYLIFTER2::spinnyOffset1},
  {7, 0, sizeof(bool), (Value<void*>*) &SWISHYBOATS::LIDAR1Trig},
  {7, 1, sizeof(bool), (Value<void*>*) &SWISHYBOATS::LIDAR2Trig},
  {7, 2, sizeof(bool), (Value<void*>*) &SWISHYBOATS::LIDAR3Trig},
  {7, 3, sizeof(bool), (Value<void*>*) &SWISHYBOATS::LIDAR4Trig},
  {7, 4, sizeof(uint16_t), (Value<void*>*) &SWISHYBOATS::boatNumber},
  {8, 0, sizeof(bool), (Value<void*>*) &BALLCHECK::ballSense1},
  {8, 1, sizeof(bool), (Value<void*>*) &BALLCHECK::ballSense2},
  {8, 2, sizeof(bool), (Value<void*>*) &BALLCHECK::ballSense3},
  {8, 3, sizeof(bool), (Value<void*>*) &BALLCHECK::ballSense4}
};

MasterManager<State, 10, 19> manager(0x3c618075, state_infos, wire_values, 3);

namespace IDLE {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}


}
namespace BERNOULLIFAN {
Value<uint16_t> tableAngle;
Value<uint16_t> fanAngle;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::demo();
    break;
  case 1:
    events::homeFan();
    break;
  case 2:
    events::liftBall();
    break;
  default:
    break;
  }
}

namespace amib3 {
RemoteValue<3, uint16_t> tableAngle(0);
RemoteValue<3, uint16_t> fanAngle(1);
namespace events {
void demo() { manager.sendSlaveEvent(3, 0); }
void homeFan() { manager.sendSlaveEvent(3, 1); }
void liftBall() { manager.sendSlaveEvent(3, 2); }
}
}
}
namespace FISHYTANK {
Value<uint16_t> fishyMotorSpeed;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::spinTank();
    break;
  default:
    break;
  }
}


}
namespace MAGNETICVORTEX {
Value<uint16_t> motorSpeed;
Value<uint16_t> motorDir;
Value<uint16_t> DCMotorSpeed;
Value<uint8_t> dialPosition;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::pistonStop();
    break;
  case 1:
    events::demo();
    break;
  case 2:
    events::cycleBall();
    break;
  case 3:
    events::startSensor();
    break;
  case 4:
    events::lowPiston();
    break;
  case 5:
    events::highPiston();
    break;
  default:
    break;
  }
}

namespace amib2 {

namespace events {

}
}
namespace amib3 {

namespace events {
void pistonStop() { manager.sendSlaveEvent(3, 0); }
void cycleBall() { manager.sendSlaveEvent(3, 1); }
void startSensor() { manager.sendSlaveEvent(3, 2); }
void lowPiston() { manager.sendSlaveEvent(3, 3); }
void highPiston() { manager.sendSlaveEvent(3, 4); }
}
}
}
namespace SPINNYLIFTER {
Value<int16_t> spinnyOffset1;
Value<uint16_t> topSensor;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::demo();
    break;
  case 1:
    events::cycleBall();
    break;
  case 2:
    events::liftBall();
    break;
  default:
    break;
  }
}

namespace amib2 {
RemoteValue<2, uint16_t> topSensor(0);
namespace events {
void liftBall() { manager.sendSlaveEvent(2, 0); }
}
}
}
namespace SPINNYLIFTER2 {
Value<uint16_t> spinnyOffset1;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::demo();
    break;
  case 1:
    events::cycleBall();
    break;
  case 2:
    events::cycleEntranceStop();
    break;
  case 3:
    events::cycleExitStop();
    break;
  case 4:
    events::stopMovement();
    break;
  default:
    break;
  }
}

namespace amib2 {

namespace events {
void cycleEntranceStop() { manager.sendSlaveEvent(2, 0); }
}
}
namespace amib3 {
RemoteValue<3, uint16_t> spinnyOffset1(0);
namespace events {
void demo() { manager.sendSlaveEvent(3, 0); }
void cycleBall() { manager.sendSlaveEvent(3, 1); }
void cycleExitStop() { manager.sendSlaveEvent(3, 2); }
void stopMovement() { manager.sendSlaveEvent(3, 3); }
}
}
}
namespace SPINNYPASSIVEDROP {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}


}
namespace SWISHYBOATS {
Value<bool> LIDAR1Trig;
Value<bool> LIDAR2Trig;
Value<bool> LIDAR3Trig;
Value<bool> LIDAR4Trig;
Value<uint16_t> boatNumber;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::cycleEntranceStop();
    break;
  case 1:
    events::cycleExitStop();
    break;
  case 2:
    events::cycleBall();
    break;
  case 3:
    events::lastBoat();
    break;
  case 4:
    events::entranceStopOn();
    break;
  case 5:
    events::entranceStopOff();
    break;
  case 6:
    events::test();
    break;
  default:
    break;
  }
}

namespace amib2 {
RemoteValue<2, bool> LIDAR1Trig(0);
RemoteValue<2, bool> LIDAR2Trig(1);
RemoteValue<2, bool> LIDAR3Trig(2);
RemoteValue<2, bool> LIDAR4Trig(3);
namespace events {
void cycleEntranceStop() { manager.sendSlaveEvent(2, 0); }
void cycleExitStop() { manager.sendSlaveEvent(2, 1); }
void cycleBall() { manager.sendSlaveEvent(2, 2); }
void lastBoat() { manager.sendSlaveEvent(2, 3); }
void entranceStopOn() { manager.sendSlaveEvent(2, 4); }
void entranceStopOff() { manager.sendSlaveEvent(2, 5); }
void test() { manager.sendSlaveEvent(2, 6); }
}
}
}
namespace BALLCHECK {
Value<bool> ballSense1;
Value<bool> ballSense2;
Value<bool> ballSense3;
Value<bool> ballSense4;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::checkSensors();
    break;
  case 1:
    events::waitForBall();
    break;
  case 2:
    events::amib2Ready();
    break;
  case 3:
    events::amib3Ready();
    break;
  case 4:
    events::amib2NotReady();
    break;
  case 5:
    events::amib3NotReady();
    break;
  default:
    break;
  }
}

namespace tablet {
RemoteValue<0, bool> ballSense1(0);
RemoteValue<0, bool> ballSense2(1);
RemoteValue<0, bool> ballSense3(2);
RemoteValue<0, bool> ballSense4(3);
namespace events {
void resume() { manager.sendTabletEvent(0); }
void amib1Ready() { manager.sendTabletEvent(1); }
void amib2Ready() { manager.sendTabletEvent(2); }
void amib3Ready() { manager.sendTabletEvent(3); }
void amib1NotReady() { manager.sendTabletEvent(4); }
void amib2NotReady() { manager.sendTabletEvent(5); }
void amib3NotReady() { manager.sendTabletEvent(6); }
void checkBallDone() { manager.sendTabletEvent(7); }
}
}
namespace amib2 {
RemoteValue<2, bool> ballSense1(0);
RemoteValue<2, bool> ballSense2(1);
RemoteValue<2, bool> ballSense3(2);
RemoteValue<2, bool> ballSense4(3);
namespace events {
void checkSensors() { manager.sendSlaveEvent(2, 0); }
}
}
namespace amib3 {
RemoteValue<3, bool> ballSense1(0);
RemoteValue<3, bool> ballSense2(1);
RemoteValue<3, bool> ballSense3(2);
RemoteValue<3, bool> ballSense4(3);
namespace events {
void checkSensors() { manager.sendSlaveEvent(3, 0); }
}
}
}
namespace OFF {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}


}


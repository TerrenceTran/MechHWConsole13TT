#include <SerialSlave.h>
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

static const WireValue wire_values[9] = {
  {4, 0, sizeof(uint16_t), (Value<void*>*) &SPINNYLIFTER::topSensor},
  {7, 0, sizeof(bool), (Value<void*>*) &SWISHYBOATS::LIDAR1Trig},
  {7, 1, sizeof(bool), (Value<void*>*) &SWISHYBOATS::LIDAR2Trig},
  {7, 2, sizeof(bool), (Value<void*>*) &SWISHYBOATS::LIDAR3Trig},
  {7, 3, sizeof(bool), (Value<void*>*) &SWISHYBOATS::LIDAR4Trig},
  {8, 0, sizeof(bool), (Value<void*>*) &BALLCHECK::ballSense1},
  {8, 1, sizeof(bool), (Value<void*>*) &BALLCHECK::ballSense2},
  {8, 2, sizeof(bool), (Value<void*>*) &BALLCHECK::ballSense3},
  {8, 3, sizeof(bool), (Value<void*>*) &BALLCHECK::ballSense4}
};

SlaveManager<State, 10, 9> manager(2, state_infos, wire_values);

namespace IDLE {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}

namespace master {


namespace events {

}
}
}
namespace BERNOULLIFAN {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}

namespace master {
RemoteValue<0, uint16_t> tableAngle(0);
RemoteValue<0, uint16_t> fanAngle(1);

namespace events {
void demo() { manager.sendEvent(0); }
void homeFan() { manager.sendEvent(1); }
void liftBall() { manager.sendEvent(2); }
}
}
}
namespace FISHYTANK {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}

namespace master {
RemoteValue<0, uint16_t> fishyMotorSpeed(0);

namespace events {
void spinTank() { manager.sendEvent(0); }
}
}
}
namespace MAGNETICVORTEX {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}

namespace master {
RemoteValue<0, uint16_t> motorSpeed(0);
RemoteValue<0, uint16_t> motorDir(1);
RemoteValue<0, uint16_t> DCMotorSpeed(2);
RemoteValue<0, uint8_t> dialPosition(3);

namespace events {
void pistonStop() { manager.sendEvent(0); }
void demo() { manager.sendEvent(1); }
void cycleBall() { manager.sendEvent(2); }
void startSensor() { manager.sendEvent(3); }
void lowPiston() { manager.sendEvent(4); }
void highPiston() { manager.sendEvent(5); }
}
}
}
namespace SPINNYLIFTER {
Value<uint16_t> topSensor;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::liftBall();
    break;
  default:
    break;
  }
}

namespace master {
RemoteValue<0, int16_t> spinnyOffset1(0);
RemoteValue<0, uint16_t> topSensor(1);

namespace events {
void demo() { manager.sendEvent(0); }
void cycleBall() { manager.sendEvent(1); }
void liftBall() { manager.sendEvent(2); }
}
}
}
namespace SPINNYLIFTER2 {


void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::cycleEntranceStop();
    break;
  default:
    break;
  }
}

namespace master {
RemoteValue<0, uint16_t> spinnyOffset1(0);

namespace events {
void demo() { manager.sendEvent(0); }
void cycleBall() { manager.sendEvent(1); }
void cycleEntranceStop() { manager.sendEvent(2); }
void cycleExitStop() { manager.sendEvent(3); }
void stopMovement() { manager.sendEvent(4); }
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

namespace master {


namespace events {

}
}
}
namespace SWISHYBOATS {
Value<bool> LIDAR1Trig;
Value<bool> LIDAR2Trig;
Value<bool> LIDAR3Trig;
Value<bool> LIDAR4Trig;

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

namespace master {
RemoteValue<0, bool> LIDAR1Trig(0);
RemoteValue<0, bool> LIDAR2Trig(1);
RemoteValue<0, bool> LIDAR3Trig(2);
RemoteValue<0, bool> LIDAR4Trig(3);
RemoteValue<0, uint16_t> boatNumber(4);

namespace events {
void cycleEntranceStop() { manager.sendEvent(0); }
void cycleExitStop() { manager.sendEvent(1); }
void cycleBall() { manager.sendEvent(2); }
void lastBoat() { manager.sendEvent(3); }
void entranceStopOn() { manager.sendEvent(4); }
void entranceStopOff() { manager.sendEvent(5); }
void test() { manager.sendEvent(6); }
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
  default:
    break;
  }
}

namespace master {
RemoteValue<0, bool> ballSense1(0);
RemoteValue<0, bool> ballSense2(1);
RemoteValue<0, bool> ballSense3(2);
RemoteValue<0, bool> ballSense4(3);

namespace events {
void checkSensors() { manager.sendEvent(0); }
void waitForBall() { manager.sendEvent(1); }
void amib2Ready() { manager.sendEvent(2); }
void amib3Ready() { manager.sendEvent(3); }
void amib2NotReady() { manager.sendEvent(4); }
void amib3NotReady() { manager.sendEvent(5); }
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

namespace master {


namespace events {

}
}
}


SLAVERECV

#pragma once

#define SLAVEMANAGER
#include <Manager.h>

namespace IDLE {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {


namespace events {

}
}
}

namespace BERNOULLIFAN {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {
extern RemoteValue<0, uint16_t> tableAngle;
extern RemoteValue<0, uint16_t> fanAngle;

namespace events {
void demo();
void homeFan();
void liftBall();
}
}
}

namespace FISHYTANK {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {
extern RemoteValue<0, uint16_t> fishyMotorSpeed;

namespace events {
void spinTank();
}
}
}

namespace MAGNETICVORTEX {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {
extern RemoteValue<0, uint16_t> motorSpeed;
extern RemoteValue<0, uint16_t> motorDir;
extern RemoteValue<0, uint16_t> DCMotorSpeed;
extern RemoteValue<0, uint8_t> dialPosition;

namespace events {
void pistonStop();
void demo();
void cycleBall();
void startSensor();
void lowPiston();
void highPiston();
}
}
}

namespace SPINNYLIFTER {
extern Value<uint16_t> topSensor;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {
void liftBall();
}

namespace master {
extern RemoteValue<0, int16_t> spinnyOffset1;
extern RemoteValue<0, uint16_t> topSensor;

namespace events {
void demo();
void cycleBall();
void liftBall();
}
}
}

namespace SPINNYLIFTER2 {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {
void cycleEntranceStop();
}

namespace master {
extern RemoteValue<0, uint16_t> spinnyOffset1;

namespace events {
void demo();
void cycleBall();
void cycleEntranceStop();
void cycleExitStop();
void stopMovement();
}
}
}

namespace SPINNYPASSIVEDROP {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {


namespace events {

}
}
}

namespace SWISHYBOATS {
extern Value<bool> LIDAR1Trig;
extern Value<bool> LIDAR2Trig;
extern Value<bool> LIDAR3Trig;
extern Value<bool> LIDAR4Trig;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {
void cycleEntranceStop();
void cycleExitStop();
void cycleBall();
void lastBoat();
void entranceStopOn();
void entranceStopOff();
void test();
}

namespace master {
extern RemoteValue<0, bool> LIDAR1Trig;
extern RemoteValue<0, bool> LIDAR2Trig;
extern RemoteValue<0, bool> LIDAR3Trig;
extern RemoteValue<0, bool> LIDAR4Trig;
extern RemoteValue<0, uint16_t> boatNumber;

namespace events {
void cycleEntranceStop();
void cycleExitStop();
void cycleBall();
void lastBoat();
void entranceStopOn();
void entranceStopOff();
void test();
}
}
}

namespace BALLCHECK {
extern Value<bool> ballSense1;
extern Value<bool> ballSense2;
extern Value<bool> ballSense3;
extern Value<bool> ballSense4;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {
void checkSensors();
}

namespace master {
extern RemoteValue<0, bool> ballSense1;
extern RemoteValue<0, bool> ballSense2;
extern RemoteValue<0, bool> ballSense3;
extern RemoteValue<0, bool> ballSense4;

namespace events {
void checkSensors();
void waitForBall();
void amib2Ready();
void amib3Ready();
void amib2NotReady();
void amib3NotReady();
}
}
}

namespace OFF {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {


namespace events {

}
}
}



enum State {
  STATE_IDLE,
  STATE_BERNOULLIFAN,
  STATE_FISHYTANK,
  STATE_MAGNETICVORTEX,
  STATE_SPINNYLIFTER,
  STATE_SPINNYLIFTER2,
  STATE_SPINNYPASSIVEDROP,
  STATE_SWISHYBOATS,
  STATE_BALLCHECK,
  STATE_OFF
};

extern SlaveManager<State, 10, 9> manager;

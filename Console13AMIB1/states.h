#pragma once

#include <Manager.h>

namespace IDLE {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();



namespace events {

}
}

namespace BERNOULLIFAN {
extern Value<uint16_t> tableAngle;
extern Value<uint16_t> fanAngle;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib3 {
extern RemoteValue<3, uint16_t> tableAngle;
extern RemoteValue<3, uint16_t> fanAngle;
namespace events {
void demo();

void homeFan();

void liftBall();

}
}

namespace events {
void demo();
void homeFan();
void liftBall();
}
}

namespace FISHYTANK {
extern Value<uint16_t> fishyMotorSpeed;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();



namespace events {
void spinTank();
}
}

namespace MAGNETICVORTEX {
extern Value<uint16_t> motorSpeed;
extern Value<uint16_t> motorDir;
extern Value<uint16_t> DCMotorSpeed;
extern Value<uint8_t> dialPosition;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib2 {

namespace events {

}
}
namespace amib3 {

namespace events {
void pistonStop();

void cycleBall();

void startSensor();

void lowPiston();

void highPiston();

}
}

namespace events {
void pistonStop();
void demo();
void cycleBall();
void startSensor();
void lowPiston();
void highPiston();
}
}

namespace SPINNYLIFTER {
extern Value<int16_t> spinnyOffset1;
extern Value<uint16_t> topSensor;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib2 {
extern RemoteValue<2, uint16_t> topSensor;
namespace events {
void liftBall();

}
}

namespace events {
void demo();
void cycleBall();
void liftBall();
}
}

namespace SPINNYLIFTER2 {
extern Value<uint16_t> spinnyOffset1;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib2 {

namespace events {
void cycleEntranceStop();

}
}
namespace amib3 {
extern RemoteValue<3, uint16_t> spinnyOffset1;
namespace events {
void demo();

void cycleBall();

void cycleExitStop();

void stopMovement();

}
}

namespace events {
void demo();
void cycleBall();
void cycleEntranceStop();
void cycleExitStop();
void stopMovement();
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
}

namespace SWISHYBOATS {
extern Value<bool> LIDAR1Trig;
extern Value<bool> LIDAR2Trig;
extern Value<bool> LIDAR3Trig;
extern Value<bool> LIDAR4Trig;
extern Value<uint16_t> boatNumber;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib2 {
extern RemoteValue<2, bool> LIDAR1Trig;
extern RemoteValue<2, bool> LIDAR2Trig;
extern RemoteValue<2, bool> LIDAR3Trig;
extern RemoteValue<2, bool> LIDAR4Trig;
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

namespace tablet {
extern RemoteValue<0, bool> ballSense1;
extern RemoteValue<0, bool> ballSense2;
extern RemoteValue<0, bool> ballSense3;
extern RemoteValue<0, bool> ballSense4;
namespace events {
void resume();

void amib1Ready();

void amib2Ready();

void amib3Ready();

void amib1NotReady();

void amib2NotReady();

void amib3NotReady();

void checkBallDone();

}
}
namespace amib2 {
extern RemoteValue<2, bool> ballSense1;
extern RemoteValue<2, bool> ballSense2;
extern RemoteValue<2, bool> ballSense3;
extern RemoteValue<2, bool> ballSense4;
namespace events {
void checkSensors();

}
}
namespace amib3 {
extern RemoteValue<3, bool> ballSense1;
extern RemoteValue<3, bool> ballSense2;
extern RemoteValue<3, bool> ballSense3;
extern RemoteValue<3, bool> ballSense4;
namespace events {
void checkSensors();

}
}

namespace events {
void checkSensors();
void waitForBall();
void amib2Ready();
void amib3Ready();
void amib2NotReady();
void amib3NotReady();
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

extern MasterManager<State, 10, 19> manager;


#include <FlexyStepper.h>
#include <Encoder.h>

#include "states.h"
#include "common.h"


namespace OFF {

void setup() {
}

void enter() {
    turnOffLeds();
}


void exit() {
    turnOnLeds();
}
}

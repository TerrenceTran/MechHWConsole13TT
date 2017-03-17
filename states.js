
var IDLE = {
  id: 0,
  master: {
    values: {
      
    },
    events: {
      
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_IDLE = 0;
var BERNOULLIFAN = {
  id: 1,
  master: {
    values: {
      tableAngle: new HardwareValue(1, 0, Manager.TYPE_UINT16),
      fanAngle: new HardwareValue(1, 1, Manager.TYPE_UINT16)
    },
    events: {
      demo: function demo() { manager.sendEvent(0, 1); },
      homeFan: function homeFan() { manager.sendEvent(1, 1); },
      liftBall: function liftBall() { manager.sendEvent(2, 1); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_BERNOULLIFAN = 1;
var FISHYTANK = {
  id: 2,
  master: {
    values: {
      fishyMotorSpeed: new HardwareValue(2, 0, Manager.TYPE_UINT16)
    },
    events: {
      spinTank: function spinTank() { manager.sendEvent(0, 2); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_FISHYTANK = 2;
var MAGNETICVORTEX = {
  id: 3,
  master: {
    values: {
      motorSpeed: new HardwareValue(3, 0, Manager.TYPE_UINT16),
      motorDir: new HardwareValue(3, 1, Manager.TYPE_UINT16),
      DCMotorSpeed: new HardwareValue(3, 2, Manager.TYPE_UINT16),
      dialPosition: new HardwareValue(3, 3, Manager.TYPE_UINT8)
    },
    events: {
      pistonStop: function pistonStop() { manager.sendEvent(0, 3); },
      demo: function demo() { manager.sendEvent(1, 3); },
      cycleBall: function cycleBall() { manager.sendEvent(2, 3); },
      startSensor: function startSensor() { manager.sendEvent(3, 3); },
      lowPiston: function lowPiston() { manager.sendEvent(4, 3); },
      highPiston: function highPiston() { manager.sendEvent(5, 3); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_MAGNETICVORTEX = 3;
var SPINNYLIFTER = {
  id: 4,
  master: {
    values: {
      spinnyOffset1: new HardwareValue(4, 0, Manager.TYPE_INT16),
      topSensor: new HardwareValue(4, 1, Manager.TYPE_UINT16)
    },
    events: {
      demo: function demo() { manager.sendEvent(0, 4); },
      cycleBall: function cycleBall() { manager.sendEvent(1, 4); },
      liftBall: function liftBall() { manager.sendEvent(2, 4); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_SPINNYLIFTER = 4;
var SPINNYLIFTER2 = {
  id: 5,
  master: {
    values: {
      spinnyOffset1: new HardwareValue(5, 0, Manager.TYPE_UINT16)
    },
    events: {
      demo: function demo() { manager.sendEvent(0, 5); },
      cycleBall: function cycleBall() { manager.sendEvent(1, 5); },
      cycleEntranceStop: function cycleEntranceStop() { manager.sendEvent(2, 5); },
      cycleExitStop: function cycleExitStop() { manager.sendEvent(3, 5); },
      stopMovement: function stopMovement() { manager.sendEvent(4, 5); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_SPINNYLIFTER2 = 5;
var SPINNYPASSIVEDROP = {
  id: 6,
  master: {
    values: {
      
    },
    events: {
      
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_SPINNYPASSIVEDROP = 6;
var SWISHYBOATS = {
  id: 7,
  master: {
    values: {
      LIDAR1Trig: new HardwareValue(7, 0, Manager.TYPE_BOOL),
      LIDAR2Trig: new HardwareValue(7, 1, Manager.TYPE_BOOL),
      LIDAR3Trig: new HardwareValue(7, 2, Manager.TYPE_BOOL),
      LIDAR4Trig: new HardwareValue(7, 3, Manager.TYPE_BOOL),
      boatNumber: new HardwareValue(7, 4, Manager.TYPE_UINT16)
    },
    events: {
      cycleEntranceStop: function cycleEntranceStop() { manager.sendEvent(0, 7); },
      cycleExitStop: function cycleExitStop() { manager.sendEvent(1, 7); },
      cycleBall: function cycleBall() { manager.sendEvent(2, 7); },
      lastBoat: function lastBoat() { manager.sendEvent(3, 7); },
      entranceStopOn: function entranceStopOn() { manager.sendEvent(4, 7); },
      entranceStopOff: function entranceStopOff() { manager.sendEvent(5, 7); },
      test: function test() { manager.sendEvent(6, 7); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_SWISHYBOATS = 7;
var BALLCHECK = {
  id: 8,
  master: {
    values: {
      ballSense1: new HardwareValue(8, 0, Manager.TYPE_BOOL),
      ballSense2: new HardwareValue(8, 1, Manager.TYPE_BOOL),
      ballSense3: new HardwareValue(8, 2, Manager.TYPE_BOOL),
      ballSense4: new HardwareValue(8, 3, Manager.TYPE_BOOL)
    },
    events: {
      checkSensors: function checkSensors() { manager.sendEvent(0, 8); },
      waitForBall: function waitForBall() { manager.sendEvent(1, 8); },
      amib2Ready: function amib2Ready() { manager.sendEvent(2, 8); },
      amib3Ready: function amib3Ready() { manager.sendEvent(3, 8); },
      amib2NotReady: function amib2NotReady() { manager.sendEvent(4, 8); },
      amib3NotReady: function amib3NotReady() { manager.sendEvent(5, 8); }
    }
  },
  tablet: {
    values: {
      ballSense1: new LocalValue(0, Manager.TYPE_BOOL),
      ballSense2: new LocalValue(1, Manager.TYPE_BOOL),
      ballSense3: new LocalValue(2, Manager.TYPE_BOOL),
      ballSense4: new LocalValue(3, Manager.TYPE_BOOL)
    },
    events: {
      resume: new LocalEvent(8, 0),
      amib1Ready: new LocalEvent(8, 1),
      amib2Ready: new LocalEvent(8, 2),
      amib3Ready: new LocalEvent(8, 3),
      amib1NotReady: new LocalEvent(8, 4),
      amib2NotReady: new LocalEvent(8, 5),
      amib3NotReady: new LocalEvent(8, 6),
      checkBallDone: new LocalEvent(8, 7)
    }
  }
};
var STATE_BALLCHECK = 8;
var OFF = {
  id: 9,
  master: {
    values: {
      
    },
    events: {
      
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_OFF = 9;

var STATES = {
  IDLE: IDLE,
  BERNOULLIFAN: BERNOULLIFAN,
  FISHYTANK: FISHYTANK,
  MAGNETICVORTEX: MAGNETICVORTEX,
  SPINNYLIFTER: SPINNYLIFTER,
  SPINNYLIFTER2: SPINNYLIFTER2,
  SPINNYPASSIVEDROP: SPINNYPASSIVEDROP,
  SWISHYBOATS: SWISHYBOATS,
  BALLCHECK: BALLCHECK,
  OFF: OFF
};
var manager = new Manager([IDLE, BERNOULLIFAN, FISHYTANK, MAGNETICVORTEX, SPINNYLIFTER, SPINNYLIFTER2, SPINNYPASSIVEDROP, SWISHYBOATS, BALLCHECK, OFF]);

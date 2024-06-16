#pragma once

#include <Arduino.h>

namespace eufs::hardware {

  class MotorController {

    MotorController() = default;

    virtual void InitializeMotor() = 0;

    // For driving motor, this should be neutral or forward
    // FOr steering motor, this should be left or right
    // I'd assume I will have to use some enumeration here
    // but given virtual function does not allow you to do templates
    virtual void get_direction() = 0; 

    virtual void ControlMotorSpeed() = 0;
      
  }
}
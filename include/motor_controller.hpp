#pragma once

#include <Arduino.h>

namespace eufs::hardware::motor {

  class DC {

    public:
      DC() : direction_pin_1_(0), direction_pin_2_(0), enable_pin_(0) {};

      ~DC() = default;

      void InitializeMotor(uint8_t dir_pin_1, uint8_t dir_pin_2, uint8_t en_pin);

      void ControlMotorSpeed(uint8_t pwm_val);

      void ControlMotorDirection(uint8_t input_1, uint8_t input_2);

    private:
      uint8_t direction_pin_1_;
      uint8_t direction_pin_2_;
      uint8_t enable_pin_;
  };

};
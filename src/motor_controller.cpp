#include "../include/motor_controller.hpp"

namespace eufs::hardware::motor {

  void DC::InitializeMotor(uint8_t dir_pin_1, uint8_t dir_pin_2, uint8_t en_pin) {
    
    // TODO: Assert that the pins are reasonable (e.g. the pins actually exist)
    // If not, return false
    direction_pin_1_ = dir_pin_1;
    direction_pin_2_ = dir_pin_2;
    enable_pin_ = en_pin;

    Serial.println(direction_pin_1_);
    Serial.println(direction_pin_2_);
    Serial.println(enable_pin_);
    
    // Set the respective pins as OUTPUT
    pinMode(direction_pin_1_, OUTPUT);
    pinMode(direction_pin_2_, OUTPUT);
    pinMode(enable_pin_, OUTPUT);

  };

  void DC::ControlMotorSpeed(uint8_t pwm_val) {
    analogWrite(enable_pin_, pwm_val);
  }

  void DC::ControlMotorDirection(uint8_t input_1, uint8_t input_2) {
    digitalWrite(direction_pin_1_, input_1);
    digitalWrite(direction_pin_2_, input_2);
  }

}
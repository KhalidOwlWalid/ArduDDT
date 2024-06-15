#pragma once

#include "../can_message.hpp"

namespace eufs::can::message {

  class SteeringCanMessage : public CanMessage {
    public:
      explicit SteeringCanMessage(uint32_t can_id) :
        CanMessage(can_id, 2) {
          Serial.println("Steering Can Message of ID " + String(can_id) + " initialized!");
          
          // Clean up
          for (int i = 0; i < len_; i++) {
            data_[i] = 0;
          }

        };
      
      // We should always be expecting a buffer of size 8 bytes
      inline void ExtractDataFrame(const uint8_t (&received_data)[8]) override {
        
        // Only look for data of the size of our message
        for (int i = 0; i < len_; i++) {
          data_[i] = received_data[i];
        }

      };

      inline void ParseData() {

        // BO_ 1299 AI2VCU_Steer: 2 AI
        //   SG_ STEER_REQUEST : 0|16@1- (0.1,0) [-21|21] "deg" Vector__XXX
        cmd_steering_ = static_cast<double>((int16_t)(data_[1] << 8 | data_[0]) * 0.1);
        // Serial.println("Commanded Steering: " + String(cmd_steering_));

      };

      inline uint8_t CalculateNormalizedSteering() {
        double max_steering_angle = 15.0;
        double cmd_steering = this->cmd_steering_;

        if (cmd_steering_ > max_steering_angle) {
          cmd_steering = max_steering_angle;
        } else if (cmd_steering_ < -max_steering_angle) {
          cmd_steering = -max_steering_angle;
        }

        // If commanded steering is negative, then make it positive
        cmd_steering = cmd_steering < 0 ? -1.0 * cmd_steering : cmd_steering;

        double normalized_steering_angle;

        normalized_steering_angle = (cmd_steering / max_steering_angle) * 255;
        uint8_t  pwm_value = static_cast<uint8_t>(normalized_steering_angle);

        return pwm_value;

      };

      inline double get_command_steering() const {return cmd_steering_; };

      private:
        double cmd_steering_;

  };

};

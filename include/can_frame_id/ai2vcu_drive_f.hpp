#pragma once

#include "../can_message.hpp"

namespace eufs::can::message {

  class DriveCanMessage : public CanMessage {
    public:
      explicit DriveCanMessage(uint32_t can_id) :
        CanMessage(can_id, 4) {
          Serial.println("Drive Can Message of ID ");
          Serial.print(can_id);
          Serial.print(" Initialized!");
          
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
        // BO_ 1297 AI2VCU_Drive_F: 4 AI
        //   SG_ FRONT_AXLE_TRQ_REQUEST : 0|16@1+ (0.1,0) [0|195] "Nm" Vector__XXX
        //   SG_ FRONT_MOTOR_SPEED_MAX : 16|16@1+ (1,0) [0|4000] "rpm" Vector__XXX
        axle_torque_request_ = static_cast<double>((uint16_t)(data_[1] << 8 | data_[0]) * 0.1);
        front_motor_speed_max_ = (uint16_t)(data_[2] << 8 | data_[1]); 
        // Serial.println("Axle torque requested: " + String(axle_torque_request_));
        // Serial.println("Front Motor Speed Max: " + String(front_motor_speed_max_));

      };

      inline double get_axle_torque_req() {return axle_torque_request_;};

      inline uint8_t CalculateNormalizedAxleTorque() {

        uint8_t pwm_value;
        double normalized_axle_torque;
        double max_axle_torque = 60;

        if (axle_torque_request_ >= 60) {
          axle_torque_request_ = 60;
        }

        if (axle_torque_request_ < 10) {
          return 0;
        } else {
          // Normalized to PWM max output
          normalized_axle_torque = (axle_torque_request_ / max_axle_torque) * 255;
          pwm_value = static_cast<uint8_t>(normalized_axle_torque);
        }

        return pwm_value;

      };

      private:
        double axle_torque_request_;
        uint16_t front_motor_speed_max_ ;

  };

};

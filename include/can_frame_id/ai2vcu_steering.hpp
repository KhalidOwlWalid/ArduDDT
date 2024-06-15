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

        // Extract signed bit
        int sign = data_[1] && 0b1000000;

        cmd_steering_ = sign * cmd_steering_;
        Serial.println("Commanded Steering: " + String(cmd_steering_));

      };

      private:
        double cmd_steering_;

  };

};

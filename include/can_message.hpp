#pragma once

#include <Arduino.h>

namespace eufs::can::message {

  class CanMessage {

    public:

      explicit CanMessage(uint32_t can_id, uint8_t len) :
        can_id_(can_id), len_(len) {};

      virtual ~CanMessage() = default;

      virtual void ExtractDataFrame(const uint8_t (&received_data)[8]) = 0;

      inline void clear() {
          // Clean up
          for (int i = 0; i < len_; i++) {
            data_[i] = 0;
          }
      };

    protected:
      uint8_t len_;
      uint32_t can_id_;
      uint8_t data_[8];

  };

}; // namespace eufs::can::message

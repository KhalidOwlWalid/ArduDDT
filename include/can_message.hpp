#pragma once

#include <Arduino.h>

namespace eufs::can::message {

  class CanMessage {

    public:

      explicit CanMessage(uint32_t can_id, uint8_t len) :
        can_id_(can_id), len_(len) {};

      virtual void ExtractDataFrame() = 0;

    private:
      uint8_t len_;
      uint32_t can_id_;
      uint8_t data_[8];

  };

}; // namespace eufs::can::message

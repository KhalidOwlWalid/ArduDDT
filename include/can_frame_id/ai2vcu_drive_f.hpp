#pragma once

#include "../can_message.hpp"

namespace eufs::can::message {

  class DriveCanMessage : public CanMessage {
    public:
      explicit DriveCanMessage(uint32_t can_id) :
        CanMessage(can_id, 4) {};
      
      inline void ExtractDataFrame() override {};

      inline double GetTorqueCommand() {};

  };

};

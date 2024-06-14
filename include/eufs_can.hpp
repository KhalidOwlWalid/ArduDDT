#pragma once

#include <Arduino.h>
#include <can-serial.h>
#include <mcp_can.h>
#include <mcp2515_can_dfs.h>
#include <mcp2515_can.h>

#include "can_param.hpp"

namespace eufs::can {

  using namespace eufs::can::param;

  class CAN : public mcp2515_can {

    public:

      CAN() : mcp2515_can(spi_cs_pin_) {};

      void InitializeCanBus(unsigned long timeout_s, bool report_flag = false);

      void ReportCanBusStatus();

    private:
      const int can_int_pin_ = 2;
      const int max_data_size_ = 8;

};

}; // namespace eufs::can

#pragma once

#define CAN_2515
#define DIY_MORE

namespace eufs::can::param {

  // This parameter depends on which CAN Bus shield you have
  #ifdef DIY_MORE
    const int spi_cs_pin_ = 10;
  #else
    // Most CAN Bus shield (e.g. Seeedstudio uses 9)
    // You will need to refer to the datasheet
    const int spi_cs_pin_ = 9;
  #endif // DIY_MORE

  const int test = 2;

} // namespace eufs::can::param
